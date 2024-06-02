#include <iostream>
#define DEBUG

#ifdef DEBUG
  int main1() {} 
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
