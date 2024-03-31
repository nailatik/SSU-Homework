#include <iostream>
#include <string>
#include <fstream>
#include <vector>

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
    vector<int> count(10000, 0);

    for (int i = 0; i < birthYears.size(); i++) {
        count[birthYears[i]]++;
    }

    for (int i = 1; i < count.size(); i++) {
        count[i] += count[i - 1];
    }

    for (int i = persons.size() - 1; i >= 0; i--) {
        sortedPersons[count[birthYears[i]] - 1] = persons[i];
        count[birthYears[i]]--;
    }

    persons = sortedPersons;
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
    cout << "Hello! You can select the sorting type: " << endl;
    cout << "1. Counting sotr \n" << "2. Diff sort\n" << "3. Diff sort\n" << "What type of sorting do you choose? --> ";
    cin >> numSort;

    switch (numSort){
        case 1: countingSort(persons, birthYears);
    }

    ofstream outFile("output.txt");

    for (const Person& inf : persons) {
        outFile << "Name: " << inf.name << endl;
        outFile << "Rank: " << inf.rank << endl;
        outFile << "BirthDate: " << inf.birthDate << endl;
        outFile << "Experience: " << inf.exp << endl;
        outFile << "Wage: " << inf.wage << endl;
        outFile << endl;
    }

    return 0;
}
