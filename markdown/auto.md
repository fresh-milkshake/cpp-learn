
# auto

- [auto](#auto)
  - [Как именно это работает](#как-именно-это-работает)
  - [Ограничения и сообщения об ошибках](#ограничения-и-сообщения-об-ошибках)
  - [Ссылки](#ссылки)

## Как именно это работает

Ключевое слово `auto` позволяет определить переменную, которая будет автоматически приведена к типу, который вы указали. Например, если вы хотите создать переменную, которая будет хранить целое число, то вы можете написать следующее:

```cpp
auto a = 5;
```

То, благодаря чему это работает, называется `type deduction` (выделение типа). Компилятор сам понимает, что вы хотите создать переменную типа `int`, и создает ее. Таким образом, вы можете создать переменную любого типа, не указывая его явно. 

## Ограничения и сообщения об ошибках

| Номер | Описание | Пример |
| --- | --- | --- |
| [C3530](https://learn.microsoft.com/ru-ru/cpp/error-messages/compiler-errors-2/compiler-error-c3530?view=msvc-170) | Ключевое auto слово не может быть объединено с любым другим описательом типа. | `auto auto a;` |
| [C3531](https://learn.microsoft.com/ru-ru/cpp/error-messages/compiler-errors-2/compiler-error-c3531?view=msvc-170) | Символ, объявленный с ключевым словом auto , должен иметь инициализатор. | `auto a;` |
| [C3532](https://learn.microsoft.com/ru-ru/cpp/error-messages/compiler-errors-2/compiler-error-c3532?view=msvc-170) | Вы неправильно использовали ключевое auto слово для объявления типа. Например, был объявлен тип возвращаемого значения метода или массив. | `auto a = 5;` |
| [C3533](https://learn.microsoft.com/ru-ru/cpp/error-messages/compiler-errors-2/compiler-error-c3533?view=msvc-170) | Параметр или аргумент шаблона нельзя объявить с помощью ключевого auto слова. | `template <auto a> void f();` |
| [C3535](https://learn.microsoft.com/ru-ru/cpp/error-messages/compiler-errors-2/compiler-error-c3535?view=msvc-170) | Невозможно объявить параметр метода или шаблона с ключевым словом auto . | `void f(auto a);` |
| [C3536](https://learn.microsoft.com/ru-ru/cpp/error-messages/compiler-errors-2/compiler-error-c3536?view=msvc-170) | Символ нельзя использовать перед инициализацией. На практике это означает, что переменная не может использоваться для инициализации себя. | `auto a = a;` |
| [C3537](https://learn.microsoft.com/ru-ru/cpp/error-messages/compiler-errors-2/compiler-error-c3537?view=msvc-170) | Нельзя привести к типу, объявленному с помощью ключевого auto слова. | `auto a = 5; int b = a;` |
| [C3538](https://learn.microsoft.com/ru-ru/cpp/error-messages/compiler-errors-2/compiler-error-c3538?view=msvc-170) | Все символы в списке деклараторов, объявленных с auto ключевым словом, должны разрешаться в один и тот же тип. Дополнительные сведения см. в объявлениях и определениях. | `auto a = 5, b = 5.0;` |
| [C3539](https://learn.microsoft.com/ru-ru/cpp/error-messages/compiler-errors-2/compiler-error-c3539?view=msvc-170) | Указанный тип аргумента шаблона не может содержать использование auto ключевого слова. | `template <auto a> void f();` |
| [C3540](https://learn.microsoft.com/ru-ru/cpp/error-messages/compiler-errors-2/compiler-error-c3540?view=msvc-170) | Нельзя использовать ключевое auto слово для объявления символа, объявленного внутри шаблона. | `template <typename T> class A { auto a; };` |

## Ссылки

* [Microsoft C++](https://learn.microsoft.com/ru-ru/cpp/cpp/auto-cpp?view=msvc-170)