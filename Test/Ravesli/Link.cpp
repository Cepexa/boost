#include <iostream>
#define вуа

#ifdef Итоговый_тест
//Задание №1
//
//Какие типы отношений(композиция, агрегация, ассоциация или зависимость) описываются ниже ?
//
//a) Класс Животное, который содержит Тип Животного и его Имя.
//
//Ответ №1.a)
//
//Композиция.Тип Животного и его Имя не используются вне класса Животное.
//
//b) Класс TextEditor с методом Save(), который принимает объект file.Метод Save() записывает содержимое редактора на диск.
//
//Ответ №1.b)
//
//Зависимость.Класс TextEditor использует объект file для выполнения определенного задания — сохранения объекта на диск.
//
//c) Класс Авантюрист, который может хранить разные Предметы : мечи, копья, зелья или книги заклинаний.Эти Предметы могут быть отброшены и подняты другими Авантюристами.
//
//Ответ №1.c)
//
//Агрегация.Когда Предметы связаны с Авантюристом, то Авантюрист «имеет» эти предметы.Меч, используемый Авантюристом, не может одновременно быть использован другим Авантюристом.Но Авантюрист не управляет существованием самих Предметов.
//
//d) Программист использует Компьютер для просмотра видео с котами в Интернете.
//
//Ответ №1.d)
//
//Ассоциация.Программист и Компьютер не связаны между собой, за исключением случаев, когда Программист использует Компьютер для просмотра видео с котами.
//
//e) Класс Компьютер, который содержит класс Процессор.Процессор можно вынуть из Компьютера и посмотреть.
//
//Ответ №1.e)
//
//Агрегация.Компьютер имеет Процессор, но не управляет его существованием.
#endif

#ifdef Контейнерный_класс_массив + initializer_list
#include <cassert> // для assert()
#include <initializer_list> // для std::initializer_list

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

    ArrayInt(const std::initializer_list<int>& list) : // позволяем инициализацию ArrayInt через список инициализации
        ArrayInt(list.size()) // используем концепцию делегирования конструкторов для создания начального массива, в который будет выполняться копирование элементов
    {
        // Инициализация нашего начального массива значениями из списка инициализации
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
        // Здесь нужно указать m_data значение nullptr, чтобы на выходе не было висячего указателя
        m_data = nullptr;
        m_length = 0;
    }

    int& operator[](int index)
    {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }

    // Функция reallocate() изменяет размер массива. Все существующие элементы внутри массива будут уничтожены. Процесс быстрый
    void reallocate(int newLength)
    {
        // Удаляем все существующие элементы внутри массива
        erase();

        // Если наш массив должен быть пустым, то выполняем возврат здесь
        if (newLength <= 0)
            return;

        // Затем выделяем новые элементы
        m_data = new int[newLength];
        m_length = newLength;
    }

    // Функция resize() изменяет размер массива. Все существующие элементы сохраняются. Процесс медленный
    void resize(int newLength)
    {
        // Если массив нужной длины, то выполняем return
        if (newLength == m_length)
            return;

        // Если нужно сделать массив пустым, то делаем это и затем выполняем return
        if (newLength <= 0)
        {
            erase();
            return;
        }

        // Теперь предположим, что newLength состоит, по крайней мере, из одного элемента. Выполняется следующий алгоритм действий:
        // 1. Выделяем новый массив.
        // 2. Копируем элементы из существующего массива в наш только что выделенный массив.
        // 3. Уничтожаем старый массив и даем команду m_data указывать на новый массив.

        // Выделяем новый массив
        int* data = new int[newLength];

        // Затем нам нужно разобраться с количеством копируемых элементов в новый массив.
        // Нам нужно скопировать столько элементов, сколько их есть в меньшем из массивов
        if (m_length > 0)
        {
            int elementsToCopy = (newLength > m_length) ? m_length : newLength;

            // Поочередно копируем элементы
            for (int index = 0; index < elementsToCopy; ++index)
                data[index] = m_data[index];
        }

        // Удаляем старый массив, так как он нам уже не нужен
        delete[] m_data;

        // И используем вместо старого массива новый! Обратите внимание, m_data указывает на тот же адрес, на который указывает наш новый динамически выделенный массив.
        // Поскольку данные были динамически выделены, то они не будут уничтожены, когда выйдут из области видимости
        m_data = data;
        m_length = newLength;
    }

    void insertBefore(int value, int index)
    {
        // Проверка корректности передаваемого индекса
        assert(index >= 0 && index <= m_length);

        // Создаем новый массив на один элемент больше старого массива
        int* data = new int[m_length + 1];

        // Копируем все элементы аж до index
        for (int before = 0; before < index; ++before)
            data[before] = m_data[before];

        // Вставляем наш новый элемент в наш новый массив
        data[index] = value;

        // Копируем все значения после вставляемого элемента
        for (int after = index; after < m_length; ++after)
            data[after + 1] = m_data[after];

        // Удаляем старый массив и используем вместо него новый массив
        delete[] m_data;
        m_data = data;
        ++m_length;
    }

    void remove(int index)
    {
        // Проверка на корректность передаваемого индекса
        assert(index >= 0 && index < m_length);

        // Если это последний элемент массива, то делаем массив пустым и выполняем return
        if (m_length == 1)
        {
            erase();
            return;
        }

        // Cоздаем новый массив на один элемент меньше нашего старого массива
        int* data = new int[m_length - 1];

        // Копируем все элементы аж до index
        for (int before = 0; before < index; ++before)
            data[before] = m_data[before];

        // Копируем все значения после удаляемого элемента
        for (int after = index + 1; after < m_length; ++after)
            data[after - 1] = m_data[after];

        // Удаляем старый массив и используем вместо него новый массив
        delete[] m_data;
        m_data = data;
        --m_length;
    }

    // Несколько дополнительных функций просто для удобства
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
    ArrayInt array1{ 7, 6, 5, 4, 3, 2, 1 }; // список инициализации
    for (int count = 0; count < array1.getLength(); ++count)
        std::cout << array1[count] << ' ';
    std::cout << std::endl;
    array1 = { 1, 4, 9, 12, 15, 17, 19, 21 };

    for (int count = 0; count < array1.getLength(); ++count)
        std::cout << array1[count] << ' ';

    std::cout << std::endl;

    // Объявляем массив с 10 элементами
    ArrayInt array(10);

    // Заполняем массив числами от 1 до 10
    for (int i = 0; i < 10; i++)
        array[i] = i + 1;

    // Изменяем размер массива до 7 элементов
    array.resize(7);

    // Вставляем число 15 перед элементом с индексом 4
    array.insertBefore(15, 4);

    // Удаляем элемент с индексом 5
    array.remove(5);

    // Добавляем числа 35 и 50 в конец и в начало
    array.insertAtEnd(35);
    array.insertAtBeginning(50);

    // Выводим все элементы массива
    for (int j = 0; j < array.getLength(); j++)
        std::cout << array[j] << " ";

    return 0;
}
#endif

#ifdef Зависимость
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
	// Поскольку функция перегрузки operator<< является дружественной классу Point, то мы имеем прямой доступ к закрытым членам класса Point
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

#ifdef Композиция_vs_Агрегация_vs_Ассоциация
Свойства			:   Композиция			Агрегация			Ассоциация
Отношения			:	Части - целое 		Части - целое 		Объекты не связаны между собой
Члены могут 
принадлежать 
одновременно 
сразу нескольким 
классам				:	Нет 				Да					Да
Существование 
членов управляется 
классами			: 	Да 					Нет 				Нет
Вид отношений		: 	Однонаправленные 	Однонаправленные 	Однонаправленные или Двунаправленные
Тип отношений		:	«Часть чего - то» 	«Имеет» 			«Использует»
#endif

#ifdef Двунаправленная_ассоциация
#include <string>
#include <vector>

// Поскольку отношения между этими классами двунаправленные, то для класса Doctor здесь нужно использовать предварительное объявление
class Doctor;

class Patient
{
private:
	std::string m_name;
	std::vector<Doctor*> m_doctor; // благодаря вышеприведенному предварительному объявлению Doctor, эта строка не вызовет ошибку компиляции

	// Мы объявляем метод addDoctor() закрытым, так как не хотим его публичного использования.
	// Вместо этого доступ к нему будет осуществляться через Doctor::addPatient().
	// Мы определим этот метод после определения класса Doctor, так как нам сначала нужно определить Doctor, чтобы использовать что-либо, связанное с ним
	void addDoctor(Doctor* doc);

public:
	Patient(std::string name)
		: m_name(name)
	{
	}

	// Мы реализуем перегрузку оператора вывода ниже определения класса Doctor, так как он как раз и требуется для реализации перегрузки
	friend std::ostream& operator<<(std::ostream& out, const Patient& pat);

	std::string getName() const { return m_name; }

	// Мы делаем класс Doctor дружественным, чтобы иметь доступ к закрытому методу addDoctor().
	// Примечание: Мы бы хотели сделать дружественным только один метод addDoctor(), но мы не можем это сделать, так как Doctor предварительно объявлен
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
		// Врач добавляет Пациента
		m_patient.push_back(pat);

		// Пациент добавляет Врача
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
	// Создаем Пациентов вне области видимости класса Doctor
	Patient* p1 = new Patient("Anton");
	Patient* p2 = new Patient("Ivan");
	Patient* p3 = new Patient("Derek");

	// Создаем Докторов вне области видимости класса Patient
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