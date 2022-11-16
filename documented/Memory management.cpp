// include - preprocessor directive for including header files
// it copies the contents of the header file to the current
#include <memory.h> // memory management functions
#include <iostream> // input/output stream classes

// template - a generic class or function
// typename - a keyword used to declare a type
// T - a template parameter
template <typename T>
class WeakPtr
{
private:
    // pointer to the object
    T* m_ptr;
    // pointer to the reference counter
    unsigned int* m_refCount;

public:
    // constructor
    WeakPtr(T* ptr = nullptr)
    {
        m_ptr = ptr;
        m_refCount = new unsigned int(1);
    }

    // copy constructor
    WeakPtr(const WeakPtr<T>& other)
    {
        m_ptr = other.m_ptr;
        m_refCount = other.m_refCount;
        (*m_refCount)++;
    }

    // destructor
    ~WeakPtr()
    {
        (*m_refCount)--;
        if (*m_refCount == 0)
        {
            delete m_ptr;
            delete m_refCount;
        }
    }

    // assignment operator
    WeakPtr<T>& operator=(const WeakPtr<T>& other)
    {
        if (this != &other)
        {
            (*m_refCount)--;
            if (*m_refCount == 0)
            {
                delete m_ptr;
                delete m_refCount;
            }
            m_ptr = other.m_ptr;
            m_refCount = other.m_refCount;
            (*m_refCount)++;
        }
        return *this;
    }

    // dereference operator
    T& operator*()
    {
        return *m_ptr;
    }

    // member access operator
    T* operator->()
    {
        return m_ptr;
    }

    // conversion operator
    operator bool()
    {
        return m_ptr != nullptr;
    }
};


void test_weak() {
    WeakPtr<int> p1(new int(5));
    WeakPtr<int> p2(p1);
    WeakPtr<int> p3;
    p3 = p1;
    std::cout << *p1 << std::endl;
    std::cout << *p2 << std::endl;
    std::cout << *p3 << std::endl;
}

int main()
{
    test_weak();
    return 0;
};