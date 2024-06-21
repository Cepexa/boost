#include <iostream>
#define ����

#ifdef ����1 ����������� �������
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

    // ���������� ������ ������� �������
    for (auto const& element : v)
    {
        // ��������� �������� �� ������� ��������� ���������� ������������� ����������
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

    // ����� ��������� ������� v �����
    for (auto const& element : v)
        std::cout << *element << '\n';

    std::cout << "The largest radius is: " << getLargestRadius(v) << '\n'; // ���������� ��� �������

// �������� ��������� ������� v �����
    for (auto const& element : v)
        delete element;
    return 0;
}
#endif

#ifdef ������������_���������� dynamic_cast<_type>
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

    Child* ch = dynamic_cast<Child*>(p); // ���������� dynamic_cast ��� ����������� ��������� ������ Parent � ��������� ������ Child

    if (ch) // ��������� �������� ch �� ������� ���������
        std::cout << "The name of the Child is: " << ch->getName() << '\n';

    delete p;

    return 0;
}
#endif

#ifdef ������� std::reference_wrapper
#include <vector>
#include <functional> // ��� std::reference_wrapper
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
    Parent p(7); // p � ch �� ����� ���� ���������� ���������
    Child ch(8);
    v.push_back(p); // ��������� ������ ������ Parent � ��� ������
    v.push_back(ch); // ��������� ������ ������ Child � ��� ������

    // ������� ��� �������� ������ �������
    for (int count = 0; count < v.size(); ++count)
        std::cout << "I am a " << v[count].get().getName() << " with value " << v[count].get().getValue() << "\n"; // ���������� .get() ��� ��������� ��������� �� std::reference_wrapper


    return 0;
}

#endif

#ifdef �����_������ ����������� ������� �����
class PoweredDevice
{
public:
    PoweredDevice(int power)
    {
        std::cout << "PoweredDevice: " << power << '\n';
    }
};

class Scanner : virtual public PoweredDevice // ����������: PoweredDevice ������ ����������� ������� �����
{
public:
    Scanner(int scanner, int power)
        : PoweredDevice(power) // ��� ������ ���������� ��� �������� �������� ������ Scanner, �� � ���� ��������� ��� ������������
    {
        std::cout << "Scanner: " << scanner << '\n';
    }
};

class Printer : virtual public PoweredDevice // ����������: PoweredDevice ������ ����������� ������� �����
{
public:
    Printer(int printer, int power)
        : PoweredDevice(power) // ��� ������ ���������� ��� �������� �������� ������ Printer, �� � ���� ��������� ��� ������������
    {
        std::cout << "Printer: " << printer << '\n';
    }
};

class Copier : public Scanner, public Printer
{
public:
    Copier(int scanner, int printer, int power)
        : Scanner(scanner, power), Printer(printer, power),
        PoweredDevice(power) // ���������� PoweredDevice ����������� �����
    {
    }
};

int main()
{
    Copier copier(1, 2, 3);
}
#endif

#ifdef ������_����������� �������
//����������� ����� ����� ����� ���������� - ����� � ����� ��� ������� ���� ������ ����������� �������, 
//� �� ����� ��� ��������� �� ����� ���������� - ������, � ��� ��� ������ ������ ���� ������� ������������ ���������.
#include <string>

class Animal // ���� Animal �������� ����������� ������������ �������
{
protected:
    std::string m_name;

public:
    Animal(std::string name)
        : m_name(name)
    {
    }

    std::string getName() { return m_name; }
    virtual const char* speak() = 0; // �������� ��������, speak() �������� ������ ����������� ��������
};
const char* Animal::speak()  // �������� �� ��, ��� ��� ����� ��������� � �����������
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

    virtual const char* speak() // ���� ����� ��� �� �������� �����������, ��� ��� �� �������������� ������� speak()
    {
        return Animal::speak(); // ������������ ���������� �� ��������� ������ Animal
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

#ifdef �����������_�������
class Parent
{
public:
    //FunctionPointer* __vptr; // ����� ������� ��������� �� ������� ������������ ����� � ������������ ���������
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
    Parent* cPtr = &c1; //����� ���������� ������� ���������� ����������� ������� � ����������� ��������
    cPtr->function1();  //��������� ����������� ������� �� �������� ��� ���� ����� �� ������ C1
}
#endif

#ifdef �������_���������� (��� ������������� ��������)
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

    // ������� ��������� �� ������� � ������ pFcn (��������, ��������� ������)
    int (*pFcn)(int, int) = nullptr;

    // ��������� pFcn ��������� �� �������, ������� ������� ������������
    switch (op)
    {
    case 0: pFcn = add; break;
    case 1: pFcn = subtract; break;
    case 2: pFcn = multiply; break;
    }

    // �������� �������, �� ������� ��������� pFcn � ����������� a � b.
    // ������������ ������� ����������
    std::cout << "The answer is: " << pFcn(a, b) << std::endl;

    return 0;
}
#endif

#ifdef ������������� ����������� �������
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
    // ����� Parent::GetName() ������ ��������������� Child::GetName()
    std::cout << parent.Parent::getName() << std::endl;
}
#endif

#ifdef �����������_������� � �����������
#include <iostream>
#include <string>

class Animal
{
protected:
    std::string m_name;

    // �� ������ ���� ����������� protected ��� ��� �� �����, ����� ������������ ����� ����������� ��������� ������� ������ Animal ��������,
    // �� �����, ����� � �������� ������� ������ ��� ������
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

#ifdef ���������������_������� 
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
    int getValue() = delete; // ������ ���� ����� �����������
    void identify()
    {
        Parent::identify(); // ������� ����������� ����� Parent::identify() 
        std::cout << "I am a Child!\n"; // ����� ��� ����� ����� ������
    }
    // Parent::printValue �������� protected, ������� ������ � ���� �� �������� �������� ��� ���� ��������.
    // �� �� ����� ��� ��������� � ������� "using-����������"
    using Parent::printValue; // �������� ��������, ��� ������� ������ (��� using ���� ��������, ��������� ���������� )
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

#ifdef ����_������������
class Parent
{
public:
    int m_public;
private:
    int m_private;
protected:
    int m_protected;
};

// �������� ������������
class Pub : public Parent
{
    // �������� ������������ ��������, ���:
// - �������������� public-����� �������� public � �������� ������;
// - �������������� protected-����� �������� protected � �������� ������;
// - �������������� private-����� �������� ������������ � �������� ������.
};

// �������� ������������
class Pri : private Parent
{
    // �������� ������������ ��������, ���:
// - public-����� ���������� private � �������� ������;
// - protected-����� ���������� private � �������� ������;
// - private-����� ���������� ��� ��������� ������.
};

// ���������� ������������
class Pro : protected Parent
{
    // ���������� ������������ ��������, ���:
// - public-����� ���������� protected � �������� ������;
// - protected-����� �������� protected � �������� ������;
// - private-����� ���������� ��� ��������� ������.
};

class Def : Parent // �� ��������� ���� C++ ������������� �������� ������������
{
};

int main()
{
}

#endif

#ifdef ������������_�������1
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

#ifdef ������������_�������
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

// BasketballPlayer ������� ��������� Human
class BasketballPlayer : public Human
{
public:
    double m_gameAverage;
    int m_points;

    BasketballPlayer(std::string name = "", int age = 0,
        double gameAverage = 0.0, int points = 0)
        : Human(name, age), // ���������� Human(std::string, int) ��� ������������� ������ name � age
        m_gameAverage(gameAverage), m_points(points)
    {
    }

    double getGameAverage() const { return m_gameAverage; }
    int getPoints() const { return m_points; }
};

// Employee ������� ��������� Human
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
    // ���� ����������� ����� ��������� �������� �� 5-��� �����������
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

    // ������� ������ �������������
    BasketballPlayer anton;
    // ����������� ��� ��� (�� ����� ������ ��� ��������, ��� ��� m_name �������� public)
    anton.m_name = "Anton";
    // ������� ��� �������������
    std::cout << anton.getName() << '\n'; // ���������� ����� getName(), ������� �� ������������ �� ������ Human

    Employee ivan(350, 787);
    ivan.m_name = "Ivan"; // �� ����� ��� �������, ��� ��� m_name �������� public

    ivan.printNameAndWage();

    return 0;
}

#endif