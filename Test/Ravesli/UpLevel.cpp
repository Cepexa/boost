#include <iostream>
#define Перегрузка_тест

#ifdef Перегрузка_тест
class Fraction
{
public:
	Fraction(int numerator = 0, int denominator = 1);
	~Fraction();
	void print();
	friend Fraction operator*(const Fraction& fraction, int decimal);
	friend Fraction operator*(int decimal, const Fraction& fraction);
	friend Fraction operator*(const Fraction& fr1, const Fraction& fr2);
	friend std::ostream& operator<<(std::ostream& out, const Fraction& fr);
	friend std::istream& operator>>(std::istream& in, Fraction& fr);
	static int nod(int a, int b);
	void reduce();
private:
	int numerator, denominator;
};
void Fraction::reduce() {
	int n = nod(numerator, denominator);
	numerator /= n;
	denominator /= n;
}
int Fraction::nod(int a, int b) {
	return (b == 0) ? (a > 0 ? a : -a) : nod(b, a % b);
}
Fraction::Fraction(int numerator, int denominator) :numerator(numerator), denominator(denominator) {
	reduce();
}
Fraction::~Fraction() {}
void Fraction::print() {
	std::cout << numerator << '/' << denominator << std::endl;
}
Fraction operator*(const Fraction& fraction, int decimal) {
	return Fraction(fraction.numerator * decimal, fraction.denominator);
}
Fraction operator*(int decimal, const Fraction& fraction) {
	return fraction * decimal;
}
Fraction operator*(const Fraction& fr1, const Fraction& fr2) {
	return Fraction(fr1.numerator * fr2.numerator, fr1.denominator * fr2.denominator);
}
std::ostream& operator<<(std::ostream& out, const Fraction& fr) {
	out << fr.numerator << '/' << fr.denominator;
	return out;
}
std::istream& operator>>(std::istream& in, Fraction& fr) {
	char c;
	// Перезаписываем значения объекта f1
	in >> fr.numerator;
	in >> c; // игнорируем разделитель '/'
	in >> fr.denominator;
	// Поскольку мы перезаписали существующий f1, то нам нужно повторно выполнить уменьшение дроби
	fr.reduce();
	return in;
}
int main()
{
	Fraction f1(3, 4);
	f1.print();

	Fraction f2(2, 7);
	f2.print();

	Fraction f3 = f1 * f2;
	f3.print();

	Fraction f4 = f1 * 3;
	f4.print();

	Fraction f5 = 3 * f2;
	f5.print();

	Fraction f6 = Fraction(1, 2) * Fraction(2, 3) * Fraction(3, 4);
	f6.print();

	Fraction f11;
	std::cout << "Enter fraction 1: ";
	std::cin >> f11;

	Fraction f21;
	std::cout << "Enter fraction 2: ";
	std::cin >> f21;

	std::cout << f11 << " * " << f21 << " is " << f11 * f21 << '\n';

	return 0;
}
#endif

#ifdef Перегрузка_оператора_ввода и вывода
class Point
{
private:
	double m_x, m_y, m_z;

public:
	Point(double x = 0.0, double y = 0.0, double z = 0.0) : m_x(x), m_y(y), m_z(z)
	{
	}

	friend std::ostream& operator<< (std::ostream& out, const Point& point);
	friend std::istream& operator>> (std::istream& in, Point& point);
};

std::ostream& operator<< (std::ostream& out, const Point& point)
{
	// Поскольку operator<< является другом класса Point, то мы имеем прямой доступ к членам Point
	out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z << ")";

	return out;
}

std::istream& operator>> (std::istream& in, Point& point)
{
	// Поскольку operator>> является другом класса Point, то мы имеем прямой доступ к членам Point.
	// Обратите внимание, параметр point (объект класса Point) должен быть неконстантным, чтобы мы имели возможность изменить члены класса
	in >> point.m_x;
	in >> point.m_y;
	in >> point.m_z;

	return in;
}
int main()
{
	std::cout << "Enter a point: \n";

	Point point;
	std::cin >> point;

	std::cout << "You entered: " << point << '\n';

	return 0;
}
#endif

#ifdef Перегрузка_оператора_плюс и минус 
class Dollars
{
private:
	int m_dollars;

public:
	Dollars(int dollars) { m_dollars = dollars; }

	// Выполняем Dollars + Dollars через дружественную функцию
	friend Dollars operator+(const Dollars& d1, const Dollars& d2);
	// Выполняем Dollars - Dollars через дружественную функцию
	friend Dollars operator-(const Dollars& d1, const Dollars& d2);
	// Выполняем Dollars + int через дружественную функцию
	friend Dollars operator+(const Dollars& d1, int value);
	// Выполняем int + Dollars через дружественную функцию
	friend Dollars operator+(int value, const Dollars& d1);

	int getDollars() const { return m_dollars; }
};

// Примечание: Эта функция не является методом класса!
Dollars operator+(const Dollars& d1, const Dollars& d2)
{
	// Используем конструктор Dollars и operator+(int, int).
	// Мы имеем доступ к закрытому члену m_dollars, поскольку эта функция является дружественной классу Dollars
	return Dollars(d1.m_dollars + d2.m_dollars);
}
// Примечание: Эта функция не является методом класса!
Dollars operator-(const Dollars& d1, const Dollars& d2)
{
	// Используем конструктор Dollars и operator-(int, int).
	// Мы имеем доступ к закрытому члену m_dollars, поскольку эта функция является дружественной классу Dollars
	return Dollars(d1.m_dollars - d2.m_dollars);
}
// Примечание: Эта функция не является методом класса!
Dollars operator+(const Dollars& d1, int value)
{
	// Используем конструктор Dollars и operator+(int, int).
	// Мы имеем доступ к закрытому члену m_dollars, поскольку эта функция является дружественной классу Dollars
	return Dollars(d1.m_dollars + value);
}
// Примечание: Эта функция не является методом класса!
Dollars operator+(int value, const Dollars& d1)
{
	// Используем конструктор Dollars и operator+(int, int).
	// Мы имеем доступ к закрытому члену m_dollars, поскольку эта функция является дружественной классу Dollars
	return d1 + value;
}
int main()
{
	Dollars d1 = Dollars(5) + 5;
	Dollars d2 = 5 + Dollars(5);
	std::cout << "I have " << d1.getDollars() << " dollars." << std::endl;
	std::cout << "I have " << d2.getDollars() << " dollars." << std::endl;
	Dollars dollars1(7);
	Dollars dollars2(9);
	Dollars dollarsSum  = dollars1 + dollars2;
	Dollars dollarsSum2 = dollars1 - dollars2;
	std::cout << "I have " << dollarsSum.getDollars() << " dollars." << std::endl;
	std::cout << "I have " << dollarsSum2.getDollars() << " dollars." << std::endl;

	return 0;
}
#endif 