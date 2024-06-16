#include <iostream>
#define Типы_наследований

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