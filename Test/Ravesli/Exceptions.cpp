#include <iostream>
#define ���������_���������_����������

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
