#include <iostream>
#define тест

#ifdef тест1 Виртуальные функции
#include <vector>
class Point
{
private:
    int m_x = 0;
    int m_y = 0;
    int m_z = 0;

public:
    Point(int x, int y, int z)
        : m_x(x), m_y(y), m_z(z)
    {

    }

    friend std::ostream& operator<<(std::ostream& out, const Point& p)
    {
        out << "Point(" << p.m_x << ", " << p.m_y << ", " << p.m_z << ")";
        return out;
    }
};
class Shape
{
public:
    Shape();
    virtual ~Shape();
    virtual std::ostream& print(std::ostream& out) const = 0;
    friend std::ostream& operator<<(std::ostream& out,const Shape& s) {
        return s.print(out);
    }
private:

};

Shape::Shape()
{
}

Shape::~Shape()
{
}
class Triangle :public Shape
{
public:
    Triangle(Point p1, Point p2, Point p3);
    ~Triangle();
    std::ostream& print(std::ostream& out) const override{
        out << "Triangle(" << p1<<", " << p2 << ", " << p3 << ")";
        return out;
    }
private:
    Point p1, p2, p3;
};

Triangle::Triangle(Point p1, Point p2, Point p3):p1(p1),p2(p2),p3(p3)
{
}

Triangle::~Triangle()
{
}
class Circle :public Shape
{
public:
    Circle(Point c, int r);
    ~Circle();
    std::ostream& print(std::ostream& out) const override {
        out << "Circle(" << c << ", radius " << r << ")";
        return out;
    }
    int getRadius() { return r; }
private:
    Point c;
    unsigned int r;
};

Circle::Circle(Point c, int r):c(c),r(r)
{

}

Circle::~Circle()
{
}
int getLargestRadius(const std::vector<Shape*>& v)
{
    int largestRadius{ 0 };

    // Перебираем каждый элемент вектора
    for (auto const& element : v)
    {
        // Выполняем проверку на нулевой указатель результата динамического приведения
        if (Circle* c = dynamic_cast<Circle*>(element))
        {
            if (c->getRadius() > largestRadius)
                largestRadius = c->getRadius();
        }
    }

    return largestRadius;
}
int main()
{
    Circle c(Point(1, 2, 3), 7);
    std::cout << c << '\n';

    Triangle t(Point(1, 2, 3), Point(4, 5, 6), Point(7, 8, 9));
    std::cout << t << '\n';

    std::vector<Shape*> v;
    v.push_back(new Circle(Point(1, 2, 3), 7));
    v.push_back(new Triangle(Point(1, 2, 3), Point(4, 5, 6), Point(7, 8, 9)));
    v.push_back(new Circle(Point(4, 5, 6), 3));

    // Вывод элементов вектора v здесь
    for (auto const& element : v)
        std::cout << *element << '\n';

    std::cout << "The largest radius is: " << getLargestRadius(v) << '\n'; // реализуйте эту функцию

// Удаление элементов вектора v здесь
    for (auto const& element : v)
        delete element;
    return 0;
}
#endif

#ifdef Динамическое_приведение dynamic_cast<_type>
#include <string>

class Parent
{
protected:
    int m_value;

public:
    Parent(int value)
        : m_value(value)
    {
    }

    virtual ~Parent() {}
};

class Child : public Parent
{
protected:
    std::string m_name;

public:
    Child(int value, std::string name)
        : Parent(value), m_name(name)
    {
    }

    const std::string& getName() { return m_name; }
};

Parent* getObject(bool bReturnChild)
{
    if (bReturnChild)
        return new Child(1, "Banana");
    else
        return new Parent(2);
}
int main()
{
    Parent* p = getObject(true);

    Child* ch = dynamic_cast<Child*>(p); // используем dynamic_cast для конвертации указателя класса Parent в указатель класса Child

    if (ch) // выполняем проверку ch на нулевой указатель
        std::cout << "The name of the Child is: " << ch->getName() << '\n';

    delete p;

    return 0;
}
#endif

#ifdef Обрезка std::reference_wrapper
#include <vector>
#include <functional> // для std::reference_wrapper
class Parent
{
protected:
    int m_value;

public:
    Parent(int value)
        : m_value(value)
    {
    }

    virtual const char* getName() const { return "Parent"; }
    int getValue() const { return m_value; }
};

class Child : public Parent
{
public:
    Child(int value)
        : Parent(value)
    {
    }

    virtual const char* getName() const { return "Child"; }
};
int main()
{
    std::vector<std::reference_wrapper<Parent> > v;
    Parent p(7); // p и ch не могут быть анонимными объектами
    Child ch(8);
    v.push_back(p); // добавляем объект класса Parent в наш вектор
    v.push_back(ch); // добавляем объект класса Child в наш вектор

    // Выводим все элементы нашего вектора
    for (int count = 0; count < v.size(); ++count)
        std::cout << "I am a " << v[count].get().getName() << " with value " << v[count].get().getValue() << "\n"; // используем .get() для получения элементов из std::reference_wrapper


    return 0;
}

#endif

#ifdef Алмаз_смерти Виртуальный базовый класс
class PoweredDevice
{
public:
    PoweredDevice(int power)
    {
        std::cout << "PoweredDevice: " << power << '\n';
    }
};

class Scanner : virtual public PoweredDevice // примечание: PoweredDevice теперь виртуальный базовый класс
{
public:
    Scanner(int scanner, int power)
        : PoweredDevice(power) // эта строка необходима для создания объектов класса Scanner, но в этой программе она игнорируется
    {
        std::cout << "Scanner: " << scanner << '\n';
    }
};

class Printer : virtual public PoweredDevice // примечание: PoweredDevice теперь виртуальный базовый класс
{
public:
    Printer(int printer, int power)
        : PoweredDevice(power) // эта строка необходима для создания объектов класса Printer, но в этой программе она игнорируется
    {
        std::cout << "Printer: " << printer << '\n';
    }
};

class Copier : public Scanner, public Printer
{
public:
    Copier(int scanner, int printer, int power)
        : Scanner(scanner, power), Printer(printer, power),
        PoweredDevice(power) // построение PoweredDevice выполняется здесь
    {
    }
};

int main()
{
    Copier copier(1, 2, 3);
}
#endif

#ifdef Чистые_Виртуальные функции
//Абстрактный класс может иметь переменные - члены и имеет как минимум одну чистую виртуальную функцию, 
//в то время как интерфейс не имеет переменных - членов, и все его методы должны быть чистыми виртуальными функциями.
#include <string>

class Animal // этот Animal является абстрактным родительским классом
{
protected:
    std::string m_name;

public:
    Animal(std::string name)
        : m_name(name)
    {
    }

    std::string getName() { return m_name; }
    virtual const char* speak() = 0; // обратите внимание, speak() является чистой виртуальной функцией
};
const char* Animal::speak()  // несмотря на то, что вот здесь находится её определение
{
    return "buzz";
}
class Dragonfly : public Animal
{

public:
    Dragonfly(std::string name)
        : Animal(name)
    {
    }

    virtual const char* speak() // этот класс уже не является абстрактным, так как мы переопределили функцию speak()
    {
        return Animal::speak(); // используется реализация по умолчанию класса Animal
    }
};
class Lion : public Animal
{
public:
    Lion(std::string name)
        : Animal(name)
    {
    }

    virtual const char* speak() { return "RAWRR!"; }
};

int main()
{
    Lion lion("John");
    std::cout << lion.getName() << " says " << lion.speak() << '\n';
    Dragonfly dfly("Barbara");
    std::cout << dfly.getName() << " says " << dfly.speak() << '\n';
}
#endif

#ifdef Виртуальные_таблицы
class Parent
{
public:
    //FunctionPointer* __vptr; // здесь скрытый указатель на главный родительский класс с виртуальными функциями
    virtual void function1() {};
    virtual void function2() {};
};

class C1 : public Parent
{
public:
    virtual void function1() {};
};

class C2 : public Parent
{
public:
    virtual void function2() {};
};
int main()
{
    C1 c1;
    Parent* cPtr = &c1; //здесь происходит позднее связывание виртуальных функций с виртуальной таблицей
    cPtr->function1();  //благодаря виртуальной таблице мы понимаем что этот метод из класса C1
}
#endif

#ifdef позднее_связывание (или «динамическая привязка»)
#include <iostream>

int add(int a, int b)
{
    return a + b;
}

int subtract(int a, int b)
{
    return a - b;
}

int multiply(int a, int b)
{
    return a * b;
}

int main()
{
    int a;
    std::cout << "Enter a number: ";
    std::cin >> a;

    int b;
    std::cout << "Enter another number: ";
    std::cin >> b;

    int op;
    do
    {
        std::cout << "Enter an operation (0 = add, 1 = subtract, 2 = multiply): ";
        std::cin >> op;
    } while (op < 0 || op > 2);

    // Создаем указатель на функцию с именем pFcn (согласен, синтаксис ужасен)
    int (*pFcn)(int, int) = nullptr;

    // Указываем pFcn указывать на функцию, которую выберет пользователь
    switch (op)
    {
    case 0: pFcn = add; break;
    case 1: pFcn = subtract; break;
    case 2: pFcn = multiply; break;
    }

    // Вызываем функцию, на которую указывает pFcn с параметрами a и b.
    // Используется позднее связывание
    std::cout << "The answer is: " << pFcn(a, b) << std::endl;

    return 0;
}
#endif

#ifdef Игнорирование виртуальных функций
class Parent
{
public:
    virtual const char* getName() { return "Parent"; }
};

class Child : public Parent
{
public:
    virtual const char* getName() { return "Child"; }
};
#include <iostream>

int main()
{
    Child child;
    Parent& parent = child;
    std::cout << parent.getName() << std::endl;
    // Вызов Parent::GetName() вместо переопределения Child::GetName()
    std::cout << parent.Parent::getName() << std::endl;
}
#endif

#ifdef Виртуальные_функции и Полиморфизм
#include <iostream>
#include <string>

class Animal
{
protected:
    std::string m_name;

    // Мы делаем этот конструктор protected так как не хотим, чтобы пользователи имели возможность создавать объекты класса Animal напрямую,
    // но хотим, чтобы в дочерних классах доступ был открыт
    Animal(std::string name)
        : m_name(name)
    {
    }

public:
    std::string getName() { return m_name; }
    virtual const char* speak() const { return "???"; }
};

class Cat : public Animal
{
public:
    Cat(std::string name)
        : Animal(name)
    {
    }

    virtual const char* speak() const override { return "Meow"; }
};

class Dog : public Animal
{
public:
    Dog(std::string name)
        : Animal(name)
    {
    }

    virtual const char* speak() const override final { return "Woof"; }
};

void report(Animal& animal)
{
    std::cout << animal.getName() << " says " << animal.speak() << '\n';
}

int main()
{
    Cat cat("Matros");
    Dog dog("Barsik");

    report(cat);
    report(dog);
}
#endif

#ifdef Переопределение_методов 
class Parent
{
protected:
    int m_value;

public:
    Parent(int value)
        : m_value(value)
    {
    }

    void identify() { std::cout << "I am a Parent!\n"; }
protected:
    void printValue() { std::cout << m_value; }
    int getValue() { return m_value; }
};
class Child : public Parent
{
public:
    Child(int value)
        : Parent(value)
    {
    }

    int GetValue() { return m_value; }
    int getValue() = delete; // делаем этот метод недоступным
    void identify()
    {
        Parent::identify(); // сначала выполняется вызов Parent::identify() 
        std::cout << "I am a Child!\n"; // затем уже вывод этого текста
    }
    // Parent::printValue является protected, поэтому доступ к нему не является открытым для всех объектов.
    // Но мы можем это исправить с помощью "using-объявления"
    using Parent::printValue; // обратите внимание, нет никаких скобок (без using тоже работает, считается устарешвим )
};

int main()
{
    Parent parent(6);
    parent.identify();

    Child child(8);
    child.identify();

    return 0;
}
#endif

#ifdef Типы_наследований
class Parent
{
public:
    int m_public;
private:
    int m_private;
protected:
    int m_protected;
};

// Открытое наследование
class Pub : public Parent
{
    // Открытое наследование означает, что:
// - унаследованные public-члены остаются public в дочернем классе;
// - унаследованные protected-члены остаются protected в дочернем классе;
// - унаследованные private-члены остаются недоступными в дочернем классе.
};

// Закрытое наследование
class Pri : private Parent
{
    // Закрытое наследование означает, что:
// - public-члены становятся private в дочернем классе;
// - protected-члены становятся private в дочернем классе;
// - private-члены недоступны для дочернего класса.
};

// Защищенное наследование
class Pro : protected Parent
{
    // Защищенное наследование означает, что:
// - public-члены становятся protected в дочернем классе;
// - protected-члены остаются protected в дочернем классе;
// - private-члены недоступны для дочернего класса.
};

class Def : Parent // по умолчанию язык C++ устанавливает закрытое наследование
{
};

int main()
{
}

#endif

#ifdef Наследование_Базовое1
#include <string>

class Fruit
{
private:
    std::string m_name;
    std::string m_color;

public:
    Fruit(std::string name, std::string color)
        : m_name(name), m_color(color)
    {
    }

    std::string getName() const { return m_name; }
    std::string getColor() const { return m_color; }

};

class Apple : public Fruit
{
private:
    double m_fiber;

public:
    Apple(std::string name, std::string color, double fiber)
        :Fruit(name, color), m_fiber(fiber)
    {
    }

    double getFiber() const { return m_fiber; }

    friend std::ostream& operator<<(std::ostream& out, const Apple& a)
    {
        out << "Apple (" << a.getName() << ", " << a.getColor() << ", " << a.getFiber() << ")\n";
        return out;
    }
};

class Banana : public Fruit
{
public:
    Banana(std::string name, std::string color)
        :Fruit(name, color)
    {
    }

    friend std::ostream& operator<<(std::ostream& out, const Banana& b)
    {
        out << "Banana (" << b.getName() << ", " << b.getColor() << ")\n";
        return out;
    }

};

int main()
{
    const Apple a("Red delicious", "red", 7.3);
    std::cout << a;

    const Banana b("Cavendish", "yellow");
    std::cout << b;

    return 0;
}
#endif

#ifdef Наследование_Базовое
#include <string>
class Human
{
public:
    std::string m_name;
    int m_age;

    Human(std::string name = "", int age = 0)
        : m_name(name), m_age(age)
    {
    }

    std::string getName() const { return m_name; }
    int getAge() const { return m_age; }

};

// BasketballPlayer открыто наследует Human
class BasketballPlayer : public Human
{
public:
    double m_gameAverage;
    int m_points;

    BasketballPlayer(std::string name = "", int age = 0,
        double gameAverage = 0.0, int points = 0)
        : Human(name, age), // вызывается Human(std::string, int) для инициализации членов name и age
        m_gameAverage(gameAverage), m_points(points)
    {
    }

    double getGameAverage() const { return m_gameAverage; }
    int getPoints() const { return m_points; }
};

// Employee открыто наследует Human
class Employee : public Human
{
public:
    int m_wage;
    long m_employeeID;

    Employee(int wage = 0, long employeeID = 0)
        : m_wage(wage), m_employeeID(employeeID)
    {
    }

    void printNameAndWage() const
    {
        std::cout << m_name << ": " << m_wage << '\n';
    }
};

class Supervisor : public Employee
{
public:
    // Этот Супервайзер может наблюдать максимум за 5-тью Работниками
    long m_nOverseesIDs[5];

    Supervisor()
    {
    }

};

int main()
{
    BasketballPlayer anton1("Anton Ivanovuch", 45, 300, 310);

    std::cout << anton1.getName() << '\n';
    std::cout << anton1.getAge() << '\n';
    std::cout << anton1.getPoints() << '\n';

    // Создаем нового Баскетболиста
    BasketballPlayer anton;
    // Присваиваем ему имя (мы можем делать это напрямую, так как m_name является public)
    anton.m_name = "Anton";
    // Выводим имя Баскетболиста
    std::cout << anton.getName() << '\n'; // используем метод getName(), который мы унаследовали от класса Human

    Employee ivan(350, 787);
    ivan.m_name = "Ivan"; // мы можем это сделать, так как m_name является public

    ivan.printNameAndWage();

    return 0;
}

#endif