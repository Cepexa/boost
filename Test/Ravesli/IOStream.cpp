#include <iostream>
#define тест

#ifdef Файловый_вывод2
#include <fstream>

int main()
{
    using namespace std;

    ofstream outf("SomeText.txt");
    outf << "See line #1!" << endl;
    outf << "See line #2!" << endl;
    outf.close(); // явно закрываем файл

    // Упс, мы кое-что забыли сделать
    outf.open("SomeText.txt", ios::app);
    outf << "See line #3!" << endl;
    outf.close();

    return 0;

    // Когда outf выйдет из области видимости, то деструктор класса ofstream автоматически закроет наш файл
}
#endif

#ifdef Файловый_вывод
#include <fstream>
#include <string>
#include <cstdlib> // для использования функции exit()
using namespace std;

int main()
{
    // Класс ofstream используется для записи данных в файл.
    // Создаем файл SomeText.txt
    ofstream outf("SomeText.txt");

    // Если мы не можем открыть этот файл для записи данных,
    if (!outf)
    {
        // то выводим сообщение об ошибке и выполняем функцию exit()
        cerr << "Uh oh, SomeText.txt could not be opened for writing!" << endl;
        exit(1);
    }

    // Записываем в файл следующие две строки
    outf << "See line #1!" << endl;
    outf << "See line #2!" << endl;

    // ifstream используется для чтения содержимого файлов.
    // Мы попытаемся прочитать содержимое файла SomeText.txt
    ifstream inf("SomeText.txt");

    // Если мы не можем открыть файл для чтения его содержимого,
    if (!inf)
    {
        // то выводим следующее сообщение об ошибке и выполняем функцию exit()
        cerr << "Uh oh, SomeText.txt could not be opened for reading!" << endl;
        exit(1);
    }

    // Пока есть, что читать,
    while (inf)
    {
        // то перемещаем то, что можем прочитать, в строку, а затем выводим эту строку на экран
        string strInput;
        getline(inf, strInput);
        cout << strInput << endl;
    }

    return 0;

    // Когда outf выйдет из области видимости, то деструктор класса ofstream автоматически закроет наш файл
    //флаги
    //app — открывает файл в режиме добавления;
    //ate — переходит в конец файла перед чтением / записью;
    //binary — открывает файл в бинарном режиме(вместо текстового режима);
    //in — открывает файл в режиме чтения(по умолчанию для ifstream);
    //out — открывает файл в режиме записи(по умолчанию для ofstream);
    //trunc — удаляет файл, если он уже существует.
}
#endif

#ifdef Строковая_валидация2
#include <string>  

bool InputMatches(std::string strUserInput, std::string strTemplate)
{
    if (strTemplate.length() != strUserInput.length())
        return false;

    // Перебираем каждый символ пользовательского ввода
    for (unsigned int nIndex = 0; nIndex < strTemplate.length(); nIndex++)
    {
        switch (strTemplate[nIndex])
        {
        case '#': // = цифра
            if (!isdigit(strUserInput[nIndex]))
                return false;
            break;
        case '_': // = пробел
            if (!isspace(strUserInput[nIndex]))
                return false;
            break;
        case '@': // = буква
            if (!isalpha(strUserInput[nIndex]))
                return false;
            break;
        case '?': // = вообще любой символ
            break;
        default: // = точное совпадение с символом
            if (strUserInput[nIndex] != strTemplate[nIndex])
                return false;
        }
    }

    return true;
}

int main()
{
    std::string strValue;

    while (1)
    {
        std::cout << "Enter a phone number (###) ###-####: ";
        std::getline(std::cin, strValue); // извлекаем целую строку, включая пробелы
        if (InputMatches(strValue, "(###) ###-####"))
            break;
    }

    std::cout << "You entered: " << strValue << std::endl;
}
#endif

#ifdef Строковая_валидация
#include <cctype>
#include <string>  

int main()
{
    while (1)
    {
        // Просим пользователя ввести свое имя
        std::cout << "Enter your name: ";
        std::string strName;
        std::getline(std::cin, strName); // извлекаем целую строку, включая пробелы

        bool bRejected = false;

        // Перебираем каждый символ строки до тех пор, пока не дойдем до конца строки или до отклонения символа
        for (unsigned int nIndex = 0; nIndex < strName.length() && !bRejected; ++nIndex)
        {
            // Если текущий символ является буквой, то всё ок
            if (isalpha(strName[nIndex]))
                continue;

            // Если пробел, то тоже ок
            if (strName[nIndex] == ' ')
                continue;

            // В противном случае, отклоняем весь пользовательский ввод
            bRejected = true;
        }

        // Если пользовательский ввод был принят, то мы выходим из цикла while, и программа завершает свое выполнение.
        // В противном случае, мы просим пользователя ввести свое имя еще раз
        if (!bRejected)
            break;
    }
}
#endif

#ifdef Потоковые_классы_Строки
#include <sstream> // для stringstream

int main()
{
    std::stringstream myString;
    myString << "Lorem ipsum!" << std::endl; // вставляем "Lorem ipsum!" в stringstream
    myString << "336000 12.14" << std::endl;
    std::cout << myString.str();
    myString.str(""); // очищаем буфер
    myString.clear(); // сбрасываем все флаги ошибок
    //конвертация str в число
    myString << "336000 12.14"; // вставляем (числовую) строку в поток
    int nValue;
    double dValue;

    myString >> nValue >> dValue;

    std::cout << nValue << " " << dValue << std::endl;
}
#endif

#ifdef Функционал_класса_ostream 
#include <iomanip> // для setprecision()
int main()
{
    //флаги
    std::cout.setf(std::ios::showpos | std::ios::uppercase); // включаем флаги std::showpos и std::uppercase
    std::cout << 30 << '\n';
    std::cout.unsetf(std::ios::showpos); // выключаем флаг std::showpos
    std::cout << 31 << '\n';
    std::cout.unsetf(std::ios::dec); // выключаем вывод в десятичной системе счисления
    std::cout.setf(std::ios::hex); // включаем вывод в шестнадцатеричной системе счисления
    std::cout << 30 << '\n';
    std::cout.setf(std::ios::hex, std::ios::basefield);
    std::cout << 30 << '\n';
    //манипуляторы
    std::cout << std::hex << 30 << '\n'; // выводим 30 в шестнадцатеричной системе счисления
    std::cout << 31 << '\n'; // мы все еще находимся в шестнадцатеричной системе счисления
    std::cout << std::dec << 32 << '\n'; // перемещаемся обратно в десятичную систему счисления

    std::cout << true << " " << false << '\n';
    std::cout.setf(std::ios::boolalpha);
    std::cout << true << " " << false << '\n';
    std::cout << std::noboolalpha << true << " " << false << '\n';
    std::cout << std::boolalpha << true << " " << false << '\n';

    std::cout << 7 << '\n';
    std::cout.setf(std::ios::showpos);
    std::cout << 7 << '\n';
    std::cout << std::noshowpos << 7 << '\n';
    std::cout << std::showpos << 7 << '\n';

    std::cout << 12345678.9 << '\n';
    std::cout.setf(std::ios::uppercase);
    std::cout << 12345678.9 << '\n';
    std::cout << std::nouppercase << 12345678.9 << '\n';
    std::cout << std::uppercase << 12345678.9 << '\n';

    std::cout << std::fixed;
    std::cout << std::setprecision(3) << 123.456 << '\n';
    std::cout << std::setprecision(4) << 123.456 << '\n';
    std::cout << std::setprecision(5) << 123.456 << '\n';
    std::cout << std::setprecision(6) << 123.456 << '\n';
    std::cout << std::setprecision(7) << 123.456 << '\n';

    std::cout << std::scientific << '\n';
    std::cout << std::setprecision(3) << 123.456 << '\n';
    std::cout << std::setprecision(4) << 123.456 << '\n';
    std::cout << std::setprecision(5) << 123.456 << '\n';
    std::cout << std::setprecision(6) << 123.456 << '\n';
    std::cout << std::setprecision(7) << 123.456 << '\n';

    //Ширина поля, символы-заполнители и выравнивание
    std::cout <<  '\n' << -12345 << '\n'; // выводим значение без использования ширины поля
    std::cout << std::setw(10) << -12345 << '\n'; // выводим значение с использованием ширины поля
    std::cout << std::setw(10) << std::left << -12345 << '\n'; // выравниваем по левому краю
    std::cout << std::setw(10) << std::right << -12345 << '\n'; // выравниваем по правому краю
    std::cout << std::setw(10) << std::internal << -12345 << '\n'; // знак значения выравнивается по левому краю, а само значение - по правому
    //символ-заполнитель
    std::cout.fill('*');
    std::cout << -12345 << '\n'; // выводим значение без использования ширины поля
    std::cout << std::setw(10) << -12345 << '\n'; // выводим значение с использованием ширины поля
    std::cout << std::setw(10) << std::left << -12345 << '\n'; // выравниваем по левому краю
    std::cout << std::setw(10) << std::right << -12345 << '\n'; // выравниваем по правому краю
    std::cout << std::setw(10) << std::internal << -12345 << '\n'; // знак значения выравнивается по левому краю, а само значение - по правому

}
#endif

#ifdef Функционал_класса_istream
#include <iomanip>
#include <string>
int main()
{
    //Манипуляторы
    char buf[12];
    std::cin >> std::setw(12) >> buf;

    //get
    char ch;
    while (std::cin.get(ch))
        std::cout << ch;

    //getline
    char strBuf[100];
    std::cin.getline(strBuf, 100);
    std::cout << strBuf << std::endl;
    std::cout << std::cin.gcount() << " characters were read" << std::endl;

    //getline() для std::string

    std::string strBuf1;
    std::getline(std::cin, strBuf1);
    std::cout << strBuf1 << std::endl;
    return 0;
    //функция ignore() — игнорирует первый символ из потока;

    //функция ignore(int nCount) — игнорирует первые nCount(количество) символов из потока;

    //функция peek() — считывает символ из потока, при этом не удаляя его из потока;

    //функция unget() — возвращает последний считанный символ обратно в поток, чтобы его можно было извлечь в следующий раз;

    //функция putback(char ch) — помещает выбранный вами символ обратно в поток, чтобы его можно было извлечь в следующий раз.
}
#endif

#ifdef стандартные_потоки
#include <cstdlib> // для exit()

int main()
{
    // Сначала мы используем оператор вставки с объектом cout для вывода текста на монитор
    std::cout << "Enter your age: " << std::endl;

    // Затем мы используем оператор извлечения с объектом cin для получения пользовательского ввода
    int nAge;
    std::cin >> nAge;

    if (nAge <= 0)
    {
        // В этом случае мы используем оператор вставки с объектом cerr для вывода сообщения об ошибке
        std::cerr << "Oops, you entered an invalid age!" << std::endl;
        exit(1);
    }

    // А здесь мы используем оператор вставки с объектом cout для вывода результата
    std::cout << "You entered " << nAge << " years old" << std::endl;

    return 0;
}
#endif