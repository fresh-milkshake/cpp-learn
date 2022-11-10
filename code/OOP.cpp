// include - preprocessor directive for including header files
// it copies the contents of the header file to the current
#include <iostream>
#include <fstream>
#include <memory>
// include also can be used to include other c/cpp code files
// for example, if we have a file called "my_functions.cpp"
// we can include it like this:
// #include "my_functions.cpp"
// and use functions from it in the current file
// HINT: it is not recommended to use this method, because
// HINT: it will copy the contents of the file to the current file
// HINT: and it will increase the size of the final executable file
// HINT: (if you are using a compiler, that compiles all files into one)
// HINT: and it will also increase the compilation time
// HINT: so, it is better to use header files for this purpose

// class - keyword for creating new classes
class Example
{
    // classes in c++ can have private, protected and public members
    // protected members can be accessed from the class and its children
    // private members are only accessible from inside the class
    // while public members are accessible from outside

    // by default, all members are private, so if we declare
    // a variable like this:
    std::ifstream private_file; /// we can leave field uninitialized ///
    int private_variable = 0;   /// or initialize it right away      ///
    // it will be private, but it will be better to explicitly
    // declare it as private, and declare it after private keyword
private: // everything going after this line in the class will be private
    int second_private_variable;
    // private members can be accessed only from inside the class
    // can be used to calculate other values:
    int sum_of = private_variable + second_private_variable;

    // same rules apply to other class members, such as methods
    void private_do_nothing()
    {
        // this method is private, so it can only be called from inside the class
    }

    // we can declare protected members, which are accessible from
    // inside the class and from derived classes
protected:
    int protected_variable;
    void protected_do_nothing()
    {
        // this method is protected, so it can be called from inside the class
        // and from derived classes
    }

    // public members are accessible from outside the class

public: // everything going after this line in the class will be public
    // here declared virtual method, which will be overriden in derived classes
    // HINT: virtual methods can be used for polymorphism
    virtual void virtual_method()
    {
        // in this version of the method, we will print "virtual method"
        std::cout << "virtual method" << std::endl;
    }

    // public members works the same way as private members
    // besides changing access modifiers
    int public_variable;
    void public_do_nothing()
    {
        // this method is public, so it can be called from outside the class
    }
    // classes can have constructors, which are called when
    // a new object of the class is created
    // constructors can be used to initialize class members
    Example() : public_variable(100)
    {
        // ": public_variable(0)" is a constructor initializer list
        // syntax is: ": member_name(value), member_name(value), ..."
        // it is used to initialize class members before the constructor body
        // it is also possible to initialize members in the constructor body
        public_variable = 100;
        private_file = std::ifstream("hello world.cpp");
        // but it is better to use initializer list, because it is more efficient
        // and easier read
    }

    // classes can have destructors (class name with ~ prefix), which are called when
    // an object of the class is destroyed
    // destructors can be used to free memory, close files, etc.
    ~Example()
    {
        // destructor body
        private_file.close(); // close file when object is destroyed
    }

    // classes can also have static members, which are shared between all objects of the class
    // static members can be accessed using class name, for example:
    inline static int static_variable = 0;
    static void static_method(int value)
    {
        static_variable += value;
    }
}; // HINT: don't forget to add semicolon after class declaration

// lets create a new class, which will inherit from Example class
// inheritance synatax: "class <derived class name> : <base class name>"
// HINT: if you want to inherit from multiple classes, you can do it like this:
// HINT: "class <derived class name> : <base class name 1>, <base class name 2>, ..."
// HINT: but it is not recommended to inherit from multiple classes in c++
// HINT: because it can cause problems with multiple inheritance and "diamond problem"
// derived class also inherits constructors and destructors from base class
// so, we don't need to declare them again and here we can use it like this:
// Derived() : Example() {}
class DerivedExample : public Example // new class with Example class as base
{
public:
    // derived classes can access protected members of the base class
    // and can override virtual methods
    // overriding virtual methods is done by declaring a method with the same name
    // and the same signature (return type and parameters) but with a special
    // override keyword after the method signature (before the body) like this:
    void virtual_method() override
    {
        // in this version of the method, we will print "derived virtual method"
        std::cout << "derived virtual method" << std::endl;
    }

    DerivedExample() : Example() {} // call base class constructor

    // we can override not only our own virtual methods, but also build-in methods
    // and operators behavior
    // for example, we can override the behavior of the + operator
    // by declaring a method with the same name and the same signature
    // and with the special operator keyword after the method signature
    // (before the body) like this:
    DerivedExample *operator+(const DerivedExample &other) const
    {
        // in this version of the method, we will add two objects
        // and return the result
        std::unique_ptr<DerivedExample> result = std::make_unique<DerivedExample>();
        // we can use unique_ptr or make_unique to store a pointer to an object
        // and not worry about memory leaks
        // the difference between unique_ptr and make_unique is that
        // unique_ptr is a class, while make_unique is a function and
        // make_unique is a shortcut for creating a new object using
        // the constructor of the class
        // HINT: std::unique_ptr is a smart pointer, which automatically deletes
        // HINT: the object, when it goes out of scope
        // HINT: it is better to use smart pointers instead of raw pointers
        // HINT: because it is more safe and easier to use
        result->public_variable = this->public_variable + other.public_variable; // this - pointer to the current object
        // HINT: we can also use "this->" to access members of the current object
        // HINT: but it is not necessary, because the compiler will do it automatically
        // HINT: (when we use "this->" it is called "explicit this")
        return result.release();
    }

    // we can also override the behavior of the << operator
    // friend keyword is used to allow access to private members
    // of the class from outside the class (in this case, from the operator<<)
    // HINT: friend keyword is useful for overloading operators, but it is not recommended
    // HINT: to use it in other cases, because "it can break encapsulation"
    // HINT: friend syntax: "friend <return type> operator<operator name>(<parameters>)"
    friend std::ostream &operator<<(std::ostream &out, const DerivedExample &example)
    {
        // in this version of the operator, we will print the value of "public_variable"
        // to the "out" stream
        out << example.public_variable;
        return out;
    }
};

// we can also declare a class as a template class
// template parameters are declared using < and > symbols
// and we can use them inside the class declaration like this:
// template <typename T, typename U>
template <typename T>
class TemplateExample
{
public:
    // we can also use template parameters to declare constructors
    // and destructors
    TemplateExample(T value) : template_variable(value) {}
    ~TemplateExample() {}

    // we can use template parameters to declare class members
    // and to declare class methods
    T template_variable;
    void template_method(T value)
    {
        // we can also use template parameters to declare method parameters
        // and to specify the return type of the method
        std::cout << "Class of T in TemplateExample is: " << typeid(T).name() << std::endl;
    }
};

void test_examples()
{
    // we can create objects of the class using the class name
    // and the constructor name like this:
    Example example;
    DerivedExample derived_example;
    // template classes with template parameters can be created like this:
    TemplateExample<int> template_example(100);

    // lets call some methods of created objects:
    // Example class methods:
    example.public_do_nothing(); // call public method
    // example.private_do_nothing(); // ERROR: private method can't be called from outside the class
    // example.protected_do_nothing(); // ERROR: protected method can't be called from outside the class
    example.virtual_method(); // call virtual method
    // DerivedExample class methods:
    derived_example.public_do_nothing(); // call public method
    // derived_example.private_do_nothing(); // ERROR: private method can't be called from outside the class
    // derived_example.protected_do_nothing(); // ERROR: protected method can't be called from outside the class
    derived_example.virtual_method(); // call virtual method

    // we can access public and protected members of the object using
    // the dot operator like this:
    example.public_variable = 999;
    // example.protected_variable = 999; // ERROR: protected member can't be accessed from outside the class
    // example.private_variable = 999;  // ERROR: private member can't be accessed from outside the class
    std::cout << "Public variable of the example object: "
              << example.public_variable << std::endl;

    // we can also access pointer to the object using the arrow operator
    // ("->") like this:
    Example *example_pointer = &example;
    example_pointer->public_variable = 100;
    // example_pointer->protected_variable = 100; // ERROR: protected member can't be accessed from outside the class
    // example_pointer->private_variable = 100; // ERROR: private member can't be accessed from outside the class
    std::cout << "Public variable of the example object (using pointer): "
              << example_pointer->public_variable << std::endl;

    // we can access static members of the class using the class name
    // and the dot operator like this:
    Example::static_variable = 100;
    Example::static_method(100);
    std::cout << "Static variable of the Example class: "
              << Example::static_variable << std::endl;

    // lets call some methods of the template class:
    template_example.template_method(100);
    std::cout << "Template variable of the template object: "
              << template_example.template_variable << std::endl;
}

int main()
{
    test_examples();
    return 0;
}