
# UML

- [UML](#uml)
  - [Что/Зачем это?](#чтозачем-это)
    - [Простейший пример](#простейший-пример)
  - [UML для некотрых паттернов](#uml-для-некотрых-паттернов)
    - [Стратегия](#стратегия)
    - [Наблюдатель](#наблюдатель)
    - [Декоратор](#декоратор)
    - [Фабричный метод](#фабричный-метод)
    - [Абстрактная фабрика](#абстрактная-фабрика)
  - [Сноски](#сноски)

## Что/Зачем это?

UML - Unified Modeling Language - язык моделирования, который позволяет описывать различные аспекты системы, в том числе и ее структуру.

GitHub использует [Mermaid](https://mermaid-js.github.io/mermaid/#/)[^1] - это инструмент для создания диаграмм, которые можно встраивать в markdown.

UML позволяет описывать:

  * Структуру системы
  * Структуру данных
  * Поведение системы
  * Поведение объектов
  * Алгоритмы и др.

### Простейший пример

Вот пример калькулятора:

```cpp
#include <iostream>

class Calculator {
public:
    double add(double a, double b) {
        return a + b;
    }

    double sub(double a, double b) {
        return a - b;
    }

    double mul(double a, double b) {
        return a * b;
    }

    double div(double a, double b) {
        return a / b;
    }
};

class ScientificCalculator : public Calculator {
public:
    double pow(double a, double b) {
        double res = 1;
        for (int i = 0; i < b; i++) {
            res *= a;
        }
        return res;
    }
};
```

А это его UML-диаграмма:

```mermaid
classDiagram
    Calculator <|-- ScientificCalculator
    class Calculator{
        + double add(double a, double b)
        + double sub(double a, double b)
        + double mul(double a, double b)
        + double div(double a, double b)
    }
    class ScientificCalculator{
        + double pow(double a, double b)
    }
```

## UML для некотрых паттернов

- [UML](#uml)
  - [Что/Зачем это?](#чтозачем-это)
    - [Простейший пример](#простейший-пример)
  - [UML для некотрых паттернов](#uml-для-некотрых-паттернов)
    - [Стратегия](#стратегия)
    - [Наблюдатель](#наблюдатель)
    - [Декоратор](#декоратор)
    - [Фабричный метод](#фабричный-метод)
    - [Абстрактная фабрика](#абстрактная-фабрика)
  - [Сноски](#сноски)

### Стратегия

```mermaid
classDiagram
    Strategy <|-- ConcreteStrategyA
    Strategy <|-- ConcreteStrategyB
    Context "1" *-- "1" Strategy : uses
    class Strategy{
        + void AlgorithmInterface()
    }
    class ConcreteStrategyA{
        + void AlgorithmInterface()
    }
    class ConcreteStrategyB{
        + void AlgorithmInterface()
    }
    class Context{
        - Strategy strategy
        + Context(Strategy strategy)
        + void ContextInterface()
    }
```

### Наблюдатель

```mermaid
classDiagram
    Subject <|-- ConcreteSubject
    Observer <|-- ConcreteObserverA
    Observer <|-- ConcreteObserverB
    Subject "1" *-- "*" Observer : notifies
    Observer "1" *-- "1" Subject : observes
    class Subject{
        + void Attach(Observer observer)
        + void Detach(Observer observer)
        + void Notify()
    }
    class ConcreteSubject{
        + void Notify()
    }
    class Observer{
        + void Update()
    }
    class ConcreteObserverA{
        + void Update()
    }
    class ConcreteObserverB{
        + void Update()
    }
```

### Декоратор

```mermaid
classDiagram
    Component <|-- ConcreteComponent
    Component <|-- Decorator
    Decorator <|-- ConcreteDecoratorA
    Decorator <|-- ConcreteDecoratorB
    Component "1" *-- "1" Decorator : decorates
    class Component{
        + void Operation()
    }
    class ConcreteComponent{
        + void Operation()
    }
    class Decorator{
        - Component component
        + Decorator(Component component)
        + void Operation()
    }
    class ConcreteDecoratorA{
        + void Operation()
    }
    class ConcreteDecoratorB{
        + void Operation()
    }
```

### Фабричный метод

```mermaid
classDiagram
    Creator <|-- ConcreteCreatorA
    Creator <|-- ConcreteCreatorB
    Creator "1" *-- "1" Product : creates
    class Creator{
        + Product FactoryMethod()
    }
    class ConcreteCreatorA{
        + Product FactoryMethod()
    }
    class ConcreteCreatorB{
        + Product FactoryMethod()
    }
    class Product{
        + void Operation()
    }
```

### Абстрактная фабрика

```mermaid
classDiagram
    AbstractFactory <|-- ConcreteFactory1
    AbstractFactory <|-- ConcreteFactory2
    AbstractProductA <|-- ProductA1
    AbstractProductA <|-- ProductA2
    AbstractProductB <|-- ProductB1
    AbstractProductB <|-- ProductB2
    AbstractFactory "1" *-- "*" AbstractProductA : creates
    AbstractFactory "1" *-- "*" AbstractProductB : creates
    class AbstractFactory{
        + AbstractProductA CreateProductA()
        + AbstractProductB CreateProductB()
    }
    class ConcreteFactory1{
        + AbstractProductA CreateProductA()
        + AbstractProductB CreateProductB()
    }
    class ConcreteFactory2{
        + AbstractProductA CreateProductA()
        + AbstractProductB CreateProductB()
    }
    class AbstractProductA{
        + void OperationA()
    }
    class ProductA1{
        + void OperationA()
    }
    class ProductA2{
        + void OperationA()
    }
    class AbstractProductB{
        + void OperationB()
    }
    class ProductB1{
        + void OperationB()
    }
    class ProductB2{
        + void OperationB()
    }
```


## Сноски

[^1]: [Mermaid Live Editor](https://mermaid-js.github.io/mermaid-live-editor/), [Mermaid Documentation](https://mermaid-js.github.io/mermaid/#/)