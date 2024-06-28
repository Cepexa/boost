#include <iostream>
#define ����

#ifdef weak_ptr_std
#include <memory> // ��� std::shared_ptr � std::weak_ptr
#include <string>
//std::weak_ptr ��� ���������� ��� ������� �������� ������������ �����������
class Human
{
    std::string m_name;
    std::weak_ptr<Human> m_partner; // �������� ��������, ����� std::weak_ptr

public:

    Human(const std::string& name) : m_name(name)
    {
        std::cout << m_name << " created\n";
    }
    ~Human()
    {
        std::cout << m_name << " destroyed\n";
    }

    friend bool partnerUp(std::shared_ptr<Human>& h1, std::shared_ptr<Human>& h2)
    {
        if (!h1 || !h2)
            return false;

        h1->m_partner = h2;
        h2->m_partner = h1;

        std::cout << h1->m_name << " is now partnered with " << h2->m_name << "\n";

        return true;
    }

    // ���������� ����� lock() ��� ����������� std::weak_ptr � std::shared_ptr
    const std::shared_ptr<Human> getPartner() const { return m_partner.lock(); }
    const std::string& getName() const { return m_name; }
};

int main()
{
    auto anton = std::make_shared<Human>("Anton");
    auto ivan = std::make_shared<Human>("Ivan");

    partnerUp(anton, ivan);

    auto partner = ivan->getPartner(); // �������� partner-� ���������� ������ ���������, ������� ������� ivan
    std::cout << ivan->getName() << "'s partner is: " << partner->getName() << '\n';

    return 0;
}
#endif

#ifdef shared_ptr_std
#include <memory> // ��� std::shared_ptr

class Item
{
public:
    Item() { std::cout << "Item acquired\n"; }
    ~Item() { std::cout << "Item destroyed\n"; }
};

int main()
{
    // �������� Item � �������� ��� � std::shared_ptr
    Item* item = new Item;
    std::shared_ptr<Item> ptr1(item);
    {
        std::shared_ptr<Item> ptr2(ptr1); // ���������� ���������� ������������� ��� �������� ������� std::shared_ptr �� ptr1, ������������ �� ��� �� Item

        std::cout << "Killing one shared pointer\n";
    } // ptr2 ������� �� ������� ��������� �����, �� ������ ������ �� ����������

    std::cout << "Killing another shared pointer\n";

    // �������� Item � �������� ��� � std::shared_ptr
    auto ptr3 = std::make_shared<Item>();
    {
        auto ptr4 = ptr3; // ������� ptr4 �� ptr3, ��������� ��������� �����������

        std::cout << "Killing one shared pointer\n";
    } // ptr4 ������� �� ������� ��������� �����, �� ������ ������ �� ����������

    std::cout << "Killing another shared pointer\n";

    return 0;
} // ptr1 ������� �� ������� ��������� �����, � ���������� Item ������������ ����� �����
#endif

#ifdef unique_ptr_std
#include <memory> // ��� std::unique_ptr
class Fraction
{
private:
    int m_numerator = 0;
    int m_denominator = 1;

public:
    Fraction(int numerator = 0, int denominator = 1) :
        m_numerator(numerator), m_denominator(denominator)
    {
    }

    friend std::ostream& operator<<(std::ostream& out, const Fraction& f1)
    {
        out << f1.m_numerator << "/" << f1.m_denominator;
        return out;
    }
};
class Item
{
public:
    Item() { std::cout << "Item acquired\n"; }
    ~Item() { std::cout << "Item destroyed\n"; }
    friend std::ostream& operator<<(std::ostream& out, const Item& item)
    {
        out << "I am an Item!\n";
        return out;
    }
};

// ��� ������� ���������� ������ Item, ������� �� �������� ��������� �� Item, � �� ������ �� ���� std::unique_ptr<Item>
void useItem(Item* item)
{
    if (item)
        std::cout << *item;
}

int main()
{
    std::unique_ptr<Item> item1(new Item); // ��������� Item
    std::unique_ptr<Item> item2; // ������������� �������� nullptr

    std::cout << "item1 is " << (static_cast<bool>(item1) ? "not null\n" : "null\n");
    std::cout << "item2 is " << (static_cast<bool>(item2) ? "not null\n" : "null\n");

    // item2 = item1; // �� ��������������: ��������� ����������� ���������
    item2 = std::move(item1); // item2 ������ ������� item1, � ��� item1 ������������� �������� null

    std::cout << "Ownership transferred\n";

    std::cout << "item1 is " << (static_cast<bool>(item1) ? "not null\n" : "null\n");
    std::cout << "item2 is " << (static_cast<bool>(item2) ? "not null\n" : "null\n");

    std::unique_ptr<Item> item(new Item);

    if (item) // ���������� ������� �������������� item � ��� bool, ����� ���������, ��� item ������� Item-��
        std::cout << *item; // ������� Item, ������� ������� item

    // ������� ������ � ����������� ���������� Fraction � numerator = 7 � denominator = 9
    std::unique_ptr<Fraction> f1 = std::make_unique<Fraction>(7, 9);
    std::cout << *f1 << '\n';

    // ������� ������ � ����������� ���������� �������� Fraction ������ 5.
    // ���������� �������������� ����������� ���� ������ � ������� ��������� ����� auto
    auto f2 = std::make_unique<Fraction[]>(5);
    std::cout << f2[0] << '\n';

    //�������� � ������������� ������������� ����������
    //some_function(std::unique_ptr<T>(new T), function_that_can_throw_exception());
    //�������: ����������� ������� std::make_unique() ������ �������� ������ ��������� 
    //std::unique_ptr � ������������� ��������� new.

    auto ptr = std::make_unique<Item>();

    useItem(ptr.get()); // ����������: ����� get() ������������ ��� ��������� ��������� �� Item

    std::cout << "Ending program\n";

    return 0;
} // Item ������������ �����, ����� item2 ������� �� ������� ���������
#endif

#ifdef �������_move std::move()
#include <string>
#include <utility>

template<class T>
void swap(T& x, T& y)
{
    T tmp{ std::move(x) }; // �������� ����������� �����������
    x = std::move(y); // �������� �������� ������������ ������������
    y = std::move(tmp); // �������� �������� ������������ ������������
}

int main()
{
    std::string x{ "Anton" };
    std::string y{ "Max" };

    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';

    swap(x, y);

    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';

    return 0;
}
#endif

#ifdef ���������_�����������
template<class T>
class Auto_ptr3
{
    T* m_ptr;
public:
    Auto_ptr3(T* ptr = nullptr)
        :m_ptr(ptr)
    {
    }

    ~Auto_ptr3()
    {
        delete m_ptr;
    }

    // ����������� �����������, ������� ��������� �������� ����������� x.m_ptr � m_ptr
    Auto_ptr3(const Auto_ptr3& x)
    {
        m_ptr = new T;
        *m_ptr = *x.m_ptr;
    }

    // ����������� �����������, ������� �������� ����� ������������� �� x.m_ptr � m_ptr
    Auto_ptr3(Auto_ptr3&& x)
        : m_ptr(x.m_ptr)
    {
        x.m_ptr = nullptr; // �� ��������� �� ���� ���� �����
    }

    // �������� ������������ ������������, ������� ��������� �������� ����������� x.m_ptr � m_ptr
    Auto_ptr3& operator=(const Auto_ptr3& x)
    {
        // �������� �� ����������������
        if (&x == this)
            return *this;

        // ������� ��, ��� � ����� ������� ����� ������� ��������� 
        delete m_ptr;

        // �������� ������������ ������
        m_ptr = new T;
        *m_ptr = *x.m_ptr;

        return *this;
    }

    // �������� ������������ ������������, ������� �������� ����� ������������� �� x.m_ptr � m_ptr
    Auto_ptr3& operator=(Auto_ptr3&& x)
    {
        // �������� �� ����������������
        if (&x == this)
            return *this;

        // ������� ��, ��� � ����� ������� ����� ������� ��������� 
        delete m_ptr;

        // �������� ����� ������������� �� x.m_ptr � m_ptr
        m_ptr = x.m_ptr;
        x.m_ptr = nullptr; // �� ��������� �� ���� ���� �����

        return *this;
    }

    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
    bool isNull() const { return m_ptr == nullptr; }
};

class Item
{
public:
    Item() { std::cout << "Item acquired\n"; }
    ~Item() { std::cout << "Item destroyed\n"; }
};

Auto_ptr3<Item> generateItem()
{
    Auto_ptr3<Item> item(new Item);
    return item; // ��� ������������ �������� �������� � ������ ������������ �����������
}

int main()
{
    Auto_ptr3<Item> mainItem;
    mainItem = generateItem(); // ��� �������� ������������ �������� � ������ ��������� ������������ ������������

    return 0;
}
#endif

#ifdef ���������_�����������_����������
template<class T>
class Auto_ptr2
{
    T* m_ptr;
public:
    Auto_ptr2(T* ptr = nullptr)
        :m_ptr(ptr)
    {
    }

    ~Auto_ptr2()
    {
        delete m_ptr;
    }

    // ����������� �����������, ������� ������������� ��������� �����������
    Auto_ptr2(Auto_ptr2& a) // ����������: ������ �� �������� �����������
    {
        m_ptr = a.m_ptr; // ���������� ��� ������ ��������� �� ��������� � ������ ���������� �������
        a.m_ptr = nullptr; // ������������, ��� �������� ������ �� ������� ����������
    }

    // �������� ������������, ������� ������������� ��������� �����������
    Auto_ptr2& operator=(Auto_ptr2& a) // ����������: ������ �� �������� �����������
    {
        if (&a == this)
            return *this;

        delete m_ptr; // ������������, ��� ������� ����� ���������, ������� ��� ��������� ������ ���� �� �����
        m_ptr = a.m_ptr; // ����� ���������� ��� ������ ��������� �� ��������� � ������ ���������� �������
        a.m_ptr = nullptr; // ������������, ��� �������� ������ �� ������� ����������
        return *this;
    }

    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
    bool isNull() const { return m_ptr == nullptr; }
};

class Item
{
public:
    Item() { std::cout << "Item acquired\n"; }
    ~Item() { std::cout << "Item destroyed\n"; }
};

int main()
{
    Auto_ptr2<Item> item1(new Item);
    Auto_ptr2<Item> item2; // ������ � nullptr

    std::cout << "item1 is " << (item1.isNull() ? "null\n" : "not null\n");
    std::cout << "item2 is " << (item2.isNull() ? "null\n" : "not null\n");

    item2 = item1; // item2 ������ �������� "����������" �������� item1, ������� item1 ������������� null

    std::cout << "Ownership transferred\n";

    std::cout << "item1 is " << (item1.isNull() ? "null\n" : "not null\n");
    std::cout << "item2 is " << (item2.isNull() ? "null\n" : "not null\n");

    return 0;
}
#endif

#ifdef �����_���������
template<class T>
class Auto_ptr1
{
    T* m_ptr;
public:
    // �������� ��������� ��� "��������" ����� �����������
    Auto_ptr1(T* ptr = nullptr)
        :m_ptr(ptr)
    {
    }

    // ���������� ����������� �� �������� ���������
    ~Auto_ptr1()
    {
        delete m_ptr;
    }

    // ��������� ���������� ��������� ������������� � ��������� ->, ����� ����� ����������� ������������ Auto_ptr1 ��� m_ptr
    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
};

// ����� ��� �������� ����������������� ���������������� ����
class Item
{
public:
    Item() { std::cout << "Item acquired\n"; }
    ~Item() { std::cout << "Item destroyed\n"; }
    void sayHi() { std::cout << "Hi!\n"; }
};

void myFunction()
{
    Auto_ptr1<Item> ptr(new Item); // ptr ������ "�������" Item-��

    int a;
    std::cout << "Enter an integer: ";
    std::cin >> a;

    if (a == 0)
        return; // ��������� ������� �������

    // ������������� ptr
    ptr->sayHi();
}

int main()
{
    myFunction();

    return 0;
}
#endif

#ifdef ����_try
#endif

#ifdef ��������������_try_����
#include <iostream>
class A
{
private:
    int m_x;
public:
    A(int x) : m_x(x)
    {
        if (x <= 0)
            throw 1;
    }
};

class B : public A
{
public:
    B(int x) try : A(x) // �������� �������� �� �������� ����� try �����
    {
    }
    catch (...) // �������� ��������, ���� ���� ��������� �� ��� �� ������ �������, ��� � �����������
    {
        // ���������� �� ������ ������������� ������ ������ B ��� ���� ������������ �������������� �����

        std::cerr << "Construction of A failed\n";

        // ���� �� ����� �� ����� ���� ����������� ����������, �� ������� (���������) ���������� ����� �������� ������������� � ���������� � ���� �������
    }
};

int main()
{
    try
    {
        B b(0);
    }
    catch (int)
    {
        std::cout << "Oops!\n";
    }
}
#endif

#ifdef ���������_���������_����������
class Parent
{
public:
    Parent() {}
    virtual void print() { std::cout << "Parent"; }
};

class Child : public Parent
{
public:
    Child() {}
    virtual void print() { std::cout << "Child"; }
};

int main()
{
    try
    {
        try
        {
            throw Child();
        }
        catch (Parent& p)
        {
            std::cout << "Caught Parent p, which is actually a ";
            p.print();
            std::cout << "\n";
            throw; // ����������: �� ����� �������� ����������� ����������
        }
}
    catch (Parent& p)
    {
        std::cout << "Caught Parent p, which is actually a ";
        p.print();
        std::cout << "\n";
    }

    return 0;
}
#endif

#ifdef ��������������_���������� //����� �������� ������ � cmd
#include <iostream>
using namespace std;
void term_func() {
    cout << "term_func was called by terminate." << endl;
    exit(-1);
}
int main() {
    try
    {
        set_terminate(term_func);
        throw "Out of memory!"; // No catch handler for this exception
    }
    catch (int)
    {
        cout << "Integer exception raised." << endl;
    }
    return 0;
}

#endif

#ifdef ������_���������� � ������������
#include <exception> // ��� std::exception
#include <string> // ��� ����� �������

class ArrayException : public std::exception
{
private:
    std::string m_error;

public:
    ArrayException(std::string error)
        : m_error(error)
    {
    }

    const char* getError() { return m_error.c_str(); }
    // ���������� std::string � �������� ����������� ������ C-style
//	const char* what() const { return m_error.c_str(); } // �� C++11
    const char* what() const noexcept { return m_error.c_str(); } // C++11 � ����
};

class ArrayInt
{
private:

    int m_data[4]; // ���� ���������� �������� ������� ������ �������� 4 � �������� ����� �������
public:
    ArrayInt() {}

    int getLength() { return 4; }

    int& operator[](const int index)
    {
        if (index < 0 || index >= getLength())
            throw ArrayException("Invalid index");

        return m_data[index];
    }

};

#include <cassert>

class Parent
{
public:
    Parent() {}
};

class Child : public Parent
{
public:
    Child() {}
};

int main()
{
    try
    {
        throw Child();
    }
    catch (Child& child)
    {
        std::cerr << "caught Child\n";
    }
    catch (Parent& parent)
    {
        std::cerr << "caught Parent\n";
    }

    
    ArrayInt array;

    try
    {
        int value = array[7];
    }
    catch (ArrayException& exception)
    {
        std::cerr << "An array exception occurred (" << exception.getError()<<"\t"
            << exception.what() << ")\n";
    }

    try
    {
        // ����� ������ ���������� ���, ������������ ����������� ���������� �++
        std::string s;
        s.resize(-1); // ������������ ���������� std::bad_alloc
        throw std::runtime_error("Bad things happened");
    }
    // ���� ���������� ����� std::bad_alloc � ��� �������� ��� ������-����������
    catch (std::bad_alloc& exception)
    {
        std::cerr << "You ran out of memory!" << '\n';
    }
    // ���� ���������� ����� std::exception � ��� �������� ��� ������-����������
    catch (std::exception& exception)
    {
        std::cerr << "Standard exception: " << exception.what() << '\n';
    }

}
#endif

#ifdef catch_all
int doSomething() throw() { return 0; } // �� ������������� ����������
template <typename T>
T doSomething(T) throw(T) { throw "Hi"; return 1; } // ����� �������������� ���������� ���� double
int doSomething(double) throw(...) { return 2; } // ����� �������������� ����� ����������
int main()
{
    try
    {
        std::cout<<doSomething(2)<<std::endl;
        throw 7; // ������������� ���������� ���� int
    }
    catch (double a)
    {
        std::cout << "We caught an exception of type double: " << a << '\n';
    }
    catch (...) // ���������� catch-all
    {
        std::cout << "We caught an exception of an undetermined type!\n";
    }
}
#endif

#ifdef �������_�������������_�����
void last() // ���������� �������� three()
{
    std::cout << "Start last\n";
    std::cout << "last throwing int exception\n";
    throw - 1;
    std::cout << "End last\n";

}

void three() // ���������� �������� two()
{
    std::cout << "Start three\n";
    last();
    std::cout << "End three\n";
}

void two() // ���������� �������� one()
{
    std::cout << "Start two\n";
    try
    {
        three();
    }
    catch (double)
    {
        std::cerr << "two caught double exception\n";
    }
    std::cout << "End two\n";
}

void one() // ���������� �������� main()
{
    std::cout << "Start one\n";
    try
    {
        two();
    }
    catch (int)
    {
        std::cerr << "one caught int exception\n";
    }
    catch (double)
    {
        std::cerr << "one caught double exception\n";
    }
    std::cout << "End one\n";
}

int main()
{
    std::cout << "Start main\n";
    try
    {
        one();
    }
    catch (int)
    {
        std::cerr << "main caught int exception\n";
    }
    std::cout << "End main\n";

    return 0;
}
#endif

#ifdef �������������_throw_try � catch
#include <string>

int main()
{
    try
    {
        // ����� �� ����� ����������, ������� ����� ������������ ��������� ����������
        throw - 1; // �������� ��������� throw
    }
    catch (int a)
    {
        // ����� ���������� ���� int, ��������������� � ����� try, ����������� ����, �������������� �����
        std::cerr << "We caught an int exception with value: " << a << '\n';
    }
    catch (double) // �� �� ��������� ��� ����������, ��� ��� � ���� ��� ���������� (�� � ����� � ����� �� ����������)
    {
        // ����� ���������� ���� double, ��������������� � ����� try, ����������� ����, �������������� �����
        std::cerr << "We caught an exception of type double" << '\n';
    }
    catch (const std::string& str) // ����� ���������� �� ����������� ������
    {
        // ����� ���������� ���� std::string, ��������������� ������ ����� try, ����������� ����, �������������� �����
        std::cerr << "We caught an exception of type std::string" << '\n';
    }

    std::cout << "Continuing our way!\n";

    return 0;
}
#endif // �������������_throw_try � catch
