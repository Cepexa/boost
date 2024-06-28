#include <iostream>
#define ����

#ifdef ��������_�����2
#include <fstream>

int main()
{
    using namespace std;

    ofstream outf("SomeText.txt");
    outf << "See line #1!" << endl;
    outf << "See line #2!" << endl;
    outf.close(); // ���� ��������� ����

    // ���, �� ���-��� ������ �������
    outf.open("SomeText.txt", ios::app);
    outf << "See line #3!" << endl;
    outf.close();

    return 0;

    // ����� outf ������ �� ������� ���������, �� ���������� ������ ofstream ������������� ������� ��� ����
}
#endif

#ifdef ��������_�����
#include <fstream>
#include <string>
#include <cstdlib> // ��� ������������� ������� exit()
using namespace std;

int main()
{
    // ����� ofstream ������������ ��� ������ ������ � ����.
    // ������� ���� SomeText.txt
    ofstream outf("SomeText.txt");

    // ���� �� �� ����� ������� ���� ���� ��� ������ ������,
    if (!outf)
    {
        // �� ������� ��������� �� ������ � ��������� ������� exit()
        cerr << "Uh oh, SomeText.txt could not be opened for writing!" << endl;
        exit(1);
    }

    // ���������� � ���� ��������� ��� ������
    outf << "See line #1!" << endl;
    outf << "See line #2!" << endl;

    // ifstream ������������ ��� ������ ����������� ������.
    // �� ���������� ��������� ���������� ����� SomeText.txt
    ifstream inf("SomeText.txt");

    // ���� �� �� ����� ������� ���� ��� ������ ��� �����������,
    if (!inf)
    {
        // �� ������� ��������� ��������� �� ������ � ��������� ������� exit()
        cerr << "Uh oh, SomeText.txt could not be opened for reading!" << endl;
        exit(1);
    }

    // ���� ����, ��� ������,
    while (inf)
    {
        // �� ���������� ��, ��� ����� ���������, � ������, � ����� ������� ��� ������ �� �����
        string strInput;
        getline(inf, strInput);
        cout << strInput << endl;
    }

    return 0;

    // ����� outf ������ �� ������� ���������, �� ���������� ������ ofstream ������������� ������� ��� ����
    //�����
    //app � ��������� ���� � ������ ����������;
    //ate � ��������� � ����� ����� ����� ������� / �������;
    //binary � ��������� ���� � �������� ������(������ ���������� ������);
    //in � ��������� ���� � ������ ������(�� ��������� ��� ifstream);
    //out � ��������� ���� � ������ ������(�� ��������� ��� ofstream);
    //trunc � ������� ����, ���� �� ��� ����������.
}
#endif

#ifdef ���������_���������2
#include <string>  

bool InputMatches(std::string strUserInput, std::string strTemplate)
{
    if (strTemplate.length() != strUserInput.length())
        return false;

    // ���������� ������ ������ ����������������� �����
    for (unsigned int nIndex = 0; nIndex < strTemplate.length(); nIndex++)
    {
        switch (strTemplate[nIndex])
        {
        case '#': // = �����
            if (!isdigit(strUserInput[nIndex]))
                return false;
            break;
        case '_': // = ������
            if (!isspace(strUserInput[nIndex]))
                return false;
            break;
        case '@': // = �����
            if (!isalpha(strUserInput[nIndex]))
                return false;
            break;
        case '?': // = ������ ����� ������
            break;
        default: // = ������ ���������� � ��������
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
        std::getline(std::cin, strValue); // ��������� ����� ������, ������� �������
        if (InputMatches(strValue, "(###) ###-####"))
            break;
    }

    std::cout << "You entered: " << strValue << std::endl;
}
#endif

#ifdef ���������_���������
#include <cctype>
#include <string>  

int main()
{
    while (1)
    {
        // ������ ������������ ������ ���� ���
        std::cout << "Enter your name: ";
        std::string strName;
        std::getline(std::cin, strName); // ��������� ����� ������, ������� �������

        bool bRejected = false;

        // ���������� ������ ������ ������ �� ��� ���, ���� �� ������ �� ����� ������ ��� �� ���������� �������
        for (unsigned int nIndex = 0; nIndex < strName.length() && !bRejected; ++nIndex)
        {
            // ���� ������� ������ �������� ������, �� �� ��
            if (isalpha(strName[nIndex]))
                continue;

            // ���� ������, �� ���� ��
            if (strName[nIndex] == ' ')
                continue;

            // � ��������� ������, ��������� ���� ���������������� ����
            bRejected = true;
        }

        // ���� ���������������� ���� ��� ������, �� �� ������� �� ����� while, � ��������� ��������� ���� ����������.
        // � ��������� ������, �� ������ ������������ ������ ���� ��� ��� ���
        if (!bRejected)
            break;
    }
}
#endif

#ifdef ���������_������_������
#include <sstream> // ��� stringstream

int main()
{
    std::stringstream myString;
    myString << "Lorem ipsum!" << std::endl; // ��������� "Lorem ipsum!" � stringstream
    myString << "336000 12.14" << std::endl;
    std::cout << myString.str();
    myString.str(""); // ������� �����
    myString.clear(); // ���������� ��� ����� ������
    //����������� str � �����
    myString << "336000 12.14"; // ��������� (��������) ������ � �����
    int nValue;
    double dValue;

    myString >> nValue >> dValue;

    std::cout << nValue << " " << dValue << std::endl;
}
#endif

#ifdef ����������_������_ostream 
#include <iomanip> // ��� setprecision()
int main()
{
    //�����
    std::cout.setf(std::ios::showpos | std::ios::uppercase); // �������� ����� std::showpos � std::uppercase
    std::cout << 30 << '\n';
    std::cout.unsetf(std::ios::showpos); // ��������� ���� std::showpos
    std::cout << 31 << '\n';
    std::cout.unsetf(std::ios::dec); // ��������� ����� � ���������� ������� ���������
    std::cout.setf(std::ios::hex); // �������� ����� � ����������������� ������� ���������
    std::cout << 30 << '\n';
    std::cout.setf(std::ios::hex, std::ios::basefield);
    std::cout << 30 << '\n';
    //������������
    std::cout << std::hex << 30 << '\n'; // ������� 30 � ����������������� ������� ���������
    std::cout << 31 << '\n'; // �� ��� ��� ��������� � ����������������� ������� ���������
    std::cout << std::dec << 32 << '\n'; // ������������ ������� � ���������� ������� ���������

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

    //������ ����, �������-����������� � ������������
    std::cout <<  '\n' << -12345 << '\n'; // ������� �������� ��� ������������� ������ ����
    std::cout << std::setw(10) << -12345 << '\n'; // ������� �������� � �������������� ������ ����
    std::cout << std::setw(10) << std::left << -12345 << '\n'; // ����������� �� ������ ����
    std::cout << std::setw(10) << std::right << -12345 << '\n'; // ����������� �� ������� ����
    std::cout << std::setw(10) << std::internal << -12345 << '\n'; // ���� �������� ������������� �� ������ ����, � ���� �������� - �� �������
    //������-�����������
    std::cout.fill('*');
    std::cout << -12345 << '\n'; // ������� �������� ��� ������������� ������ ����
    std::cout << std::setw(10) << -12345 << '\n'; // ������� �������� � �������������� ������ ����
    std::cout << std::setw(10) << std::left << -12345 << '\n'; // ����������� �� ������ ����
    std::cout << std::setw(10) << std::right << -12345 << '\n'; // ����������� �� ������� ����
    std::cout << std::setw(10) << std::internal << -12345 << '\n'; // ���� �������� ������������� �� ������ ����, � ���� �������� - �� �������

}
#endif

#ifdef ����������_������_istream
#include <iomanip>
#include <string>
int main()
{
    //������������
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

    //getline() ��� std::string

    std::string strBuf1;
    std::getline(std::cin, strBuf1);
    std::cout << strBuf1 << std::endl;
    return 0;
    //������� ignore() � ���������� ������ ������ �� ������;

    //������� ignore(int nCount) � ���������� ������ nCount(����������) �������� �� ������;

    //������� peek() � ��������� ������ �� ������, ��� ���� �� ������ ��� �� ������;

    //������� unget() � ���������� ��������� ��������� ������ ������� � �����, ����� ��� ����� ���� ������� � ��������� ���;

    //������� putback(char ch) � �������� ��������� ���� ������ ������� � �����, ����� ��� ����� ���� ������� � ��������� ���.
}
#endif

#ifdef �����������_������
#include <cstdlib> // ��� exit()

int main()
{
    // ������� �� ���������� �������� ������� � �������� cout ��� ������ ������ �� �������
    std::cout << "Enter your age: " << std::endl;

    // ����� �� ���������� �������� ���������� � �������� cin ��� ��������� ����������������� �����
    int nAge;
    std::cin >> nAge;

    if (nAge <= 0)
    {
        // � ���� ������ �� ���������� �������� ������� � �������� cerr ��� ������ ��������� �� ������
        std::cerr << "Oops, you entered an invalid age!" << std::endl;
        exit(1);
    }

    // � ����� �� ���������� �������� ������� � �������� cout ��� ������ ����������
    std::cout << "You entered " << nAge << " years old" << std::endl;

    return 0;
}
#endif