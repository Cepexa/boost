#include <iostream>
#define тест

#ifdef Вставка_символов_cтрок в std::string
#include <string>

int main()
{
	std::string sString("bbb");

	const std::string sInsert("012345");
	sString.insert(1, sInsert, 2, 4); // вставляем подстроку sInsert длиной 4, начиная с символа под индексом 2, в строку sString, начиная с индекса 1
	std::cout << sString << std::endl;
}
#endif

#ifdef Добавление_к_String
#include <string>

int main()
{
	std::string sString("one");

	sString += " two";
	sString.append(" three" + std::string("dd"),0,20);
	std::cout << sString << std::endl;
}
#endif

#ifdef Присваивание_перестановка
#include <string>

int main()
{
	using namespace std;

	string sString;

	// Присваиваем std::string другую строку
	sString = string("One");
	cout << sString << endl;

	const string sTwo("Two");
	sString.assign(sTwo);
	cout << sString << endl;

	// Присваиваем std::string строку C-style
	sString = "Three";
	cout << sString << endl;

	sString.assign("Four");
	cout << sString << endl;

	// Присваиваем std::string значение типа char
	sString = '5';
	cout << sString << endl;

	// Связываем объекты
	string sOther;
	sString = sOther = "Six";
	cout << sString << " " << sOther << endl;

	string sStr1("green");
	string sStr2("white");

	cout << sStr1 << " " << sStr2 << endl;
	swap(sStr1, sStr2);
	cout << sStr1 << " " << sStr2 << endl;
	sStr1.swap(sStr2);
	cout << sStr1 << " " << sStr2 << endl;


	return 0;
}
#endif


#ifdef Конвертация
#include <string>

int main()
{
	std::string sSomething("abcdefg");
	const char* szString = "abcdefg";
	// Функция memcmp() сравнивает две вышеприведенные строки C-style и возвращает 0, если они равны
	if (memcmp(sSomething.data(), szString, sSomething.length()) == 0)
		std::cout << "The strings are equal\n";
	else
		std::cout << "The strings are not equal\n";

	std::string sSomething1("lorem ipsum dolor sit amet");

	char szBuf[20];
	int nLength = sSomething1.copy(szBuf, 6, 9);
	szBuf[nLength] = '\0'; // завершаем строку в буфере

	std::cout << szBuf << std::endl;
}
#endif

#ifdef max_size_Std
#include <string>
#include <cstdlib> // для rand() и srand()
#include <ctime> // для time()
int main()
{
	std::string sString("MyString");
	std::cout << sString.max_size() << std::endl;

	srand(time(0)); // генерация случайного числа

	std::string sString2; // длина 0
	sString2.reserve(80); // резервируем 80 символов 

	// Заполняем строку случайными строчными символами
	for (int nCount = 0; nCount < 80; ++nCount)
		sString2 += 'a' + rand() % 26;

	std::cout << sString2 << std::endl;
	std::cout << "Length: " << sString2.length() << std::endl;
	std::cout << "Capacity: " << sString2.capacity() << std::endl;


	return 0;
}
#endif

#ifdef числа_из_string
#include <sstream>
#include <string>

template <typename T>
inline bool FromString(const std::string& sString, T& tX)
{
	std::istringstream iStream(sString);
	return (iStream >> tX) ? true : false; // извлекаем значение в tX, возвращаем true (если удачно) или false (если неудачно)
}

int main()
{
	double dX;
	if (FromString("4.5", dX))
		std::cout << dX << std::endl;
	if (FromString("TOM", dX))
		std::cout << dX << std::endl;
}
#endif

#ifdef string_из_чисел
#include <sstream>
#include <string>

template <typename T>
inline std::string ToString(T tX)
{
	std::ostringstream oStream;
	oStream << tX;
	return oStream.str();
}

int main()
{
	std::string sFive(ToString(5));
	std::string sSevenPointEight(ToString(7.8));
	std::string sB(ToString('B'));
	std::cout << sFive << std::endl;
	std::cout << sSevenPointEight << std::endl;
	std::cout << sB << std::endl;
}
#endif

#ifdef string_std
#include <string>

int main()
{
	std::string sSomething("What a string!");
	std::string sOutput(sSomething, 3);
	std::cout << sOutput << std::endl;
	std::string sOutput2(sSomething, 5, 6);
	std::cout << sOutput2 << std::endl;

	const char* szSomething("What a string!");
	std::string _sOutput(szSomething,80);
	std::cout << _sOutput << std::endl;

	return 0;
}
#endif

#ifdef Алгоритмы_STL
#include <list>
#include <vector>
#include <algorithm> 
int main()
{
	std::list<int> li;
	for (int nCount = 0; nCount < 5; ++nCount)
		li.push_back(nCount);

	std::list<int>::const_iterator it; // объявляем итератор
	it = min_element(li.begin(), li.end());
	std::cout << *it << ' ';
	it = max_element(li.begin(), li.end());
	std::cout << *it << ' ';
	std::cout << '\n';

	std::list<int>::iterator it1; // объявляем итератор
	it1 = find(li.begin(), li.end(), 2); // ищем в списке число 2
	li.insert(it1, 7); // используем алгоритм list::insert() для добавления числа 7 перед числом 2

	for (it1 = li.begin(); it1 != li.end(); ++it1) // выводим с помощью цикла и итератора элементы списка
		std::cout << *it1 << ' ';

	std::cout << '\n';


	std::vector<int> vect;
	vect.push_back(4);
	vect.push_back(8);
	vect.push_back(-3);
	vect.push_back(3);
	vect.push_back(-8);
	vect.push_back(12);
	vect.push_back(5);

	std::sort(vect.begin(), vect.end()); // выполняем сортировку элементов вектора

	std::vector<int>::const_iterator it2; // объявляем итератор
	for (it2 = vect.begin(); it2 != vect.end(); ++it2) // выводим с помощью цикла и итератора элементы вектора
		std::cout << *it2 << ' ';

	std::cout << '\n';

	std::reverse(vect.begin(), vect.end()); // записываем элементы вектора в обратном порядке

	for (it2 = vect.begin(); it2 != vect.end(); ++it2) // выводим с помощью цикла и итератора элементы вектора
		std::cout << *it2 << ' ';

	std::cout << '\n';
}
#endif

#ifdef Итератор
#include <map>
#include <string>

int main()
{
	std::map<int, std::string> myMap;
	myMap.insert(std::make_pair(3, "cat"));
	myMap.insert(std::make_pair(2, "dog"));
	myMap.insert(std::make_pair(5, "chicken"));
	myMap.insert(std::make_pair(4, "lion"));
	myMap.insert(std::make_pair(1, "spider"));

	std::map<int, std::string>::const_iterator it; // объявляем итератор
	it = myMap.begin(); // присваиваем ему начальный элемент вектора
	while (it != myMap.end()) // пока итератор не достигнет последнего элемента
	{
		std::cout << it->first << "=" << it->second << " "; // выводим значение элемента, на который указывает итератор
		++it; // и переходим к следующему элементу
	}

	std::cout << '\n';
}
#endif