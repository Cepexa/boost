#include <iostream>
#define DEBUG

#ifdef DEBUG
#include <iostream>
#include <bitset>
int main1() {
    int array[]{ 4, 5, 8, 9, 12 };
    float i = 90;
    i = i / 3.6;
    std::cout << i << "\n";
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

int main() {
    system("chcp 1251 > nul");
    main1();
    return 0;
}