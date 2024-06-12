#include <iostream>
#define DEBUG1

#ifdef DEBUG
int returnByValue()
{
    return 7;
}

int& returnByReference()
{
    static int y = 7; // static гарантирует то, что переменная y не уничтожится, когда выйдет из локальной области видимости
    return y;
}

int main1()
{
    int value = returnByReference(); // случай A: всё хорошо, обрабатывается как возврат по значению
    const int& ref = returnByValue(); // случай B: ошибка компилятора, так как 7 - это r-value, а r-value не может быть привязано к неконстантной ссылке
    const int& cref = returnByValue(); // случай C: всё хорошо, время жизни возвращаемого значения продлевается в соответствии со временем жизни cref
    return 1;
}
#endif

#ifdef тайминг
#include <chrono> // для функций из std::chrono
#include <iostream>
#include <array>
#include <chrono> // для функций из std::chrono
#include <algorithm> // для std::sort()

const int g_arrayElements = 10000; // общее количество всех элементов массива

class Timer
{
private:
    // Псевдонимы типов используются для удобного доступа к вложенным типам
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

    // Перебираем каждый элемент массива (кроме последнего, он уже будет отсортирован к тому времени, когда мы до него доберемся)
    for (int startIndex = 0; startIndex < g_arrayElements - 1; ++startIndex)
    {
        // В переменной smallestIndex хранится индекс наименьшего значения, которое мы нашли в этой итерации.
        // Начнем с того, что наименьший элемент в этой итерации - это первый элемент (индекс 0)
        int smallestIndex = startIndex;

        // Затем ищем элемент меньше нашего smallestIndex в оставшейся части массива
        for (int currentIndex = startIndex + 1; currentIndex < g_arrayElements; ++currentIndex)
        {
            // Если нашли элемент, который меньше нашего наименьшего элемента,
            if (array[currentIndex] < array[smallestIndex])
                // то записываем/запоминаем его
                smallestIndex = currentIndex;
        }

        // smallestIndex теперь наименьший элемент в оставшейся части массива.
        // Меняем местами наше стартовое наименьшее значение с тем, которое мы обнаружили
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

#ifdef Вложенные_типы
#include <iostream>

class Fruit
{
public:
    // Мы переместили FruitList внутрь класса под спецификатор доступа public
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
    // Доступ к FruitList осуществляется через Fruit
    Fruit avocado(Fruit::AVOCADO);
    if (avocado.getType() == Fruit::AVOCADO)
        std::cout << "I am an avocado!";
    else
        std::cout << "I am not an avocado!";
    return 0;
}
#endif

#ifdef Дружественный_класс
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

    // Делаем класс Display другом класса Values
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
        else // или сначала выводим double
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

#ifdef Дружественные_методы
#include <iostream>

class Values; // предварительное объявление класса Values

class Display
{
private:
    bool m_displayIntFirst;

public:
    Display(bool displayIntFirst) { m_displayIntFirst = displayIntFirst; }

    void displayItem(Values& value); // предварительное объявление, приведенное выше, требуется для этой строки
};

class Values // полное определение класса Values
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

    // Делаем метод Display::displayItem() другом класса Values
    friend void Display::displayItem(Values& value);
};

// Теперь мы можем определить метод Display::displayItem(), которому требуется увидеть полное определение класса Values
void Display::displayItem(Values& value)
{
    if (m_displayIntFirst)
        std::cout << value.m_intValue << " " << value.m_dValue << '\n';
    else // или выводим сначала double
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

#ifdef Дружественные_функции
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

#ifdef Статические_методы
#include <iostream>

class IDGenerator
{
private:
    static int s_nextID; // объявление статической переменной-члена

public:
    static int getNextID(); // объявление статического метода
};

// Определение статической переменной-члена находится вне тела класса. Обратите внимание, мы не используем здесь ключевое слово static.
// Начинаем генерировать ID с 1
int IDGenerator::s_nextID = 1;

// Определение статического метода находится вне тела класса. Обратите внимание, мы не используем здесь ключевое слово static
int IDGenerator::getNextID() { return s_nextID++; }

int main1()
{
    for (int count = 0; count < 4; ++count)
        std::cout << "The next ID is: " << IDGenerator::getNextID() << '\n';

    return 0;
}
#endif

#ifdef статические_переменные_члены класса
#include <iostream>

class Anything
{
private:
    static int s_idGenerator;
    int m_id;

public:
    Anything() { m_id = s_idGenerator++; } // увеличиваем значение идентификатора для следующего объекта

    int getID() const { return m_id; }
};

// Мы определяем и инициализируем s_idGenerator несмотря на то, что он объявлен как private.
// Это нормально, поскольку определение не подпадает под действия спецификаторов доступа
int Anything::s_idGenerator = 1; // начинаем наш ID-генератор со значения 1

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

#ifdef Константные_методы_классов
class Anything
{
public:
    int m_value;

    Anything() { m_value = 0; }

    void resetValue() { m_value = 0; }
    void setValue(int value) { m_value = value; }

    const int& getValue() const; // обратите внимание на ключевое слово const здесь
    int& getValue(); 
};
const int& Anything::getValue() const // и здесь
{
    return m_value;
}
int& Anything::getValue()
{
    return m_value;
}
int main1()
{
    const Anything anything; // вызываем конструктор по умолчанию

    //anything.m_value = 7; // ошибка компиляции: нарушение const
    //anything.setValue(7); // ошибка компиляции: нарушение const
    std::cout << anything.getValue();
    return 0;
}
#endif

#ifdef Методы_отдельно от класса
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

#ifdef делегирующие конструкторы
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

    // Используем делегирующие конструкторы для сокращения дублированного кода
    Employee(const std::string& name) : Employee(0, name) { }
};

int main1()
{
    Employee a;
    Employee b("Ivan");

    return 0;
}
#endif

#ifdef списки_инициализации
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
        : m_value1(value1), m_value2(value2), m_value3{ value3 }, // напрямую инициализируем переменные-члены класса
        m_array{ 3, 4, 5, 6, 7, 8, 9 }, // используем uniform-инициализацию для инициализации массива
        m_a(b - 1)
    {
        // Нет необходимости использовать присваивание
    }

    void print()
    {
        std::cout << "Values(" << m_value1 << ", " << m_value2 << ", " << m_value3 << ")\n";
    }

};
int main1()
{
    Values value(3, 4.5); // value1 = 3, value2 = 4.5, value3 = 'd' (значение по умолчанию)
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
    // Конструктор по умолчанию
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
    int m_array[10]; // это будут данные нашего стека 
    int m_next; // это будет индексом следующего свободного элемента стека

public:

    void reset()
    {
        m_next = 0;
        for (int i = 0; i < 10; ++i)
            m_array[i] = 0;
    }

    bool push(int value)
    {
        // Если стек уже заполнен, то возвращаем false
        if (m_next == 10)
            return false;

        m_array[m_next++] = value; // присваиваем следующему свободному элементу значение value, а затем увеличиваем m_next
        return true;
    }

    int pop()
    {
        // Если элементов в стеке нет, то выводим стейтмент assert
        assert(m_next > 0);

        // m_next указывает на следующий свободный элемент, поэтому последний элемент со значением - это m_next-1.
        // Мы хотим сделать следующее:
        // int val = m_array[m_next-1]; // получаем последний элемент со значением
        // --m_next; // m_next теперь на единицу меньше, так как мы только что вытянули верхний элемент стека
        // return val; // возвращаем элемент
        // Весь вышеприведенный код можно заменить следующей (одной) строкой кода
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
    Fraction drob; // вызов Fraction(0, 1)
    Fraction seven(7); // вызов Fraction(7, 1)
    Fraction sixTwo(6, 2); // вызов Fraction(6, 2)
    return 0;
    }
#endif

#ifdef Бинарный поиск
// array - это массив, в котором мы проводим поиски.
// target - это искомое значение.
// min - это индекс минимальной границы массива, в котором мы осуществляем поиск.
// max - это индекс максимальной границы массива, в котором мы осуществляем поиск.
// Функция binarySearch() должна возвращать индекс искомого значения, если он обнаружен. В противном случае, возвращаем -1
int binarySearch(int* array, int target, int min, int max)
{
    while (min <= max)
    {
        // Итеративная реализация
        int midpoint = min + ((max - min) / 2); // такой способ вычисления середины массива избегает вероятность возникновения переполнения

        if (array[midpoint] > target)
        {
            // Если array[midpoint] > target, то тогда понимаем, что искомое число не находится в правой половине массива.
            // Мы можем использовать midpoint - 1 в качестве индекса максимальной границы, так как в следующей итерации этот индекс вычислять не нужно
            max = midpoint - 1;
        }
        else if (array[midpoint] < target)
        {
            // Если array[midpoint] < target, то тогда понимаем, что искомое число не находится в левой половине массива.
            // Мы можем использовать midpoint + 1 в качестве индекса минимальной границы, так как в следующей итерации этот индекс вычислять не нужно
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

#ifdef Эллипсис3 строка-декодер
#include <iostream>
#include <string>
#include <cstdarg> // требуется для использования эллипсиса

// Эллипсис должен быть последним параметром 
double findAverage(std::string decoder, ...)
{
    double sum = 0;

    // Мы получаем доступ к эллипсису через va_list, поэтому объявляем переменную этого типа
    va_list list;

    // Инициализируем va_list, используя va_start. Первый параметр - это список, который необходимо инициализировать.
    // Второй параметр - это последний параметр, который не является эллипсисом
    va_start(list, decoder);

    int count = 0;
    // Бесконечный цикл
    while (1)
    {
        char codetype = decoder[count];
        switch (codetype)
        {
        default:
        case '\0':
            // Выполняем очистку va_list, когда уже сделали всё необходимое
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

#ifdef Эллипсис2 контрольное значение
#include <iostream>
#include <cstdarg> // требуется для использования эллипсиса 

// Эллипсис должен быть последним параметром
double findAverage(int first, ...)
{
    // Обработка первого значения
    double sum = first;

    // Мы получаем доступ к эллипсису через va_list, поэтому объявляем переменную этого типа
    va_list list;

    // Инициализируем va_list, используя va_start. Первый параметр - это список, который нужно инициализировать.
    // Второй параметр - это последний параметр, который не является эллипсисом
    va_start(list, first);

    int count = 1;
    // Бесконечный цикл
    while (1)
    {
        // Используем va_arg для получения параметров из эллипсиса.
        // Первый параметр - это va_list, который мы используем.
        // Второй параметр - это ожидаемый тип параметров
        int arg = va_arg(list, int);

        // Если текущий параметр является контрольным значением, то прекращаем выполнение цикла
        if (arg == -1)
            break;

        sum += arg;
        count++;
    }

    // Выполняем очистку va_list, когда уже сделали всё необходимое
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

#ifdef Эллипсис ...
#include <iostream>
#include <cstdarg> // требуется для использования эллипсиса

// Эллипсис должен быть последним параметром.
// Переменная count - это количество переданных аргументов
double findAverage(int count, ...)
{
    double sum = 0;

    // Мы получаем доступ к эллипсису через va_list, поэтому объявляем переменную этого типа
    va_list list;

    // Инициализируем va_list, используя va_start. Первый параметр - это список, который нужно инициализировать.
    // Второй параметр - это последний параметр, который не является эллипсисом
    va_start(list, count);

    // Перебираем каждый из аргументов эллипсиса 
    for (int arg = 0; arg < count; ++arg)
        // Используем va_arg для получения параметров из эллипсиса.
        // Первый параметр - это va_list, который мы используем.
        // Второй параметр - это ожидаемый тип параметров
        sum += va_arg(list, int);

    // Выполняем очистку va_list, когда уже сделали всё необходимое 
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

#ifdef Обработка_числовых_аргументов
#include <iostream>
#include <string>
#include <sstream> // для std::stringstream
#include <cstdlib> // для exit()

int main(int argc, char* argv[])
{
    if (argc <= 1)
    {
        // В некоторых операционных системах argv[0] может быть просто пустой строкой, без имени программы

        // Обрабатываем случай, когда argv[0] может быть пустым или не пустым
        if (argv[0])
            std::cout << "Usage: " << argv[0] << " <number>" << '\n';
        else
            std::cout << "Usage: <program name> <number>" << '\n';

        exit(1);
    }

    std::stringstream convert(argv[1]); // создаем переменную stringstream с именем convert, инициализируя её значением argv[1]

    int myint;
    if (!(convert >> myint)) // выполняем конвертацию
        myint = 0; // если конвертация терпит неудачу, то присваиваем myint значение по умолчанию

    std::cout << "Got integer: " << myint << '\n';

    return 0;
}
#endif

#ifdef static_assert_
#include <cassert> // для assert()
#include <array>
int getArrayValue(const std::array<int, 10>& array, int index)
{
    // Предполагается, что значение index-а находится между 0 и 8
    assert(index >= 0 && index <= 8); // это строка 6 в Program.cpp

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
    // Выводим cstring при условии, что он не нулевой
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

#ifdef Передача_функций в качестве аргументов
#include <iostream> 
#include <utility>
#include <functional>
//typedef bool (*validateFcn)(int, int);
using validateFcn = std::function<bool(int, int)>;
// Вот функция сравнения, которая выполняет сортировку в порядке возрастания (обратите внимание, это та же функция ascending(), что и в примере, приведенном выше)
bool ascending(int a, int b)
{
    return a > b; // меняем местами, если первый элемент больше второго
}

// Вот функция сравнения, которая выполняет сортировку в порядке убывания
bool descending(int a, int b)
{
    return a < b; // меняем местами, если второй элемент больше первого
}
// Обратите внимание, третьим параметром является пользовательский выбор выполнения сортировки
void selectionSort(int* array, int size, validateFcn pfcn = ascending)
{
    // Перебираем каждый элемент массива
    for (int startIndex = 0; startIndex < size; ++startIndex)
    {
        // bestIndex - это индекс наименьшего/наибольшего элемента, который мы обнаружили до этого момента
        int bestIndex = startIndex;

        // Ищем наименьший/наибольший элемент среди оставшихся в массиве (начинаем со startIndex+1)
        for (int currentIndex = startIndex + 1; currentIndex < size; ++currentIndex)
        {
            // Если текущий элемент меньше/больше нашего предыдущего найденного наименьшего/наибольшего элемента,
            if (pfcn(array[bestIndex], array[currentIndex])) // СРАВНЕНИЕ ВЫПОЛНЯЕТСЯ ЗДЕСЬ
                // то это наш новый наименьший/наибольший элемент в этой итерации
                bestIndex = currentIndex;
        }

        // Меняем местами наш стартовый элемент с найденным наименьшим/наибольшим элементом
        std::swap(array[startIndex], array[bestIndex]);
    }
}

// Эта функция выводит значения массива
void printArray(int* array, int size)
{
    for (int index = 0; index < size; ++index)
        std::cout << array[index] << " ";
    std::cout << '\n';
}

int main1()
{
    int array[8] = { 4, 8, 5, 6, 2, 3, 1, 7 };

    // Сортируем массив в порядке убывания, используя функцию descending()
    selectionSort(array, 8, descending);
    printArray(array, 8);

    // Сортируем массив в порядке возрастания, используя функцию ascending()
    selectionSort(array, 8);
    printArray(array, 8);

    return 0;
}
#endif

#ifdef указатель_на_функцию
/*
// Прототипы функций
int boo();
double doo();
int moo(int a);
// Присваивание значений указателям на функции
int (*fcnPtr1)() = boo; // ок
int (*fcnPtr2)() = doo; // не ок: тип указателя и тип возврата функции не совпадают!
double (*fcnPtr4)() = doo; // ок
fcnPtr1 = moo; // не ок: fcnPtr1 не имеет параметров, но moo() имеет
int (*fcnPtr3)(int) = moo; // ок
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
    int (*fcnPtr)() = boo; // fcnPtr указывает на функцию boo()
    fcnPtr = doo; // fcnPtr теперь указывает на функцию doo()

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

#ifdef Возврат_значений
#include <iostream> 
#include <array>

// Возвращаем ссылку на элемент массива по индексу index
int& getElement(std::array<int, 20>& array, int index)
{
    // Мы знаем, что array[index] не уничтожится, когда мы будем возвращать данные в caller (так как caller сам передал этот array в функцию!)
    // Так что здесь не должно быть никаких проблем с возвратом по ссылке 
    return array[index];
}

int* allocateArray(int size)
{
    return new int[size];
}

int main1()
{
    int* array = allocateArray(20);

    // Делаем что-нибудь с array

    delete[] array;

    std::array<int, 20> array1;

    // Присваиваем элементу массива под индексом 15 значение 7
    getElement(array1, 15) = 7;

    std::cout << array1[15] << '\n';


    return 0;
}
#endif

#ifdef Блэкджек
#include <iostream>
#include <array>
#include <ctime> // для time()
#include <cstdlib> // для rand() и srand()

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

// Генерируем случайное число между min и max (предполагается, что функция srand() уже была вызвана)
int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    // Равномерно распределяем генерацию случайного числа в диапазоне значений
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void shuffleDeck(std::array<Card, 52>& deck)
{
    // Перебираем каждую карту в колоде
    for (int index = 0; index < 52; ++index)
    {
        // Выбираем любую случайную карту
        int swapIndex = getRandomNumber(0, 51);
        // Меняем местами с нашей текущей картой
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
    // Настраиваем стартовый режим игры
    const Card* cardPtr = &deck[0];

    int playerTotal = 0;
    int dealerTotal = 0;

    // Дилер получает одну карту
    dealerTotal += getCardValue(*cardPtr++);
    std::cout << "The dealer is showing: " << dealerTotal << '\n';

    // Игрок получает две карты
    playerTotal += getCardValue(*cardPtr++);
    playerTotal += getCardValue(*cardPtr++);

    // Игрок начинает
    while (1)
    {
        std::cout << "You have: " << playerTotal << '\n';

        // Смотрим, не больше ли 21 очка у игрока
        if (playerTotal > 21)
            return false;

        char choice = getPlayerChoice();
        if (choice == 's')
            break;

        playerTotal += getCardValue(*cardPtr++);
    }

    // Если игрок не проиграл и у него не больше 21 очка, то тогда дилер получает карты до тех пор, пока у него не получится в сумме 17 очков
    while (dealerTotal < 17)
    {
        dealerTotal += getCardValue(*cardPtr++);
        std::cout << "The dealer now has: " << dealerTotal << '\n';
    }

    // Если у дилера больше 21 очка, то игрок победил
    if (dealerTotal > 21)
        return true;

    return (playerTotal > dealerTotal);
}

int main1()
{
    srand(static_cast<unsigned int>(time(0))); // устанавливаем значение системных часов в качестве стартового числа 
    rand(); // если используете Visual Studio, сбрасываем первое сгенерированное рандомное число

    std::array<Card, 52> deck;

    // Можно было бы вручную (по отдельности) инициализировать каждую карту, но мы ведь программисты! Цикл нам в помощь!
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
    array.resize(4); // изменяем длину array на 4

    std::cout << "The length is: " << array.size() << '\n';

    for (auto const& element : array)
        std::cout << element << ' ';

    return 0;
}
#endif

#ifdef std_array
//std::array — это отличная замена стандартных фиксированных массивов.
#include <iostream>
#include <array>
#include <algorithm> // для std::sort

int main1()
{
    std::array<int, 5> myarray{ 8, 4, 2, 7, 1 };
    std::sort(myarray.begin(), myarray.end()); // сортировка массива по возрастанию
//    std::sort(myarray.rbegin(), myarray.rend()); // сортировка массива по убыванию

    for (const auto& element : myarray)
        std::cout << element << ' ';

    return 0;
}
#endif

#ifdef Указатель_на_указатель
#include <iostream>
#include <bitset>
int main1() {
    int** array = new int* [15]; // выделяем массив из 15 указателей типа int — это наши строки
    for (int count = 0; count < 15; ++count)
        array[count] = new int[7]; // а это наши столбцы

    for (int count = 0; count < 15; ++count)
        delete[] array[count];
    delete[] array; // это следует выполнять в конце
    return 0;
}
#endif

#ifdef void_указатель //void*
//Указатель типа void — это указатель, который может указывать на объект 
//любого типа данных, но он сам не знает, какой это будет тип.
//Для разыменования указатель типа void должен быть явно преобразован 
//с помощью оператора static_cast в другой тип данных.Нулевой указатель — это указатель, 
//который не указывает на адрес.Указатель типа void может быть нулевым указателем.
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
        std::cout << *static_cast<int*>(ptr) << '\n'; // конвертируем в указатель типа int и выполняем разыменование
        break;
    case DOUBLE:
        std::cout << *static_cast<double*>(ptr) << '\n'; // конвертируем в указатель типа double и выполняем разыменование
        break;
    case CSTRING:
        std::cout << static_cast<char*>(ptr) << '\n'; // конвертируем в указатель типа char (без разыменования)
        // std::cout знает, что char* следует обрабатывать как строку C-style.
        // Если бы мы разыменовали результат (целое выражение), то тогда бы вывелся просто первый символ из массива букв, на который указывает ptr
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

#ifdef Константная_Ссылка
#include <iostream>

void printIt(const int& a)
{
    std::cout << a;
}

int main1()
{
    int x = 3;
    printIt(x); // неконстантное l-value

    const int y = 4;
    printIt(y); // константное l-value

    printIt(5); // литерал в качестве r-value

    printIt(3 + y); // выражение в качестве r-value

    return 0;
}
#endif

#ifdef Константные_указатели
#include <iostream>
#include <bitset>
int main1() {
    int value = 7;
    // ptr1 указывает на "const int", поэтому это указатель на константное значение 
    const int* ptr1 = &value;
    // ptr2 указывает на "int", поэтому это константный указатель на неконстантное значение
    int* const ptr2 = &value; 
    // ptr3 указывает на "const int", поэтому это константный указатель на константное значение    
    const int* const ptr3 = &value;

    return 0;
}
#endif

#ifdef Динамические массивы
#include <iostream>
#include <string>
#include <utility> // для std::swap(). Если у вас не поддерживается C++11, то тогда #include <algorithm>

void sortArray(std::string* array, int length)
{
    // Перебираем каждый элемент массива
    for (int startIndex = 0; startIndex < length; ++startIndex)
    {
        // smallestIndex - индекс наименьшего элемента, с которым мы столкнулись
        int smallestIndex = startIndex;

        // Ищем наименьший элемент, который остался в массиве (начиная со startIndex+1)
        for (int currentIndex = startIndex + 1; currentIndex < length; ++currentIndex)
        {
            // Если текущий элемент меньше нашего ранее найденного наименьшего элемента,
            if (array[currentIndex] < array[smallestIndex])
                // то тогда это новое наименьшее значение в этой итерации
                smallestIndex = currentIndex;
        }

        // Меняем местами наш начальный элемент с найденным наименьшим элементом массива
        std::swap(array[startIndex], array[smallestIndex]);
    }
}

int main1()
{
    std::cout << "How many names would you like to enter? ";
    int length;
    std::cin >> length;

    // Выделяем массив для хранения имен
    std::string* names = new std::string[length];

    // Просим пользователя ввести все имена
    for (int i = 0; i < length; ++i)
    {
        std::cout << "Enter name #" << i + 1 << ": ";
        std::cin >> names[i];
    }

    // Сортируем массив
    sortArray(names, length);

    std::cout << "\nHere is your sorted list:\n";
    // Выводим отсортированный массив
    for (int i = 0; i < length; ++i)
        std::cout << "Name #" << i + 1 << ": " << names[i] << '\n';

    delete[] names; // не забываем использовать оператор delete[] для освобождения памяти
    names = nullptr; // используйте 0, если не поддерживается C++11

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

#ifdef Арфиметика указателей
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
    doAnything(nullptr); // теперь аргумент является точно нулевым указателем, а не целочисленным значением
    doAnything1(nullptr); // теперь аргумент является точно нулевым указателем, а не целочисленным значением

    return 0;
}
#endif

#ifdef указатели
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
    char dest[50]; // обратите внимание, длина массива dest всего 5 символов!
    strcpy_s(dest, text); // переполнение если 5!
    std::cout << dest<< std::endl;

    char name[15] = "Max"; // используется только 4 символа (3 буквы + нуль-терминатор)
    std::cout << "My name is " << name << '\n';
    std::cout << name << " has " << strlen(name) << " letters.\n";
    std::cout << name << " has " << sizeof(name) << " characters in the array.\n";

    // Просим пользователя ввести строку
    char buffer[255];
    std::cout << "Enter a string: ";
    std::cin.getline(buffer, 255);

    int spacesFound = 0;
    // Перебираем каждый символ, который ввел пользователь
    for (int index = 0; index < strlen(buffer); ++index)
    {
        // Подсчитываем количество пробелов
        if (buffer[index] == ' ')
            spacesFound++;
    }

    std::cout << "You typed " << spacesFound << " spaces!\n";
    
    //функция strcat() — добавляет одну строку к другой(опасно);

    //функция strncat() — добавляет одну строку к другой(с проверкой размера места назначения);

    //функция strcmp() — сравнивает две строки(возвращает 0, если они равны);

    //функция strncmp() — сравнивает две строки до определенного количества символов(возвращает 0, если до указанного символа не было различий).
    
    return 0;
}
#endif

#ifdef двумерныйМассив табл. умножения
#include <iostream>

int main1()
{
    // Объявляем массив 10x10 
    const int numRows = 10;
    const int numCols = 10;
    int product[numRows][numCols] = { 0 };

    // Создаем таблицу умножения
    for (int row = 0; row < numRows; ++row)
        for (int col = 0; col < numCols; ++col)
            product[row][col] = row * col;

    // Выводим таблицу умножения
    for (int row = 1; row < numRows; ++row)
    {
        for (int col = 1; col < numCols; ++col)
            std::cout << product[row][col] << "\t";
        std::cout << '\n';
    }
    return 0;
}
#endif

#ifdef Пузырьком сортировка
#include <iostream> 
#include <algorithm> // для std::swap. В C++11 используйте заголовок <utility>

int main()
{
    const int length(9);
    int array[length] = { 7, 5, 6, 4, 9, 8, 2, 1, 3 };

    for (int iteration = 0; iteration < length - 1; ++iteration)
    {
        // Помните о том, что последний элемент будет отсортирован и в каждой последующей итерации цикла,
        // поэтому наша сортировка «заканчивается» на один элемент раньше
        int endOfArrayIndex(length - iteration);

        bool swapped(false); // отслеживаем, были ли выполнены замены в этой итерации

        // Перебираем каждый элемент массива до последнего (не включительно).
        // Последний элемент не имеет пары для сравнения
        for (int currentIndex = 0; currentIndex < endOfArrayIndex - 1; ++currentIndex)
        {
            // Если текущий элемент больше элемента, следующего за ним,
            if (array[currentIndex] > array[currentIndex + 1])
            {
                // то выполняем замену
                std::swap(array[currentIndex], array[currentIndex + 1]);
                swapped = true;
            }
        }

        // Если в этой итерации не выполнилось ни одной замены, то цикл можно завершать
        if (!swapped)
        {
            // Выполнение начинается с 0-й итерации, но мы привыкли считать, начиная с 1, поэтому для подсчета количества итераций добавляем единицу
            std::cout << "Early termination on iteration: " << iteration + 1 << '\n';
            break;
        }
    }

    // Выводим отсортированный массив на экран
    for (int index = 0; index < length; ++index)
        std::cout << array[index] << ' ';

    return 0;
}
#endif

#ifdef Сортировка массивов методом выбора
#include <iostream> 
#include <algorithm> // для std::swap. В C++11 используйте заголовок <utility>

int main1()
{
    const int length = 5;
    int array[length] = { 30, 50, 20, 10, 40 };

    // Перебираем каждый элемент массива (кроме последнего, он уже будет отсортирован к тому времени, когда мы до него доберемся)
    for (int startIndex = 0; startIndex < length - 1; ++startIndex)
    {
        // В переменной smallestIndex хранится индекс наименьшего значения, которое мы нашли в этой итерации.
        // Начинаем с того, что наименьший элемент в этой итерации - это первый элемент (индекс 0)
        int smallestIndex = startIndex;

        // Затем ищем элемент поменьше в остальной части массива
        for (int currentIndex = startIndex + 1; currentIndex < length; ++currentIndex)
        {
            // Если мы нашли элемент, который меньше нашего наименьшего элемента,
            if (array[currentIndex] < array[smallestIndex])
                // то запоминаем его
                smallestIndex = currentIndex;
        }

        // smallestIndex теперь наименьший элемент. 
        // Меняем местами наше начальное наименьшее число с тем, которое мы обнаружили
        std::swap(array[startIndex], array[smallestIndex]);
    }

    // Теперь, когда весь массив отсортирован - выводим его на экран
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

#ifdef Массив в цикле пример
#include <iostream>

int main1()
{
    int students[] = { 73, 85, 84, 44, 78 };
    const int numStudents = sizeof(students) / sizeof(students[0]);

    int maxScore = 0; // отслеживаем самую высокую оценку
    for (int person = 0; person < numStudents; ++person)
        if (students[person] > maxScore)
            maxScore = students[person];

    std::cout << "The best score was " << maxScore << '\n';

    return 0;
}
#endif

#ifdef фиксированый массив
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
    int testScores[StudentNames::MAX_STUDENTS]; // всего 6 студентов
    testScores[StudentNames::JOHN] = 65;
    std::cout << testScores[StudentNames::JOHN];
    return 0;
}
#endif

#ifdef Hi_Lo
#include <iostream>
#include <cstdlib> // для функций srand() и rand()
#include <ctime> // для функции time()

// Генерируем случайное число между min и max.
// Предполагается, что srand() уже вызывали
int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    // Равномерно распределяем выбор случайного числа в диапазоне
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

// Возвращаем true, если пользователь выиграл, false - если проиграл
bool playGame(int guesses, int number)
{
    // Цикл работы с догадками пользователя 
    for (int count = 1; count <= guesses; ++count)
    {
        std::cout << "Guess #" << count << ": ";
        int guess;
        std::cin >> guess;

        if (guess > number)
            std::cout << "Your guess is too high.\n";
        else if (guess < number)
            std::cout << "Your guess is too low.\n";
        else // догадка == число
            return true;
    }

    return false;
}

bool playAgain()
{
    // Продолжаем спрашивать у пользователя, хочет ли он сыграть еще раз до тех пор, пока он не нажмет 'y' или 'n'
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
    srand(static_cast<unsigned int>(time(0))); // в качестве стартового числа используем системные часы
    rand(); // сбрасываем первый результат, так как функция rand() не особо хорошо рандомизирует первое случайное число в Visual Studio

    const int guesses = 7; // у пользователя есть 7 попыток

    do
    {
        int number = getRandomNumber(1, 100); // число, которое пользователь должен угадать 

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

#ifdef ПользовательскийВвод2
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
        std::string input = ""; // Строка для хранения введенных символов

        std::cout << "Введите число: ";

        while (true) {
            current_char = _getch();

            if (current_char == '\r') { // Enter - завершение ввода
                break;
            }
            else if (current_char == '\b' && !input.empty()) { // Backspace - удаление последнего символа
                std::cout << "\b \b"; // Удаление последнего символа на экране
                input.pop_back(); // Удаление последнего символа из строки
                if (input.empty()) { // Если строка пустая, то сбрасываем флаги is_negative и has_decimal
                    is_negative = false;
                    has_decimal = false;
                    continue;
                }
                if (input.back() == '.') { // Если удаляется точка, то сбрасываем флаг has_decimal
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
            else { // Недопустимый символ - подаем звуковой сигнал
                std::cout << "\a"; // Звуковой сигнал
            }
        }
        std::cout << std::endl;
        // Проверка на очень большие и очень маленькие числа
        if (input.length() > 10 || (input.length() == 10 && (input[0] == '1' || (input[0] == '-' && input[1] == '1')))) {
            std::cout << "Ошибка: число слишком " << ((input[0] == '-')?"маленькое!":"большое!") << std::endl;
            continue; // Переходим к следующему вводу
        }

        if (has_decimal) {
            number = atof(input.c_str()); // Преобразуем строку в число с плавающей точкой
        }
        else {
            number = atoi(input.c_str()); // Преобразуем строку в целое число
        }

        std::cout << "Ваше число: " << number << std::endl;
        //break; // Выход из цикла, если число успешно введено
    }

    return 0;
}



#endif

#ifdef ПользовательскийВвод1
#include <iostream>
#include <string>
#include <regex>

bool is_valid_char(char c) {
    // Проверяем, является ли символ допустимым
    return (c >= '0' && c <= '9') || c == '-' || c == '.';
}

int main1() {
    std::string input;
    char current_char;

    std::cout << "Введите число: ";

    while (std::cin.get(current_char)) {
        if (is_valid_char(current_char)) {
            input += current_char; // Добавляем символ к строке
            std::cout << current_char; // Выводим символ на экран
        }
        // Если ввод - Enter, выходим из цикла
        if (current_char == '\n') {
            break;
        }
    }
    // Преобразуем строку в число (только если она не пуста)
    if (!input.empty()) {
        double number = std::stod(input);

        // Проверяем на очень большие и очень маленькие числа:
        if (number > 1e10 || number < -1e10) {
            std::cout << "Ошибка: число слишком большое!" << std::endl;
        }
        else if (number > -1e-10 && number < 1e-10) {
            std::cout << "Ошибка: число слишком маленькое!" << std::endl;
        }
        else {
            std::cout << "Число: " << number << std::endl;
        }
    }
    else {
        std::cout << "Ошибка: ввод пуст!" << std::endl;
    }

    return 0;
}

#endif

#ifdef ПользовательскийВвод
#include <iostream>

double getValue()
{
    while (true) // цикл продолжается до тех пор, пока пользователь не введет корректное значение
    {
        std::cout << "Enter a double value: ";
        double a;
        std::cin >> a;

        // Проверка на предыдущее извлечение
        if (std::cin.fail()) // если предыдущее извлечение оказалось неудачным,
        {
            std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
            std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
            std::cout << "Oops, that input is invalid.  Please try again.\n";
        }
        else
        {
            std::cin.ignore(32767, '\n'); // удаляем лишние значения

            return a;
        }
    }
}

char getOperator()
{
    while (true) // цикл продолжается до тех пор, пока пользователь не введет корректное значение
    {
        std::cout << "Enter one of the following: +, -, *, or /: ";
        char sm;
        std::cin >> sm;

        // Переменные типа char могут принимать любые символы из пользовательского ввода, поэтому нам не стоит беспокоиться по поводу возникновения неудачного извлечения

        std::cin.ignore(32767, '\n'); // удаляем лишний балласт

        // Выполняем проверку пользовательского ввода
        if (sm == '+' || sm == '-' || sm == '*' || sm == '/')
            return sm; // возвращаем обратно в caller
        else // в противном случае, сообщаем пользователю что что-то пошло не так
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

#ifdef ВихрьМерсенна генерация случайных чисел
#include <iostream>
// #include <ctime> // раскомментируйте, если используете Code::Blocks
#include <random> // для std::random_device и std::mt19937

int main1()
{
    std::random_device rd;
    std::mt19937 mersenne(rd()); // инициализируем Вихрь Мерсенна случайным стартовым числом 

// Примечание: Из-за одного бага в компиляторе Code::Blocks (если вы используете Code::Blocks в Windows) - удалите две строки кода выше и раскомментируйте следующую строку:
// std::mt19937 mersenne(static_cast<unsigned int>(time(0))); // инициализируем Вихрь Мерсенна случайным стартовым числом

    // Выводим несколько случайных чисел
    for (int count = 0; count < 48; ++count)
    {
        std::cout << mersenne() << "\t";

        // Если вывели 5 чисел, то вставляем символ новой строки
        if ((count + 1) % 5 == 0)
            std::cout << "\n";
    }
    return 0;
}
#endif

#ifdef ГПСЧ генератор псевдослучайных чисел
#include <iostream>
#include <cstdlib> // для функций rand() и srand()
#include <ctime> // для функции time()

unsigned int PRNG()
{
    // Наше стартовое число - 4 541
    static unsigned int seed = 4541;
    // Берем стартовое число и, с его помощью, генерируем новое значение.
    // Из-за использования очень больших чисел (и переполнения) угадать следующее число исходя из предыдущего - очень сложно
    seed = (8253729 * seed + 2396403);
    // Берем стартовое число и возвращаем значение в диапазоне от 0 до 32767
    return seed % 32768;
}
int main1()
{
    // Выводим 100 случайных чисел
    for (int count = 0; count < 100; ++count)
    {
        std::cout << PRNG() << "\t";
        // Если вывели 5 чисел, то вставляем символ новой строки
        if ((count + 1) % 5 == 0)
            std::cout << "\n";
    }
    std::cout << std::endl;
    srand(static_cast<unsigned int>(time(0))); // устанавливаем значение системных часов в качестве стартового числа

    for (int count = 0; count < 100; ++count)
    {
        std::cout << rand() << "\t";

        // Если вывели 5 чисел, то вставляем символ новой строки
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
    case '0': // если p = 0
    case '1': // если p = 1
    case '2': // если p = 2
    case '3': // если p = 3
    case '4': // если p = 4
    case '5': // если p = 5
    case '6': // если p = 6
    case '7': // если p = 7
    case '8': // если p = 8
    case '9': // если p = 9
        return true; // возвращаем true
    default: // в противном случае, возвращаем false
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

#ifdef Структуры
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

    // Выводим информацию о John
    printInformation(john);

    std::cout << "\n";

    // Выводим информацию о James
    printInformation(james);
    std::cout << sizeof(james);
    return 0;
}
#endif

#ifdef typedef_using
//Следующий typedef:
typedef double time_t; // используем time_t в качестве псевдонима для типа double

//В С++11 можно объявить как :
using time_t = double; // используем time_t в качестве псевдонима для типа double

//Эти два способа функционально эквивалентны.
#endif

#ifdef enum_class
#include <iostream>

int main1()
{
    enum class Fruits // добавление "class" к enum определяет перечисление с ограниченной областью видимости, вместо стандартного "глобального" перечисления 
    {
        LEMON, // LEMON находится внутри той же области видимости, что и Fruits
        KIWI
    };

    enum class Colors
    {
        PINK, // PINK находится внутри той же области видимости, что и Colors
        GRAY
    };

    Fruits fruit = Fruits::LEMON; // примечание: LEMON напрямую не доступен, мы должны использовать Fruits::LEMON
    Colors color = Colors::PINK; // примечание: PINK напрямую не доступен, мы должны использовать Colors::PINK

    //if (fruit == color) // ошибка компиляции, поскольку компилятор не знает, как сравнивать разные типы: Fruits и Colors
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
    COLOR_PURPLE, // присваивается 0
    COLOR_GRAY,   // присваивается 1
    COLOR_BLUE,   // присваивается 2
    COLOR_GREEN,  // присваивается 3
    COLOR_BROWN,  // присваивается 4
    COLOR_PINK,   // присваивается 5
    COLOR_YELLOW, // присваивается 6
    COLOR_MAGENTA // присваивается 7
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
    //std::cin >> color; // приведет к ошибке компиляции
    int inputColor;
    std::cin >> inputColor;
    Colors color = static_cast<Colors>(inputColor);
    printColor(color);
    return 0;
}
#endif

#ifdef String строки
#include <iostream>
#include <string>

int main1()
{
    //При вводе числовых значений не забывайте удалять символ новой строки 
    //из входного потока данных с помощью std::cin.ignore().
    std::cout << "Pick 1 or 2: ";
    int choice;
    std::cin >> choice;

    std::cin.ignore(32767, '\n'); // удаляем символ новой строки из входного потока данных

    std::cout << "Now enter your name: ";
    std::string myName;
    std::getline(std::cin, myName);

    std::cout << "Hello, " << myName << ", you picked " << choice << '\n';

    std::cout << myName << " has " << myName.length() << " characters\n";

    return 0;
}
#endif

#ifdef Явное_Приведение
int main1() {
    int i = 90;
    i = (int)(i / 3.6); //C-style избегаем, не проверяется компилятором
    i = static_cast<int>(i / 3.6);
    return 0;
}
#endif

#ifdef using_ объявления
#include <iostream>

int main1()
{
    using std::cout; // "using-объявление" сообщает компилятору, что cout следует обрабатывать, как std::cout
    cout << "Hello, world!"; // и никакого префикса std:: уже здесь не нужно!
    return 0;
}
#endif

#ifdef Foo_BooDoo Псевдонимы для пространств имен
#include <iostream>

namespace Boo
{
    namespace Doo
    {
        const int g_x = 7;
    }
}

namespace Foo = Boo::Doo; // Foo теперь считается как Boo::Doo

int main1()
{
    std::cout << Foo::g_x; // это, на самом деле, Boo::Doo::g_x
    return 0;
}
#endif

#ifdef BooDoo конфликтов имен (пространства имен)
namespace Boo
{
    // Эта версия doOperation() принадлежит пространству имен Boo
    constexpr int doOperation(int a, int b) noexcept
    {
        return a + b;
    }
}
namespace Doo
{
    // Эта версия doOperation() принадлежит пространству имен Doo
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

#ifdef s_ Статическая продолжительность жизни
int generateID()
{
    static int s_itemID = 0;
    return s_itemID++;
}
//выходя из области видимости, s_itemID не уничтожается
//но
//добавляя static к переменной, объявленной вне блока, мы определяем её как внутреннюю, 
//то есть такую, которую можно использовать только в файле, в котором она определена
#endif //

#ifdef g_ глобальные переменные – зло
double g_gravity(9.8); // можно экспортировать и использовать напрямую в любом файле
//Сделайте следующее :
static double g_gravity(9.8); // ограничиваем доступ к переменной только на этот файл
double getGravity() // эта функция может быть экспортирована в другие файлы для доступа к глобальной переменной
{
    return g_gravity;
}
//В - третьих, при написании автономной функции, использующей глобальные переменные, 
// не используйте их непосредственно в теле функции.Передавайте их в качестве параметров.
// Таким образом, если в вашей функции нужно будет когда - либо использовать другое значение, 
// то вы сможете просто изменить параметр.Это улучшит модульность вашей программы. 
//    Вместо следующего :
// Эта функция полезна только для расчета мгновенной скорости на основе глобальной гравитации
double instantVelocity(int time)
{
    return g_gravity * time;
}
//Сделайте следующее :
// Эта функция вычисляет мгновенную скорость для любого значения гравитации.
// Передайте возвращаемое значение из getGravity() в параметр gravity, 
// если хотите использовать глобальную переменную gravity
double instantVelocity(int time, double gravity)
{
    return gravity * time;
}
#endif //

#ifdef bitset
#include <iostream>
#include <bitset>

// Обратите внимание, используя std::bitset, наши options соответствуют порядковым номерам бит, а не их значениям
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
    // Помните, что отсчет бит начинается не с 1, а с 0
    std::bitset<8> bits(0x2); // нам нужно 8 бит, начнем с битового шаблона 0000 0010
    bits.set(option_5); // включаем 4-й бит - его значение изменится на 1 (теперь мы имеем 0001 0010)
    bits.flip(option_6); // изменяем значения 5-го бита на противоположное (теперь мы имеем 0011 0010)
    bits.reset(option_6); // выключаем 5-й бит - его значение снова 0 (теперь мы имеем 0001 0010)

    std::cout << "Bit 4 has value: " << std::boolalpha << bits.test(option_5) << '\n';
    std::cout << "Bit 5 has value: " << bits.test(option_6) << '\n';
    std::cout << "All the bits: " << bits << '\n';

    return 0;
}
#endif // 

#ifdef БитовыеФлаги
#include <iostream>

int main1()
{
    // Определяем набор физических/эмоциональных состояний 
    const unsigned char isHungry = 0x01; // шестнадцатеричный литерал для 0000 0001
    const unsigned char isSad = 0x02; // шестнадцатеричный литерал для 0000 0010
    const unsigned char isMad = 0x04; // шестнадцатеричный литерал для 0000 0100
    const unsigned char isHappy = 0x08; // шестнадцатеричный литерал для 0000 1000
    const unsigned char isLaughing = 0x10; // шестнадцатеричный литерал для 0001 0000
    const unsigned char isAsleep = 0x20; // шестнадцатеричный литерал для 0010 0000
    const unsigned char isDead = 0x40; // шестнадцатеричный литерал для 0100 0000
    const unsigned char isCrying = 0x80; // шестнадцатеричный литерал для 1000 0000

    unsigned char me = 0; // все флаги/параметры отключены до старта
    me |= isHappy | isLaughing; // Я isHappy и isLaughing
    me &= ~isLaughing; // Я уже не isLaughing

    // Запрашиваем сразу несколько состояний (мы будем использовать static_cast<bool> для конвертации результатов в значения типа bool)
    std::cout << "I am happy? " << std::boolalpha << static_cast<bool>(me & isHappy) << '\n'; //<< std::noboolalpha //для отмены boolalpha;
    std::cout << "I am laughing? " << static_cast<bool>(me & isLaughing) << '\n';

    return 0;
}
#endif // 

#ifdef epsilon Сравнение чисел типа с плавающей точкой
#include <cmath> // для функции fabs()
bool isAlmostEqual(double a, double b, double epsilon)
{
    // Если разница между a и b меньше значения эпсилона, то тогда a и b можно считать равными
    return fabs(a - b) <= epsilon;
}
//Дональд Кнут, известный учёный, предложил следующий способ в своей книге «Искусство программирования, том 2: Получисленные алгоритмы» (1968):
// Возвращаем true, если разница между a и b в пределах процента эпсилона 
bool approximatelyEqual(double a, double b, double epsilon)
{
    return fabs(a - b) <= ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}
//С удачно подобранным absEpsilon, функция approximatelyEqualAbsRel() обрабатывает близкие к нулю и нулевые значения корректно.
// Возвращаем true, если разница между a и b меньше absEpsilon или в пределах relEpsilon 
bool approximatelyEqualAbsRel(double a, double b, double absEpsilon, double relEpsilon)
{
    // Проверяем числа на равенство их друг другу - это нужно в случаях, когда сравниваемые числа являются нулевыми или около нуля
    double diff = fabs(a - b);
    if (diff <= absEpsilon)
        return true;

    // В противном случае, возвращаемся к алгоритму Кнута
    return diff <= ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * relEpsilon);
}
//Сравнение чисел типа с плавающей точкой — сложная тема, и нет одного идеального алгоритма, который подойдет в любой ситуации.
//Однако для большинства случаев, с которыми вы будете сталкиваться, функции approximatelyEqualAbsRel() должно быть достаточно.
int main1()
{
    // Значение a очень близко к 1.0, но, из-за ошибок округления, чуть меньше 1.0
    double a = 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1;

    std::cout << approximatelyEqual(a, 1.0, 1e-8) << "\n";     // сравниваем "почти 1.0" с 1.0
    std::cout << approximatelyEqual(a - 1.0, 0.0, 1e-8) << "\n"; // сравниваем "почти 0.0" с 0.0
    std::cout << approximatelyEqualAbsRel(a - 1.0, 0.0, 1e-12, 1e-8) << "\n"; // сравниваем "почти 0.0" с 0.0
}
#endif // 

#ifdef ЧислоЧетное?
bool isEven(int aDec)
{
    return !(aDec & 0x1);
}
#endif // ЧислоЧетное?

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

#ifdef Степень_int
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
#endif // Степень_int

