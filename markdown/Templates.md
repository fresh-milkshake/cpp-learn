
# Шаблоны

- [Шаблоны](#шаблоны)
    - [Основные принципы](#основные-принципы)
    - [Специализация шаблонов](#специализация-шаблонов)
    - [Пример](#пример)
  - [Ссылки](#ссылки)

### Основные принципы

Шаблоны позволяют создавать классы и функции, которые могут работать с разными типами данных.

Чтобы создать шаблон, нужно использовать ключевое слово `template`. Например:

```cpp
template <class T>
T max(T a, T b) {
    return a > b ? a : b;
}
```

В данном примере мы создали шаблон функции `max`, которая возвращает наибольший из двух элементов. В качестве типа `T` мы можем использовать любой тип данных. В данном случае мы используем его для создания переменных `a` и `b`. Чтобы использовать шаблон, нужно указать тип данных в угловых скобках при вызове функции. Например:

```cpp
int a = 1, b = 2;
cout << max<int>(a, b) << endl;
```

### Специализация шаблонов

Чтобы создать специализацию шаблона, нужно использовать `template<>`:

```cpp
template <>
const char* max<const char*>(const char* a, const char* b) {
    return strcmp(a, b) > 0 ? a : b;
}

int main() {
    cout << max<int>(1, 2) << endl;
    cout << max<const char*>("abc", "def") << endl;

    // output: 2
    //         def
}
```

В данном случае мы создали специализацию шаблона функции `max` для типа данных `const char*`. Теперь при вызове функции max с типом `const char*`, будет использоваться эта специализация, а не общая функция.

### Пример

Создадим шаблон класса для работы с массивами:

```cpp
template <class T>
class Array {
private:
    T* data;
    int size;
public:
    Array(int size) {
        this->size = size;
        data = new T[size];
    }

    ~Array() {
        delete[] data;
    }

    T& operator[](int index) {
        return data[index];
    }

    int getSize() {
        return size;
    }
};
```

Теперь мы можем создавать массивы разных типов:

```cpp
int main() {
    Array<int> a(10);
    for (int i = 0; i < a.getSize(); i++) {
        a[i] = i * 10;
    }

    for (int i = 0; i < a.getSize(); i++) {
        cout << a[i] << " ";
    }

    cout << endl;

    Array<double> b(5);
    for (int i = 0; i < b.getSize(); i++) {
        b[i] = i * 1.5;
    }

    for (int i = 0; i < b.getSize(); i++) {
        cout << b[i] << " ";
    }

    cout << endl;

    // output: 0 10 20 30 40 50 60 70 80 90
    //         0 1.5 3 4.5 6
}
```

## Ссылки
    
* [cppreference.com](https://en.cppreference.com/w/cpp/language/templates)
* [geekforgeeks.org](https://www.geeksforgeeks.org/templates-cpp/)
* [Microsoft Docs](https://learn.microsoft.com/ru-ru/cpp/cpp/templates-cpp)