#include <iostream>
#define ���

#ifdef ��������_����
//������� �1
//
//����� ���� ���������(����������, ���������, ���������� ��� �����������) ����������� ���� ?
//
//a) ����� ��������, ������� �������� ��� ��������� � ��� ���.
//
//����� �1.a)
//
//����������.��� ��������� � ��� ��� �� ������������ ��� ������ ��������.
//
//b) ����� TextEditor � ������� Save(), ������� ��������� ������ file.����� Save() ���������� ���������� ��������� �� ����.
//
//����� �1.b)
//
//�����������.����� TextEditor ���������� ������ file ��� ���������� ������������� ������� � ���������� ������� �� ����.
//
//c) ����� ����������, ������� ����� ������� ������ �������� : ����, �����, ����� ��� ����� ����������.��� �������� ����� ���� ��������� � ������� ������� �������������.
//
//����� �1.c)
//
//���������.����� �������� ������� � ������������, �� ���������� ������ ��� ��������.���, ������������ ������������, �� ����� ������������ ���� ����������� ������ ������������.�� ���������� �� ��������� �������������� ����� ���������.
//
//d) ����������� ���������� ��������� ��� ��������� ����� � ������ � ���������.
//
//����� �1.d)
//
//����������.����������� � ��������� �� ������� ����� �����, �� ����������� �������, ����� ����������� ���������� ��������� ��� ��������� ����� � ������.
//
//e) ����� ���������, ������� �������� ����� ���������.��������� ����� ������ �� ���������� � ����������.
//
//����� �1.e)
//
//���������.��������� ����� ���������, �� �� ��������� ��� ��������������.
#endif

#ifdef ������������_�����_������ + initializer_list
#include <cassert> // ��� assert()
#include <initializer_list> // ��� std::initializer_list

class ArrayInt
{
private:
    int m_length;
    int* m_data;

public:
    ArrayInt() :
        m_length(0), m_data(nullptr)
    {
    }

    ArrayInt(int length) :
        m_length(length)
    {
        assert(length >= 0);
        if (length > 0)
            m_data = new int[length];
        else
            m_data = nullptr;
    }

    ArrayInt(const std::initializer_list<int>& list) : // ��������� ������������� ArrayInt ����� ������ �������������
        ArrayInt(list.size()) // ���������� ��������� ������������� ������������� ��� �������� ���������� �������, � ������� ����� ����������� ����������� ���������
    {
        // ������������� ������ ���������� ������� ���������� �� ������ �������������
        int count = 0;
        for (auto& element : list)
        {
            m_data[count] = element;
            ++count;
        }
    }

    ~ArrayInt()
    {
        delete[] m_data;
    }

    void erase()
    {
        delete[] m_data;
        // ����� ����� ������� m_data �������� nullptr, ����� �� ������ �� ���� �������� ���������
        m_data = nullptr;
        m_length = 0;
    }

    int& operator[](int index)
    {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }

    // ������� reallocate() �������� ������ �������. ��� ������������ �������� ������ ������� ����� ����������. ������� �������
    void reallocate(int newLength)
    {
        // ������� ��� ������������ �������� ������ �������
        erase();

        // ���� ��� ������ ������ ���� ������, �� ��������� ������� �����
        if (newLength <= 0)
            return;

        // ����� �������� ����� ��������
        m_data = new int[newLength];
        m_length = newLength;
    }

    // ������� resize() �������� ������ �������. ��� ������������ �������� �����������. ������� ���������
    void resize(int newLength)
    {
        // ���� ������ ������ �����, �� ��������� return
        if (newLength == m_length)
            return;

        // ���� ����� ������� ������ ������, �� ������ ��� � ����� ��������� return
        if (newLength <= 0)
        {
            erase();
            return;
        }

        // ������ �����������, ��� newLength �������, �� ������� ����, �� ������ ��������. ����������� ��������� �������� ��������:
        // 1. �������� ����� ������.
        // 2. �������� �������� �� ������������� ������� � ��� ������ ��� ���������� ������.
        // 3. ���������� ������ ������ � ���� ������� m_data ��������� �� ����� ������.

        // �������� ����� ������
        int* data = new int[newLength];

        // ����� ��� ����� ����������� � ����������� ���������� ��������� � ����� ������.
        // ��� ����� ����������� ������� ���������, ������� �� ���� � ������� �� ��������
        if (m_length > 0)
        {
            int elementsToCopy = (newLength > m_length) ? m_length : newLength;

            // ���������� �������� ��������
            for (int index = 0; index < elementsToCopy; ++index)
                data[index] = m_data[index];
        }

        // ������� ������ ������, ��� ��� �� ��� ��� �� �����
        delete[] m_data;

        // � ���������� ������ ������� ������� �����! �������� ��������, m_data ��������� �� ��� �� �����, �� ������� ��������� ��� ����� ����������� ���������� ������.
        // ��������� ������ ���� ����������� ��������, �� ��� �� ����� ����������, ����� ������ �� ������� ���������
        m_data = data;
        m_length = newLength;
    }

    void insertBefore(int value, int index)
    {
        // �������� ������������ ������������� �������
        assert(index >= 0 && index <= m_length);

        // ������� ����� ������ �� ���� ������� ������ ������� �������
        int* data = new int[m_length + 1];

        // �������� ��� �������� �� �� index
        for (int before = 0; before < index; ++before)
            data[before] = m_data[before];

        // ��������� ��� ����� ������� � ��� ����� ������
        data[index] = value;

        // �������� ��� �������� ����� ������������ ��������
        for (int after = index; after < m_length; ++after)
            data[after + 1] = m_data[after];

        // ������� ������ ������ � ���������� ������ ���� ����� ������
        delete[] m_data;
        m_data = data;
        ++m_length;
    }

    void remove(int index)
    {
        // �������� �� ������������ ������������� �������
        assert(index >= 0 && index < m_length);

        // ���� ��� ��������� ������� �������, �� ������ ������ ������ � ��������� return
        if (m_length == 1)
        {
            erase();
            return;
        }

        // C������ ����� ������ �� ���� ������� ������ ������ ������� �������
        int* data = new int[m_length - 1];

        // �������� ��� �������� �� �� index
        for (int before = 0; before < index; ++before)
            data[before] = m_data[before];

        // �������� ��� �������� ����� ���������� ��������
        for (int after = index + 1; after < m_length; ++after)
            data[after - 1] = m_data[after];

        // ������� ������ ������ � ���������� ������ ���� ����� ������
        delete[] m_data;
        m_data = data;
        --m_length;
    }

    // ��������� �������������� ������� ������ ��� ��������
    void insertAtBeginning(int value) { insertBefore(value, 0); }
    void insertAtEnd(int value) { insertBefore(value, m_length); }

    int getLength() { return m_length; }

    ArrayInt& operator= (const std::initializer_list<int>& ili) {
        reallocate(ili.size());
        int count = 0;
        for (const auto& el :ili)
            m_data[count++] = el;
        return *this;
    }
};
int main()
{
    ArrayInt array1{ 7, 6, 5, 4, 3, 2, 1 }; // ������ �������������
    for (int count = 0; count < array1.getLength(); ++count)
        std::cout << array1[count] << ' ';
    std::cout << std::endl;
    array1 = { 1, 4, 9, 12, 15, 17, 19, 21 };

    for (int count = 0; count < array1.getLength(); ++count)
        std::cout << array1[count] << ' ';

    std::cout << std::endl;

    // ��������� ������ � 10 ����������
    ArrayInt array(10);

    // ��������� ������ ������� �� 1 �� 10
    for (int i = 0; i < 10; i++)
        array[i] = i + 1;

    // �������� ������ ������� �� 7 ���������
    array.resize(7);

    // ��������� ����� 15 ����� ��������� � �������� 4
    array.insertBefore(15, 4);

    // ������� ������� � �������� 5
    array.remove(5);

    // ��������� ����� 35 � 50 � ����� � � ������
    array.insertAtEnd(35);
    array.insertAtBeginning(50);

    // ������� ��� �������� �������
    for (int j = 0; j < array.getLength(); j++)
        std::cout << array[j] << " ";

    return 0;
}
#endif

#ifdef �����������
class Point
{
private:
	double m_x, m_y, m_z;

public:
	Point(double x = 0.0, double y = 0.0, double z = 0.0) : m_x(x), m_y(y), m_z(z)
	{
	}

	friend std::ostream& operator<< (std::ostream& out, const Point& point);
};

std::ostream& operator<< (std::ostream& out, const Point& point)
{
	// ��������� ������� ���������� operator<< �������� ������������� ������ Point, �� �� ����� ������ ������ � �������� ������ ������ Point
	out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z << ")";

	return out;
}

int main()
{
	Point point1(5.0, 6.0, 7.0);

	std::cout << point1;

	return 0;
}
#endif

#ifdef ����������_vs_���������_vs_����������
��������			:   ����������			���������			����������
���������			:	����� - ����� 		����� - ����� 		������� �� ������� ����� �����
����� ����� 
������������ 
������������ 
����� ���������� 
�������				:	��� 				��					��
������������� 
������ ����������� 
��������			: 	�� 					��� 				���
��� ���������		: 	���������������� 	���������������� 	���������������� ��� ���������������
��� ���������		:	������ ���� - �� 	������ 			�����������
#endif

#ifdef ���������������_����������
#include <string>
#include <vector>

// ��������� ��������� ����� ����� �������� ���������������, �� ��� ������ Doctor ����� ����� ������������ ��������������� ����������
class Doctor;

class Patient
{
private:
	std::string m_name;
	std::vector<Doctor*> m_doctor; // ��������� ���������������� ���������������� ���������� Doctor, ��� ������ �� ������� ������ ����������

	// �� ��������� ����� addDoctor() ��������, ��� ��� �� ����� ��� ���������� �������������.
	// ������ ����� ������ � ���� ����� �������������� ����� Doctor::addPatient().
	// �� ��������� ���� ����� ����� ����������� ������ Doctor, ��� ��� ��� ������� ����� ���������� Doctor, ����� ������������ ���-����, ��������� � ���
	void addDoctor(Doctor* doc);

public:
	Patient(std::string name)
		: m_name(name)
	{
	}

	// �� ��������� ���������� ��������� ������ ���� ����������� ������ Doctor, ��� ��� �� ��� ��� � ��������� ��� ���������� ����������
	friend std::ostream& operator<<(std::ostream& out, const Patient& pat);

	std::string getName() const { return m_name; }

	// �� ������ ����� Doctor �������������, ����� ����� ������ � ��������� ������ addDoctor().
	// ����������: �� �� ������ ������� ������������� ������ ���� ����� addDoctor(), �� �� �� ����� ��� �������, ��� ��� Doctor �������������� ��������
	friend class Doctor;
};

class Doctor
{
private:
	std::string m_name;
	std::vector<Patient*> m_patient;

public:
	Doctor(std::string name) :
		m_name(name)
	{
	}

	void addPatient(Patient* pat)
	{
		// ���� ��������� ��������
		m_patient.push_back(pat);

		// ������� ��������� �����
		pat->addDoctor(this);
	}


	friend std::ostream& operator<<(std::ostream& out, const Doctor& doc)
	{
		unsigned int length = doc.m_patient.size();
		if (length == 0)
		{
			out << doc.m_name << " has no patients right now";
			return out;
		}

		out << doc.m_name << " is seeing patients: ";
		for (unsigned int count = 0; count < length; ++count)
			out << doc.m_patient[count]->getName() << ' ';

		return out;
	}

	std::string getName() const { return m_name; }
};

void Patient::addDoctor(Doctor* doc)
{
	m_doctor.push_back(doc);
}

std::ostream& operator<<(std::ostream& out, const Patient& pat)
{
	unsigned int length = pat.m_doctor.size();
	if (length == 0)
	{
		out << pat.getName() << " has no doctors right now";
		return out;
	}

	out << pat.m_name << " is seeing doctors: ";
	for (unsigned int count = 0; count < length; ++count)
		out << pat.m_doctor[count]->getName() << ' ';

	return out;
}


int main()
{
	// ������� ��������� ��� ������� ��������� ������ Doctor
	Patient* p1 = new Patient("Anton");
	Patient* p2 = new Patient("Ivan");
	Patient* p3 = new Patient("Derek");

	// ������� �������� ��� ������� ��������� ������ Patient
	Doctor* d1 = new Doctor("John");
	Doctor* d2 = new Doctor("Tom");

	d1->addPatient(p1);

	d2->addPatient(p1);
	d2->addPatient(p3);

	std::cout << *d1 << '\n';
	std::cout << *d2 << '\n';
	std::cout << *p1 << '\n';
	std::cout << *p2 << '\n';
	std::cout << *p3 << '\n';

	delete p1;
	delete p2;
	delete p3;

	delete d1;
	delete d2;

	return 0;
}
#endif