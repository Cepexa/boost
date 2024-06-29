#include <iostream>
#include <thread>
#include <chrono>
using namespace std;
#define Метод_Класса_в_потоке

#ifdef Метод_Класса_в_потоке
class MyClass
{
public:
	void DoWork() {
		this_thread::sleep_for(chrono::milliseconds(300));
		cout << "Id Потока - " << this_thread::get_id() << " DoWork start" << endl;
		this_thread::sleep_for(chrono::milliseconds(300));
		cout << "Id Потока - " << this_thread::get_id() << " DoWork stopped" << endl;
	}
	void DoWork2(int a) {
		this_thread::sleep_for(chrono::milliseconds(300));
		cout << "Id Потока - " << this_thread::get_id() << " DoWork start" << endl;
		this_thread::sleep_for(chrono::milliseconds(300));
		cout << "Параметр = " << a << endl;
		cout << "Id Потока - " << this_thread::get_id() << " DoWork stopped" << endl;
	}
	int Sum(int a, int b) {
		this_thread::sleep_for(chrono::milliseconds(300));
		cout << "+++++Dowork begin+++++" << endl;
		this_thread::sleep_for(chrono::milliseconds(300));
		cout << "+++++Dowork end+++++" << endl;
		return a + b;
	}
private:

};

int main() {
	system("chcp 1251 > nul");
	MyClass m;
	int result;
	thread th([&]() 
		{
			result = m.Sum(4, 3);
		});
	thread th1(&MyClass::DoWork,m);
	thread th2(&MyClass::DoWork2,m,6);
	for (size_t i = 0; i < 8; i++)
	{
		this_thread::sleep_for(chrono::milliseconds(200));
		cout << "Id Потока - " << this_thread::get_id() << " main" << endl;
	}
	th.join();
	th1.join();
	th2.join();
	cout << "result = " << result<<endl;
}
#endif

#ifdef возврат_с_помощью_Лямбда
int Sum(int a, int b) {
	this_thread::sleep_for(chrono::milliseconds(300));
	cout << "+++++Dowork begin+++++" << endl;
	this_thread::sleep_for(chrono::milliseconds(300));
	cout << "+++++Dowork end+++++" << endl;
	return a + b;
}
int main() {
	system("chcp 1251 > nul");
	int result;
	thread th([&result]() {result = Sum(2, 5); });
	for (size_t i = 0; i<8; i++)
	{
		this_thread::sleep_for(chrono::milliseconds(200));
		cout << "Id Потока - " << this_thread::get_id() << " main" << endl;
	}
	th.join();
	cout << result << endl;
}
#endif

#ifdef возврат_по_ссылке
void DoWork(int &a) {
	this_thread::sleep_for(chrono::milliseconds(300));
	cout << "Id Потока - " << this_thread::get_id() << "+++++Dowork begin+++++" << endl;
	this_thread::sleep_for(chrono::milliseconds(300));
	a *= 2;
	cout << "Id Потока - " << this_thread::get_id() << "+++++Dowork end+++++" << endl;
}
int main() {
	system("chcp 1251 > nul");
	int q = 5;
	thread th(DoWork,std::ref(q));//если здесь оставить просто q, код не скомпилируется
	for (size_t i = 0; i<10; i++)
	{
		this_thread::sleep_for(chrono::milliseconds(200));
		cout << "Id Потока - " << this_thread::get_id() << " main" << endl;
	}
	th.join();
	cout << q << endl;
}
#endif

#ifdef параметры
void DoWork(int a, int b) {
	this_thread::sleep_for(chrono::milliseconds(300));
	cout << "+++++Dowork begin+++++" << endl;
	this_thread::sleep_for(chrono::milliseconds(300));
	cout << "a+b = " << a + b << endl;
	this_thread::sleep_for(chrono::milliseconds(300));
	cout << "+++++Dowork end+++++" << endl;
}
int main() {
	system("chcp 1251 > nul");
	thread th(DoWork,2, 3);
	for (size_t i = 0; true; i++)
	{
		this_thread::sleep_for(chrono::milliseconds(200));
		cout << "Id Потока - " << this_thread::get_id() << " main" << endl;
	}
	th.join();
}
#endif

#ifdef многопоточка_база

void DoWork( ) {
	for (size_t i = 0; i < 10; i++)
	{
		this_thread::sleep_for(chrono::milliseconds(300));
		cout << "Id Потока - " << this_thread::get_id() << " DoWork" << endl;

	}

}

int main() {
	system("chcp 1251 > nul");
	cout << "Start" << endl;
	thread th(DoWork);
	thread th2(DoWork);
	for (size_t i = 0; i < 10; i++)
	{
	this_thread::sleep_for(chrono::milliseconds(200));
	cout << "Id Потока - " << this_thread::get_id() << " main" << endl;

	}
	th.join();
	th2.join();
	cout << "End" << endl;
}

#endif
