#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Person {
    string name;
    string rank;
    string birthDate;
    int year;
    int exp;
    int wage;
};

int getYear(const string& dateString) {
    size_t pos = dateString.rfind('.');
    string yearString = dateString.substr(pos + 1);
    return stoi(yearString);
}

void countingSort(vector<Person>& persons, vector<int>& birthYears) {
    vector<Person> sortedPersons(persons.size());
    vector<int> count(10000, 0); // Создается вспомогательный массив count, где индекс элемента соответствует значению года рождения, а значения - количество элементов с этим годом рождения.

    // Подсчитываем количество людей с каждым конкретным годом рождения.
    for (int i = 0; i < birthYears.size(); i++) {
        count[birthYears[i]]++;
    }

    // Накопление значений в массиве count. Определяем конечные позиции каждого уникального года рождения.
    for (int i = 1; i < count.size(); i++) {
        count[i] += count[i - 1];
    }

    // Находится правильная позиция для человека, используя значения из массива count. Затем уменьшаем на единицу, обновляя тем самым позиции для следующего элемента.
    for (int i = persons.size() - 1; i >= 0; i--) {
        sortedPersons[count[birthYears[i]] - 1] = persons[i];
        count[birthYears[i]]--;
    }

    persons = sortedPersons;
}

void mergeSort(vector<Person>& persons) {
    sort(persons.begin(), persons.end(), [](const Person& a, const Person& b) { //Разделяем на две части.
        if (a.wage == b.wage) {
            if (getYear(a.birthDate) == getYear(b.birthDate)) {
                return a.exp < b.exp;  // Если зарплаты равны, переходим дальше.
            }
            return getYear(a.birthDate) < getYear(b.birthDate); // Сортируем по дате рождения.
        }
        return a.wage > b.wage; // Сортируем по зарплате.
    });
}

void selectionSort(vector<Person>& persons) {
    int n = persons.size();
    for (int i = 0; i < n - 1; i++) { // Проходим по всем элементам вектора persons за исключением последнего элемента.
        int cur = i;
        for (int j = i + 1; j < n; j++) {
            if (persons[j].wage > persons[cur].wage ||
                (persons[j].wage == persons[cur].wage && getYear(persons[j].birthDate) < getYear(persons[cur].birthDate)) ||
                (persons[j].wage == persons[cur].wage && getYear(persons[j].birthDate) == getYear(persons[cur].birthDate) && persons[j].exp < persons[cur].exp)) {
                cur = j; // Обновляем индекс cur, если подходит нашему условию.
            }
        }
        swap(persons[i], persons[cur]); // Повторяем процесс для следующего индекса i, уменьшая область поиска на 1 элемент.
    }
}

int main() {
    ifstream file("input.txt");
    if (!file.is_open()) {
        cout << "Unable to open file.\n";
        return 1;
    }

    vector<Person> persons;
    vector<int> birthYears;

    while (!file.eof()) {
        Person inf;
        string temp;
        getline(file, inf.name, ',');
        getline(file, inf.rank, ',');
        getline(file, inf.birthDate, ',');
        file >> inf.exp;
        file >> temp;
        file >> inf.wage;
        getline(file, temp);

        persons.push_back(inf);
        birthYears.push_back(getYear(inf.birthDate));
    }

    file.close();

    int numSort;
    cout << "Hello! You can select the sorting type:\n1. Counting sort\n2. Merge sort (wage, then year)\n3. Selection sort (wage, then year, then experience)\nWhat type of sorting do you choose? --> ";
    cin >> numSort;

    switch (numSort) {
        case 1: 
            countingSort(persons, birthYears);
            break;
        case 2:
            mergeSort(persons);
            break;
        case 3:
            selectionSort(persons);
            break;
        default:
            cout << "Invalid sorting type selected.\n";
            return 0;
    }

    ofstream outFile("output.txt");
    for (const Person& inf : persons) {
        outFile << "Name: " << inf.name << '\n';
        outFile << "Rank: " << inf.rank << '\n';
        outFile << "BirthDate: " << inf.birthDate << '\n';
        outFile << "Experience: " << inf.exp << '\n';
        outFile << "Wage: " << inf.wage << '\n';
    }

    return 0;
}

