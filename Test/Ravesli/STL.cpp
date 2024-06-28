#include <iostream>
#define ����

#ifdef �������_��������_c���� � std::string
#include <string>

int main()
{
	std::string sString("bbb");

	const std::string sInsert("012345");
	sString.insert(1, sInsert, 2, 4); // ��������� ��������� sInsert ������ 4, ������� � ������� ��� �������� 2, � ������ sString, ������� � ������� 1
	std::cout << sString << std::endl;
}
#endif

#ifdef ����������_�_String
#include <string>

int main()
{
	std::string sString("one");

	sString += " two";
	sString.append(" three" + std::string("dd"),0,20);
	std::cout << sString << std::endl;
}
#endif

#ifdef ������������_������������
#include <string>

int main()
{
	using namespace std;

	string sString;

	// ����������� std::string ������ ������
	sString = string("One");
	cout << sString << endl;

	const string sTwo("Two");
	sString.assign(sTwo);
	cout << sString << endl;

	// ����������� std::string ������ C-style
	sString = "Three";
	cout << sString << endl;

	sString.assign("Four");
	cout << sString << endl;

	// ����������� std::string �������� ���� char
	sString = '5';
	cout << sString << endl;

	// ��������� �������
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


#ifdef �����������
#include <string>

int main()
{
	std::string sSomething("abcdefg");
	const char* szString = "abcdefg";
	// ������� memcmp() ���������� ��� ��������������� ������ C-style � ���������� 0, ���� ��� �����
	if (memcmp(sSomething.data(), szString, sSomething.length()) == 0)
		std::cout << "The strings are equal\n";
	else
		std::cout << "The strings are not equal\n";

	std::string sSomething1("lorem ipsum dolor sit amet");

	char szBuf[20];
	int nLength = sSomething1.copy(szBuf, 6, 9);
	szBuf[nLength] = '\0'; // ��������� ������ � ������

	std::cout << szBuf << std::endl;
}
#endif

#ifdef max_size_Std
#include <string>
#include <cstdlib> // ��� rand() � srand()
#include <ctime> // ��� time()
int main()
{
	std::string sString("MyString");
	std::cout << sString.max_size() << std::endl;

	srand(time(0)); // ��������� ���������� �����

	std::string sString2; // ����� 0
	sString2.reserve(80); // ����������� 80 �������� 

	// ��������� ������ ���������� ��������� ���������
	for (int nCount = 0; nCount < 80; ++nCount)
		sString2 += 'a' + rand() % 26;

	std::cout << sString2 << std::endl;
	std::cout << "Length: " << sString2.length() << std::endl;
	std::cout << "Capacity: " << sString2.capacity() << std::endl;


	return 0;
}
#endif

#ifdef �����_��_string
#include <sstream>
#include <string>

template <typename T>
inline bool FromString(const std::string& sString, T& tX)
{
	std::istringstream iStream(sString);
	return (iStream >> tX) ? true : false; // ��������� �������� � tX, ���������� true (���� ������) ��� false (���� ��������)
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

#ifdef string_��_�����
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

#ifdef ���������_STL
#include <list>
#include <vector>
#include <algorithm> 
int main()
{
	std::list<int> li;
	for (int nCount = 0; nCount < 5; ++nCount)
		li.push_back(nCount);

	std::list<int>::const_iterator it; // ��������� ��������
	it = min_element(li.begin(), li.end());
	std::cout << *it << ' ';
	it = max_element(li.begin(), li.end());
	std::cout << *it << ' ';
	std::cout << '\n';

	std::list<int>::iterator it1; // ��������� ��������
	it1 = find(li.begin(), li.end(), 2); // ���� � ������ ����� 2
	li.insert(it1, 7); // ���������� �������� list::insert() ��� ���������� ����� 7 ����� ������ 2

	for (it1 = li.begin(); it1 != li.end(); ++it1) // ������� � ������� ����� � ��������� �������� ������
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

	std::sort(vect.begin(), vect.end()); // ��������� ���������� ��������� �������

	std::vector<int>::const_iterator it2; // ��������� ��������
	for (it2 = vect.begin(); it2 != vect.end(); ++it2) // ������� � ������� ����� � ��������� �������� �������
		std::cout << *it2 << ' ';

	std::cout << '\n';

	std::reverse(vect.begin(), vect.end()); // ���������� �������� ������� � �������� �������

	for (it2 = vect.begin(); it2 != vect.end(); ++it2) // ������� � ������� ����� � ��������� �������� �������
		std::cout << *it2 << ' ';

	std::cout << '\n';
}
#endif

#ifdef ��������
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

	std::map<int, std::string>::const_iterator it; // ��������� ��������
	it = myMap.begin(); // ����������� ��� ��������� ������� �������
	while (it != myMap.end()) // ���� �������� �� ��������� ���������� ��������
	{
		std::cout << it->first << "=" << it->second << " "; // ������� �������� ��������, �� ������� ��������� ��������
		++it; // � ��������� � ���������� ��������
	}

	std::cout << '\n';
}
#endif