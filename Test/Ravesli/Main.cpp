#include <iostream>
#define DEBUG1

#ifdef DEBUG
int returnByValue()
{
    return 7;
}

int& returnByReference()
{
    static int y = 7; // static ����������� ��, ��� ���������� y �� �����������, ����� ������ �� ��������� ������� ���������
    return y;
}

int main1()
{
    int value = returnByReference(); // ������ A: �� ������, �������������� ��� ������� �� ��������
    const int& ref = returnByValue(); // ������ B: ������ �����������, ��� ��� 7 - ��� r-value, � r-value �� ����� ���� ��������� � ������������� ������
    const int& cref = returnByValue(); // ������ C: �� ������, ����� ����� ������������� �������� ������������ � ������������ �� �������� ����� cref
    return 1;
}
#endif

#ifdef �������
#include <chrono> // ��� ������� �� std::chrono
#include <iostream>
#include <array>
#include <chrono> // ��� ������� �� std::chrono
#include <algorithm> // ��� std::sort()

const int g_arrayElements = 10000; // ����� ���������� ���� ��������� �������

class Timer
{
private:
    // ���������� ����� ������������ ��� �������� ������� � ��������� �����
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1> >;

    std::chrono::time_point<clock_t> m_beg;

public:
    Timer() : m_beg(clock_t::now())
    {
    }

    void reset()
    {
        m_beg = clock_t::now();
    }

    double elapsed() const
    {
        return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
    }
};

void sortArray(std::array<int, g_arrayElements>& array)
{

    // ���������� ������ ������� ������� (����� ����������, �� ��� ����� ������������ � ���� �������, ����� �� �� ���� ���������)
    for (int startIndex = 0; startIndex < g_arrayElements - 1; ++startIndex)
    {
        // � ���������� smallestIndex �������� ������ ����������� ��������, ������� �� ����� � ���� ��������.
        // ������ � ����, ��� ���������� ������� � ���� �������� - ��� ������ ������� (������ 0)
        int smallestIndex = startIndex;

        // ����� ���� ������� ������ ������ smallestIndex � ���������� ����� �������
        for (int currentIndex = startIndex + 1; currentIndex < g_arrayElements; ++currentIndex)
        {
            // ���� ����� �������, ������� ������ ������ ����������� ��������,
            if (array[currentIndex] < array[smallestIndex])
                // �� ����������/���������� ���
                smallestIndex = currentIndex;
        }

        // smallestIndex ������ ���������� ������� � ���������� ����� �������.
        // ������ ������� ���� ��������� ���������� �������� � ���, ������� �� ����������
        std::swap(array[startIndex], array[smallestIndex]);
    }
}

int main1()
{
    std::array<int, g_arrayElements> array;
    for (int i = 0; i < g_arrayElements; ++i)
        array[i] = g_arrayElements - i;

    Timer t;

    std::sort(array.begin(), array.end());
    //sortArray(array);

    std::cout << "Time taken: " << t.elapsed() << '\n';

    return 0;
}
#endif

#ifdef ���������_����
#include <iostream>

class Fruit
{
public:
    // �� ����������� FruitList ������ ������ ��� ������������ ������� public
    enum FruitList
    {
        AVOCADO,
        BLACKBERRY,
        LEMON
    };

private:
    FruitList m_type;

public:

    Fruit(FruitList type) :
        m_type(type)
    {
    }
    FruitList getType() { return m_type; }
};

int main1()
{
    // ������ � FruitList �������������� ����� Fruit
    Fruit avocado(Fruit::AVOCADO);
    if (avocado.getType() == Fruit::AVOCADO)
        std::cout << "I am an avocado!";
    else
        std::cout << "I am not an avocado!";
    return 0;
}
#endif

#ifdef �������������_�����
#include <iostream>

class Values
{
private:
    int m_intValue;
    double m_dValue;
public:
    Values(int intValue, double dValue)
    {
        m_intValue = intValue;
        m_dValue = dValue;
    }

    // ������ ����� Display ������ ������ Values
    friend class Display;
};

class Display
{
private:
    bool m_displayIntFirst;

public:
    Display(bool displayIntFirst) { m_displayIntFirst = displayIntFirst; }

    void displayItem(Values& value)
    {
        if (m_displayIntFirst)
            std::cout << value.m_intValue << " " << value.m_dValue << '\n';
        else // ��� ������� ������� double
            std::cout << value.m_dValue << " " << value.m_intValue << '\n';
    }
};

int main1()
{
    Values value(7, 8.4);
    Display display(false);

    display.displayItem(value);

    return 0;
}
#endif

#ifdef �������������_������
#include <iostream>

class Values; // ��������������� ���������� ������ Values

class Display
{
private:
    bool m_displayIntFirst;

public:
    Display(bool displayIntFirst) { m_displayIntFirst = displayIntFirst; }

    void displayItem(Values& value); // ��������������� ����������, ����������� ����, ��������� ��� ���� ������
};

class Values // ������ ����������� ������ Values
{
private:
    int m_intValue;
    double m_dValue;
public:
    Values(int intValue, double dValue)
    {
        m_intValue = intValue;
        m_dValue = dValue;
    }

    // ������ ����� Display::displayItem() ������ ������ Values
    friend void Display::displayItem(Values& value);
};

// ������ �� ����� ���������� ����� Display::displayItem(), �������� ��������� ������� ������ ����������� ������ Values
void Display::displayItem(Values& value)
{
    if (m_displayIntFirst)
        std::cout << value.m_intValue << " " << value.m_dValue << '\n';
    else // ��� ������� ������� double
        std::cout << value.m_dValue << " " << value.m_intValue << '\n';
}

int main1()
{
    Values value(7, 8.4);
    Display display(false);

    display.displayItem(value);

    return 0;
}
#endif

#ifdef �������������_�������
#include <iostream>

class Humidity;

class Temperature
{
private:
    int m_temp;
public:
    Temperature(int temp = 0) { m_temp = temp; }

    friend void outWeather(const Temperature& temperature, const Humidity& humidity);
};

class Humidity
{
private:
    int m_humidity;
public:
    Humidity(int humidity = 0) { m_humidity = humidity; }

    friend void outWeather(const Temperature& temperature, const Humidity& humidity);
};

void outWeather(const Temperature& temperature, const Humidity& humidity)
{
    std::cout << "The temperature is " << temperature.m_temp <<
        " and the humidity is " << humidity.m_humidity << '\n';
}

int main1()
{
    Temperature temp(15);
    Humidity hum(11);

    outWeather(temp, hum);

    return 0;
}
#endif

#ifdef �����������_������
#include <iostream>

class IDGenerator
{
private:
    static int s_nextID; // ���������� ����������� ����������-�����

public:
    static int getNextID(); // ���������� ������������ ������
};

// ����������� ����������� ����������-����� ��������� ��� ���� ������. �������� ��������, �� �� ���������� ����� �������� ����� static.
// �������� ������������ ID � 1
int IDGenerator::s_nextID = 1;

// ����������� ������������ ������ ��������� ��� ���� ������. �������� ��������, �� �� ���������� ����� �������� ����� static
int IDGenerator::getNextID() { return s_nextID++; }

int main1()
{
    for (int count = 0; count < 4; ++count)
        std::cout << "The next ID is: " << IDGenerator::getNextID() << '\n';

    return 0;
}
#endif

#ifdef �����������_����������_����� ������
#include <iostream>

class Anything
{
private:
    static int s_idGenerator;
    int m_id;

public:
    Anything() { m_id = s_idGenerator++; } // ����������� �������� �������������� ��� ���������� �������

    int getID() const { return m_id; }
};

// �� ���������� � �������������� s_idGenerator �������� �� ��, ��� �� �������� ��� private.
// ��� ���������, ��������� ����������� �� ��������� ��� �������� �������������� �������
int Anything::s_idGenerator = 1; // �������� ��� ID-��������� �� �������� 1

int main1()
{
    Anything first;
    Anything second;
    Anything third;

    std::cout << first.getID() << '\n';
    std::cout << second.getID() << '\n';
    std::cout << third.getID() << '\n';
    return 0;
}
#endif

#ifdef �����������_������_�������
class Anything
{
public:
    int m_value;

    Anything() { m_value = 0; }

    void resetValue() { m_value = 0; }
    void setValue(int value) { m_value = value; }

    const int& getValue() const; // �������� �������� �� �������� ����� const �����
    int& getValue(); 
};
const int& Anything::getValue() const // � �����
{
    return m_value;
}
int& Anything::getValue()
{
    return m_value;
}
int main1()
{
    const Anything anything; // �������� ����������� �� ���������

    //anything.m_value = 7; // ������ ����������: ��������� const
    //anything.setValue(7); // ������ ����������: ��������� const
    std::cout << anything.getValue();
    return 0;
}
#endif

#ifdef ������_�������� �� ������
class Mathem
{
private:
    int m_value = 0;

public:
    Mathem(int value = 0);

    Mathem& add(int value);
    Mathem& sub(int value);
    Mathem& divide(int value);

    int getValue() { return m_value; }
};

Mathem::Mathem(int value) : m_value(value)
{
}

Mathem& Mathem::add(int value)
{
    m_value += value;
    return *this;
}

Mathem& Mathem::sub(int value)
{
    m_value -= value;
    return *this;
}

Mathem& Mathem::divide(int value)
{
    m_value /= value;
    return *this;
}
#endif

#ifdef ������������ ������������
#include <iostream> 
#include <string>

class Employee
{
private:
    int m_id;
    std::string m_name;

public:
    Employee(int id = 0, const std::string& name = "") :
        m_id(id), m_name(name)
    {
        std::cout << "Employee " << m_name << " created.\n";
    }

    // ���������� ������������ ������������ ��� ���������� �������������� ����
    Employee(const std::string& name) : Employee(0, name) { }
};

int main1()
{
    Employee a;
    Employee b("Ivan");

    return 0;
}
#endif

#ifdef ������_�������������
#include <iostream>
class A
{
public:
    A(int a) { std::cout << "A " << a << "\n"; }
};
class Values
{
private:
    int m_value1;
    double m_value2;
    char m_value3{ 'c' };
    const int m_array[7];
    A m_a;
public:
    Values(int value1, double value2, char value3 = 's' , int b = 2)
        : m_value1(value1), m_value2(value2), m_value3{ value3 }, // �������� �������������� ����������-����� ������
        m_array{ 3, 4, 5, 6, 7, 8, 9 }, // ���������� uniform-������������� ��� ������������� �������
        m_a(b - 1)
    {
        // ��� ������������� ������������ ������������
    }

    void print()
    {
        std::cout << "Values(" << m_value1 << ", " << m_value2 << ", " << m_value3 << ")\n";
    }

};
int main1()
{
    Values value(3, 4.5); // value1 = 3, value2 = 4.5, value3 = 'd' (�������� �� ���������)
    value.print();
    return 0;
}
#endif

#ifdef Stack_OOP
#include <iostream>
#include <cassert>

class Fraction
{
private:
    int m_numerator;
    int m_denominator;

public:
    // ����������� �� ���������
    Fraction(int numerator = 0, int denominator = 1)
    {
        assert(denominator != 0);
        m_numerator = numerator;
        m_denominator = denominator;
    }

    int getNumerator() { return m_numerator; }
    int getDenominator() { return m_denominator; }
    double getValue() { return static_cast<double>(m_numerator) / m_denominator; }
};

class Stack
{
private:
    int m_array[10]; // ��� ����� ������ ������ ����� 
    int m_next; // ��� ����� �������� ���������� ���������� �������� �����

public:

    void reset()
    {
        m_next = 0;
        for (int i = 0; i < 10; ++i)
            m_array[i] = 0;
    }

    bool push(int value)
    {
        // ���� ���� ��� ��������, �� ���������� false
        if (m_next == 10)
            return false;

        m_array[m_next++] = value; // ����������� ���������� ���������� �������� �������� value, � ����� ����������� m_next
        return true;
    }

    int pop()
    {
        // ���� ��������� � ����� ���, �� ������� ��������� assert
        assert(m_next > 0);

        // m_next ��������� �� ��������� ��������� �������, ������� ��������� ������� �� ��������� - ��� m_next-1.
        // �� ����� ������� ���������:
        // int val = m_array[m_next-1]; // �������� ��������� ������� �� ���������
        // --m_next; // m_next ������ �� ������� ������, ��� ��� �� ������ ��� �������� ������� ������� �����
        // return val; // ���������� �������
        // ���� ��������������� ��� ����� �������� ��������� (�����) ������� ����
        return m_array[--m_next];
    }

    void print()
    {
        std::cout << "( ";
        for (int i = 0; i < m_next; ++i)
            std::cout << m_array[i] << ' ';
        std::cout << ")\n";
    }
};

int main1()
{
    Stack stack;
    stack.reset();

    stack.print();

    stack.push(3);
    stack.push(7);
    stack.push(5);
    stack.print();

    stack.pop();
    stack.print();

    stack.pop();
    stack.pop();

    stack.print();
    Fraction drob; // ����� Fraction(0, 1)
    Fraction seven(7); // ����� Fraction(7, 1)
    Fraction sixTwo(6, 2); // ����� Fraction(6, 2)
    return 0;
    }
#endif

#ifdef �������� �����
// array - ��� ������, � ������� �� �������� ������.
// target - ��� ������� ��������.
// min - ��� ������ ����������� ������� �������, � ������� �� ������������ �����.
// max - ��� ������ ������������ ������� �������, � ������� �� ������������ �����.
// ������� binarySearch() ������ ���������� ������ �������� ��������, ���� �� ���������. � ��������� ������, ���������� -1
int binarySearch(int* array, int target, int min, int max)
{
    while (min <= max)
    {
        // ����������� ����������
        int midpoint = min + ((max - min) / 2); // ����� ������ ���������� �������� ������� �������� ����������� ������������� ������������

        if (array[midpoint] > target)
        {
            // ���� array[midpoint] > target, �� ����� ��������, ��� ������� ����� �� ��������� � ������ �������� �������.
            // �� ����� ������������ midpoint - 1 � �������� ������� ������������ �������, ��� ��� � ��������� �������� ���� ������ ��������� �� �����
            max = midpoint - 1;
        }
        else if (array[midpoint] < target)
        {
            // ���� array[midpoint] < target, �� ����� ��������, ��� ������� ����� �� ��������� � ����� �������� �������.
            // �� ����� ������������ midpoint + 1 � �������� ������� ����������� �������, ��� ��� � ��������� �������� ���� ������ ��������� �� �����
            min = midpoint + 1;
        }
        else
            return midpoint;
    }

    return -1;
}
int main1()
{
    int array[] = { 4, 7, 9, 13, 15, 19, 22, 24, 28, 33, 37, 41, 43, 47, 50 };

    std::cout << "Enter a number: ";
    int x;
    std::cin >> x;

    int index = binarySearch(array, x, 0, 14);

    if (array[index] == x)
        std::cout << "Good! Your value " << x << " is on position " << index << " in array!\n";
    else
        std::cout << "Fail! Your value " << x << " isn't in array!\n";
    return 0;
}
#endif

#ifdef ��������3 ������-�������
#include <iostream>
#include <string>
#include <cstdarg> // ��������� ��� ������������� ���������

// �������� ������ ���� ��������� ���������� 
double findAverage(std::string decoder, ...)
{
    double sum = 0;

    // �� �������� ������ � ��������� ����� va_list, ������� ��������� ���������� ����� ����
    va_list list;

    // �������������� va_list, ��������� va_start. ������ �������� - ��� ������, ������� ���������� ����������������.
    // ������ �������� - ��� ��������� ��������, ������� �� �������� ����������
    va_start(list, decoder);

    int count = 0;
    // ����������� ����
    while (1)
    {
        char codetype = decoder[count];
        switch (codetype)
        {
        default:
        case '\0':
            // ��������� ������� va_list, ����� ��� ������� �� �����������
            va_end(list);
            return sum / count;

        case 'i':
            sum += va_arg(list, int);
            count++;
            break;

        case 'd':
            sum += va_arg(list, double);
            count++;
            break;
        }
    }
}

int main1()
{
    std::cout << findAverage("iiii", 1, 2, 3, 4) << '\n';
    std::cout << findAverage("iiiii", 1, 2, 3, 4, 5) << '\n';
    std::cout << findAverage("ididdi", 1, 2.2, 3, 3.5, 4.5, 5) << '\n';
    return 0;
}
#endif

#ifdef ��������2 ����������� ��������
#include <iostream>
#include <cstdarg> // ��������� ��� ������������� ��������� 

// �������� ������ ���� ��������� ����������
double findAverage(int first, ...)
{
    // ��������� ������� ��������
    double sum = first;

    // �� �������� ������ � ��������� ����� va_list, ������� ��������� ���������� ����� ����
    va_list list;

    // �������������� va_list, ��������� va_start. ������ �������� - ��� ������, ������� ����� ����������������.
    // ������ �������� - ��� ��������� ��������, ������� �� �������� ����������
    va_start(list, first);

    int count = 1;
    // ����������� ����
    while (1)
    {
        // ���������� va_arg ��� ��������� ���������� �� ���������.
        // ������ �������� - ��� va_list, ������� �� ����������.
        // ������ �������� - ��� ��������� ��� ����������
        int arg = va_arg(list, int);

        // ���� ������� �������� �������� ����������� ���������, �� ���������� ���������� �����
        if (arg == -1)
            break;

        sum += arg;
        count++;
    }

    // ��������� ������� va_list, ����� ��� ������� �� �����������
    va_end(list);

    return sum / count;
}

int main1()
{
    std::cout << findAverage(1, 2, 3, 4, -1) << '\n';
    std::cout << findAverage(1, 2, 3, 4, 5, -1) << '\n';
    return 0;
}
#endif

#ifdef �������� ...
#include <iostream>
#include <cstdarg> // ��������� ��� ������������� ���������

// �������� ������ ���� ��������� ����������.
// ���������� count - ��� ���������� ���������� ����������
double findAverage(int count, ...)
{
    double sum = 0;

    // �� �������� ������ � ��������� ����� va_list, ������� ��������� ���������� ����� ����
    va_list list;

    // �������������� va_list, ��������� va_start. ������ �������� - ��� ������, ������� ����� ����������������.
    // ������ �������� - ��� ��������� ��������, ������� �� �������� ����������
    va_start(list, count);

    // ���������� ������ �� ���������� ��������� 
    for (int arg = 0; arg < count; ++arg)
        // ���������� va_arg ��� ��������� ���������� �� ���������.
        // ������ �������� - ��� va_list, ������� �� ����������.
        // ������ �������� - ��� ��������� ��� ����������
        sum += va_arg(list, int);

    // ��������� ������� va_list, ����� ��� ������� �� ����������� 
    va_end(list);

    return sum / count;
}

int main1()
{
    std::cout << findAverage(4, 1, 2, 3, 4) << '\n';
    std::cout << findAverage(5, 1, 2, 3, 4, 5) << '\n';
    return 0;
}
#endif

#ifdef ���������_��������_����������
#include <iostream>
#include <string>
#include <sstream> // ��� std::stringstream
#include <cstdlib> // ��� exit()

int main(int argc, char* argv[])
{
    if (argc <= 1)
    {
        // � ��������� ������������ �������� argv[0] ����� ���� ������ ������ �������, ��� ����� ���������

        // ������������ ������, ����� argv[0] ����� ���� ������ ��� �� ������
        if (argv[0])
            std::cout << "Usage: " << argv[0] << " <number>" << '\n';
        else
            std::cout << "Usage: <program name> <number>" << '\n';

        exit(1);
    }

    std::stringstream convert(argv[1]); // ������� ���������� stringstream � ������ convert, ������������� � ��������� argv[1]

    int myint;
    if (!(convert >> myint)) // ��������� �����������
        myint = 0; // ���� ����������� ������ �������, �� ����������� myint �������� �� ���������

    std::cout << "Got integer: " << myint << '\n';

    return 0;
}
#endif

#ifdef static_assert_
#include <cassert> // ��� assert()
#include <array>
int getArrayValue(const std::array<int, 10>& array, int index)
{
    // ��������������, ��� �������� index-� ��������� ����� 0 � 8
    assert(index >= 0 && index <= 8); // ��� ������ 6 � Program.cpp

    return array[index];
}
static_assert(sizeof(int) == 4, "int must be 4 bytes");
static_assert(sizeof(long) == 4, "long must be 4 bytes");
int main1()
{
    std::array<int,10> myarray{ 8, 4, 2, 7, 1 };
    getArrayValue(myarray, 10);
    return 0;
}
#endif

#ifdef cerr_
void printString(const char* cstring)
{
    // ������� cstring ��� �������, ��� �� �� �������
    if (cstring)
        std::cout << cstring;
    else
        std::cerr << "function printString() received a null parameter";
}
int main1()
{
    printString("Hello world!");
    std::cout << std::endl;
    printString(nullptr);
    return 0;
}
#endif

#ifdef ��������_������� � �������� ����������
#include <iostream> 
#include <utility>
#include <functional>
//typedef bool (*validateFcn)(int, int);
using validateFcn = std::function<bool(int, int)>;
// ��� ������� ���������, ������� ��������� ���������� � ������� ����������� (�������� ��������, ��� �� �� ������� ascending(), ��� � � �������, ����������� ����)
bool ascending(int a, int b)
{
    return a > b; // ������ �������, ���� ������ ������� ������ �������
}

// ��� ������� ���������, ������� ��������� ���������� � ������� ��������
bool descending(int a, int b)
{
    return a < b; // ������ �������, ���� ������ ������� ������ �������
}
// �������� ��������, ������� ���������� �������� ���������������� ����� ���������� ����������
void selectionSort(int* array, int size, validateFcn pfcn = ascending)
{
    // ���������� ������ ������� �������
    for (int startIndex = 0; startIndex < size; ++startIndex)
    {
        // bestIndex - ��� ������ �����������/����������� ��������, ������� �� ���������� �� ����� �������
        int bestIndex = startIndex;

        // ���� ����������/���������� ������� ����� ���������� � ������� (�������� �� startIndex+1)
        for (int currentIndex = startIndex + 1; currentIndex < size; ++currentIndex)
        {
            // ���� ������� ������� ������/������ ������ ����������� ���������� �����������/����������� ��������,
            if (pfcn(array[bestIndex], array[currentIndex])) // ��������� ����������� �����
                // �� ��� ��� ����� ����������/���������� ������� � ���� ��������
                bestIndex = currentIndex;
        }

        // ������ ������� ��� ��������� ������� � ��������� ����������/���������� ���������
        std::swap(array[startIndex], array[bestIndex]);
    }
}

// ��� ������� ������� �������� �������
void printArray(int* array, int size)
{
    for (int index = 0; index < size; ++index)
        std::cout << array[index] << " ";
    std::cout << '\n';
}

int main1()
{
    int array[8] = { 4, 8, 5, 6, 2, 3, 1, 7 };

    // ��������� ������ � ������� ��������, ��������� ������� descending()
    selectionSort(array, 8, descending);
    printArray(array, 8);

    // ��������� ������ � ������� �����������, ��������� ������� ascending()
    selectionSort(array, 8);
    printArray(array, 8);

    return 0;
}
#endif

#ifdef ���������_��_�������
/*
// ��������� �������
int boo();
double doo();
int moo(int a);
// ������������ �������� ���������� �� �������
int (*fcnPtr1)() = boo; // ��
int (*fcnPtr2)() = doo; // �� ��: ��� ��������� � ��� �������� ������� �� ���������!
double (*fcnPtr4)() = doo; // ��
fcnPtr1 = moo; // �� ��: fcnPtr1 �� ����� ����������, �� moo() �����
int (*fcnPtr3)(int) = moo; // ��
*/
int boo()
{
    return 7;
}

int doo()
{
    return 8;
}

int main1()
{
    int (*fcnPtr)() = boo; // fcnPtr ��������� �� ������� boo()
    fcnPtr = doo; // fcnPtr ������ ��������� �� ������� doo()

    return 0;
}
#endif

#ifdef inline_f 
#include <iostream>

inline int constexpr max(int a, int b) noexcept
{
    return a < b ? b : a;
}
int main1()
{
    std::cout << max(7, 8) << '\n';
    std::cout << max(5, 4) << '\n';
    return 0;
}
#endif

#ifdef �������_��������
#include <iostream> 
#include <array>

// ���������� ������ �� ������� ������� �� ������� index
int& getElement(std::array<int, 20>& array, int index)
{
    // �� �����, ��� array[index] �� �����������, ����� �� ����� ���������� ������ � caller (��� ��� caller ��� ������� ���� array � �������!)
    // ��� ��� ����� �� ������ ���� ������� ������� � ��������� �� ������ 
    return array[index];
}

int* allocateArray(int size)
{
    return new int[size];
}

int main1()
{
    int* array = allocateArray(20);

    // ������ ���-������ � array

    delete[] array;

    std::array<int, 20> array1;

    // ����������� �������� ������� ��� �������� 15 �������� 7
    getElement(array1, 15) = 7;

    std::cout << array1[15] << '\n';


    return 0;
}
#endif

#ifdef ��������
#include <iostream>
#include <array>
#include <ctime> // ��� time()
#include <cstdlib> // ��� rand() � srand()

enum CardSuit
{
    SUIT_TREFU,
    SUIT_BYBNU,
    SUIT_CHERVU,
    SUIT_PIKI,
    MAX_SUITS
};

enum CardRank
{
    RANK_2,
    RANK_3,
    RANK_4,
    RANK_5,
    RANK_6,
    RANK_7,
    RANK_8,
    RANK_9,
    RANK_10,
    RANK_VALET,
    RANK_DAMA,
    RANK_KOROL,
    RANK_TYZ,
    MAX_RANKS
};

struct Card
{
    CardRank rank;
    CardSuit suit;
};

void printCard(const Card& card)
{
    switch (card.rank)
    {
    case RANK_2:		std::cout << "2"; break;
    case RANK_3:		std::cout << "3"; break;
    case RANK_4:		std::cout << "4"; break;
    case RANK_5:		std::cout << "5"; break;
    case RANK_6:		std::cout << "6"; break;
    case RANK_7:		std::cout << "7"; break;
    case RANK_8:		std::cout << "8"; break;
    case RANK_9:		std::cout << "9"; break;
    case RANK_10:		std::cout << "T"; break;
    case RANK_VALET:	std::cout << "V"; break;
    case RANK_DAMA:	        std::cout << "D"; break;
    case RANK_KOROL:	std::cout << "K"; break;
    case RANK_TYZ:		std::cout << "T"; break;
    }

    switch (card.suit)
    {
    case SUIT_TREFU:	std::cout << "TR"; break;
    case SUIT_BYBNU:	std::cout << "B"; break;
    case SUIT_CHERVU:	std::cout << "CH"; break;
    case SUIT_PIKI:	        std::cout << "P"; break;
    }
}

void printDeck(const std::array<Card, 52>& deck)
{
    for (const auto& card : deck)
    {
        printCard(card);
        std::cout << ' ';
    }

    std::cout << '\n';
}

void swapCard(Card& a, Card& b)
{
    Card temp = a;
    a = b;
    b = temp;
}

// ���������� ��������� ����� ����� min � max (��������������, ��� ������� srand() ��� ���� �������)
int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    // ���������� ������������ ��������� ���������� ����� � ��������� ��������
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void shuffleDeck(std::array<Card, 52>& deck)
{
    // ���������� ������ ����� � ������
    for (int index = 0; index < 52; ++index)
    {
        // �������� ����� ��������� �����
        int swapIndex = getRandomNumber(0, 51);
        // ������ ������� � ����� ������� ������
        swapCard(deck[index], deck[swapIndex]);
    }
}

int getCardValue(const Card& card)
{
    switch (card.rank)
    {
    case RANK_2:		return 2;
    case RANK_3:		return 3;
    case RANK_4:		return 4;
    case RANK_5:		return 5;
    case RANK_6:		return 6;
    case RANK_7:		return 7;
    case RANK_8:		return 8;
    case RANK_9:		return 9;
    case RANK_10:		return 10;
    case RANK_VALET:	return 10;
    case RANK_DAMA:	    return 10;
    case RANK_KOROL:	return 10;
    case RANK_TYZ:		return 11;
    }

    return 0;
}

char getPlayerChoice()
{
    std::cout << "(h) to hit, or (s) to stand: ";
    char choice;
    do
    {
        std::cin >> choice;
    } while (choice != 'h' && choice != 's');

    return choice;
}

bool playBlackjack(const std::array<Card, 52>& deck)
{
    // ����������� ��������� ����� ����
    const Card* cardPtr = &deck[0];

    int playerTotal = 0;
    int dealerTotal = 0;

    // ����� �������� ���� �����
    dealerTotal += getCardValue(*cardPtr++);
    std::cout << "The dealer is showing: " << dealerTotal << '\n';

    // ����� �������� ��� �����
    playerTotal += getCardValue(*cardPtr++);
    playerTotal += getCardValue(*cardPtr++);

    // ����� ��������
    while (1)
    {
        std::cout << "You have: " << playerTotal << '\n';

        // �������, �� ������ �� 21 ���� � ������
        if (playerTotal > 21)
            return false;

        char choice = getPlayerChoice();
        if (choice == 's')
            break;

        playerTotal += getCardValue(*cardPtr++);
    }

    // ���� ����� �� �������� � � ���� �� ������ 21 ����, �� ����� ����� �������� ����� �� ��� ���, ���� � ���� �� ��������� � ����� 17 �����
    while (dealerTotal < 17)
    {
        dealerTotal += getCardValue(*cardPtr++);
        std::cout << "The dealer now has: " << dealerTotal << '\n';
    }

    // ���� � ������ ������ 21 ����, �� ����� �������
    if (dealerTotal > 21)
        return true;

    return (playerTotal > dealerTotal);
}

int main1()
{
    srand(static_cast<unsigned int>(time(0))); // ������������� �������� ��������� ����� � �������� ���������� ����� 
    rand(); // ���� ����������� Visual Studio, ���������� ������ ��������������� ��������� �����

    std::array<Card, 52> deck;

    // ����� ���� �� ������� (�� �����������) ���������������� ������ �����, �� �� ���� ������������! ���� ��� � ������!
    int card = 0;
    for (int suit = 0; suit < MAX_SUITS; ++suit)
        for (int rank = 0; rank < MAX_RANKS; ++rank)
        {
            deck[card].suit = static_cast<CardSuit>(suit);
            deck[card].rank = static_cast<CardRank>(rank);
            ++card;
        }

    shuffleDeck(deck);

    if (playBlackjack(deck))
        std::cout << "You win!\n";
    else
        std::cout << "You lose!\n";

    return 0;
}
#endif

#ifdef std_vector
#include <vector>
#include <iostream>

int main1()
{
    std::vector<int> array{ 0, 1, 4, 7, 9, 11 };
    array.resize(4); // �������� ����� array �� 4

    std::cout << "The length is: " << array.size() << '\n';

    for (auto const& element : array)
        std::cout << element << ' ';

    return 0;
}
#endif

#ifdef std_array
//std::array � ��� �������� ������ ����������� ������������� ��������.
#include <iostream>
#include <array>
#include <algorithm> // ��� std::sort

int main1()
{
    std::array<int, 5> myarray{ 8, 4, 2, 7, 1 };
    std::sort(myarray.begin(), myarray.end()); // ���������� ������� �� �����������
//    std::sort(myarray.rbegin(), myarray.rend()); // ���������� ������� �� ��������

    for (const auto& element : myarray)
        std::cout << element << ' ';

    return 0;
}
#endif

#ifdef ���������_��_���������
#include <iostream>
#include <bitset>
int main1() {
    int** array = new int* [15]; // �������� ������ �� 15 ���������� ���� int � ��� ���� ������
    for (int count = 0; count < 15; ++count)
        array[count] = new int[7]; // � ��� ���� �������

    for (int count = 0; count < 15; ++count)
        delete[] array[count];
    delete[] array; // ��� ������� ��������� � �����
    return 0;
}
#endif

#ifdef void_��������� //void*
//��������� ���� void � ��� ���������, ������� ����� ��������� �� ������ 
//������ ���� ������, �� �� ��� �� �����, ����� ��� ����� ���.
//��� ������������� ��������� ���� void ������ ���� ���� ������������ 
//� ������� ��������� static_cast � ������ ��� ������.������� ��������� � ��� ���������, 
//������� �� ��������� �� �����.��������� ���� void ����� ���� ������� ����������.
#include <iostream>

enum Type
{
    INT,
    DOUBLE,
    CSTRING
};

void printValue(void* ptr, Type type)
{
    switch (type)
    {
    case INT:
        std::cout << *static_cast<int*>(ptr) << '\n'; // ������������ � ��������� ���� int � ��������� �������������
        break;
    case DOUBLE:
        std::cout << *static_cast<double*>(ptr) << '\n'; // ������������ � ��������� ���� double � ��������� �������������
        break;
    case CSTRING:
        std::cout << static_cast<char*>(ptr) << '\n'; // ������������ � ��������� ���� char (��� �������������)
        // std::cout �����, ��� char* ������� ������������ ��� ������ C-style.
        // ���� �� �� ������������ ��������� (����� ���������), �� ����� �� ������� ������ ������ ������ �� ������� ����, �� ������� ��������� ptr
        break;
    }
}

int main1()
{
    int nValue = 7;
    double dValue = 9.3;
    char szValue[] = "Jackie";

    printValue(&nValue, INT);
    printValue(&dValue, DOUBLE);
    printValue(szValue, CSTRING);

    return 0;
}

#endif

#ifdef �����������_������
#include <iostream>

void printIt(const int& a)
{
    std::cout << a;
}

int main1()
{
    int x = 3;
    printIt(x); // ������������� l-value

    const int y = 4;
    printIt(y); // ����������� l-value

    printIt(5); // ������� � �������� r-value

    printIt(3 + y); // ��������� � �������� r-value

    return 0;
}
#endif

#ifdef �����������_���������
#include <iostream>
#include <bitset>
int main1() {
    int value = 7;
    // ptr1 ��������� �� "const int", ������� ��� ��������� �� ����������� �������� 
    const int* ptr1 = &value;
    // ptr2 ��������� �� "int", ������� ��� ����������� ��������� �� ������������� ��������
    int* const ptr2 = &value; 
    // ptr3 ��������� �� "const int", ������� ��� ����������� ��������� �� ����������� ��������    
    const int* const ptr3 = &value;

    return 0;
}
#endif

#ifdef ������������ �������
#include <iostream>
#include <string>
#include <utility> // ��� std::swap(). ���� � ��� �� �������������� C++11, �� ����� #include <algorithm>

void sortArray(std::string* array, int length)
{
    // ���������� ������ ������� �������
    for (int startIndex = 0; startIndex < length; ++startIndex)
    {
        // smallestIndex - ������ ����������� ��������, � ������� �� �����������
        int smallestIndex = startIndex;

        // ���� ���������� �������, ������� ������� � ������� (������� �� startIndex+1)
        for (int currentIndex = startIndex + 1; currentIndex < length; ++currentIndex)
        {
            // ���� ������� ������� ������ ������ ����� ���������� ����������� ��������,
            if (array[currentIndex] < array[smallestIndex])
                // �� ����� ��� ����� ���������� �������� � ���� ��������
                smallestIndex = currentIndex;
        }

        // ������ ������� ��� ��������� ������� � ��������� ���������� ��������� �������
        std::swap(array[startIndex], array[smallestIndex]);
    }
}

int main1()
{
    std::cout << "How many names would you like to enter? ";
    int length;
    std::cin >> length;

    // �������� ������ ��� �������� ����
    std::string* names = new std::string[length];

    // ������ ������������ ������ ��� �����
    for (int i = 0; i < length; ++i)
    {
        std::cout << "Enter name #" << i + 1 << ": ";
        std::cin >> names[i];
    }

    // ��������� ������
    sortArray(names, length);

    std::cout << "\nHere is your sorted list:\n";
    // ������� ��������������� ������
    for (int i = 0; i < length; ++i)
        std::cout << "Name #" << i + 1 << ": " << names[i] << '\n';

    delete[] names; // �� �������� ������������ �������� delete[] ��� ������������ ������
    names = nullptr; // ����������� 0, ���� �� �������������� C++11

    return 0;
}
#endif

#ifdef C_style
#include <iostream>

int main1() {
    char ch[] = "R";
    std::cout << ch << std::endl;
    std::cout << static_cast<void*>(ch) << std::endl;
    std::cout << &ch;
    return 0;
}
#endif

#ifdef ���������� ����������
#include <iostream>

int main1()
{
    const int arrayLength = 10;
    char name[arrayLength] = "Jonathanu";
    int numVowels(0);
    for (char* ptr = name; ptr < name + arrayLength; ++ptr)
    {
        switch (*ptr)
        {
        case 'A':
        case 'a':
        case 'E':
        case 'e':
        case 'I':
        case 'i':
        case 'O':
        case 'o':
        case 'U':
        case 'u':
            ++numVowels;
        }
    }

    std::cout << name << " has " << numVowels << " vowels.\n";

    return 0;
}
#endif

#ifdef nullptr_
#include <iostream>

void doAnything(int* ptr)
{
    if (ptr)
        std::cout << "You passed in " << *ptr << '\n';
    else
        std::cout << "You passed in a null pointer\n";
}
void doAnything1(std::nullptr_t ptr)
{
    std::cout << "in doAnything()\n";
}
int main1()
{
    doAnything(nullptr); // ������ �������� �������� ����� ������� ����������, � �� ������������� ���������
    doAnything1(nullptr); // ������ �������� �������� ����� ������� ����������, � �� ������������� ���������

    return 0;
}
#endif

#ifdef ���������
#include <iostream>
#include <bitset>
int main1() {
    short value = 7; // &value = 0012FF60
    short otherValue = 3; // &otherValue = 0012FF54

    short* ptr = &value;

    std::cout << &value << '\n';
    std::cout << value << '\n';
    std::cout << ptr << '\n';
    std::cout << *ptr << '\n';
    std::cout << '\n';

    *ptr = 9;

    std::cout << &value << '\n';
    std::cout << value << '\n';
    std::cout << ptr << '\n';
    std::cout << *ptr << '\n';
    std::cout << '\n';

    ptr = &otherValue;

    std::cout << &otherValue << '\n';
    std::cout << otherValue << '\n';
    std::cout << ptr << '\n';
    std::cout << *ptr << '\n';
    std::cout << '\n';

    std::cout << sizeof(ptr) << '\n';
    std::cout << sizeof(*ptr) << '\n';    
    return 0;
}
#endif

#ifdef cstring
#include <iostream>
#include <cstring>

int main1()
{
    char text[] = "Print this!";
    char dest[50]; // �������� ��������, ����� ������� dest ����� 5 ��������!
    strcpy_s(dest, text); // ������������ ���� 5!
    std::cout << dest<< std::endl;

    char name[15] = "Max"; // ������������ ������ 4 ������� (3 ����� + ����-����������)
    std::cout << "My name is " << name << '\n';
    std::cout << name << " has " << strlen(name) << " letters.\n";
    std::cout << name << " has " << sizeof(name) << " characters in the array.\n";

    // ������ ������������ ������ ������
    char buffer[255];
    std::cout << "Enter a string: ";
    std::cin.getline(buffer, 255);

    int spacesFound = 0;
    // ���������� ������ ������, ������� ���� ������������
    for (int index = 0; index < strlen(buffer); ++index)
    {
        // ������������ ���������� ��������
        if (buffer[index] == ' ')
            spacesFound++;
    }

    std::cout << "You typed " << spacesFound << " spaces!\n";
    
    //������� strcat() � ��������� ���� ������ � ������(������);

    //������� strncat() � ��������� ���� ������ � ������(� ��������� ������� ����� ����������);

    //������� strcmp() � ���������� ��� ������(���������� 0, ���� ��� �����);

    //������� strncmp() � ���������� ��� ������ �� ������������� ���������� ��������(���������� 0, ���� �� ���������� ������� �� ���� ��������).
    
    return 0;
}
#endif

#ifdef ��������������� ����. ���������
#include <iostream>

int main1()
{
    // ��������� ������ 10x10 
    const int numRows = 10;
    const int numCols = 10;
    int product[numRows][numCols] = { 0 };

    // ������� ������� ���������
    for (int row = 0; row < numRows; ++row)
        for (int col = 0; col < numCols; ++col)
            product[row][col] = row * col;

    // ������� ������� ���������
    for (int row = 1; row < numRows; ++row)
    {
        for (int col = 1; col < numCols; ++col)
            std::cout << product[row][col] << "\t";
        std::cout << '\n';
    }
    return 0;
}
#endif

#ifdef ��������� ����������
#include <iostream> 
#include <algorithm> // ��� std::swap. � C++11 ����������� ��������� <utility>

int main()
{
    const int length(9);
    int array[length] = { 7, 5, 6, 4, 9, 8, 2, 1, 3 };

    for (int iteration = 0; iteration < length - 1; ++iteration)
    {
        // ������� � ���, ��� ��������� ������� ����� ������������ � � ������ ����������� �������� �����,
        // ������� ���� ���������� ��������������� �� ���� ������� ������
        int endOfArrayIndex(length - iteration);

        bool swapped(false); // �����������, ���� �� ��������� ������ � ���� ��������

        // ���������� ������ ������� ������� �� ���������� (�� ������������).
        // ��������� ������� �� ����� ���� ��� ���������
        for (int currentIndex = 0; currentIndex < endOfArrayIndex - 1; ++currentIndex)
        {
            // ���� ������� ������� ������ ��������, ���������� �� ���,
            if (array[currentIndex] > array[currentIndex + 1])
            {
                // �� ��������� ������
                std::swap(array[currentIndex], array[currentIndex + 1]);
                swapped = true;
            }
        }

        // ���� � ���� �������� �� ����������� �� ����� ������, �� ���� ����� ���������
        if (!swapped)
        {
            // ���������� ���������� � 0-� ��������, �� �� �������� �������, ������� � 1, ������� ��� �������� ���������� �������� ��������� �������
            std::cout << "Early termination on iteration: " << iteration + 1 << '\n';
            break;
        }
    }

    // ������� ��������������� ������ �� �����
    for (int index = 0; index < length; ++index)
        std::cout << array[index] << ' ';

    return 0;
}
#endif

#ifdef ���������� �������� ������� ������
#include <iostream> 
#include <algorithm> // ��� std::swap. � C++11 ����������� ��������� <utility>

int main1()
{
    const int length = 5;
    int array[length] = { 30, 50, 20, 10, 40 };

    // ���������� ������ ������� ������� (����� ����������, �� ��� ����� ������������ � ���� �������, ����� �� �� ���� ���������)
    for (int startIndex = 0; startIndex < length - 1; ++startIndex)
    {
        // � ���������� smallestIndex �������� ������ ����������� ��������, ������� �� ����� � ���� ��������.
        // �������� � ����, ��� ���������� ������� � ���� �������� - ��� ������ ������� (������ 0)
        int smallestIndex = startIndex;

        // ����� ���� ������� �������� � ��������� ����� �������
        for (int currentIndex = startIndex + 1; currentIndex < length; ++currentIndex)
        {
            // ���� �� ����� �������, ������� ������ ������ ����������� ��������,
            if (array[currentIndex] < array[smallestIndex])
                // �� ���������� ���
                smallestIndex = currentIndex;
        }

        // smallestIndex ������ ���������� �������. 
        // ������ ������� ���� ��������� ���������� ����� � ���, ������� �� ����������
        std::swap(array[startIndex], array[smallestIndex]);
    }

    // ������, ����� ���� ������ ������������ - ������� ��� �� �����
    for (int index = 0; index < length; ++index)
        std::cout << array[index] << ' ';

    std::cout << std::endl;
    const int length1 = 5;
    int array1[length1] = { 30, 50, 20, 10, 40 };

    std::sort(array1, array1 + length1);

    for (int i = 0; i < length1; ++i)
        std::cout << array1[i] << ' ';
    return 0;
    }
#endif

#ifdef ������ � ����� ������
#include <iostream>

int main1()
{
    int students[] = { 73, 85, 84, 44, 78 };
    const int numStudents = sizeof(students) / sizeof(students[0]);

    int maxScore = 0; // ����������� ����� ������� ������
    for (int person = 0; person < numStudents; ++person)
        if (students[person] > maxScore)
            maxScore = students[person];

    std::cout << "The best score was " << maxScore << '\n';

    return 0;
}
#endif

#ifdef ������������ ������
namespace StudentNames
{
    enum StudentNames
    {
        SMITH, // 0
        ANDREW, // 1
        IVAN, // 2
        JOHN, // 3
        ANTON, // 4
        MISHA, // 5
        MAX_STUDENTS // 6
    };
}

int main1()
{
    int testScores[StudentNames::MAX_STUDENTS]; // ����� 6 ���������
    testScores[StudentNames::JOHN] = 65;
    std::cout << testScores[StudentNames::JOHN];
    return 0;
}
#endif

#ifdef Hi_Lo
#include <iostream>
#include <cstdlib> // ��� ������� srand() � rand()
#include <ctime> // ��� ������� time()

// ���������� ��������� ����� ����� min � max.
// ��������������, ��� srand() ��� ��������
int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    // ���������� ������������ ����� ���������� ����� � ���������
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

// ���������� true, ���� ������������ �������, false - ���� ��������
bool playGame(int guesses, int number)
{
    // ���� ������ � ��������� ������������ 
    for (int count = 1; count <= guesses; ++count)
    {
        std::cout << "Guess #" << count << ": ";
        int guess;
        std::cin >> guess;

        if (guess > number)
            std::cout << "Your guess is too high.\n";
        else if (guess < number)
            std::cout << "Your guess is too low.\n";
        else // ������� == �����
            return true;
    }

    return false;
}

bool playAgain()
{
    // ���������� ���������� � ������������, ����� �� �� ������� ��� ��� �� ��� ���, ���� �� �� ������ 'y' ��� 'n'
    char ch;
    do
    {
        std::cout << "Would you like to play again (y/n)? ";
        std::cin >> ch;
    } while (ch != 'y' && ch != 'n');

    return (ch == 'y');
}

int main1()
{
    srand(static_cast<unsigned int>(time(0))); // � �������� ���������� ����� ���������� ��������� ����
    rand(); // ���������� ������ ���������, ��� ��� ������� rand() �� ����� ������ ������������� ������ ��������� ����� � Visual Studio

    const int guesses = 7; // � ������������ ���� 7 �������

    do
    {
        int number = getRandomNumber(1, 100); // �����, ������� ������������ ������ ������� 

        std::cout << "Let's play a game.  I'm thinking of a number.  You have " << guesses << " tries to guess what it is.\n";

        bool won = playGame(guesses, number);
        if (won)
            std::cout << "Correct!  You win!\n";
        else
            std::cout << "Sorry, you lose.  The correct number was " << number << "\n";

    } while (playAgain());

    std::cout << "Thank you for playing.\n";
    return 0;
}
#endif

#ifdef ��������������������2
#include <iostream>
#include <limits>
#include <conio.h>
#include <algorithm>

int main1() {
    while (true) {
        char current_char;
        bool is_negative = false;
        bool has_decimal = false;
        double number = 0;
        int decimal_place = 0;
        std::string input = ""; // ������ ��� �������� ��������� ��������

        std::cout << "������� �����: ";

        while (true) {
            current_char = _getch();

            if (current_char == '\r') { // Enter - ���������� �����
                break;
            }
            else if (current_char == '\b' && !input.empty()) { // Backspace - �������� ���������� �������
                std::cout << "\b \b"; // �������� ���������� ������� �� ������
                input.pop_back(); // �������� ���������� ������� �� ������
                if (input.empty()) { // ���� ������ ������, �� ���������� ����� is_negative � has_decimal
                    is_negative = false;
                    has_decimal = false;
                    continue;
                }
                if (input.back() == '.') { // ���� ��������� �����, �� ���������� ���� has_decimal
                    has_decimal = false;
                }
            }
            else if (current_char == '-' && !is_negative && !has_decimal && number == 0) {
                is_negative = true;
                std::cout << current_char;
                input += current_char;
            }
            else if (current_char >= '0' && current_char <= '9') {
                number = number * 10 + (current_char - '0');
                std::cout << current_char;
                input += current_char;
            }
            else if (current_char == '.' && !has_decimal) {
                has_decimal = true;
                std::cout << current_char;
                input += current_char;
            }
            else { // ������������ ������ - ������ �������� ������
                std::cout << "\a"; // �������� ������
            }
        }
        std::cout << std::endl;
        // �������� �� ����� ������� � ����� ��������� �����
        if (input.length() > 10 || (input.length() == 10 && (input[0] == '1' || (input[0] == '-' && input[1] == '1')))) {
            std::cout << "������: ����� ������� " << ((input[0] == '-')?"���������!":"�������!") << std::endl;
            continue; // ��������� � ���������� �����
        }

        if (has_decimal) {
            number = atof(input.c_str()); // ����������� ������ � ����� � ��������� ������
        }
        else {
            number = atoi(input.c_str()); // ����������� ������ � ����� �����
        }

        std::cout << "���� �����: " << number << std::endl;
        //break; // ����� �� �����, ���� ����� ������� �������
    }

    return 0;
}



#endif

#ifdef ��������������������1
#include <iostream>
#include <string>
#include <regex>

bool is_valid_char(char c) {
    // ���������, �������� �� ������ ����������
    return (c >= '0' && c <= '9') || c == '-' || c == '.';
}

int main1() {
    std::string input;
    char current_char;

    std::cout << "������� �����: ";

    while (std::cin.get(current_char)) {
        if (is_valid_char(current_char)) {
            input += current_char; // ��������� ������ � ������
            std::cout << current_char; // ������� ������ �� �����
        }
        // ���� ���� - Enter, ������� �� �����
        if (current_char == '\n') {
            break;
        }
    }
    // ����������� ������ � ����� (������ ���� ��� �� �����)
    if (!input.empty()) {
        double number = std::stod(input);

        // ��������� �� ����� ������� � ����� ��������� �����:
        if (number > 1e10 || number < -1e10) {
            std::cout << "������: ����� ������� �������!" << std::endl;
        }
        else if (number > -1e-10 && number < 1e-10) {
            std::cout << "������: ����� ������� ���������!" << std::endl;
        }
        else {
            std::cout << "�����: " << number << std::endl;
        }
    }
    else {
        std::cout << "������: ���� ����!" << std::endl;
    }

    return 0;
}

#endif

#ifdef ��������������������
#include <iostream>

double getValue()
{
    while (true) // ���� ������������ �� ��� ���, ���� ������������ �� ������ ���������� ��������
    {
        std::cout << "Enter a double value: ";
        double a;
        std::cin >> a;

        // �������� �� ���������� ����������
        if (std::cin.fail()) // ���� ���������� ���������� ��������� ���������,
        {
            std::cin.clear(); // �� ���������� cin � '�������' ����� ������
            std::cin.ignore(32767, '\n'); // � ������� �������� ����������� ����� �� �������� ������
            std::cout << "Oops, that input is invalid.  Please try again.\n";
        }
        else
        {
            std::cin.ignore(32767, '\n'); // ������� ������ ��������

            return a;
        }
    }
}

char getOperator()
{
    while (true) // ���� ������������ �� ��� ���, ���� ������������ �� ������ ���������� ��������
    {
        std::cout << "Enter one of the following: +, -, *, or /: ";
        char sm;
        std::cin >> sm;

        // ���������� ���� char ����� ��������� ����� ������� �� ����������������� �����, ������� ��� �� ����� ������������ �� ������ ������������� ���������� ����������

        std::cin.ignore(32767, '\n'); // ������� ������ �������

        // ��������� �������� ����������������� �����
        if (sm == '+' || sm == '-' || sm == '*' || sm == '/')
            return sm; // ���������� ������� � caller
        else // � ��������� ������, �������� ������������ ��� ���-�� ����� �� ���
            std::cout << "Oops, that input is invalid.  Please try again.\n";
    }
}

void printResult(double a, char sm, double b)
{
    if (sm == '+')
        std::cout << a << " + " << b << " is " << a + b << '\n';
    else if (sm == '-')
        std::cout << a << " - " << b << " is " << a - b << '\n';
    else if (sm == '*')
        std::cout << a << " * " << b << " is " << a * b << '\n';
    else if (sm == '/')
        std::cout << a << " / " << b << " is " << a / b << '\n';
    else
        std::cout << "Something went wrong: printResult() got an invalid operator.";

}

int main1()
{
    double a = getValue();
    char sm = getOperator();
    double b = getValue();

    printResult(a, sm, b);

    return 0;
}
#endif

#ifdef ������������� ��������� ��������� �����
#include <iostream>
// #include <ctime> // ����������������, ���� ����������� Code::Blocks
#include <random> // ��� std::random_device � std::mt19937

int main1()
{
    std::random_device rd;
    std::mt19937 mersenne(rd()); // �������������� ����� �������� ��������� ��������� ������ 

// ����������: ��-�� ������ ���� � ����������� Code::Blocks (���� �� ����������� Code::Blocks � Windows) - ������� ��� ������ ���� ���� � ���������������� ��������� ������:
// std::mt19937 mersenne(static_cast<unsigned int>(time(0))); // �������������� ����� �������� ��������� ��������� ������

    // ������� ��������� ��������� �����
    for (int count = 0; count < 48; ++count)
    {
        std::cout << mersenne() << "\t";

        // ���� ������ 5 �����, �� ��������� ������ ����� ������
        if ((count + 1) % 5 == 0)
            std::cout << "\n";
    }
    return 0;
}
#endif

#ifdef ���� ��������� ��������������� �����
#include <iostream>
#include <cstdlib> // ��� ������� rand() � srand()
#include <ctime> // ��� ������� time()

unsigned int PRNG()
{
    // ���� ��������� ����� - 4 541
    static unsigned int seed = 4541;
    // ����� ��������� ����� �, � ��� �������, ���������� ����� ��������.
    // ��-�� ������������� ����� ������� ����� (� ������������) ������� ��������� ����� ������ �� ����������� - ����� ������
    seed = (8253729 * seed + 2396403);
    // ����� ��������� ����� � ���������� �������� � ��������� �� 0 �� 32767
    return seed % 32768;
}
int main1()
{
    // ������� 100 ��������� �����
    for (int count = 0; count < 100; ++count)
    {
        std::cout << PRNG() << "\t";
        // ���� ������ 5 �����, �� ��������� ������ ����� ������
        if ((count + 1) % 5 == 0)
            std::cout << "\n";
    }
    std::cout << std::endl;
    srand(static_cast<unsigned int>(time(0))); // ������������� �������� ��������� ����� � �������� ���������� �����

    for (int count = 0; count < 100; ++count)
    {
        std::cout << rand() << "\t";

        // ���� ������ 5 �����, �� ��������� ������ ����� ������
        if ((count + 1) % 5 == 0)
            std::cout << "\n";
    }
    return 0;
}
#endif

#ifdef Switch_Case
#include <iostream>

bool isDigit(char p)
{
    switch (p)
    {
    case '0': // ���� p = 0
    case '1': // ���� p = 1
    case '2': // ���� p = 2
    case '3': // ���� p = 3
    case '4': // ���� p = 4
    case '5': // ���� p = 5
    case '6': // ���� p = 6
    case '7': // ���� p = 7
    case '8': // ���� p = 8
    case '9': // ���� p = 9
        return true; // ���������� true
    default: // � ��������� ������, ���������� false
        return false;
    }
}
int calculate(int x, int y, char op)
{
    switch (op)
    {
    case '+':
        return x + y;
    case '-':
        return x - y;
    case '*':
        return x * y;
    case '/':
        return x / y;
    case '%':
        return x % y;
    default:
        std::cout << "calculate(): Unhandled case\n";
        return 0;
    }
}

int main1()
{
    std::cout << "Enter an integer: ";
    int x;
    std::cin >> x;

    std::cout << "Enter another integer: ";
    int y;
    std::cin >> y;

    std::cout << "Enter a mathematical operator (+, -, *, /, or %): ";
    char op;
    std::cin >> op;

    std::cout << x << " " << op << " " << y << " is " << calculate(x, y, op) << "\n";

    return 0;
}

#endif

#ifdef auto_
auto d = 4.0;
auto subtract(int, int) -> int;
int subtract(int a, int b)
{
    return a - b;
}
auto divide(double a, double b) -> double;
auto printThis() -> void;
auto calculateResult(int a, double x)->std::string;
#endif

#ifdef ���������
#include <iostream>

struct Employee
{
    short id;
    int age;
    double salary;
};

void printInformation(Employee employee)
{
    std::cout << "ID: " << employee.id << "\n";
    std::cout << "Age: " << employee.age << "\n";
    std::cout << "Salary: " << employee.salary << "\n";
}

int main1()
{
    Employee john = { 21, 27, 28.45 };
    Employee james = { 22, 29, 19.29 };

    // ������� ���������� � John
    printInformation(john);

    std::cout << "\n";

    // ������� ���������� � James
    printInformation(james);
    std::cout << sizeof(james);
    return 0;
}
#endif

#ifdef typedef_using
//��������� typedef:
typedef double time_t; // ���������� time_t � �������� ���������� ��� ���� double

//� �++11 ����� �������� ��� :
using time_t = double; // ���������� time_t � �������� ���������� ��� ���� double

//��� ��� ������� ������������� ������������.
#endif

#ifdef enum_class
#include <iostream>

int main1()
{
    enum class Fruits // ���������� "class" � enum ���������� ������������ � ������������ �������� ���������, ������ ������������ "�����������" ������������ 
    {
        LEMON, // LEMON ��������� ������ ��� �� ������� ���������, ��� � Fruits
        KIWI
    };

    enum class Colors
    {
        PINK, // PINK ��������� ������ ��� �� ������� ���������, ��� � Colors
        GRAY
    };

    Fruits fruit = Fruits::LEMON; // ����������: LEMON �������� �� ��������, �� ������ ������������ Fruits::LEMON
    Colors color = Colors::PINK; // ����������: PINK �������� �� ��������, �� ������ ������������ Colors::PINK

    //if (fruit == color) // ������ ����������, ��������� ���������� �� �����, ��� ���������� ������ ����: Fruits � Colors
    if (static_cast<int>(fruit) == static_cast<int>(color))
        std::cout << "fruit and color are equal\n";
    else
        std::cout << "fruit and color are not equal\n";

    return 0;
}
#endif

#ifdef enums 
#include <iostream>
#include <bitset>
#include <iostream>

enum Colors
{
    COLOR_PURPLE, // ������������� 0
    COLOR_GRAY,   // ������������� 1
    COLOR_BLUE,   // ������������� 2
    COLOR_GREEN,  // ������������� 3
    COLOR_BROWN,  // ������������� 4
    COLOR_PINK,   // ������������� 5
    COLOR_YELLOW, // ������������� 6
    COLOR_MAGENTA // ������������� 7
};
void printColor(Colors color)
{
    if (color == COLOR_PURPLE)
        std::cout << "Purple";
    else if (color == COLOR_GRAY)
        std::cout << "Gray";
    else if (color == COLOR_BLUE)
        std::cout << "Blue";
    else if (color == COLOR_GREEN)
        std::cout << "Green";
    else if (color == COLOR_BROWN)
        std::cout << "Brown";
    else if (color == COLOR_PINK)
        std::cout << "Pink";
    else if (color == COLOR_YELLOW)
        std::cout << "Yellow";
    else if (color == COLOR_MAGENTA)
        std::cout << "Magenta";
    else
        std::cout << "Who knows!";
}
int main1()
{
    //Colors color;
    //std::cin >> color; // �������� � ������ ����������
    int inputColor;
    std::cin >> inputColor;
    Colors color = static_cast<Colors>(inputColor);
    printColor(color);
    return 0;
}
#endif

#ifdef String ������
#include <iostream>
#include <string>

int main1()
{
    //��� ����� �������� �������� �� ��������� ������� ������ ����� ������ 
    //�� �������� ������ ������ � ������� std::cin.ignore().
    std::cout << "Pick 1 or 2: ";
    int choice;
    std::cin >> choice;

    std::cin.ignore(32767, '\n'); // ������� ������ ����� ������ �� �������� ������ ������

    std::cout << "Now enter your name: ";
    std::string myName;
    std::getline(std::cin, myName);

    std::cout << "Hello, " << myName << ", you picked " << choice << '\n';

    std::cout << myName << " has " << myName.length() << " characters\n";

    return 0;
}
#endif

#ifdef �����_����������
int main1() {
    int i = 90;
    i = (int)(i / 3.6); //C-style ��������, �� ����������� ������������
    i = static_cast<int>(i / 3.6);
    return 0;
}
#endif

#ifdef using_ ����������
#include <iostream>

int main1()
{
    using std::cout; // "using-����������" �������� �����������, ��� cout ������� ������������, ��� std::cout
    cout << "Hello, world!"; // � �������� �������� std:: ��� ����� �� �����!
    return 0;
}
#endif

#ifdef Foo_BooDoo ���������� ��� ����������� ����
#include <iostream>

namespace Boo
{
    namespace Doo
    {
        const int g_x = 7;
    }
}

namespace Foo = Boo::Doo; // Foo ������ ��������� ��� Boo::Doo

int main1()
{
    std::cout << Foo::g_x; // ���, �� ����� ����, Boo::Doo::g_x
    return 0;
}
#endif

#ifdef BooDoo ���������� ���� (������������ ����)
namespace Boo
{
    // ��� ������ doOperation() ����������� ������������ ���� Boo
    constexpr int doOperation(int a, int b) noexcept
    {
        return a + b;
    }
}
namespace Doo
{
    // ��� ������ doOperation() ����������� ������������ ���� Doo
    constexpr int doOperation(int a, int b) noexcept
    {
        return a - b;
    }
}
int main1(void)
{
    std::cout << Boo::doOperation(5, 4) << '\n';
    std::cout << Doo::doOperation(5, 4) << '\n';
    return 0;
}
#endif //

#ifdef s_ ����������� ����������������� �����
int generateID()
{
    static int s_itemID = 0;
    return s_itemID++;
}
//������ �� ������� ���������, s_itemID �� ������������
//��
//�������� static � ����������, ����������� ��� �����, �� ���������� � ��� ����������, 
//�� ���� �����, ������� ����� ������������ ������ � �����, � ������� ��� ����������
#endif //

#ifdef g_ ���������� ���������� � ���
double g_gravity(9.8); // ����� �������������� � ������������ �������� � ����� �����
//�������� ��������� :
static double g_gravity(9.8); // ������������ ������ � ���������� ������ �� ���� ����
double getGravity() // ��� ������� ����� ���� �������������� � ������ ����� ��� ������� � ���������� ����������
{
    return g_gravity;
}
//� - �������, ��� ��������� ���������� �������, ������������ ���������� ����������, 
// �� ����������� �� ��������������� � ���� �������.����������� �� � �������� ����������.
// ����� �������, ���� � ����� ������� ����� ����� ����� - ���� ������������ ������ ��������, 
// �� �� ������� ������ �������� ��������.��� ������� ����������� ����� ���������. 
//    ������ ���������� :
// ��� ������� ������� ������ ��� ������� ���������� �������� �� ������ ���������� ����������
double instantVelocity(int time)
{
    return g_gravity * time;
}
//�������� ��������� :
// ��� ������� ��������� ���������� �������� ��� ������ �������� ����������.
// ��������� ������������ �������� �� getGravity() � �������� gravity, 
// ���� ������ ������������ ���������� ���������� gravity
double instantVelocity(int time, double gravity)
{
    return gravity * time;
}
#endif //

#ifdef bitset
#include <iostream>
#include <bitset>

// �������� ��������, ��������� std::bitset, ���� options ������������� ���������� ������� ���, � �� �� ���������
const int option_1 = 0;
const int option_2 = 1;
const int option_3 = 2;
const int option_4 = 3;
const int option_5 = 4;
const int option_6 = 5;
const int option_7 = 6;
const int option_8 = 7;

int main1()
{
    // �������, ��� ������ ��� ���������� �� � 1, � � 0
    std::bitset<8> bits(0x2); // ��� ����� 8 ���, ������ � �������� ������� 0000 0010
    bits.set(option_5); // �������� 4-� ��� - ��� �������� ��������� �� 1 (������ �� ����� 0001 0010)
    bits.flip(option_6); // �������� �������� 5-�� ���� �� ��������������� (������ �� ����� 0011 0010)
    bits.reset(option_6); // ��������� 5-� ��� - ��� �������� ����� 0 (������ �� ����� 0001 0010)

    std::cout << "Bit 4 has value: " << std::boolalpha << bits.test(option_5) << '\n';
    std::cout << "Bit 5 has value: " << bits.test(option_6) << '\n';
    std::cout << "All the bits: " << bits << '\n';

    return 0;
}
#endif // 

#ifdef ������������
#include <iostream>

int main1()
{
    // ���������� ����� ����������/������������� ��������� 
    const unsigned char isHungry = 0x01; // ����������������� ������� ��� 0000 0001
    const unsigned char isSad = 0x02; // ����������������� ������� ��� 0000 0010
    const unsigned char isMad = 0x04; // ����������������� ������� ��� 0000 0100
    const unsigned char isHappy = 0x08; // ����������������� ������� ��� 0000 1000
    const unsigned char isLaughing = 0x10; // ����������������� ������� ��� 0001 0000
    const unsigned char isAsleep = 0x20; // ����������������� ������� ��� 0010 0000
    const unsigned char isDead = 0x40; // ����������������� ������� ��� 0100 0000
    const unsigned char isCrying = 0x80; // ����������������� ������� ��� 1000 0000

    unsigned char me = 0; // ��� �����/��������� ��������� �� ������
    me |= isHappy | isLaughing; // � isHappy � isLaughing
    me &= ~isLaughing; // � ��� �� isLaughing

    // ����������� ����� ��������� ��������� (�� ����� ������������ static_cast<bool> ��� ����������� ����������� � �������� ���� bool)
    std::cout << "I am happy? " << std::boolalpha << static_cast<bool>(me & isHappy) << '\n'; //<< std::noboolalpha //��� ������ boolalpha;
    std::cout << "I am laughing? " << static_cast<bool>(me & isLaughing) << '\n';

    return 0;
}
#endif // 

#ifdef epsilon ��������� ����� ���� � ��������� ������
#include <cmath> // ��� ������� fabs()
bool isAlmostEqual(double a, double b, double epsilon)
{
    // ���� ������� ����� a � b ������ �������� ��������, �� ����� a � b ����� ������� �������
    return fabs(a - b) <= epsilon;
}
//������� ����, ��������� ������, ��������� ��������� ������ � ����� ����� ���������� ����������������, ��� 2: ������������� ���������� (1968):
// ���������� true, ���� ������� ����� a � b � �������� �������� �������� 
bool approximatelyEqual(double a, double b, double epsilon)
{
    return fabs(a - b) <= ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}
//� ������ ����������� absEpsilon, ������� approximatelyEqualAbsRel() ������������ ������� � ���� � ������� �������� ���������.
// ���������� true, ���� ������� ����� a � b ������ absEpsilon ��� � �������� relEpsilon 
bool approximatelyEqualAbsRel(double a, double b, double absEpsilon, double relEpsilon)
{
    // ��������� ����� �� ��������� �� ���� ����� - ��� ����� � �������, ����� ������������ ����� �������� �������� ��� ����� ����
    double diff = fabs(a - b);
    if (diff <= absEpsilon)
        return true;

    // � ��������� ������, ������������ � ��������� �����
    return diff <= ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * relEpsilon);
}
//��������� ����� ���� � ��������� ������ � ������� ����, � ��� ������ ���������� ���������, ������� �������� � ����� ��������.
//������ ��� ����������� �������, � �������� �� ������ ������������, ������� approximatelyEqualAbsRel() ������ ���� ����������.
int main1()
{
    // �������� a ����� ������ � 1.0, ��, ��-�� ������ ����������, ���� ������ 1.0
    double a = 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1;

    std::cout << approximatelyEqual(a, 1.0, 1e-8) << "\n";     // ���������� "����� 1.0" � 1.0
    std::cout << approximatelyEqual(a - 1.0, 0.0, 1e-8) << "\n"; // ���������� "����� 0.0" � 0.0
    std::cout << approximatelyEqualAbsRel(a - 1.0, 0.0, 1e-12, 1e-8) << "\n"; // ���������� "����� 0.0" � 0.0
}
#endif // 

#ifdef �����������?
bool isEven(int aDec)
{
    return !(aDec & 0x1);
}
#endif // �����������?

#ifdef static_cast_Example
void static_cast_Example()
{
    int x = 7;
    int y = 4;
    std::cout << "int / int = " << x / y << "\n";
    std::cout << "double / int = " << static_cast<double>(x) / y << "\n";
    std::cout << "int / double = " << x / static_cast<double>(y) << "\n";
    std::cout << "double / double = " << static_cast<double>(x) / static_cast<double>(y) << "\n";
}
#endif // static_cast_Example

#ifdef �������_int
int pow(int base, int exp)
{
    int result = 1;
    while (exp)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }

    return result;
}
#endif // �������_int

