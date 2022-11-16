
# Стандартная библиотека + STL

- [Стандартная библиотека + STL](#стандартная-библиотека--stl)
  - [Поток ввода/вывода](#поток-вводавывода)
    - [Пример работы с потоком вывода в терминал](#пример-работы-с-потоком-вывода-в-терминал)
  - [Дата/время](#датавремя)
    - [Пример работы с датой/временем](#пример-работы-с-датойвременем)
  - [Контейнеры](#контейнеры)
    - [vector](#vector)
    - [list](#list)
    - [deque](#deque)
    - [set](#set)
    - [map](#map)
    - [stack](#stack)
  - [Итераторы](#итераторы)
  - [Алгоритмы](#алгоритмы)

## Поток ввода/вывода

В языке C++ потоки ввода/вывода реализованы с помощью классов `istream` и `ostream`, которые являются базовыми классами для всех потоков ввода/вывода. Классы `istream` и `ostream` содержат в себе методы, которые позволяют считывать и записывать данные в потоки. Классы `istream` и `ostream` являются абстрактными классами, поэтому непосредственно создать объекты классов `istream` и `ostream` нельзя. Вместо этого используются классы-наследники, которые реализуют абстрактные методы базовых классов.

Классы-наследники `istream` и `ostream`:

  * `ifstream` - поток ввода из файла
  * `ofstream` - поток вывода в файл
  * `stringstream` - поток ввода/вывода из/в строку

### Пример работы с потоком вывода в терминал

Пример вывода в терминал:

```cpp
#include <iostream>
using namespace std;

int main() {
  cout << "Hello world!" << endl;
  return 0;
}
```

В примере выше используется объект `cout`, который является экземпляром класса `ostream`. Вызов метода `cout << "Hello world!" << endl;` эквивалентен вызову метода `cout.operator<<(operator<<(operator<<("Hello world!"), endl));` (см. [перегрузка операторов](/markdown/Data%20types.md#перегрузка-операторов)).

## Дата/время

В языке C++ для работы с датой/временем используется класс `chrono` из стандартной библиотеки. Для работы с датой/временем нужно подключить библиотеку `chrono`:

```cpp
#include <chrono>
```

Для работы с датой/временем используются следующие классы:

  * `chrono::system_clock` - класс, который предоставляет текущее время системы
  * `chrono::steady_clock` - класс, который предоставляет текущее время системы, которое не может быть изменено
  * `chrono::high_resolution_clock` - класс, который предоставляет текущее время системы с максимальной точностью

### Пример работы с датой/временем

Пример получения текущего времени:

```cpp
#include <chrono>
#include <iostream>
using namespace std;

int main() {
  chrono::system_clock::time_point now = chrono::system_clock::now();
  cout << "Current time: " << chrono::system_clock::to_time_t(now) << endl;
  return 0;
}
```

В примере выше используется объект `now`, который является экземпляром класса `chrono::system_clock::time_point`. Вызов метода `chrono::system_clock::to_time_t(now)` эквивалентен вызову метода `chrono::system_clock::to_time_t.operator()(now)` (см. [перегрузка операторов](/markdown/Functions.md#перегрузка-стандартных-операторов).

## Контейнеры

В языке C++ существует несколько типов контейнеров:

  * [vector](/markdown/Standard%20library%20+%20STL.md#vector)
  * [list](/markdown/Standard%20library%20+%20STL.md#list)
  * [deque](/markdown/Standard%20library%20+%20STL.md#deque)
  * [set](/markdown/Standard%20library%20+%20STL.md#set)
  * [map](/markdown/Standard%20library%20+%20STL.md#map)
  * [stack](/markdown/Standard%20library%20+%20STL.md#stack)
  * [queue](/markdown/Standard%20library%20+%20STL.md#queue)

### vector

Контейнер `vector` представляет собой динамический массив. Для работы с контейнером `vector` нужно подключить библиотеку `vector`:

```cpp
#include <vector>
```

Для работы с контейнером `vector` используются следующие методы:

  * `vector::push_back` - добавляет элемент в конец контейнера
  * `vector::pop_back` - удаляет элемент из конца контейнера
  * `vector::at` - возвращает элемент по индексу
  * `vector::size` - возвращает размер контейнера
  * `vector::empty` - возвращает `true`, если контейнер пустой

Пример кода:

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<int> v;
  for (int i = 0; i < 10; i++) {
    v.push_back(i);
  }

  for (int i = 0; i < v.size(); i++) {
    cout << v.at(i) << " ";
  }

  // output: 0 1 2 3 4 5 6 7 8 9

  cout << endl;
  return 0;
}
```

### list

Контейнер `list` представляет собой двусвязный список. Для работы с контейнером `list` нужно подключить библиотеку `list`:

```cpp
#include <list>
```

Для работы с контейнером `list` используются следующие методы:

  * `list::push_back` - добавляет элемент в конец контейнера
  * `list::push_front` - добавляет элемент в начало контейнера
  * `list::pop_back` - удаляет элемент из конца контейнера
  * `list::pop_front` - удаляет элемент из начала контейнера
  * `list::at` - возвращает элемент по индексу
  * `list::size` - возвращает размер контейнера
  * `list::empty` - возвращает `true`, если контейнер пустой

Пример кода:

```cpp
#include <iostream>
#include <list>
using namespace std;

int main() {
  list<int> l;
  for (int i = 0; i < 10; i++) {
    l.push_back(i);
  }

  for (int i = 0; i < l.size(); i++) {
    cout << l.at(i) << " ";
  }

  // output: 0 1 2 3 4 5 6 7 8 9

  cout << endl;
  return 0;
}
```

### deque

Контейнер `deque` представляет собой двустороннюю очередь. Для работы с контейнером `deque` нужно подключить библиотеку `deque`:

```cpp
#include <deque>
```

Для работы с контейнером `deque` используются следующие методы:

  * `deque::push_back` - добавляет элемент в конец контейнера
  * `deque::push_front` - добавляет элемент в начало контейнера
  * `deque::pop_back` - удаляет элемент из конца контейнера
  * `deque::pop_front` - удаляет элемент из начала контейнера
  * `deque::at` - возвращает элемент по индексу
  * `deque::size` - возвращает размер контейнера
  * `deque::empty` - возвращает `true`, если контейнер пустой

Пример кода:

```cpp
#include <iostream>
#include <deque>
using namespace std;

int main() {
  deque<int> d;
  for (int i = 0; i < 10; i++) {
    d.push_back(i);
  }

  for (int i = 0; i < d.size(); i++) {
    cout << d.at(i) << " ";
  }

  // output: 0 1 2 3 4 5 6 7 8 9

  cout << endl;
  return 0;
}
```

### set

Контейнер `set` представляет собой множество. Для работы с контейнером `set` нужно подключить библиотеку `set`:

```cpp
#include <set>
```

Для работы с контейнером `set` используются следующие методы:

  * `set::insert` - добавляет элемент в контейнер
  * `set::erase` - удаляет элемент из контейнера
  * `set::find` - возвращает итератор на элемент, если он есть в контейнере, иначе возвращает итератор на конец контейнера
  * `set::size` - возвращает размер контейнера
  * `set::empty` - возвращает `true`, если контейнер пустой

Пример кода:

```cpp
#include <iostream>
#include <set>
using namespace std;

int main() {
  set<int> s;
  for (int i = 0; i < 10; i++) {
    s.insert(i);
  }

  for (auto it = s.begin(); it != s.end(); it++) {
    cout << *it << " ";
  }

  // output: 0 1 2 3 4 5 6 7 8 9

  cout << endl;
  return 0;
}
```

### map

Контейнер `map` представляет собой ассоциативный массив. Для работы с контейнером `map` нужно подключить библиотеку `map`:

```cpp
#include <map>
```

Для работы с контейнером `map` используются следующие методы:

  * `map::insert` - добавляет элемент в контейнер
  * `map::erase` - удаляет элемент из контейнера
  * `map::find` - возвращает итератор на элемент, если он есть в контейнере, иначе возвращает итератор на конец контейнера
  * `map::size` - возвращает размер контейнера
  * `map::empty` - возвращает `true`, если контейнер пустой

Пример кода:

```cpp
#include <iostream>
#include <map>
using namespace std;

int main() {
  map<string, int> m;
  m.insert(make_pair("one", 1));
  m.insert(make_pair("two", 2));
  m.insert(make_pair("three", 3));

  for (auto it = m.begin(); it != m.end(); it++) {
    cout << it->first << " " << it->second << endl;
  }

  // output:
  // one 1
  // three 3
  // two 2

  cout << endl;
  return 0;
}
```

Так же здесь используется метод `make_pair`, который создает пару из двух элементов. Этот метод определен в библиотеке `utility`:

```cpp
#include <utility>
```

### stack

Контейнер `stack` представляет собой стек. Для работы с контейнером `stack` нужно подключить библиотеку `stack`:

```cpp
#include <stack>
```

Для работы с контейнером `stack` используются следующие методы:

  * `stack::push` - добавляет элемент в стек
  * `stack::pop` - удаляет элемент из стека
  * `stack::top` - возвращает верхний элемент стека
  * `stack::size` - возвращает размер стека
  * `stack::empty` - возвращает `true`, если стек пустой

Пример кода:

```cpp
#include <iostream>
#include <stack>
using namespace std;

int main() {
  stack<int> s;
  for (int i = 0; i < 10; i++) {
    s.push(i);
  }

  while (!s.empty()) {
    cout << s.top() << " ";
    s.pop();
  }

  // output: 9 8 7 6 5 4 3 2 1 0

  cout << endl;
  return 0;
}
```

## Итераторы

Итераторы позволяют обходить элементы контейнеров. Все контейнеры имеют методы `begin` и `end`, которые возвращают итераторы на первый и последний элементы контейнера соответственно. Для работы с итераторами используются операторы `*` (разыменование) и `->` (доступ к полю объекта, на который указывает итератор).

Пример кода:

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<int> v;
  for (int i = 0; i < 10; i++) {
    v.push_back(i);
  }

  for (auto it = v.begin(); it != v.end(); it++) {
    cout << *it << " ";
  }

  // output: 0 1 2 3 4 5 6 7 8 9

  cout << endl;
  return 0;
}
```

## Алгоритмы

В библиотеке `algorithm` реализованы алгоритмы, которые могут работать с контейнерами. Для работы с алгоритмами нужно подключить библиотеку `algorithm`:

```cpp
#include <algorithm>
```

Список алгоритмов:

  * `sort` - сортирует элементы контейнера в порядке возрастания (для сортировки элементов контейнера нужно, чтобы элементы контейнера имели оператор `<`)
      ```cpp
      vector<int> v;
      for (int i = 10; i > 0; i--) {
        v.push_back(i);
      }

      sort(v.begin(), v.end());

      for (auto it = v.begin(); it != v.end(); it++) {
        cout << *it << " ";
      }

      // output: 1 2 3 4 5 6 7 8 9 10
      ```
  * `reverse` - переворачивает элементы контейнера
      ```cpp
      vector<int> v;
      for (int i = 0; i < 10; i++) {
        v.push_back(i);
      }

      reverse(v.begin(), v.end());

      for (auto it = v.begin(); it != v.end(); it++) {
        cout << *it << " ";
      }

      // output: 9 8 7 6 5 4 3 2 1 0
      ```
  * `unique` - удаляет все повторяющиеся элементы контейнера, находящиеся рядом
      ```cpp
      vector<int> v;
      for (int i = 0; i < 10; i++) {
        v.push_back(i);
        v.push_back(i);
      }

      sort(v.begin(), v.end());
      v.erase(unique(v.begin(), v.end()), v.end());

      for (auto it = v.begin(); it != v.end(); it++) {
        cout << *it << " ";
      }

      // output: 0 1 2 3 4 5 6 7 8 9
      ```
  * `lower_bound` - возвращает итератор на первый элемент, который не меньше заданного
      ```cpp
      vector<int> v;
      for (int i = 0; i < 10; i++) {
        v.push_back(i);
      }

      auto it = lower_bound(v.begin(), v.end(), 5);
      cout << *it << endl;

      // output: 5
      ```
  * `upper_bound` - возвращает итератор на первый элемент, который больше заданного
      ```cpp
      vector<int> v;
      for (int i = 0; i < 10; i++) {
        v.push_back(i);
      }

      auto it = upper_bound(v.begin(), v.end(), 5);
      cout << *it << endl;

      // output: 6
      ```
  * `binary_search` - возвращает `true`, если элемент есть в контейнере
      ```cpp
      vector<int> v;
      for (int i = 0; i < 10; i++) {
        v.push_back(i);
      }

      cout << binary_search(v.begin(), v.end(), 5) << endl;

      // output: 1
      ```
