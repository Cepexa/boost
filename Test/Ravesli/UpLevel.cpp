#include <iostream>
#define ��������_����1

#ifdef ��������_����



class Average
{
public:
	Average();
	~Average();
	Average& operator += (const int32_t& value) {
		sum += value;
		++count;
		return *this;
	}
	friend std::ostream& operator << (std::ostream& out, const Average& a);
private:
	int32_t sum = 0;
	int8_t count = 0;
};
Average::Average()
{
}
Average::~Average()
{
}
std::ostream& operator << (std::ostream& out, const Average& a) {
	out << static_cast<double>(a.sum) / a.count;
	return out;
}

#include <cassert> // ��� ����������� assert
class IntArray
{
public:
	IntArray(int size);
	IntArray(const IntArray& ia);
	~IntArray();
	int& operator[] (const int& index);
	IntArray& operator = (const IntArray& ia);
	friend std::ostream& operator << (std::ostream& out, const IntArray& a);
private:
	int* arr;
	int size;
};
IntArray& IntArray::operator = (const IntArray& ia) {
	if (&ia == this) 
		return *this;
	delete[] arr;// ���� ������ ��� ����������, �� ������� ���, ���� �� ��������� ������ ������

	size = ia.size;
	arr = new int[size];
	for (int i = 0; i < size; i++)
	{
		arr[i] = ia.arr[i];
	}
	return *this;
}
std::ostream& operator << (std::ostream& out, const IntArray& a) {
	for (int i = 0; i < a.size; i++)
	{
		out << *(a.arr + i) << ' ';
	}
	return out;
}
int& IntArray::operator[] (const int& index) {
	assert(index >= 0);
	assert(index < size);
	return arr[index];
}
IntArray::IntArray(int size):size(size)
{
	assert(size > 0 && "IntArray length should be a positive integer");
	arr = new int[size] {0};
}
IntArray::IntArray(const IntArray& ia): size(ia.size)
{
	arr = new int[size];
	for (int i = 0; i < size; i++)
	{
		arr[i] = ia.arr[i];
	}
}
IntArray::~IntArray()
{
	delete[] arr;
}
IntArray fillArray()
{
	IntArray a(6);
	a[0] = 6;
	a[1] = 7;
	a[2] = 3;
	a[3] = 4;
	a[4] = 5;
	a[5] = 8;

	return a;
}

class FixedPoint
{
public:
	FixedPoint(int16_t first, int16_t second);
	FixedPoint(double d);
	~FixedPoint();
	operator double() const;
	friend std::ostream& operator<< (std::ostream& out, const FixedPoint& fp);
	friend bool operator==(const FixedPoint& fp1, const FixedPoint& fp2)
	{
		return (fp1.first == fp2.first && fp1.second == fp2.second);
	}

	friend std::istream& operator >> (std::istream& in, FixedPoint& fp)
	{
		double d;
		in >> d;
		fp = FixedPoint(d);

		return in;
	}

	friend FixedPoint operator+(const FixedPoint& fp1, const FixedPoint& fp2)
	{
		return FixedPoint(static_cast<double>(fp1) + static_cast<double>(fp2));
	}

	FixedPoint operator-()
	{
		return FixedPoint(-first, -second);
	}
private:
	int16_t first;
	int16_t second;
	bool sign;
};

FixedPoint::FixedPoint(int16_t first, int16_t second):first(abs(first)), 
													  second(abs(second)),
												      sign(second >= 0 && first >= 0)
{}
FixedPoint::FixedPoint(double d)
{
	// ������� ��� ����� �������� ����� ����� ��������.
	// �� ����� ������� ���, ����������� ���� ����� ���� double � ����� ���� int
	first = static_cast<int16_t>(d); // ������������� ������� �����

	// ������ ��� ����� �������� ������� ����� ������ ��������:
	// 1) d - m_base ��������� ������ ������� �����,
	// 2) ������� ����� �� ����� �������� �� 100, ���������� ��� ����� �� ������� ����� � ����� ����� ��������
	// 3) ������ �� ����� ��� ���� ���������
	// 4) �, �������, �������������� � ��� int, ����� ��������� ����� �������������� �����
	second = static_cast<std::int8_t>(round((d - first) * 100));
}
FixedPoint::~FixedPoint()
{
}

FixedPoint::operator double() const {
	return (this->sign ? 1 : -1) * (this->first +  static_cast<double> (this->second) / 100);
}
std::ostream& operator<< (std::ostream& out, const FixedPoint& fp) {
	out << static_cast<double>(fp);
	return out;
}
void SomeTest()
{
	std::cout << std::boolalpha;
	std::cout << (FixedPoint(0.75) + FixedPoint(1.23) == FixedPoint(1.98)) << '\n'; // ��� �������� �������������, �������� ������������
	std::cout << (FixedPoint(0.75) + FixedPoint(1.50) == FixedPoint(2.25)) << '\n'; // ��� �������� �������������, ������������
	std::cout << (FixedPoint(-0.75) + FixedPoint(-1.23) == FixedPoint(-1.98)) << '\n'; // ��� �������� �������������, �������� ������������
	std::cout << (FixedPoint(-0.75) + FixedPoint(-1.50) == FixedPoint(-2.25)) << '\n'; // ��� �������� �������������, ������������
	std::cout << (FixedPoint(0.75) + FixedPoint(-1.23) == FixedPoint(-0.48)) << '\n'; // ������ �������� �������������, �������� ������������
	std::cout << (FixedPoint(0.75) + FixedPoint(-1.50) == FixedPoint(-0.75)) << '\n'; // ������ �������� �������������, �������� ������������
	std::cout << (FixedPoint(-0.75) + FixedPoint(1.23) == FixedPoint(0.48)) << '\n'; // ������ �������� �������������, �������� ������������
	std::cout << (FixedPoint(-0.75) + FixedPoint(1.50) == FixedPoint(0.75)) << '\n'; // ������ �������� �������������, �������� ������������
}
int main()
{
	//������� 4
	SomeTest();
	FixedPoint a3(-0.48);
	std::cout << a3 << '\n';

	std::cout << -a3 << '\n';

	std::cout << "Enter a number: "; // ������� 5.678
	std::cin >> a3;

	std::cout << "You entered: " << a3 << '\n';

	FixedPoint a2(0.03);
	std::cout << a2 << '\n';

	FixedPoint b2(-0.03);
	std::cout << b2 << '\n';

	FixedPoint c2(4.01); // ����������, ��� 4.0099999..., ������� ��� ����� ��� �� ���������
	std::cout << c2 << '\n';

	FixedPoint d2(-4.01); // ����������, ��� -4.0099999..., ������� ��� ����� ��� �� ���������
	std::cout << d2 << '\n';

	FixedPoint a1(37, 58);
	std::cout << a1 << '\n';

	FixedPoint b1(-3, 9);
	std::cout << b1 << '\n';

	FixedPoint c1(4, -7);
	std::cout << c1 << '\n';

	FixedPoint d1(-5, -7);
	std::cout << d1 << '\n';

	FixedPoint e1(0, -3);
	std::cout << e1 << '\n';

	std::cout << static_cast<double>(e1) << '\n';

	return 0;

	//������� 3
	IntArray a = fillArray();
	std::cout << a << '\n';
	IntArray b(1);
	a = a;
	b = a;
	std::cout << b << '\n';
	return 0;

	//������� 2
	Average avg;
	avg += 5;
	std::cout << avg << '\n'; // 5 / 1 = 5
	avg += 9;
	std::cout << avg << '\n'; // (5 + 9) / 2 = 7
	avg += 19;
	std::cout << avg << '\n'; // (5 + 9 + 19) / 3 = 11
	avg += -9;
	std::cout << avg << '\n'; // (5 + 9 + 19 - 9) / 4 = 6
	(avg += 7) += 11; // ���������� ������� ��������
	std::cout << avg << '\n'; // (5 + 9 + 19 - 9 + 7 + 11) / 6 = 7
	Average copy = avg;
	std::cout << copy << '\n';
	return 0;
}
#endif

#ifdef �������������_�����������
#include <cassert> // ��� assert()

class SomeString
{
private:
	char* m_data;
	int m_length;

public:
	SomeString(const char* source = "")
	{
		assert(source); // ��������� �� �������� �� source ������� �������

		// ���������� ����� source + ��� ���� ������ ��� ����-����������� (������ ���������� ������)
		m_length = strlen(source) + 1;

		// �������� ���������� ������ ��� �������� ����������� �������� � ������������ � ������ ����� ��������
		m_data = new char[m_length];

		// �������� �������� �� �������� � ���� ���������� ������
		for (int i = 0; i < m_length; ++i)
			m_data[i] = source[i];

		// ����������, ��� ������ ���������
		m_data[m_length - 1] = '\0';
	}
	SomeString(const SomeString& source);
	SomeString& operator=(const SomeString& source);
	~SomeString() // ����������
	{
		// ����������� ������, ���������� ��� ����� ������
		delete[] m_data;
	}


	char* getString() { return m_data; }
	int getLength() { return m_length; }
};
	// �������� ������������
	SomeString& SomeString::operator=(const SomeString& source)
	{
		// �������� �� ����������������
		if (this == &source)
			return *this;

		// ������� ��� ����� �������� ���������� �������� m_data (����� �������� �������)
		delete[] m_data;

		// ��������� m_length �� �������� ����������, �� �� ����� ��������� ������������� �����������
		m_length = source.m_length;

		// m_data �������� ����������, ������� ��� ����� ��������� �������� �����������, ��� �������, ��� ���� ��������� �� �������� �������
		if (source.m_data)
		{
			// �������� ������ ��� ����� �����
			m_data = new char[m_length];

			// ��������� �����������
			for (int i = 0; i < m_length; ++i)
				m_data[i] = source.m_data[i];
		}
		else
			m_data = 0;

		return *this;
	}
// ����������� �����������
SomeString::SomeString(const SomeString& source)
{
	// ��������� m_length �� �������� ����������, �� �� ����� ��������� ������������� �����������
	m_length = source.m_length;

	// m_data �������� ����������, ������� ��� ����� ��������� �������� �����������, ��� �������, ��� ���� ��������� �� �������� �������
	if (source.m_data)
	{
		// �������� ������ ��� ����� �����
		m_data = new char[m_length];

		// ��������� �����������
		for (int i = 0; i < m_length; ++i)
			m_data[i] = source.m_data[i];
	}
	else
		m_data = 0;
}
int main()
{
	SomeString hello("Hello, world!");
	{
		SomeString copy = hello; // ������������ ����������� ����������� �� ���������
	} // ������ copy �������� ��������� ����������, ������� ������������ �����. ���������� ������� ��������-������ ������� copy, ��������, ����� �������, hello � ������� ����������

	std::cout << hello.getString() << '\n'; // ����� �������������� ����������

	return 0;
}
#endif

#ifdef ����������_���������_������������
#include <cassert>
class Drob
{
private:
	int m_numerator;
	int m_denominator;

public:
	// ����������� �� ���������
	Drob(int numerator = 0, int denominator = 1) :
		m_numerator(numerator), m_denominator(denominator)
	{
		assert(denominator != 0);
	}

	// ����������� �����������
	Drob(const Drob& copy) = delete;

	// ���������� ��������� ������������
	Drob& operator= (const Drob& drob) = delete; // ��� �������� ����� �������� ����� �������� ������������!

	friend std::ostream& operator<<(std::ostream& out, const Drob& d1);

};

std::ostream& operator<<(std::ostream& out, const Drob& d1)
{
	out << d1.m_numerator << "/" << d1.m_denominator;
	return out;
}

int main()
{
	Drob sixSeven(6, 7);
	Drob d;
	d = sixSeven; // ������ ����������, operator= ��� ������
	std::cout << d;

	return 0;
}
#endif

#ifdef ������������_�������������� �������� ����� explicit � delete
#include <cassert>

class Drob
{
private:
	int m_numerator;
	int m_denominator;

public:
	// ����������� �� ���������
	Drob(int numerator = 0, int denominator = 1) :
		m_numerator(numerator), m_denominator(denominator)
	{
		assert(denominator != 0);
	}

	// ����������� �����������
	Drob(const Drob& copy) :
		m_numerator(copy.m_numerator), m_denominator(copy.m_denominator)
	{
		// ��� ������������� ��������� �������� denominator �����, ��� ��� ��� �������� ��� ������������ � ������������ �� ���������
		std::cout << "Copy constructor worked here!\n"; // ������, ����� ��������, ��� ��� ��������
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
	SomeString(char) = delete; // ����� ������������� ����� ������������ �������� � ������
	// �������� ����� explicit ������ ���� ����������� �������� ��� ���������� ����� ������� ��������������
	explicit SomeString(int a) // �������� ������ �������� a
	{
		m_string.resize(a);
	}

	SomeString(const char* string) // �������� ������ ��� �������� �������� ���� string
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
	SomeString mystring = "a";//'a'; // ������ ����������, ��������� SomeString(int) ������ �������� explicit �, ��������������, ����������, � ������� ����������� ������������ ��� �������������� ���������� �� �����
	std::cout << mystring;
	return 0;

	std::cout << makeNegative(7); // �������� ������������� ��������

	return 0;
}
#endif

#ifdef �����������_�����������
#include <cassert>

class Drob
{
private:
	int m_numerator;
	int m_denominator;
	
public:
	// ����������� �� ���������
	Drob(int numerator = 0, int denominator = 1) :
		m_numerator(numerator), m_denominator(denominator)
	{
		assert(denominator != 0);
	}

	// ����������� �����������
	Drob(const Drob& drob) :
		m_numerator(drob.m_numerator), m_denominator(drob.m_denominator)
		// ����������: �� ����� ������ ������ � ������ ������� drob, ��������� �� ������ ��������� ������ ������ Drob
	{
		// ��� ������������� ��������� �������� denominator �����, ��� ��� ��� �������� ��� �������������� � ������������ ������ Drob
		std::cout << "Copy constructor worked here!\n"; // ������, ����� ��������, ��� ��� ��������
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
	Drob sixSeven(6, 7); // ������ ������������� ������� ������ Drob, ���������� ����������� Drob(int, int)
	Drob dCopy(sixSeven); // ������ �������������, ���������� ����������� ����������� ������ Drob
	std::cout << dCopy << '\n';

	Drob sixSeven_(Drob(6, 7));//������
	//����������� ����������� ���������� �� ������ ������������ ����������� � ������ ��������� ������ �������������
	std::cout << sixSeven_ << '\n';
}

#endif

#ifdef ����������_��������_�������������� ����� ������
class Dollars
{
private:
	int m_dollars;
public:
	Dollars(int dollars = 0)
	{
		m_dollars = dollars;
	}

	// ���������� �������� �������������� �������� ���� Dollars � �������� ���� int
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

	// ��������� ����������� Cents � Dollars
	operator Dollars() { return Dollars(m_cents / 100); }
};

void printDollars(Dollars dollars)
{
	std::cout << dollars; // dollars ������ �������������� � int �����
}

int main()
{
	Cents cents(700);
	printDollars(cents); // cents ������ �������������� � Dollars �����

	return 0;
}
#endif

#ifdef ��������_����
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
	std::cout << string(7, 6); // �������� � 7-�� ������� (�������) � ���������� ��������� 6 ��������

	return 0;
}
#endif 

#ifdef �������� ����������_���������_ ()
#include <cassert> // ��� assert()

class Matrix
{
private:
	double data[5][5];
public:
	Matrix()
	{
		// ����������� ���� ��������� ������� �������� 0.0
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
	// ���������� �������� ���� ��������� ������� �� 0.0
	for (int row = 0; row < 5; ++row)
		for (int col = 0; col < 5; ++col)
			data[row][col] = 0.0;
}

int main()
{
	Matrix matrix;
	matrix(2, 3) = 3.6;
	matrix(); // ��������� �����
	std::cout << matrix(2, 3);
	return 0;
}
#endif

#ifdef ����������_��������_����
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


	char& gradeJohn = grades["John"]; // ����������� push_back
	gradeJohn = 'A';

	char& gradeMartin = grades["Martin"]; // ����������� push_back
	gradeMartin = 'B';

	std::cout << "John has a grade of " << gradeJohn << '\n';
	std::cout << "Martin has a grade of " << gradeMartin << '\n';

	return 0;
}
#endif

#ifdef ����������_���������_���������� []
#include <cassert>
class IntArray
{
private:
	int m_array[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // ��������� ��������� ��������

public:
	int& operator[] (const int index);
	const int& operator[] (const int index) const;
};

int& IntArray::operator[] (const int index) // ��� ������������� ��������: ����� �������������� ��� ��� ������������ �������� ���������, ��� � ��� �� ���������
{
	assert(index >= 0 && index < 10);
	return m_array[index];
}

const int& IntArray::operator[] (const int index) const // ��� ����������� ��������: ������������ ������ ��� ��������� (������) ��������� �������
{
	return m_array[index];
}

int main()
{
	IntArray array;
	array[11] = 5; // ������: ���������� ������������� ������ operator[]()
	std::cout << array[4]<<std::endl;

	const IntArray carray;
	//carray[4] = 5; // ������ ����������: ���������� ����������� ������ operator[](), ������� ���������� ����������� ������. ��������� �������� ������������ ������
	std::cout << carray[4] << std::endl;

	return 0;
}
#endif

#ifdef ����������_����������_���������� � ���������� ++ --
class Number
{
private:
	int m_number;
public:
	Number(int number = 0)
		: m_number(number)
	{
	}

	Number& operator++(); // ������ �������
	Number& operator--(); // ������ �������

	Number operator++(int); // ������ ��������
	Number operator--(int); // ������ ��������

	friend std::ostream& operator<< (std::ostream& out, const Number& n);
};

Number& Number::operator++()
{
	// ���� ��������� ���������� m_number �������� 8, �� ��������� ����� �������� m_number �� 0
	if (m_number == 8)
		m_number = 0;
	// � ��������� ������, ������ ����������� m_number �� �������
	else
		++m_number;

	return *this;
}

Number& Number::operator--()
{
	// ���� ��������� ���������� m_number �������� 0, �� ����������� m_number �������� 8
	if (m_number == 0)
		m_number = 8;
	// � ��������� ������, ������ ��������� m_number �� �������
	else
		--m_number;

	return *this;
}

Number Number::operator++(int)
{
	// ������� ��������� ������ ������ Number � ������� ��������� ���������� m_number
	Number temp(m_number);

	// ���������� �������� ���������� ������ ������� ��� ���������� ���������� ��������� ���������� ������ ��������
	++(*this); // ���������� ����������

	// ���������� ��������� ������
	return temp;
}

Number Number::operator--(int)
{
	// ������� ��������� ������ ������ Number � ������� ��������� ���������� m_number
	Number temp(m_number);

	// ���������� �������� ���������� ������ ������� ��� ���������� ���������� ��������� ���������� ������ ��������
	--(*this); // ���������� ����������

	// ���������� ��������� ������
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
	std::cout << ++number; // ���������� Number::operator++();
	std::cout << number++; // ���������� Number::operator++(int);
	std::cout << number;
	std::cout << --number; // ���������� Number::operator--();
	std::cout << number--; // ���������� Number::operator--(int);
	std::cout << number;

	return 0;
}
#endif

#ifdef ����������_����������_���������
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

	std::sort(v.begin(), v.end()); // ��������� ���������� ��������� < ��� ������ Car

	for (auto& car : v)
		std::cout << car << '\n'; // ��������� ���������� ��������� << ��� ������ Car

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

#ifdef ����������_�������_����������
class Dollars
{
private:
	int m_dollars;

public:
	Dollars(int dollars) { m_dollars = dollars; }

	// ��������� -Dollars ����� ����� ������
	Dollars operator-() const;

	int getDollars() const { return m_dollars; }
};

// ��� ������� �������� ������� ������!
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

	// ������������ ������ ������ Something � ������������� 
	Something operator- () const
	{
		return Something(-m_a, -m_b, -m_c);
	}

	// ������������ ������ ������ Something � ������������� 
	Something operator+ () const
	{
		return *this;
	}

	// ���������� true, ���� ������������ �������� �� ���������, � ��������� ������ - false
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
	Something something; // ���������� ����������� �� ��������� �� ���������� 0.0, 0.0, 0.0

	if (!something)
		std::cout << "Something is null.\n";
	else
		std::cout << "Something is not null.\n";


	const Dollars dollars1(7);
	std::cout << "My debt is " << (dollars1).getDollars() << " dollars.\n";

	return 0;
}
#endif

#ifdef ����������_�����_������ �������
#include <iostream>

class Dollars
{
private:
	int m_dollars;

public:
	Dollars(int dollars) { m_dollars = dollars; }

	// ��������� Dollars + int
	Dollars operator+(int value);

	int getDollars() { return m_dollars; }
};

// ����������: ��� ������� �������� ������� ������!
// ������ ��������� dollars � ���������� ����� ������������� ������� ����� ������� ��������, �� ������� ��������� ��������� *this
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

#ifdef ����������_����
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
	// �������������� �������� ������� f1
	in >> fr.numerator;
	in >> c; // ���������� ����������� '/'
	in >> fr.denominator;
	// ��������� �� ������������ ������������ f1, �� ��� ����� �������� ��������� ���������� �����
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

#ifdef ����������_���������_����� � ������
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
	// ��������� operator<< �������� ������ ������ Point, �� �� ����� ������ ������ � ������ Point
	out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z << ")";

	return out;
}

std::istream& operator>> (std::istream& in, Point& point)
{
	// ��������� operator>> �������� ������ ������ Point, �� �� ����� ������ ������ � ������ Point.
	// �������� ��������, �������� point (������ ������ Point) ������ ���� �������������, ����� �� ����� ����������� �������� ����� ������
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

#ifdef ����������_���������_���� � ����� 
class Dollars
{
private:
	int m_dollars;

public:
	Dollars(int dollars) { m_dollars = dollars; }

	// ��������� Dollars + Dollars ����� ������������� �������
	friend Dollars operator+(const Dollars& d1, const Dollars& d2);
	// ��������� Dollars - Dollars ����� ������������� �������
	friend Dollars operator-(const Dollars& d1, const Dollars& d2);
	// ��������� Dollars + int ����� ������������� �������
	friend Dollars operator+(const Dollars& d1, int value);
	// ��������� int + Dollars ����� ������������� �������
	friend Dollars operator+(int value, const Dollars& d1);

	int getDollars() const { return m_dollars; }
};

// ����������: ��� ������� �� �������� ������� ������!
Dollars operator+(const Dollars& d1, const Dollars& d2)
{
	// ���������� ����������� Dollars � operator+(int, int).
	// �� ����� ������ � ��������� ����� m_dollars, ��������� ��� ������� �������� ������������� ������ Dollars
	return Dollars(d1.m_dollars + d2.m_dollars);
}
// ����������: ��� ������� �� �������� ������� ������!
Dollars operator-(const Dollars& d1, const Dollars& d2)
{
	// ���������� ����������� Dollars � operator-(int, int).
	// �� ����� ������ � ��������� ����� m_dollars, ��������� ��� ������� �������� ������������� ������ Dollars
	return Dollars(d1.m_dollars - d2.m_dollars);
}
// ����������: ��� ������� �� �������� ������� ������!
Dollars operator+(const Dollars& d1, int value)
{
	// ���������� ����������� Dollars � operator+(int, int).
	// �� ����� ������ � ��������� ����� m_dollars, ��������� ��� ������� �������� ������������� ������ Dollars
	return Dollars(d1.m_dollars + value);
}
// ����������: ��� ������� �� �������� ������� ������!
Dollars operator+(int value, const Dollars& d1)
{
	// ���������� ����������� Dollars � operator+(int, int).
	// �� ����� ������ � ��������� ����� m_dollars, ��������� ��� ������� �������� ������������� ������ Dollars
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