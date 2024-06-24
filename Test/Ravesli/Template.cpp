#include <iostream>
#define test

#ifdef test1
template <typename T1, typename T2>
class Pair
{
public:
    Pair(const T1& f, const T2& s) :f(f), s(s) {};
    ~Pair() {};
    const T1& first() const { return f; }
    const T2& second() const { return s; }
    T1& first() { return f; }
    T2& second() { return s; }
private:
    T1 f;
    T2 s;
};

template <typename T2>
class StringValuePair : public Pair<std::string, T2>
{
public:
    StringValuePair(const std::string& f, const T2& s):Pair<std::string, T2>(f,s) {};
    ~StringValuePair() {};
private:

};

template <typename T>
class Pair1
{
public:
    Pair1(const T& f, const T& s) :f(f), s(s) {};
    ~Pair1() {};
    const T& first() const { return f; }
    const T& second() const { return s; }
    T& first() { return f; }
    T& second() { return s; }
private:
    T f,s;
};

int main()
{
    Pair1<int> p11(6, 9);
    std::cout << "Pair: " << p11.first() << ' ' << p11.second() << '\n';

    const Pair1<double> p22(3.4, 7.8);
    std::cout << "Pair: " << p22.first() << ' ' << p22.second() << '\n';

    Pair<int, double> p1(6, 7.8);
    std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

    const Pair<double, int> p2(3.4, 5);
    std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

        StringValuePair<int> svp("Amazing", 7);
        std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';

        return 0;
    
}
#endif

#ifdef ���������_�������������_�������� � ���������
// ����� ������ ������ Repository
template <class T>
class Repository
{
private:
    T m_value;
public:
    Repository(T value)
    {
        m_value = value;
    }

    ~Repository()
    {
    }

    void print()
    {
        std::cout << m_value << '\n';
    }
};

template <typename T>
class Repository<T*> // ��������� ������������� ������� ������ Repository ��� ������ � ������ ����������
{
private:
    T* m_value;
public:
    Repository(T* value) // T - ��� ���������
    {
        // ��������� �������� �����������
        m_value = new T(*value); // ����� ���������� ������ ���� ��������� �������� (�� ������ ��������)
    }

    ~Repository()
    {
        delete m_value; // � ����� ����������� �������� ����� ��������
    }

    void print()
    {
        std::cout << *m_value << '\n';
    }
};
// ������ ������������� ������� ������������ ������ Repository ��� ������ � ����� char*
template <>
Repository<char*>::Repository(char* value)
{
    // ���������� ����� value
    int length = 0;
    while (value[length] != '\0')
        ++length;
    ++length; // +1, �������� ����-����������

    // �������� ������ ��� �������� �������� value
    m_value = new char[length];

    // �������� ����������� �������� value � m_value
    for (int count = 0; count < length; ++count)
        m_value[count] = value[count];
}

// ������ ������������� ������� ����������� ������ Repository ��� ������ � ����� char*
template<>
Repository<char*>::~Repository()
{
    delete[] m_value;
}

// ������ ������������� ������� ������ print() ��� ������ � ����� char*.
// ��� ����� ����� Repository<char*> ������ �� � ������ Repository<T*>::print(), ������� ������� ������ ���� �������� (� ������ �� ������� C-style - ������ ������ ������)
template<>
void Repository<char*>::print()
{
    std::cout << m_value;
}
int main()
{
    // ��������� ������������� ������ ��� �������� ������ ������ ������� ������
    Repository<int> myint(6);
    myint.print();

    // ��������� ������ � ����� ��������� ��� �������� ������ ��������� ������������� �������
    int x = 8;
    Repository<int*> myintptr(&x);

    // ���� �� � myintptr ����������� ������������� ����������� (������������ ���������),
    // �� ��������� �������� x �������� �� � �������� myintptr
    x = 10;
    myintptr.print();

    // ����������� �������� ��������� ������
    char* name = new char[40]{ "Anton" }; // ��������� C++14

    // ���� ��� ���������� �� ������������ C++14, �� ��������������� ������ ���� � ���������������� ������, ����������� ����
//	char *name = new char[40];
//	strcpy(name, "Anton");

    // ��������� ���
    Repository<char*> myname(name);

    // ������� ��������� ������
    delete[] name;

    // ������� ���
    myname.print();
}
#endif

#ifdef ���������_�������������_�������2 ����� ������������ �����
template <class T, int size> // size �������� non-type ���������� �������
class StaticArray_Base
{
protected:
    // �������� size �������� �� ����� �������
    T m_array[size];

public:
    T* getArray() { return m_array; }

    T& operator[](int index)
    {
        return m_array[index];
    }
    virtual void print()
    {
        for (int i = 0; i < size; i++)
            std::cout << m_array[i] << ' ';
        std::cout << "\n";
    }
};

template <class T, int size> // size �������� non-type ���������� �������
class StaticArray : public StaticArray_Base<T, size>
{
public:
    StaticArray()
    {

    }
};

template <int size> // size �������� non-type ���������� �������
class StaticArray<double, size> : public StaticArray_Base<double, size>
{
public:

    virtual void print() override
    {
        for (int i = 0; i < size; i++)
            std::cout << std::scientific << this->m_array[i] << " ";
        // ����������: ������� this-> �� ��������������� ������ ���������. ������? ������� ����� - https://stackoverflow.com/a/6592617
        std::cout << "\n";
    }
};

int main()
{
    // ��������� ������������� ������ ������ 5
    StaticArray<int, 5> intArray;

    // ��������� ���, � ����� �������
    for (int count = 0; count < 5; ++count)
        intArray[count] = count;
    intArray.print();

    // ��������� ������ ���� double ������ 4
    StaticArray<double, 4> doubleArray;

    // ��������� ���, � ����� �������
    for (int count = 0; count < 4; ++count)
        doubleArray[count] = (4. + 0.1 * count);
    doubleArray.print();

    return 0;
}
#endif

#ifdef ���������_�������������_�������1
#include <cstring>

template <class T, int size> // size �������� non-type ���������� �������
class StaticArray
{
private:
    // �������� size �������� �� ����� �������
    T m_array[size];

public:
    T* getArray() { return m_array; }

    T& operator[](int index)
    {
        return m_array[index];
    }
};

template <typename T, int size>
void print(StaticArray<T, size>& array)
{
    for (int count = 0; count < size; ++count)
        std::cout << array[count] << ' ';
}

// ������ ������� print() � �������� ������������������ �������� ������ StaticArray<char, size> � �������� ���������
template <int size>
void print(StaticArray<char, size>& array)
{
    for (int count = 0; count < size; ++count)
        std::cout << array[count];
}

int main()
{
    // ��������� ������ ���� char ������ 14
    StaticArray<char, 14> char14;

    strcpy_s(char14.getArray(), 14, "Hello, world!");

    // ������� �������� �������
    print(char14);

    // ������ ��������� ������ ���� char ������ 12
    StaticArray<char, 12> char12;

    strcpy_s(char12.getArray(), 12, "Hello, dad!");

    // ������� �������� �������
    print(char12);

    return 0;
}
#endif

#ifdef �����_�������������_�������_������
template <class T>
class Repository8
{
private:
    T m_array[8];

public:
    void set(int index, const T& value)
    {
        m_array[index] = value;
    }

    const T& get(int index)
    {
        return m_array[index];
    }
};
template <>
class Repository8<bool> // �������������� ������ ������ Repository8 ��� ������ � ����� bool
{
    // ���������� ������
private:
    unsigned char m_data;

public:
    Repository8() : m_data(0)
    {
    }

    void set(int index, bool value)
    {
        // �������� ����������� ���
        unsigned char mask = 1 << index;

        if (value) // ���� �� ����� � ��� true, �� ��� ����� "��������"
            m_data |= mask; // ���������� ��������� ���, ����� "��������" ���
        else // ���� �� ����� � ��� false, �� ��� ����� "���������" 
            m_data &= ~mask; // ���������� ��������� �, ����� "���������" ���
    }

    bool get(int index)
    {
        // �������� ���
        unsigned char mask = 1 << index;
        // ���������� ��������� � ��� ��������� �������� ����, � ����� ����������� ��� ������� �������������� � ��� bool
        return (m_data & mask) != 0;
    }
};
int main()
{
    // ��������� ������������� ������-������
    Repository8<int> intRepository;

    for (int count = 0; count < 8; ++count)
        intRepository.set(count, count);

    for (int count = 0; count < 8; ++count)
        std::cout << intRepository.get(count) << '\n';

    // ��������� ������-������ ���� bool
    Repository8<bool> boolRepository;

    for (int count = 0; count < 8; ++count)
        boolRepository.set(count, count % 5);

    for (int count = 0; count < 8; ++count)
        std::cout << (boolRepository.get(count) ? "true" : "false") << '\n';

    return 0;
}
#endif

#ifdef �����_�������������_�������_�������
template <class T>
class Repository
{
private:
    T m_value;
public:
    Repository(T value)
    {
        m_value = value;
    }

    ~Repository()
    {
    }

    void print()
    {
        std::cout << m_value << '\n';
    }
};
template <>
void Repository<double>::print()
{
    std::cout << std::scientific << m_value << '\n';
}
template <>
Repository<char*>::Repository(char* value)
{
    // ���������� ����� value
    int length = 0;
    while (value[length] != '\0')
        ++length;
    ++length; // +1, �������� ����-����������

    // �������� ������ ��� �������� �������� value
    m_value = new char[length];

    // �������� ����������� �������� value � m_value
    for (int count = 0; count < length; ++count)
        m_value[count] = value[count];
}
template <>
Repository<char*>::~Repository()
{
    delete[] m_value;
}
int main()
{
    // �������������� ������� ������
    Repository<int> nValue(7);
    Repository<double> dValue(8.4);

    // ������� �������� �������� ������
    nValue.print();
    dValue.print();

    // ����������� �������� ��������� ������
    char* string = new char[40];

    // ������ ������������ ������ ���� ���
    std::cout << "Enter your name: ";
    std::cin >> string;

    // ��������� ��, ��� ���� ������������
    Repository<char*> repository(string);

    // ������� ��������� ������
    delete[] string;

    // �������� ������� ��, ��� ���� ������������
    repository.print(); // �������� �����
}
#endif

#ifdef ��������__non_type
template <class T, int size> // size �������� ���������� non-type � ������� ������
class StaticArray
{
private:
    // �������� non-type � ������� ������ �������� �� ������ ����������� �������
    T m_array[size];

public:
    T* getArray();

    T& operator[](int index)
    {
        return m_array[index];
    }
};

// ��������� ����������� ������� ������ � ������ ������ ��� ���� ������ � ���������� non-type
template <class T, int size>
T* StaticArray<T, size>::getArray()
{
    return m_array;
}

int main()
{
    // ��������� ������������� ������ �� 10 ���������
    StaticArray<int, 10> intArray;

    // ��������� ������ ����������
    for (int count = 0; count < 10; ++count)
        intArray[count] = count;

    // ������� �������� ������� � �������� ������� 
    for (int count = 9; count >= 0; --count)
        std::cout << intArray[count] << " ";
    std::cout << '\n';

    // ��������� ������ ���� double �� 5 ���������
    StaticArray<double, 5> doubleArray;

    // ��������� ������ ����������
    for (int count = 0; count < 5; ++count)
        doubleArray[count] = 5.5 + 0.1 * count;

    // ������� �������� ������� 
    for (int count = 0; count < 5; ++count)
        std::cout << doubleArray[count] << ' ';

    return 0;
}
#endif

#ifdef �������_������
#include <assert.h> // ��� assert()

template <class T> // ��� ������ ������ � T ������ ������������ (�������������) ���� ������
class Array
{
private:
    int m_length;
    T* m_data;

public:
    Array()
    {
        m_length = 0;
        m_data = nullptr;
    }

    Array(int length)
    {
        m_data = new T[length];
        m_length = length;
    }

    ~Array()
    {
        delete[] m_data;
    }

    void Erase()
    {
        delete[] m_data;
        // ����������� �������� nullptr ��� m_data, ����� �� ������ �� �������� ������� ���������!
        m_data = nullptr;
        m_length = 0;
    }


    T& operator[](int index)
    {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }

    // ����� ������� ������ �������� ������������� ���������, ��� �� ������� �� ���� ��������� �������
    int getLength(); // ���������� ����� � ������ ������ getLength() ����
};

template <typename T> // �����, ������������ ��� ���� ������, ��������� � ����������� ����������� ������� ������
int Array<T>::getLength() { return m_length; } // �������� ��������, ��� ������ - Array<T>, � �� ������ Array

int main()
{
    Array<int> intArray(10);
    Array<double> doubleArray(10);

    for (int count = 0; count < intArray.getLength(); ++count)
    {
        intArray[count] = count;
        doubleArray[count] = count + 0.5;
    }

    for (int count = intArray.getLength() - 1; count >= 0; --count)
        std::cout << intArray[count] << "\t" << doubleArray[count] << '\n';

    return 0;
}

#endif

#ifdef �������_�������
class Dollars
{
private:
    int m_dollars;
public:
    Dollars(int dollars)
        : m_dollars(dollars)
    {
    }

    friend bool operator>(const Dollars& d1, const Dollars& d2)
    {
        return (d1.m_dollars > d2.m_dollars);
    }

    friend std::ostream& operator<< (std::ostream& out, const Dollars& dollars)
    {
        out << dollars.m_dollars << " dollars ";
        return out;
    }

    Dollars& operator+=(Dollars dollars)
    {
        m_dollars += dollars.m_dollars;
        return *this;
    }

    Dollars& operator/=(int value)
    {
        m_dollars /= value;
        return *this;
    }
};

template <typename T>
const T& max(const T& a, const T& b)
{
    return (a > b) ? a : b;
}
template <class T>
T average(T* array, int length)
{
    T sum = 0;
    for (int count = 0; count < length; ++count)
        sum += array[count];

    sum /= length;
    return sum;
}

int main()
{
    Dollars array3[] = { Dollars(7), Dollars(12), Dollars(18), Dollars(15) };
    std::cout << average(array3, 4) << '\n';

    int i = max(4, 8);
    std::cout << i << '\n';

    double d = max(7.56, 21.434);
    std::cout << d << '\n';

    char ch = max('b', '9');
    std::cout << ch << '\n';

    return 0;
}
#endif