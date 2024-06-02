//#pragma region test1
//
//// Example1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
////
//#include <iomanip>
//#include <iostream>
//#include <ios>
//#include <string>
//
//using std::cin;      using std::setprecision;
//using std::cout;     using std::string;
//using std::endl;     using std::streamsize;
//
//int main(){
//    system("chcp 1251 > nul");
//    cout << "Пожалуйста, введите своё имя: ";
//    string name;
//    cin >> name;
//    cout << "Привет, " << name << "!" << endl;
//
//    cout << "Пожалуйста, введите оценки по экзаменам "
//        "в середине и в конце семестра: ";
//    double midterm, _final;
//    cin >> midterm >> _final;
//
//    cout << "Введите все оценки за выполнение домашних заданий, "
//        "завершив ввод признаком конца файла: ";
//
//    int count = 0;
//    double sum = 0;
//
//    double x;
//
//    while (cin >> x) {
//        ++count;
//        sum += x;
//    }
//
//    streamsize prec = cout.precision();
//    cout << "Ваша итоговая оценка равна " //<< setprecision(3)
//        << 0.2 * midterm + 0.4 * _final + 0.4 * sum / count
//        //<< setprecision(prec) 
//        << endl;
//    return 0;
//}
//
//// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
//// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"
//
//// Советы по началу работы 
////   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
////   2. В окне Team Explorer можно подключиться к системе управления версиями.
////   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
////   4. В окне "Список ошибок" можно просматривать ошибки.
////   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
////   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
//
//#pragma endregion

#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

// Класс для представления измерений
class Dimension {
public:
    Dimension(string name) : name(name) {}

    string getName() const {
        return name;
    }

private:
    string name;
};

// Класс для представления фактов
class Fact {
public:
    Fact(vector<double> values) : values(values) {}

    vector<double> getValues() const {
        return values;
    }

private:
    vector<double> values;
};

// Класс для представления многомерных данных
class MultidimensionalData {
public:
    MultidimensionalData() {}

    void addDimension(Dimension dimension) {
        dimensions.push_back(dimension);
    }

    void addFact(Fact fact) {
        facts.push_back(fact);
    }

    vector<Fact> getFacts() const {
        return facts;
    }

    vector<Dimension> getDimensions() const {
        return dimensions;
    }

private:
    vector<Dimension> dimensions;
    vector<Fact> facts;
};

// Функция для загрузки данных в многомерные данные
void loadData(MultidimensionalData& data) {
    // Загрузка данных из источника данных
    // Пример:
    data.addDimension(Dimension("Region"));
    data.addDimension(Dimension("Product"));

    vector<double> values1 = { 100, 200 };
    Fact fact1(values1);
    data.addFact(fact1);

    vector<double> values2 = { 150, 250 };
    Fact fact2(values2);
    data.addFact(fact2);

    vector<double> values3 = { 300, 400 };
    Fact fact3(values3);
    data.addFact(fact3);
}

// Функция для агрегации данных
vector<double> aggregateData(const MultidimensionalData& data) {
    vector<double> aggregatedData;

    vector<Fact> facts = data.getFacts();
    for (const Fact& fact : facts) {
        vector<double> values = fact.getValues();
        for (double value : values) {
            aggregatedData.push_back(value);
        }
    }

    return aggregatedData;
}

// Функция для фильтрации данных
MultidimensionalData filterData(const MultidimensionalData& data, const string& dimensionName, const string& dimensionValue) {
    MultidimensionalData filteredData;

    vector<Dimension> dimensions = data.getDimensions();

    for (const Dimension& dimension : dimensions) {
        if (dimension.getName() == dimensionName) {
            filteredData.addDimension(dimension);
        }
    }

    vector<Fact> facts = data.getFacts();
    for (const Fact& fact : facts) {
        vector<double> values = fact.getValues();
        if (values[0] == stod(dimensionValue)) {
            filteredData.addFact(fact);
        }
    }

    return filteredData;
}

// Функция для расчета суммы значений
double calculateSum(const vector<double>& values) {
    double sum = 0;

    for (double value : values) {
        sum += value;
    }

    return sum;
}

int main() {
    MultidimensionalData data;

    // Загрузка данных
    loadData(data);

    // Агрегация данных
    vector<double> aggregatedData = aggregateData(data);
    cout << "Aggregated data: ";
    for (double value : aggregatedData) {
        cout << value << " ";
    }
    cout << endl;

    // Фильтрация данных
    MultidimensionalData filteredData = filterData(data, "Region", "100");
    vector<Fact> filteredFacts = filteredData.getFacts();
    cout << "Filtered data: ";
    for (const Fact& fact : filteredFacts) {
        vector<double> values = fact.getValues();
        for (double value : values) {
            cout << value << " ";
        }
    }
    cout << endl;

    // Расчет суммы значений
    cout << "Sum: " << calculateSum(aggregatedData) << endl;

    return 0;
}