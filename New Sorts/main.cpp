#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

void outArr(int n, vector<vector<int>> &arr){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << arr[i][j] << ' ';
        }
        cout << endl;
    }
}

void countingSort(vector<vector<int>> &arr, int n) {
    vector<vector<int>> counts(n, vector<int>(41, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            counts[i][arr[i][j] + 20]++;
        }
    }

    for (int i = 0; i < n; i++) {
        int index = 0;
        for (int k = 0; k < 41; k++) {
            while (counts[i][k] > 0) {
                arr[i][index] = k - 20;
                index++;
                counts[i][k]--;
            }
        }
    }
}


void combSort(vector<vector<int>> &arr, int n) {
    float gap = n / 1.247;
    while (gap >= 1) {
        if (gap < 1) {
            gap = 1;
        }
        for (int j = 0; j < n; j++) {
            if ((j + 1) % 3 == 0) {
                for (int i = 0; i < n - gap; i++) {
                    if (arr[i][j] < arr[i + gap][j]) {
                        swap(arr[i][j], arr[i + gap][j]);
                    }
                }
            } else {
                for (int i = 0; i < n - gap; i++) {
                    if (arr[i][j] > arr[i + gap][j]) {
                        swap(arr[i][j], arr[i + gap][j]);
                    }
                }
            }
        }
        gap /= 1.247;
    }
}

int main(){
    setlocale(LC_ALL, "RU");
    int n;
    cout << "Введите размерность N вашего будущего массива: ";
    cin >> n;
    ofstream fileOutput("input.txt");

    srand(time(NULL));

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            fileOutput << rand() % 41 - 20 << ' ';
        }
        fileOutput << endl;
    }
    fileOutput.close();

    ifstream fileInput("input.txt");
    if (!fileInput.is_open()) {
        cout << "Невозможно открыть файл. \n";
        return 1;
    }

    vector<vector<int>> arr;
    int num;

    string line;

    while (getline(fileInput, line)) {
        istringstream iss(line);
        vector<int> row;
        int num;
            while (iss >> num) {
                row.push_back(num);
            }
        arr.push_back(row);
        row.clear();
    }

    fileInput.close();

    cout << "Так выглядит ваш получившийся случайный массив: " << endl;
    outArr(n, arr);

    int var;
    do {
        cout << "Введите номер сортировки, которую хотите применить: \n" << "1. Сортировка подсчётом. \n" << "2. Сортировка расчёской. \n";
        cin >> var;

        switch (var)
        {
        case 1:
            cout << "Вы выбрали сортировку подсчётом, так выглядит ваш отсортированный массив: \n";
            countingSort(arr, n);
            break;
        
        case 2:
            cout << "Вы выбрали сортировку подсчётом, так выглядит ваш отсортированный массив: \n";
            combSort(arr, n);
            break;
        
        case 3:
            break;

        default:
            cout << "Пожалуйста, укажите число от [1-3]!\n";
            break;
        }
    } while (var != 1 && var != 2 && var !=3);

    outArr(n, arr);


    return 0;
}
