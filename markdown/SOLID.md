
# SOLID

- [SOLID](#solid)
  - [S - Single Responsibility Principle](#s---single-responsibility-principle)
  - [O - Open Closed Principle](#o---open-closed-principle)
  - [L - Liskov Substitution Principle](#l---liskov-substitution-principle)
  - [I - Interface Segregation Principle](#i---interface-segregation-principle)
  - [D - Dependency Inversion Principle](#d---dependency-inversion-principle)

## S - Single Responsibility Principle

Принцип единой ответственности (Single Responsibility Principle) гласит, что каждый объект должен иметь одну ответственность и эта ответственность должна быть полностью инкапсулирована в класс. Все его поведения должны быть направлены исключительно на обеспечение этой ответственности.

Пример его соблюдения, и его нарушения:

```cpp
class Journal { // Создаем класс журнал
    string title; // Заголовок
    vector<string> entries; // Записи

    Journal(const string& title) : title(title) {} // Конструктор

    void add(const string& entry) {
        static int count = 1;
        entries.push_back(lexical_cast<string>(count++) + ": " + entry);
    }

    // Нарушение принципа единой ответственности
    // Перенесем функцию сохранения в отдельный класс
    void save(const string& filename) {
        ofstream ofs(filename);
        for (auto& e : entries)
            ofs << e << endl;
    }
};

// Перенесем функцию сохранения в отдельный класс
class PersistenceManager {
    static void save(const Journal& j, const string& filename) {
        ofstream ofs(filename);
        for (auto& e : j.entries)
            ofs << e << endl;
    }
};

int main() {
    Journal journal{"Dear Diary"};
    journal.add("I ate a bug");
    journal.add("I cried today");

    journal.save("diary.txt");

    PersistenceManager pm;
    pm.save(journal, "diary.txt");

    return 0;
}
```

Принцип единой ответственности позволяет нам рассматривать классы как части системы, которые можно заменить другими классами, не нарушая работу всей системы. Это позволяет нам создавать более гибкие и масштабируемые системы.

## O - Open Closed Principle

Принцип открытости/закрытости (Open Closed Principle) гласит, что программные сущности должны быть открыты для расширения, но закрыты для модификации. **Иначе говоря, расширяя поведение класса, мы не должны изменять код, использующий его функциональность**

Пример его соблюдения, и его нарушения:

```cpp
enum class Color { Red, Green, Blue };
enum class Size { Small, Medium, Large };

struct Product {
    string name;
    Color color;
    Size size;
};

template <typename T> struct Specification {
    virtual bool is_satisfied(T* item) = 0;
};

template <typename T> struct Filter {
    virtual vector<T*> filter(vector<T*> items, Specification<T>& spec) = 0;
};

struct BetterFilter : Filter<Product> {
    vector<Product*> filter(vector<Product*> items, Specification<Product>& spec) override {
        vector<Product*> result;
        for (auto& p : items)
            if (spec.is_satisfied(p))
                result.push_back(p);
        return result;
    }
};

struct ColorSpecification : Specification<Product> {
    Color color;

    explicit ColorSpecification(const Color color) : color(color) {}

    bool is_satisfied(Product* item) override {
        return item->color == color;
    }
};

struct SizeSpecification : Specification<Product> {
    Size size;

    explicit SizeSpecification(const Size size) : size(size) {}

    bool is_satisfied(Product* item) override {
        return item->size == size;
    }
};

template <typename T> struct AndSpecification : Specification<T> {
    Specification<T>& first;
    Specification<T>& second;

    AndSpecification(Specification<T>& first, Specification<T>& second) : first(first), second(second) {}

    bool is_satisfied(T* item) override {
        return first.is_satisfied(item) && second.is_satisfied(item);
    }
};

int main() {
    Product apple{"Apple", Color::Green, Size::Small};
    Product tree{"Tree", Color::Green, Size::Large};
    Product house{"House", Color::Blue, Size::Large};

    vector<Product*> items{&apple, &tree, &house};

    BetterFilter bf;
    ColorSpecification green(Color::Green);

    auto green_things = bf.filter(items, green);
    for (auto& x : green_things)
        cout << x->name << " is green\n";

    SizeSpecification large(Size::Large);
    AndSpecification<Product> green_and_large(green, large);
    for (auto& x : bf.filter(items, green_and_large))
        cout << x->name << " is green and large\n";

    return 0;
}
```

Принцип открытости/закрытости позволяет нам создавать более гибкие и масштабируемые системы.

## L - Liskov Substitution Principle

Принцип подстановки Барбары Лисков (Liskov Substitution Principle) гласит, что объекты в программе должны быть заменяемыми на экземпляры их подтипов, без изменения правильности выполнения программы. **Иначе говоря, если класс B является подклассом класса A, то мы должны иметь возможность заменить B на A, не нарушая работоспособности программы**

Пример его соблюдения, и его нарушения:

```cpp
class Rectangle {
protected:
    int width, height;

public:
    Rectangle(const int width, const int height) : width(width), height(height) {}

    int get_width() const { return width; }
    virtual void set_width(const int width) { Rectangle::width = width; }
    int get_height() const { return height; }
    virtual void set_height(const int height) { Rectangle::height = height; }

    int area() const { return width * height; }
};

class Square : public Rectangle {
public:
    Square(int size) : Rectangle(size, size) {}

    void set_width(const int width) override {
        this->width = height = width;
    }

    void set_height(const int height) override {
        this->height = width = height;
    }
};

void process(Rectangle& r) {
    int w = r.get_width();
    r.set_height(10);

    cout << "expected area = " << (w * 10)
         << ", got " << r.area() << endl;
}

int main() {
    Rectangle r{5, 5};
    process(r);

    Square s{5};
    process(s);

    return 0;
}
```

## I - Interface Segregation Principle

Принцип разделения интерфейса (Interface Segregation Principle) гласит, что **много интерфейсов специально предназначенных для клиентов лучше, чем один интерфейс общего назначения**. **Интерфейсы должны быть максимально специализированы**.

Пример его соблюдения, и его нарушения:

```cpp
struct Document;

struct IMachine {
    virtual void print(vector<Document*> docs) = 0;
    virtual void scan(vector<Document*> docs) = 0;
    virtual void fax(vector<Document*> docs) = 0;
};

struct MFP : IMachine {
    void print(vector<Document*> docs) override;
    void scan(vector<Document*> docs) override;
    void fax(vector<Document*> docs) override;
};

struct IPrinter {
    virtual void print(vector<Document*> docs) = 0;
};

struct IScanner {
    virtual void scan(vector<Document*> docs) = 0;
};

struct Printer : IPrinter {
    void print(vector<Document*> docs) override;
};

struct Scanner : IScanner {
    void scan(vector<Document*> docs) override;
};

struct PrinterScanner : IPrinter, IScanner {
    IPrinter& printer;
    IScanner& scanner;

    PrinterScanner(IPrinter& printer, IScanner& scanner)
        : printer(printer), scanner(scanner) {}

    void print(vector<Document*> docs) override {
        printer.print(docs);
    }

    void scan(vector<Document*> docs) override {
        scanner.scan(docs);
    }
};
```

## D - Dependency Inversion Principle

Принцип инверсии зависимостей (Dependency Inversion Principle) гласит, что **модули верхних уровней не должны зависеть от модулей нижних уровней. Оба типа модулей должны зависеть от абстракций**. Абстракции не должны зависеть от деталей. Детали должны зависеть от абстракций.

Пример его соблюдения, и его нарушения:

```cpp
enum class Relationship {
    parent,
    child,
    sibling
};

struct Person {
    string name;
};

struct RelationshipBrowser {
    virtual vector<Person> find_all_children_of(const string& name) = 0;
};

struct Relationships : RelationshipBrowser { // low-level
    vector<tuple<Person, Relationship, Person>> relations;

    void add_parent_and_child(const Person& parent, const Person& child) {
        relations.push_back({parent, Relationship::parent, child});
        relations.push_back({child, Relationship::child, parent});
    }

    vector<Person> find_all_children_of(const string& name) override {
        vector<Person> result;
        for (auto&& [first, rel, second] : relations) {
            if (first.name == name && rel == Relationship::parent) {
                result.push_back(second);
            }
        }
        return result;
    }
};

struct Research { // high-level
    Research(RelationshipBrowser& browser) {
        for (auto& child : browser.find_all_children_of("John")) {
            cout << "John has a child called " << child.name << endl;
        }
    }
};

int main() {
    Person parent{"John"};
    Person child1{"Chris"}, child2{"Matt"};

    Relationships relationships;
    relationships.add_parent_and_child(parent, child1);
    relationships.add_parent_and_child(parent, child2);

    Research _(relationships);

    return 0;
}
```