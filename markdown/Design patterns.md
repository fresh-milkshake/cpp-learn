
# Паттерны проектирования

- [Паттерны проектирования](#паттерны-проектирования)
  - [Что/Зачем это?](#чтозачем-это)
  - [Структурные паттрены](#структурные-паттрены)
    - [Адаптер](#адаптер)
    - [Компоновщик](#компоновщик)
    - [Декоратор](#декоратор)
    - [Фасад](#фасад)
  - [Поведенческие паттерны](#поведенческие-паттерны)
    - [Цепочка обязанностей](#цепочка-обязанностей)
    - [Команда](#команда)
    - [Итератор](#итератор)
    - [Посредник](#посредник)
  - [Пораждающие паттерны](#пораждающие-паттерны)
    - [Абстрактная фабрика](#абстрактная-фабрика)
    - [Строитель](#строитель)
    - [Фабричный метод](#фабричный-метод)
    - [Прототип](#прототип)
    - [Одиночка](#одиночка)
  - [Ссылки](#ссылки)

## Что/Зачем это?

Паттерны проектирования - это решения, которые позволяют решить часто встречающиеся проблемы при разработке программного обеспечения. Они не являются каким то конкретным кодом, а лишь только идея, реализуемая на основе конкретного языка программирования и рассматриваемого контекста задачи.

## Структурные паттрены

Структурные паттерны описывают как классы и объекты могут быть совмещены в более крупные структуры, позволяя им работать вместе.

- [Паттерны проектирования](#паттерны-проектирования)
  - [Что/Зачем это?](#чтозачем-это)
  - [Структурные паттрены](#структурные-паттрены)
    - [Адаптер](#адаптер)
    - [Компоновщик](#компоновщик)
    - [Декоратор](#декоратор)
    - [Фасад](#фасад)
  - [Поведенческие паттерны](#поведенческие-паттерны)
    - [Цепочка обязанностей](#цепочка-обязанностей)
    - [Команда](#команда)
    - [Итератор](#итератор)
    - [Посредник](#посредник)
  - [Пораждающие паттерны](#пораждающие-паттерны)
    - [Абстрактная фабрика](#абстрактная-фабрика)
    - [Строитель](#строитель)
    - [Фабричный метод](#фабричный-метод)
    - [Прототип](#прототип)
    - [Одиночка](#одиночка)
  - [Ссылки](#ссылки)

### Адаптер

Адаптер - это структурный паттерн проектирования, который позволяет объектам с несовместимыми интерфейсами работать вместе.

Пример:

```cpp
#include <iostream>
#include <string>

class ITarget
{
public:
    virtual ~ITarget() {}
    virtual std::string Request() const {
        return "ITarget: The default target's behavior.";
    }
};

class Adaptee
{
public:
    std::string SpecificRequest() const {
        return ".eetpadA eht fo roivaheb laicepS";
    }
};

class Adapter : public ITarget
{
private:
    Adaptee *adaptee_;

public:
    Adapter(Adaptee *adaptee) : adaptee_(adaptee) {}
    std::string Request() const override {
        std::string to_reverse = this->adaptee_->SpecificRequest();
        std::reverse(to_reverse.begin(), to_reverse.end());
        return "Adapter: (TRANSLATED) " + to_reverse;
    }
};

void ClientCode(const ITarget *target)
{
    std::cout << target->Request();
}

int main()
{
    std::cout << "Client: I can work just fine with the Target objects:\n";
    ITarget *target = new Target;
    ClientCode(target);
    std::cout << "A client: The Adaptee class has a weird interface. See, I don't understand it:\n";
    Adaptee *adaptee = new Adaptee;
    std::cout << "Adaptee: " << adaptee->SpecificRequest();
    std::cout << "Client: But I can work with it via the Adapter:\n";
    Adapter *adapter = new Adapter(adaptee);
    ClientCode(adapter);
    std::cout << "Client: I can work just fine with the Target objects:\n";
    std::cout << "Target: " << target->Request();
    delete target;
    delete adaptee;
    delete adapter;
    return 0;
}
```

Результат:

```txt
Client: I can work just fine with the Target objects:
Target: The default target's behavior.
A client: The Adaptee class has a weird interface. See, I don't understand it:
Adaptee: .eetpadA eht fo roivaheb laicepS
Client: But I can work with it via the Adapter:
Adapter: (TRANSLATED) Special behavior of the Adaptee.
Client: I can work just fine with the Target objects:
Target: The default target's behavior.
```

### Компоновщик

Компоновщик - это структурный паттерн проектирования, который позволяет сгруппировать множество объектов в древовидную структуру, а затем работать с ней так, как будто это единичный объект.

Пример:

```cpp
#include <iostream>
#include <string>
#include <vector>

class Component
{
public:
    virtual ~Component() {}
    virtual std::string Operation() const = 0;
};

class Leaf : public Component
{
public:
    std::string Operation() const override {
        return "Leaf";
    }
};

class Composite : public Component
{
private:
    std::vector<Component *> children_;

public:
    ~Composite() {
        for (size_t i = 0; i < children_.size(); i++) {
            delete children_[i];
        }
    }
    void Add(Component *component) {
        this->children_.push_back(component);
    }
    void Remove(Component *component) {
        std::vector<Component *>::iterator it = std::find(this->children_.begin(), this->children_.end(), component);
        if (it != this->children_.end()) {
            this->children_.erase(it);
        }
    }
    std::string Operation() const override {
        std::string result;
        for (size_t i = 0; i < this->children_.size(); i++) {
            if (this->children_[i] == this->children_.back()) {
                result += this->children_[i]->Operation();
            } else {
                result += this->children_[i]->Operation() + "+";
            }
        }
        return "Branch(" + result + ")";
    }
};

void ClientCode(Component *component)
{
    std::cout << "RESULT: " << component->Operation();
}

int main()
{
    Composite *tree = new Composite;
    Composite *branch1 = new Composite;
    branch1->Add(new Leaf);
    branch1->Add(new Leaf);
    Composite *branch2 = new Composite;
    branch2->Add(new Leaf);
    tree->Add(branch1);
    tree->Add(branch2);
    std::cout << "Client: I get a simple component:\n";
    Leaf *leaf = new Leaf;
    std::cout << "Client: I don't need to check the components classes even when managing the tree:\n";
    ClientCode(tree);
    std::cout << "\n";
    std::cout << "Client: I can merge components into the tree:\n";
    ClientCode(branch1);
    std::cout << "\n";
    std::cout << "Client: And I can destroy the tree without breaking the client code:\n";
    delete tree;
    delete leaf;
    return 0;
}
```

Результат:

```txt
Client: I get a simple component:
Client: I don't need to check the components classes even when managing the tree:
RESULT: Branch(Leaf+Leaf+Leaf)
Client: I can merge components into the tree
RESULT: Branch(Leaf+Leaf)
Client: And I can destroy the tree without breaking the client code:
```

### Декоратор

Декоратор - это структурный паттерн проектирования, который позволяет динамически добавлять объектам новую функциональность, оборачивая их в полезные «обёртки».

Пример:

```cpp
#include <iostream>
#include <string>

class Component
{
public:
    virtual ~Component() {}
    virtual std::string Operation() const = 0;
};

class ConcreteComponent : public Component
{
public:
    std::string Operation() const override {
        return "ConcreteComponent";
    }
};

class Decorator : public Component
{
protected:
    Component *component_;

public:
    Decorator(Component *component) : component_(component) {}
    std::string Operation() const override {
        return this->component_->Operation();
    }
};

class ConcreteDecoratorA : public Decorator
{
public:
    ConcreteDecoratorA(Component *component) : Decorator(component) {}
    std::string Operation() const override {
        return "ConcreteDecoratorA(" + Decorator::Operation() + ")";
    }
};

class ConcreteDecoratorB : public Decorator
{
public:
    ConcreteDecoratorB(Component *component) : Decorator(component) {}
    std::string Operation() const override {
        return "ConcreteDecoratorB(" + Decorator::Operation() + ")";
    }
};

void ClientCode(Component *component)
{
    std::cout << "RESULT: " << component->Operation();
}

int main()
{
    Component *simple = new ConcreteComponent;
    std::cout << "Client: I've got a simple component:\n";
    ClientCode(simple);
    std::cout << "\n\n";
    Decorator *decorator1 = new ConcreteDecoratorA(simple);
    Decorator *decorator2 = new ConcreteDecoratorB(decorator1);
    std::cout << "Client: Now I've got a decorated component:\n";
    ClientCode(decorator1);
    std::cout << "\n";
    ClientCode(decorator2);
    delete simple;
    delete decorator1;
    delete decorator2;
    return 0;
}
```

Результат:

```txt
Client: I've got a simple component:
RESULT: ConcreteComponent

Client: Now I've got a decorated component:
RESULT: ConcreteDecoratorA(ConcreteComponent)
RESULT: ConcreteDecoratorB(ConcreteDecoratorA(ConcreteComponent))
```

### Фасад

Фасад - это структурный паттерн проектирования, который предоставляет простой интерфейс к сложной системе классов, библиотеке или фреймворку.

Пример:

```cpp
#include <iostream>

class Subsystem1
{
public:
    std::string Operation1() const {
        return "Subsystem1: Ready!\n";
    }
    // ...
    std::string OperationN() const {
        return "Subsystem1: Go!\n";
    }
};

class Subsystem2
{
public:
    std::string Operation1() const {
        return "Subsystem2: Get ready!\n";
    }
    // ...
    std::string OperationZ() const {
        return "Subsystem2: Fire!\n";
    }
};

class Facade
{
protected:
    Subsystem1 *subsystem1_;
    Subsystem2 *subsystem2_;
    // ...

public:
    Facade(Subsystem1 *subsystem1 = nullptr, Subsystem2 *subsystem2 = nullptr) {
        this->subsystem1_ = subsystem1 ?: new Subsystem1;
        this->subsystem2_ = subsystem2 ?: new Subsystem2;
        // ...
    }
    ~Facade() {
        delete subsystem1_;
        delete subsystem2_;
        // ...
    }
    std::string Operation() {
        std::string result = "Facade initializes subsystems:\n";
        result += this->subsystem1_->Operation1();
        result += this->subsystem2_->Operation1();
        result += "Facade orders subsystems to perform the action:\n";
        result += this->subsystem1_->OperationN();
        result += this->subsystem2_->OperationZ();
        return result;
    }
};

void ClientCode(Facade *facade) {
    std::cout << facade->Operation();
}

int main() {
    Subsystem1 *subsystem1 = new Subsystem1;
    Subsystem2 *subsystem2 = new Subsystem2;
    Facade *facade = new Facade(subsystem1, subsystem2);
    ClientCode(facade);
    delete facade;
    return 0;
}
```

Результат:

```txt
Facade initializes subsystems:
Subsystem1: Ready!
Subsystem2: Get ready!
Facade orders subsystems to perform the action:
Subsystem1: Go!
Subsystem2: Fire!
```

## Поведенческие паттерны

Поведенческие паттерны проектирования решают задачи эффективного и безопасного взаимодействия между объектами программы.

* [Цепочка обязанностей](#Цепочка-обязанностей)
* [Команда](#Команда)
* [Итератор](#Итератор)
* [Посредник](#Посредник)

### Цепочка обязанностей

Цепочка обязанностей - это поведенческий паттерн проектирования, который позволяет передавать запросы последовательно по цепочке обработчиков. Каждый последующий обработчик решает, может ли он обработать запрос сам и стоит ли передавать запрос дальше по цепи.

Пример:

```cpp
#include <iostream>
#include <string>
#include <memory>

class Handler
{
public:
    virtual ~Handler() {}
    virtual void SetNext(std::shared_ptr<Handler> handler) = 0;
    virtual std::string Handle(const std::string &request) = 0;
};

class AbstractHandler : public Handler
{
private:
    std::shared_ptr<Handler> next_handler_;

public:
    AbstractHandler() : next_handler_(nullptr) {}
    void SetNext(std::shared_ptr<Handler> handler) override {
        this->next_handler_ = handler;
    }
    std::string Handle(const std::string &request) override {
        if (this->next_handler_) {
            return this->next_handler_->Handle(request);
        }
        return {};
    }
};

class MonkeyHandler : public AbstractHandler
{
public:
    std::string Handle(const std::string &request) override {
        if (request == "Banana") {
            return "Monkey: I'll eat the " + request + ".\n";
        } else {
            return AbstractHandler::Handle(request);
        }
    }
};

class SquirrelHandler : public AbstractHandler
{
public:
    std::string Handle(const std::string &request) override {
        if (request == "Nut") {
            return "Squirrel: I'll eat the " + request + ".\n";
        } else {
            return AbstractHandler::Handle(request);
        }
    }
};

class DogHandler : public AbstractHandler
{
public:
    std::string Handle(const std::string &request) override {
        if (request == "MeatBall") {
            return "Dog: I'll eat the " + request + ".\n";
        } else {
            return AbstractHandler::Handle(request);
        }
    }
};

void ClientCode(std::shared_ptr<Handler> handler) {
    const std::vector<std::string> food = {"Nut", "Banana", "Cup of coffee"};
    for (const std::string &f : food) {
        std::cout << "Client: Who wants a " << f << "?\n";
        const std::string result = handler->Handle(f);
        if (!result.empty()) {
            std::cout << "  " << result;
        } else {
            std::cout << "  " << f << " was left untouched.\n";
        }
    }
}

int main() {
    std::shared_ptr<MonkeyHandler> monkey = std::make_shared<MonkeyHandler>();
    std::shared_ptr<SquirrelHandler> squirrel = std::make_shared<SquirrelHandler>();
    std::shared_ptr<DogHandler> dog = std::make_shared<DogHandler>();
    monkey->SetNext(squirrel);
    squirrel->SetNext(dog);

    std::cout << "Chain: Monkey > Squirrel > Dog\n\n";
    ClientCode(monkey);
    std::cout << "\n";
    std::cout << "Subchain: Squirrel > Dog\n\n";
    ClientCode(squirrel);
    return 0;
}
```

Результат:

```txt
Chain: Monkey > Squirrel > Dog

Client: Who wants a Nut?
  Squirrel: I'll eat the Nut.
Client: Who wants a Banana?
  Monkey: I'll eat the Banana.
Client: Who wants a Cup of coffee?
  Cup of coffee was left untouched.

Subchain: Squirrel > Dog

Client: Who wants a Nut?
  Squirrel: I'll eat the Nut.
Client: Who wants a Banana?
  Banana was left untouched.
Client: Who wants a Cup of coffee?
  Cup of coffee was left untouched.
```

### Команда

Команда - это поведенческий паттерн проектирования, который превращает запросы в объекты, позволяя передавать их как аргументы при вызове методов, ставить запросы в очередь, логировать их, а также поддерживать отмену операций.

Пример:

```cpp
#include <iostream>
#include <string>
#include <vector>

class Command {
public:
    virtual ~Command() {}
    virtual void Execute() const = 0;
};

class SimpleCommand : public Command {
private:
    std::string pay_load_;

public:
    explicit SimpleCommand(std::string pay_load) : pay_load_(pay_load) {}
    void Execute() const override {
        std::cout << "SimpleCommand: See, I can do simple things like printing (" << this->pay_load_ << ")\n";
    }
};

class ComplexCommand : public Command {
private:
    std::vector<std::shared_ptr<Command>> commands_;

public:
    ComplexCommand(std::vector<std::shared_ptr<Command>> commands) : commands_(commands) {}
    void Execute() const override {
        std::cout << "ComplexCommand: Complex stuff should be done by a receiver object.\n";
        for (const std::shared_ptr<Command> &command : this->commands_) {
            command->Execute();
        }
    }
};

class Receiver {
public:
    void DoSomething(const std::string &a) {
        std::cout << "Receiver: Working on (" << a << ".)\n";
    }
    void DoSomethingElse(const std::string &b) {
        std::cout << "Receiver: Also working on (" << b << ".)\n";
    }
};

class Invoker {
private:
    std::shared_ptr<Command> on_start_;
    std::shared_ptr<Command> on_finish_;

public:
    Invoker(std::shared_ptr<Command> on_start, std::shared_ptr<Command> on_finish) : on_start_(on_start), on_finish_(on_finish) {}
    void DoSomethingImportant() {
        std::cout << "Invoker: Does anybody want something done before I begin?\n";
        if (this->on_start_) {
            this->on_start_->Execute();
        }
        std::cout << "Invoker: ...doing something really important...\n";
        std::cout << "Invoker: Does anybody want something done after I finish?\n";
        if (this->on_finish_) {
            this->on_finish_->Execute();
        }
    }
};

int main() {
    std::shared_ptr<Invoker> invoker = std::make_shared<Invoker>(std::make_shared<SimpleCommand>("Say Hi!"), std::make_shared<ComplexCommand>(std::vector<std::shared_ptr<Command>>{std::make_shared<SimpleCommand>("Send email"), std::make_shared<SimpleCommand>("Save report")}));

    invoker->DoSomethingImportant();
    return 0;
}
```

Результат:

```txt
Invoker: Does anybody want something done before I begin?
SimpleCommand: See, I can do simple things like printing (Say Hi!)
Invoker: ...doing something really important...
Invoker: Does anybody want something done after I finish?
ComplexCommand: Complex stuff should be done by a receiver object.
SimpleCommand: See, I can do simple things like printing (Send email)
SimpleCommand: See, I can do simple things like printing (Save report)
```

### Итератор

Итератор - это поведенческий паттерн проектирования, который даёт возможность последовательно обходить элементы составных объектов, не раскрывая их внутреннего представления.

Пример:

```cpp
#include <iostream>
#include <string>
#include <vector>

class Iterator {
public:
    virtual ~Iterator() {}
    virtual std::string First() = 0;
    virtual std::string Next() = 0;
    virtual bool IsDone() = 0;
    virtual std::string CurrentItem() = 0;
};

class WordsIterator : public Iterator {
private:
    std::vector<std::string> words_;
    int index_;

public:
    WordsIterator(std::vector<std::string> words) : words_(words) {}
    std::string First() override {
        return this->words_[0];
    }
    std::string Next() override {
        std::string ret;
        this->index_++;
        if (this->index_ < this->words_.size()) {
            ret = this->words_[this->index_];
        }
        return ret;
    }
    bool IsDone() override {
        return this->index_ >= this->words_.size();
    }
    std::string CurrentItem() override {
        return this->words_[this->index_];
    }
};

class Sentence {
private:
    std::vector<std::string> words_;

public:
    Sentence(std::string plain_text) {
        std::string word;
        for (const char &c : plain_text) {
            if (c == ' ') {
                this->words_.push_back(word);
                word = "";
            } else {
                word += c;
            }
        }
        this->words_.push_back(word);
    }
    Iterator *CreateIterator() {
        return new WordsIterator(this->words_);
    }
    std::vector<std::string> GetWords() {
        return this->words_;
    }
};

int main() {
    Sentence sentence("Hello World");
    Iterator *iterator = sentence.CreateIterator();
    while (!iterator->IsDone()) {
        std::cout << iterator->CurrentItem() << "\n";
        iterator->Next();
    }
    return 0;
}
```

Результат:

```txt
Hello
World
```

### Посредник

Посредник - это поведенческий паттерн проектирования, который позволяет уменьшить связанность множества классов между собой, благодаря перемещению
этих связей в один класс-посредник.

Пример:

```cpp
#include <iostream>
#include <string>
#include <vector>

class Component;

class Mediator {
public:
    virtual ~Mediator() {}
    virtual void Notify(Component *sender, std::string event) const = 0;
};

class Component {
protected:
    Mediator *mediator_;

public:
    Component(Mediator *mediator = nullptr) : mediator_(mediator) {}
    void SetMediator(Mediator *mediator) {
        this->mediator_ = mediator;
    }
};

class ConcreteComponent1 : public Component {
public:
    void DoA() {
        std::cout << "Component 1 does A.\n";
        this->mediator_->Notify(this, "A");
    }
    void DoB() {
        std::cout << "Component 1 does B.\n";
        this->mediator_->Notify(this, "B");
    }
};

class ConcreteComponent2 : public Component {
public:
    void DoC() {
        std::cout << "Component 2 does C.\n";
        this->mediator_->Notify(this, "C");
    }
    void DoD() {
        std::cout << "Component 2 does D.\n";
        this->mediator_->Notify(this, "D");
    }
};

class ConcreteMediator : public Mediator {
private:
    ConcreteComponent1 *component1_;
    ConcreteComponent2 *component2_;

public:
    ConcreteMediator(ConcreteComponent1 *c1, ConcreteComponent2 *c2) : component1_(c1), component2_(c2) {
        this->component1_->SetMediator(this);
        this->component2_->SetMediator(this);
    }
    void Notify(Component *sender, std::string event) const override {
        if (event == "A") {
            std::cout << "Mediator reacts on A and triggers following operations:\n";
            this->component2_->DoC();
        }
        if (event == "D") {
            std::cout << "Mediator reacts on D and triggers following operations:\n";
            this->component1_->DoB();
            this->component2_->DoC();
        }
    }
};

int main() {
    ConcreteComponent1 *c1 = new ConcreteComponent1;
    ConcreteComponent2 *c2 = new ConcreteComponent2;
    ConcreteMediator *mediator = new ConcreteMediator(c1, c2);
    std::cout << "Client triggers operation A.\n";
    c1->DoA();
    std::cout << "\n";
    std::cout << "Client triggers operation D.\n";
    c2->DoD();
    return 0;
}
```

## Пораждающие паттерны

* [Абстрактная фабрика](#абстрактная-фабрика)
* [Строитель](#строитель)
* [Фабричный метод](#фабричный-метод)
* [Прототип](#прототип)
* [Одиночка](#одиночка)

### Абстрактная фабрика

Абстрактная фабрика - это порождающий паттерн проектирования, который позволяет создавать семейства связанных объектов, не привязываясь к конкретным
классам создаваемых объектов.

Пример:

```cpp
#include <iostream>
#include <string>
#include <vector>

class ProductA {
public:
    virtual ~ProductA() {}
    virtual std::string UsefulFunctionA() const = 0;
};

class ConcreteProductA1 : public ProductA {
public:
    std::string UsefulFunctionA() const override {
        return "The result of the product A1.";
    }
};

class ConcreteProductA2 : public ProductA {
public:
    std::string UsefulFunctionA() const override {
        return "The result of the product A2.";
    }
};

class ProductB {
public:
    virtual ~ProductB() {}
    virtual std::string UsefulFunctionB() const = 0;
    virtual std::string AnotherUsefulFunctionB(const ProductA &collaborator) const = 0;
};

class ConcreteProductB1 : public ProductB {
public:
    std::string UsefulFunctionB() const override {
        return "The result of the product B1.";
    }
    std::string AnotherUsefulFunctionB(const ProductA &collaborator) const override {
        const std::string result = collaborator.UsefulFunctionA();
        return "The result of the B1 collaborating with the (" + result + ")";
    }
};

class ConcreteProductB2 : public ProductB {
public:
    std::string UsefulFunctionB() const override {
        return "The result of the product B2.";
    }
    std::string AnotherUsefulFunctionB(const ProductA &collaborator) const override {
        const std::string result = collaborator.UsefulFunctionA();
        return "The result of the B2 collaborating with the (" + result + ")";
    }
};

class AbstractFactory {
public:
    virtual ProductA *CreateProductA() const = 0;
    virtual ProductB *CreateProductB() const = 0;
};

class ConcreteFactory1 : public AbstractFactory {
public:
    ProductA *CreateProductA() const override {
        return new ConcreteProductA1();
    }
    ProductB *CreateProductB() const override {
        return new ConcreteProductB1();
    }
};

class ConcreteFactory2 : public AbstractFactory {
public:
    ProductA *CreateProductA() const override {
        return new ConcreteProductA2();
    }
    ProductB *CreateProductB() const override {
        return new ConcreteProductB2();
    }
};

void ClientCode(const AbstractFactory &factory) {
    const ProductA *product_a = factory.CreateProductA();
    const ProductB *product_b = factory.CreateProductB();
    std::cout << product_b->UsefulFunctionB() << std::endl;
    std::cout << product_b->AnotherUsefulFunctionB(*product_a) << std::endl;
    delete product_a;
    delete product_b;
}

int main() {
    std::cout << "Client: Testing client code with the first factory type:\n";
    ConcreteFactory1 *f1 = new ConcreteFactory1();
    ClientCode(*f1);
    delete f1;
    std::cout << std::endl;
    std::cout << "Client: Testing the same client code with the second factory type:\n";
    ConcreteFactory2 *f2 = new ConcreteFactory2();
    ClientCode(*f2);
    delete f2;
    return 0;
}
```

### Строитель

Строитель - это порождающий паттерн проектирования, который позволяет создавать сложные объекты пошагово. Строитель даёт возможность использовать один и тот же код строительства для получения разных представлений объектов.

Пример:

```cpp
#include <iostream>
#include <string>
#include <vector>

class Product {
private:
    std::vector<std::string> parts_;

public:
    void ListParts() const {
        std::cout << "Product parts: ";
        for (size_t i = 0; i < parts_.size(); i++) {
            if (parts_[i] == parts_.back()) {
                std::cout << parts_[i];
            } else {
                std::cout << parts_[i] << ", ";
            }
        }
        std::cout << "\n\n";
    }
    void Add(const std::string &part) {
        parts_.push_back(part);
    }
};

class Builder {
public:
    virtual ~Builder() {}
    virtual void ProducePartA() const = 0;
    virtual void ProducePartB() const = 0;
    virtual void ProducePartC() const = 0;
};

class ConcreteBuilder1 : public Builder {
private:
    Product *product_;

public:
    ConcreteBuilder1() {
        this->Reset();
    }
    ~ConcreteBuilder1() {
        delete product_;
    }
    void Reset() {
        this->product_ = new Product();
    }
    void ProducePartA() const override {
        this->product_->Add("PartA1");
    }
    void ProducePartB() const override {
        this->product_->Add("PartB1");
    }
    void ProducePartC() const override {
        this->product_->Add("PartC1");
    }
    Product *GetProduct() {
        Product *result = this->product_;
        this->Reset();
        return result;
    }
};

class ConcreteBuilder2 : public Builder {
private:
    Product *product_;

public:
    ConcreteBuilder2() {
        this->Reset();
    }
    ~ConcreteBuilder2() {
        delete product_;
    }
    void Reset() {
        this->product_ = new Product();
    }
    void ProducePartA() const override {
        this->product_->Add("PartA2");
    }
    void ProducePartB() const override {
        this->product_->Add("PartB2");
    }
    void ProducePartC() const override {
        this->product_->Add("PartC2");
    }
    Product *GetProduct() {
        Product *result = this->product_;
        this->Reset();
        return result;
    }
};

class Director {
private:
    Builder *builder_;

public:
    void set_builder(Builder *builder) {
        this->builder_ = builder;
    }
    void BuildMinimalViableProduct() {
        this->builder_->ProducePartA();
    }
    void BuildFullFeaturedProduct() {
        this->builder_->ProducePartA();
        this->builder_->ProducePartB();
        this->builder_->ProducePartC();
    }
};

void ClientCode(Director &director) {
    ConcreteBuilder1 *builder = new ConcreteBuilder1();
    director.set_builder(builder);
    std::cout << "Standard basic product:\n";
    director.BuildMinimalViableProduct();
    builder->GetProduct()->ListParts();
    std::cout << "Standard full featured product:\n";
    director.BuildFullFeaturedProduct();
    builder->GetProduct()->ListParts();
    std::cout << "Custom product:\n";
    builder->ProducePartA();
    builder->ProducePartC();
    builder->GetProduct()->ListParts();
    delete builder;
}

int main() {
    Director *director = new Director();
    ClientCode(*director);
    delete director;
    return 0;
}
```

### Фабричный метод

Фабричный метод - это порождающий паттерн проектирования, который определяет общий интерфейс для создания объектов в суперклассе, позволяя подклассам изменять тип создаваемых объектов.

Пример:

```cpp
#include <iostream>
#include <string>
#include <map>
#include <memory>

class Product {
public:
    virtual ~Product() {}
    virtual std::string Operation() const = 0;
};

class ConcreteProduct1 : public Product {
public:
    std::string Operation() const override {
        return "{Result of the ConcreteProduct1}";
    }
};

class ConcreteProduct2 : public Product {
public:
    std::string Operation() const override {
        return "{Result of the ConcreteProduct2}";
    }
};

class Creator {
public:
    virtual ~Creator() {}
    virtual std::shared_ptr<Product> FactoryMethod() const = 0;
    std::string SomeOperation() const {
        std::shared_ptr<Product> product = this->FactoryMethod();
        std::string result = "Creator: The same creator's code has just worked with " + product->Operation();
        return result;
    }
};

class ConcreteCreator1 : public Creator {
public:
    std::shared_ptr<Product> FactoryMethod() const override {
        return std::make_shared<ConcreteProduct1>();
    }
};

class ConcreteCreator2 : public Creator {
public:
    std::shared_ptr<Product> FactoryMethod() const override {
        return std::make_shared<ConcreteProduct2>();
    }
};

void ClientCode(const Creator &creator) {
    std::cout << "Client: I'm not aware of the creator's class, but it still works.\n"
              << creator.SomeOperation() << std::endl;
}

int main() {
    std::cout << "App: Launched with the ConcreteCreator1.\n";
    ConcreteCreator1 *creator1 = new ConcreteCreator1();
    ClientCode(*creator1);
    std::cout << std::endl;
    std::cout << "App: Launched with the ConcreteCreator2.\n";
    ConcreteCreator2 *creator2 = new ConcreteCreator2();
    ClientCode(*creator2);
    delete creator1;
    delete creator2;
    return 0;
}
```

### Прототип

Прототип - это порождающий паттерн проектирования, который позволяет копировать объекты, не вдаваясь в подробности их реализации.

Пример:

```cpp
#include <iostream>
#include <string>
#include <memory>

class Prototype {
public:
    virtual ~Prototype() {}
    virtual std::shared_ptr<Prototype> Clone() const = 0;
    virtual void Method(float) const = 0;
};

class ConcretePrototype1 : public Prototype {
private:
    float value_;

public:
    ConcretePrototype1(float value)
        : value_(value) {
    }

    std::shared_ptr<Prototype> Clone() const override {
        return std::make_shared<ConcretePrototype1>(*this);
    }

    void Method(float value) const override {
        this->value_ = value;
        std::cout << "ConcretePrototype1: " << this->value_ << std::endl;
    }
};

class ConcretePrototype2 : public Prototype {
private:
    float value_;

public:
    ConcretePrototype2(float value)
        : value_(value) {
    }

    std::shared_ptr<Prototype> Clone() const override {
        return std::make_shared<ConcretePrototype2>(*this);
    }

    void Method(float value) const override {
        this->value_ = value;
        std::cout << "ConcretePrototype2: " << this->value_ << std::endl;
    }
};

void ClientCode() {
    std::shared_ptr<ConcretePrototype1> p1 = std::make_shared<ConcretePrototype1>(75);
    std::shared_ptr<ConcretePrototype1> c1 = std::static_pointer_cast<ConcretePrototype1>(p1->Clone());
    std::cout << "Cloned: " << c1->Method(100) << std::endl;
    std::cout << std::endl;

    std::shared_ptr<ConcretePrototype2> p2 = std::make_shared<ConcretePrototype2>(12);
    std::shared_ptr<ConcretePrototype2> c2 = std::static_pointer_cast<ConcretePrototype2>(p2->Clone());
    std::cout << "Cloned: " << c2->Method(50) << std::endl;
}

int main() {
    ClientCode();
    return 0;
}
```

### Одиночка

Одиночка - это порождающий паттерн проектирования, который гарантирует, что у класса есть только один экземпляр, и предоставляет к нему глобальную точку доступа.

Пример:

```cpp
#include <iostream>
#include <string>

class Singleton {
public:
    static Singleton& Get() {
        static Singleton instance;
        return instance;
    }

    void SomeBusinessLogic() {
        std::cout << "Singleton: I'm doing something important!\n";
    }

private:
    Singleton() {
        std::cout << "Singleton: I'm being initialized!\n";
    }

    ~Singleton() {
        std::cout << "Singleton: I'm being destroyed!\n";
    }

    Singleton(const Singleton&) = delete;
    void operator=(const Singleton&) = delete;
};

void ThreadFoo() {
    std::cout << "Thread A: I want the singleton instance!\n";
    Singleton& singleton = Singleton::Get();
    std::cout << "Thread A: I got the instance!\n";
    singleton.SomeBusinessLogic();
}

void ThreadBar() {
    std::cout << "Thread B: I want the singleton instance!\n";
    Singleton& singleton = Singleton::Get();
    std::cout << "Thread B: I got the instance!\n";
    singleton.SomeBusinessLogic();
}

int main() {
    std::cout << "If you see the same value, then singleton was reused (yay!\n"
              << "If you see different values, then 2 singletons were created (booo!!)\n\n"
              << "RESULT:\n";
    std::thread t1(ThreadFoo);
    std::thread t2(ThreadBar);
    t1.join();
    t2.join();
    return 0;
}
```

## Ссылки

* [Паттерны проектирования](https://refactoring.guru/ru/design-patterns)
* [Wiki](https://ru.wikipedia.org/wiki/Паттерн_проектирования)
* [medium.com](https://medium.com/must-know-computer-science/basic-design-patterns-in-c-39bd3d477a5c)