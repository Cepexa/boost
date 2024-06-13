#include <iostream>
#define Конструкторы_преобразования

#ifdef Конструкторы_преобразования ключевые слова explicit и delete
#include <cassert>

class Drob
{
private:
	int m_numerator;
	int m_denominator;

public:
	// Конструктор по умолчанию
	Drob(int numerator = 0, int denominator = 1) :
		m_numerator(numerator), m_denominator(denominator)
	{
		assert(denominator != 0);
	}

	// Конструктор копирования
	Drob(const Drob& copy) :
		m_numerator(copy.m_numerator), m_denominator(copy.m_denominator)
	{
		// Нет необходимости выполнять проверку denominator здесь, так как эта проверка уже осуществлена в конструкторе по умолчанию
		std::cout << "Copy constructor worked here!\n"; // просто, чтобы показать, что это работает
	}

	friend std::ostream& operator<<(std::ostream& out, const Drob& d1);
	int getNumerator() { return m_numerator; }
	void setNumerator(int numerator) { m_numerator = numerator; }
};

std::ostream& operator<<(std::ostream& out, const Drob& d1)
{
	out << d1.m_numerator << "/" << d1.m_denominator;
	return out;
}

Drob makeNegative(Drob d)
{
	d.setNumerator(-d.getNumerator());
	return d;
}
#include <string>

class SomeString
{
private:
	std::string m_string;
public:
	SomeString(char) = delete; // любое использование этого конструктора приведет к ошибке
	// Ключевое слово explicit делает этот конструктор закрытым для выполнения любых неявных преобразований
	explicit SomeString(int a) // выделяем строку размером a
	{
		m_string.resize(a);
	}

	SomeString(const char* string) // выделяем строку для хранения значения типа string
	{
		m_string = string;
	}

	friend std::ostream& operator<<(std::ostream& out, const SomeString& s);

};

std::ostream& operator<<(std::ostream& out, const SomeString& s)
{
	out << s.m_string;
	return out;
}

int main()
{
	SomeString mystring = "a";//'a'; // ошибка компиляции, поскольку SomeString(int) теперь является explicit и, соответственно, недоступен, а другого подходящего конструктора для преобразования компилятор не видит
	std::cout << mystring;
	return 0;

	std::cout << makeNegative(7); // передаем целочисленное значение

	return 0;
}
#endif

#ifdef Конструктор_копирования
#include <cassert>

class Drob
{
private:
	int m_numerator;
	int m_denominator;
	
public:
	// Конструктор по умолчанию
	Drob(int numerator = 0, int denominator = 1) :
		m_numerator(numerator), m_denominator(denominator)
	{
		assert(denominator != 0);
	}

	// Конструктор копирования
	Drob(const Drob& drob) :
		m_numerator(drob.m_numerator), m_denominator(drob.m_denominator)
		// Примечание: Мы имеем прямой доступ к членам объекта drob, поскольку мы сейчас находимся внутри класса Drob
	{
		// Нет необходимости выполнять проверку denominator здесь, так как эта проверка уже осуществляется в конструкторе класса Drob
		std::cout << "Copy constructor worked here!\n"; // просто, чтобы показать, что это работает
	}

	friend std::ostream& operator<<(std::ostream& out, const Drob& d1);
};

std::ostream& operator<<(std::ostream& out, const Drob& d1)
{
	out << d1.m_numerator << "/" << d1.m_denominator;
	return out;
}

int main()
{
	Drob sixSeven(6, 7); // прямая инициализация объекта класса Drob, вызывается конструктор Drob(int, int)
	Drob dCopy(sixSeven); // прямая инициализация, вызывается конструктор копирования класса Drob
	std::cout << dCopy << '\n';

	Drob sixSeven_(Drob(6, 7));//элизия
	//компилятору разрешается отказаться от вызова конструктора копирования и просто выполнить прямую инициализацию
	std::cout << sixSeven_ << '\n';
}

#endif

#ifdef Перегрузка_операций_преобразования типов данных
class Dollars
{
private:
	int m_dollars;
public:
	Dollars(int dollars = 0)
	{
		m_dollars = dollars;
	}

	// Перегрузка операции преобразования значения типа Dollars в значение типа int
	operator int() { return m_dollars; }

	int getDollars() { return m_dollars; }
	void setDollars(int dollars) { m_dollars = dollars; }
};

class Cents
{
private:
	int m_cents;
public:
	Cents(int cents = 0)
	{
		m_cents = cents;
	}

	// Выполняем конвертацию Cents в Dollars
	operator Dollars() { return Dollars(m_cents / 100); }
};

void printDollars(Dollars dollars)
{
	std::cout << dollars; // dollars неявно конвертируется в int здесь
}

int main()
{
	Cents cents(700);
	printDollars(cents); // cents неявно конвертируется в Dollars здесь

	return 0;
}
#endif

#ifdef функторы_Тест
class Mystring
{
public:
	Mystring(const std::string& str);
	~Mystring();
	std::string operator()(int first, int length);
private:
	std::string str;
};

Mystring::Mystring(const std::string& str=""):str(str)
{
}

Mystring::~Mystring()
{
}
std::string Mystring::operator()(int first, int length) {
	std::string ret;
	for (int count = 0; count < length; ++count)
		ret += str[first + count];
	return ret;
}
int main()
{
	Mystring string("Hello, world!");
	std::cout << string(7, 6); // начинаем с 7-го символа (индекса) и возвращаем следующие 6 символов

	return 0;
}
#endif 

#ifdef Функторы Перегрузка_оператора_ ()
#include <cassert> // для assert()

class Matrix
{
private:
	double data[5][5];
public:
	Matrix()
	{
		// Присваиваем всем элементам массива значение 0.0
		for (int row = 0; row < 5; ++row)
			for (int col = 0; col < 5; ++col)
				data[row][col] = 0.0;
	}
	double& operator()(int row, int col);
	const double& operator()(int row, int col) const;
	void operator()();
};

double& Matrix::operator()(int row, int col)
{
	assert(col >= 0 && col < 5);
	assert(row >= 0 && row < 5);
	return data[row][col];
}

const double& Matrix::operator()(int row, int col) const
{
	assert(col >= 0 && col < 5);
	assert(row >= 0 && row < 5);
	return data[row][col];
}

void Matrix::operator()()
{
	// Сбрасываем значения всех элементов массива на 0.0
	for (int row = 0; row < 5; ++row)
		for (int col = 0; col < 5; ++col)
			data[row][col] = 0.0;
}

int main()
{
	Matrix matrix;
	matrix(2, 3) = 3.6;
	matrix(); // выполняем сброс
	std::cout << matrix(2, 3);
	return 0;
}
#endif

#ifdef Перегрузка_Итоговый_тест
#include <string>
#include <vector>
struct StudentGrade
{
	std::string name;
	char score;
};
class GradeMap
{
public:
	GradeMap();
	~GradeMap();
	char& operator[](const std::string& str);
private:
	std::vector<StudentGrade> m_map;
};

GradeMap::GradeMap()
{
}

GradeMap::~GradeMap()
{
}

char& GradeMap::operator[](const std::string& name) {
	for (auto& el : m_map) {
		if (name == el.name) {
			return el.score;
		}
	}
	StudentGrade temp{ name,' ' };
	m_map.push_back(temp);

	return m_map.back().score;
}
int main()
{
	GradeMap grades;
	//grades["John"] = 'A';
	//grades["Martin"] = 'B';
	//std::cout << "John has a grade of " << grades["John"] << '\n';
	//std::cout << "Martin has a grade of " << grades["Martin"] << '\n';


	char& gradeJohn = grades["John"]; // выполняется push_back
	gradeJohn = 'A';

	char& gradeMartin = grades["Martin"]; // выполняется push_back
	gradeMartin = 'B';

	std::cout << "John has a grade of " << gradeJohn << '\n';
	std::cout << "Martin has a grade of " << gradeMartin << '\n';

	return 0;
}
#endif

#ifdef Перегрузка_оператора_индексации []
#include <cassert>
class IntArray
{
private:
	int m_array[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // указываем начальные значения

public:
	int& operator[] (const int index);
	const int& operator[] (const int index) const;
};

int& IntArray::operator[] (const int index) // для неконстантных объектов: может использоваться как для присваивания значений элементам, так и для их просмотра
{
	assert(index >= 0 && index < 10);
	return m_array[index];
}

const int& IntArray::operator[] (const int index) const // для константных объектов: используется только для просмотра (вывода) элементов массива
{
	return m_array[index];
}

int main()
{
	IntArray array;
	array[11] = 5; // хорошо: вызывается неконстантная версия operator[]()
	std::cout << array[4]<<std::endl;

	const IntArray carray;
	//carray[4] = 5; // ошибка компиляции: вызывается константная версия operator[](), которая возвращает константную ссылку. Выполнять операцию присваивания нельзя
	std::cout << carray[4] << std::endl;

	return 0;
}
#endif

#ifdef Перегрузка_операторов_инкремента и декремента ++ --
class Number
{
private:
	int m_number;
public:
	Number(int number = 0)
		: m_number(number)
	{
	}

	Number& operator++(); // версия префикс
	Number& operator--(); // версия префикс

	Number operator++(int); // версия постфикс
	Number operator--(int); // версия постфикс

	friend std::ostream& operator<< (std::ostream& out, const Number& n);
};

Number& Number::operator++()
{
	// Если значением переменной m_number является 8, то выполняем сброс значения m_number на 0
	if (m_number == 8)
		m_number = 0;
	// В противном случае, просто увеличиваем m_number на единицу
	else
		++m_number;

	return *this;
}

Number& Number::operator--()
{
	// Если значением переменной m_number является 0, то присваиваем m_number значение 8
	if (m_number == 0)
		m_number = 8;
	// В противном случае, просто уменьшаем m_number на единицу
	else
		--m_number;

	return *this;
}

Number Number::operator++(int)
{
	// Создаем временный объект класса Number с текущим значением переменной m_number
	Number temp(m_number);

	// Используем оператор инкремента версии префикс для реализации перегрузки оператора инкремента версии постфикс
	++(*this); // реализация перегрузки

	// Возвращаем временный объект
	return temp;
}

Number Number::operator--(int)
{
	// Создаем временный объект класса Number с текущим значением переменной m_number
	Number temp(m_number);

	// Используем оператор декремента версии префикс для реализации перегрузки оператора декремента версии постфикс
	--(*this); // реализация перегрузки

	// Возвращаем временный объект
	return temp;
}

std::ostream& operator<< (std::ostream& out, const Number& n)
{
	out << n.m_number;
	return out;
}

int main()
{
	Number number(6);

	std::cout << number;
	std::cout << ++number; // вызывается Number::operator++();
	std::cout << number++; // вызывается Number::operator++(int);
	std::cout << number;
	std::cout << --number; // вызывается Number::operator--();
	std::cout << number--; // вызывается Number::operator--(int);
	std::cout << number;

	return 0;
}
#endif

#ifdef Перегрузка_операторов_сравнения
#include <string>
#include <vector>
#include <algorithm>
class Car
{
private:
	std::string m_company;
	std::string m_model;

public:
	Car(std::string company, std::string model)
		: m_company(company), m_model(model)
	{
	}

	friend bool operator== (const Car& c1, const Car& c2);
	friend bool operator!= (const Car& c1, const Car& c2);
	friend bool operator< (const Car& c1, const Car& c2);
	friend std::ostream& operator<< (std::ostream& out, const Car& c);
};

bool operator== (const Car& c1, const Car& c2)
{
	return (c1.m_company == c2.m_company &&
		c1.m_model == c2.m_model);
}

bool operator!= (const Car& c1, const Car& c2)
{
	return !(c1 == c2);
}

bool operator< (const Car& c1, const Car& c2)
{
	return (c1.m_company < c2.m_company)||((c1.m_company==c2.m_company)&&(c1.m_model<c2.m_model));
}

std::ostream& operator<< (std::ostream& out, const Car& c) {
	out << '(' << c.m_company << ',' << c.m_model << ')';
	return out;
}

class Dollars
{
private:
	int m_dollars;

public:
	Dollars(int dollars) { m_dollars = dollars; }

	friend bool operator> (const Dollars& d1, const Dollars& d2);
	friend bool operator<= (const Dollars& d1, const Dollars& d2);

	friend bool operator< (const Dollars& d1, const Dollars& d2);
	friend bool operator>= (const Dollars& d1, const Dollars& d2);
};

bool operator> (const Dollars& d1, const Dollars& d2)
{
	return d1.m_dollars > d2.m_dollars;
}

bool operator< (const Dollars& d1, const Dollars& d2)
{
	return d1.m_dollars < d2.m_dollars;
}

bool operator>= (const Dollars& d1, const Dollars& d2)
{
	return !(d1 < d2);
}

bool operator<= (const Dollars& d1, const Dollars& d2)
{
	return !(d1 > d2);
}

int main()
{
	std::vector<Car> v;
	v.push_back(Car("Ford", "Mustang"));
	v.push_back(Car("Renault", "Logan"));
	v.push_back(Car("Ford", "Ranger"));
	v.push_back(Car("Renault", "Duster"));

	std::sort(v.begin(), v.end()); // требуется перегрузка оператора < для класса Car

	for (auto& car : v)
		std::cout << car << '\n'; // требуется перегрузка оператора << для класса Car

	return 0;


	Dollars ten(10);
	Dollars seven(7);

	if (ten > seven)
		std::cout << "Ten dollars are greater than seven dollars.\n";
	if (ten >= seven)
		std::cout << "Ten dollars are greater than or equal to seven dollars.\n";
	if (ten < seven)
		std::cout << "Seven dollars are greater than ten dollars.\n";
	if (ten <= seven)
		std::cout << "Seven dollars are greater than or equal to ten dollars.\n";


	Car mustang("Ford", "Mustang");
	Car logan("Renault", "Logan");

	if (mustang == logan)
		std::cout << "Mustang and Logan are the same.\n";

	if (mustang != logan)
		std::cout << "Mustang and Logan are not the same.\n";

	return 0;
}
#endif

#ifdef Перегрузка_унарных_операторов
class Dollars
{
private:
	int m_dollars;

public:
	Dollars(int dollars) { m_dollars = dollars; }

	// Выполняем -Dollars через метод класса
	Dollars operator-() const;

	int getDollars() const { return m_dollars; }
};

// Эта функция является методом класса!
Dollars Dollars::operator-() const
{
	return Dollars(-m_dollars);
}
class Something
{
private:
	double m_a, m_b, m_c;

public:
	Something(double a = 0.0, double b = 0.0, double c = 0.0) :
		m_a(a), m_b(b), m_c(c)
	{
	}

	// Конвертируем объект класса Something в отрицательный 
	Something operator- () const
	{
		return Something(-m_a, -m_b, -m_c);
	}

	// Конвертируем объект класса Something в отрицательный 
	Something operator+ () const
	{
		return *this;
	}

	// Возвращаем true, если используются значения по умолчанию, в противном случае - false
	bool operator! () const
	{
		return (m_a == 0.0 && m_b == 0.0 && m_c == 0.0);
	}

	double getA() { return m_a; }
	double getB() { return m_b; }
	double getC() { return m_c; }
};



int main()
{
	Something something; // используем конструктор по умолчанию со значениями 0.0, 0.0, 0.0

	if (!something)
		std::cout << "Something is null.\n";
	else
		std::cout << "Something is not null.\n";


	const Dollars dollars1(7);
	std::cout << "My debt is " << (dollars1).getDollars() << " dollars.\n";

	return 0;
}
#endif

#ifdef Перегрузка_через_методы классов
#include <iostream>

class Dollars
{
private:
	int m_dollars;

public:
	Dollars(int dollars) { m_dollars = dollars; }

	// Выполняем Dollars + int
	Dollars operator+(int value);

	int getDollars() { return m_dollars; }
};

// Примечание: Эта функция является методом класса!
// Вместо параметра dollars в перегрузке через дружественную функцию здесь неявный параметр, на который указывает указатель *this
Dollars Dollars::operator+(int value)
{
	return Dollars(m_dollars + value);
}

int main()
{
	Dollars dollars1(7);
	Dollars dollars2 = dollars1 + 3;
	std::cout << "I have " << dollars2.getDollars() << " dollars.\n";

	return 0;
}
#endif

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