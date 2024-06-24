#include <iostream>
#define повторная_генерация_исключений

#ifdef повторная_генерация_исключений
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
            throw; // примечание: Мы здесь повторно выбрасываем исключение
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

#ifdef Необработанные_исключения //будет работать только в cmd
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

#ifdef Классы_Исключения и Наследование
#include <exception> // для std::exception
#include <string> // для этого примера

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
    // Возвращаем std::string в качестве константной строки C-style
//	const char* what() const { return m_error.c_str(); } // до C++11
    const char* what() const noexcept { return m_error.c_str(); } // C++11 и выше
};

class ArrayInt
{
private:

    int m_data[4]; // ради сохранения простоты примера укажем значение 4 в качестве длины массива
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
        // Здесь должен находиться код, использующий Стандартную библиотеку С++
        std::string s;
        s.resize(-1); // генерируется исключение std::bad_alloc
        throw std::runtime_error("Bad things happened");
    }
    // Этот обработчик ловит std::bad_alloc и все дочерние ему классы-исключения
    catch (std::bad_alloc& exception)
    {
        std::cerr << "You ran out of memory!" << '\n';
    }
    // Этот обработчик ловит std::exception и все дочерние ему классы-исключения
    catch (std::exception& exception)
    {
        std::cerr << "Standard exception: " << exception.what() << '\n';
    }

}
#endif

#ifdef catch_all
int doSomething() throw() { return 0; } // не выбрасываются исключения
template <typename T>
T doSomething(T) throw(T) { throw "Hi"; return 1; } // могут генерироваться исключения типа double
int doSomething(double) throw(...) { return 2; } // могут генерироваться любые исключения
int main()
{
    try
    {
        std::cout<<doSomething(2)<<std::endl;
        throw 7; // выбрасывается исключение типа int
    }
    catch (double a)
    {
        std::cout << "We caught an exception of type double: " << a << '\n';
    }
    catch (...) // обработчик catch-all
    {
        std::cout << "We caught an exception of an undetermined type!\n";
    }
}
#endif

#ifdef Функции_Раскручивание_стека
void last() // вызывается функцией three()
{
    std::cout << "Start last\n";
    std::cout << "last throwing int exception\n";
    throw - 1;
    std::cout << "End last\n";

}

void three() // вызывается функцией two()
{
    std::cout << "Start three\n";
    last();
    std::cout << "End three\n";
}

void two() // вызывается функцией one()
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

void one() // вызывается функцией main()
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

#ifdef Использование_throw_try и catch
#include <string>

int main()
{
    try
    {
        // Здесь мы пишем стейтменты, которые будут генерировать следующее исключение
        throw - 1; // типичный стейтмент throw
    }
    catch (int a)
    {
        // Любые исключения типа int, сгенерированные в блоке try, приведенном выше, обрабатываются здесь
        std::cerr << "We caught an int exception with value: " << a << '\n';
    }
    catch (double) // мы не указываем имя переменной, так как в этом нет надобности (мы её нигде в блоке не используем)
    {
        // Любые исключения типа double, сгенерированные в блоке try, приведенном выше, обрабатываются здесь
        std::cerr << "We caught an exception of type double" << '\n';
    }
    catch (const std::string& str) // ловим исключения по константной ссылке
    {
        // Любые исключения типа std::string, сгенерированные внутри блока try, приведенном выше, обрабатываются здесь
        std::cerr << "We caught an exception of type std::string" << '\n';
    }

    std::cout << "Continuing our way!\n";

    return 0;
}
#endif // Использование_throw_try и catch
