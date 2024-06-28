#include <iostream>
#define тест

#ifdef weak_ptr_std
#include <memory> // для std::shared_ptr и std::weak_ptr
#include <string>
//std::weak_ptr был разработан для решения проблемы «циклической зависимости»
class Human
{
    std::string m_name;
    std::weak_ptr<Human> m_partner; // обратите внимание, здесь std::weak_ptr

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

    // используем метод lock() для конвертации std::weak_ptr в std::shared_ptr
    const std::shared_ptr<Human> getPartner() const { return m_partner.lock(); }
    const std::string& getName() const { return m_name; }
};

int main()
{
    auto anton = std::make_shared<Human>("Anton");
    auto ivan = std::make_shared<Human>("Ivan");

    partnerUp(anton, ivan);

    auto partner = ivan->getPartner(); // передаем partner-у содержимое умного указателя, которым владеет ivan
    std::cout << ivan->getName() << "'s partner is: " << partner->getName() << '\n';

    return 0;
}
#endif

#ifdef shared_ptr_std
#include <memory> // для std::shared_ptr

class Item
{
public:
    Item() { std::cout << "Item acquired\n"; }
    ~Item() { std::cout << "Item destroyed\n"; }
};

int main()
{
    // Выделяем Item и передаем его в std::shared_ptr
    Item* item = new Item;
    std::shared_ptr<Item> ptr1(item);
    {
        std::shared_ptr<Item> ptr2(ptr1); // используем копирующую инициализацию для создания второго std::shared_ptr из ptr1, указывающего на тот же Item

        std::cout << "Killing one shared pointer\n";
    } // ptr2 выходит из области видимости здесь, но больше ничего не происходит

    std::cout << "Killing another shared pointer\n";

    // Выделяем Item и передаем его в std::shared_ptr
    auto ptr3 = std::make_shared<Item>();
    {
        auto ptr4 = ptr3; // создаем ptr4 из ptr3, используя семантику копирования

        std::cout << "Killing one shared pointer\n";
    } // ptr4 выходит из области видимости здесь, но ничего больше не происходит

    std::cout << "Killing another shared pointer\n";

    return 0;
} // ptr1 выходит из области видимости здесь, и выделенный Item уничтожается также здесь
#endif

#ifdef unique_ptr_std
#include <memory> // для std::unique_ptr
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

// Эта функция использует только Item, поэтому мы передаем указатель на Item, а не ссылку на весь std::unique_ptr<Item>
void useItem(Item* item)
{
    if (item)
        std::cout << *item;
}

int main()
{
    std::unique_ptr<Item> item1(new Item); // выделение Item
    std::unique_ptr<Item> item2; // присваивается значение nullptr

    std::cout << "item1 is " << (static_cast<bool>(item1) ? "not null\n" : "null\n");
    std::cout << "item2 is " << (static_cast<bool>(item2) ? "not null\n" : "null\n");

    // item2 = item1; // не скомпилируется: семантика копирования отключена
    item2 = std::move(item1); // item2 теперь владеет item1, а для item1 присваивается значение null

    std::cout << "Ownership transferred\n";

    std::cout << "item1 is " << (static_cast<bool>(item1) ? "not null\n" : "null\n");
    std::cout << "item2 is " << (static_cast<bool>(item2) ? "not null\n" : "null\n");

    std::unique_ptr<Item> item(new Item);

    if (item) // используем неявное преобразование item в тип bool, чтобы убедиться, что item владеет Item-ом
        std::cout << *item; // выводим Item, которым владеет item

    // Создаем объект с динамически выделенным Fraction с numerator = 7 и denominator = 9
    std::unique_ptr<Fraction> f1 = std::make_unique<Fraction>(7, 9);
    std::cout << *f1 << '\n';

    // Создаем объект с динамически выделенным массивом Fraction длиной 5.
    // Используем автоматическое определение типа данных с помощью ключевого слова auto
    auto f2 = std::make_unique<Fraction[]>(5);
    std::cout << f2[0] << '\n';

    //проблема с безопасностью использования исключений
    //some_function(std::unique_ptr<T>(new T), function_that_can_throw_exception());
    //Правило: Используйте функцию std::make_unique() вместо создания умного указателя 
    //std::unique_ptr и использования оператора new.

    auto ptr = std::make_unique<Item>();

    useItem(ptr.get()); // примечание: Метод get() используется для получения указателя на Item

    std::cout << "Ending program\n";

    return 0;
} // Item уничтожается здесь, когда item2 выходит из области видимости
#endif

#ifdef Функция_move std::move()
#include <string>
#include <utility>

template<class T>
void swap(T& x, T& y)
{
    T tmp{ std::move(x) }; // вызывает конструктор перемещения
    x = std::move(y); // вызывает оператор присваивания перемещением
    y = std::move(tmp); // вызывает оператор присваивания перемещением
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

#ifdef Семантика_перемещения
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

    // Конструктор копирования, который выполняет глубокое копирование x.m_ptr в m_ptr
    Auto_ptr3(const Auto_ptr3& x)
    {
        m_ptr = new T;
        *m_ptr = *x.m_ptr;
    }

    // Конструктор перемещения, который передает право собственности на x.m_ptr в m_ptr
    Auto_ptr3(Auto_ptr3&& x)
        : m_ptr(x.m_ptr)
    {
        x.m_ptr = nullptr; // мы поговорим об этом чуть позже
    }

    // Оператор присваивания копированием, который выполняет глубокое копирование x.m_ptr в m_ptr
    Auto_ptr3& operator=(const Auto_ptr3& x)
    {
        // Проверка на самоприсваивание
        if (&x == this)
            return *this;

        // Удаляем всё, что к этому моменту может хранить указатель 
        delete m_ptr;

        // Копируем передаваемый объект
        m_ptr = new T;
        *m_ptr = *x.m_ptr;

        return *this;
    }

    // Оператор присваивания перемещением, который передает право собственности на x.m_ptr в m_ptr
    Auto_ptr3& operator=(Auto_ptr3&& x)
    {
        // Проверка на самоприсваивание
        if (&x == this)
            return *this;

        // Удаляем всё, что к этому моменту может хранить указатель 
        delete m_ptr;

        // Передаем право собственности на x.m_ptr в m_ptr
        m_ptr = x.m_ptr;
        x.m_ptr = nullptr; // мы поговорим об этом чуть позже

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
    return item; // это возвращаемое значение приведет к вызову конструктора копирования
}

int main()
{
    Auto_ptr3<Item> mainItem;
    mainItem = generateItem(); // эта операция присваивания приведет к вызову оператора присваивания копированием

    return 0;
}
#endif

#ifdef Семантика_перемещения_Устаревшая
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

    // Конструктор копирования, который реализовывает семантику перемещения
    Auto_ptr2(Auto_ptr2& a) // примечание: Ссылка не является константной
    {
        m_ptr = a.m_ptr; // перемещаем наш глупый указатель от источника к нашему локальному объекту
        a.m_ptr = nullptr; // подтверждаем, что источник больше не владеет указателем
    }

    // Оператор присваивания, который реализовывает семантику перемещения
    Auto_ptr2& operator=(Auto_ptr2& a) // примечание: Ссылка не является константной
    {
        if (&a == this)
            return *this;

        delete m_ptr; // подтверждаем, что удалили любой указатель, который наш локальный объект имел до этого
        m_ptr = a.m_ptr; // затем перемещаем наш глупый указатель из источника к нашему локальному объекту
        a.m_ptr = nullptr; // подтверждаем, что источник больше не владеет указателем
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
    Auto_ptr2<Item> item2; // начнем с nullptr

    std::cout << "item1 is " << (item1.isNull() ? "null\n" : "not null\n");
    std::cout << "item2 is " << (item2.isNull() ? "null\n" : "not null\n");

    item2 = item1; // item2 теперь является "владельцем" значения item1, объекту item1 присваивается null

    std::cout << "Ownership transferred\n";

    std::cout << "item1 is " << (item1.isNull() ? "null\n" : "not null\n");
    std::cout << "item2 is " << (item2.isNull() ? "null\n" : "not null\n");

    return 0;
}
#endif

#ifdef Умные_указатели
template<class T>
class Auto_ptr1
{
    T* m_ptr;
public:
    // Получаем указатель для "владения" через конструктор
    Auto_ptr1(T* ptr = nullptr)
        :m_ptr(ptr)
    {
    }

    // Деструктор позаботится об удалении указателя
    ~Auto_ptr1()
    {
        delete m_ptr;
    }

    // Выполняем перегрузку оператора разыменования и оператора ->, чтобы иметь возможность использовать Auto_ptr1 как m_ptr
    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
};

// Класс для проверки работоспособности вышеприведенного кода
class Item
{
public:
    Item() { std::cout << "Item acquired\n"; }
    ~Item() { std::cout << "Item destroyed\n"; }
    void sayHi() { std::cout << "Hi!\n"; }
};

void myFunction()
{
    Auto_ptr1<Item> ptr(new Item); // ptr теперь "владеет" Item-ом

    int a;
    std::cout << "Enter an integer: ";
    std::cin >> a;

    if (a == 0)
        return; // досрочный возврат функции

    // Использование ptr
    ptr->sayHi();
}

int main()
{
    myFunction();

    return 0;
}
#endif

#ifdef тест_try
#endif

#ifdef Функциональный_try_блок
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
    B(int x) try : A(x) // обратите внимание на ключевое слово try здесь
    {
    }
    catch (...) // обратите внимание, этот блок находится на том же уровне отступа, что и конструктор
    {
        // Исключения из списка инициализации членов класса B или тела конструктора обрабатываются здесь

        std::cerr << "Construction of A failed\n";

        // Если мы здесь не будем явно выбрасывать исключение, то текущее (пойманное) исключение будет повторно сгенерировано и отправлено в стек вызовов
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
