#include <iostream>
#define DEBUG

#ifdef DEBUG
#include <iostream>
#include <bitset>
int main1() {

    float i = 90;
    i = i / 3.6;
    std::cout << i << "\n";
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
            std::cout << "������: ����� ������� �������!" << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ������� ������ �����
            continue; // ��������� � ���������� �����
        }

        if (has_decimal) {
            number = atof(input.c_str()); // ����������� ������ � ����� � ��������� ������
        }
        else {
            number = atoi(input.c_str()); // ����������� ������ � ����� �����
        }

        if (is_negative) {
            number *= -1;
        }

        // �������� �� ����� ��������� �����
        if (number > -1e-10 && number < 1e-10) {
            std::cout << "������: ����� ������� ���������!" << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ������� ������ �����
            continue; // ��������� � ���������� �����
        }

        std::cout << "�����: " << number << std::endl;
        break; // ����� �� �����, ���� ����� ������� �������
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

int main() {
    system("chcp 1251 > nul");
    main1();
    return 0;
}