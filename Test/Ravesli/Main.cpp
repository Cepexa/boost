#include <iostream>
#define DEBUG

#ifdef DEBUG
  int main1() {} 
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
