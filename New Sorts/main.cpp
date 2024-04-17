#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>

using namespace std;

void outArr(int n, vector<int> &arr){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << arr[i * n + j] << ' ';
        }
        cout << endl;
    }
}

void countingSort(vector<int>& arr, int n) {
    int rowStart, rowEnd;
    for (int row = 0; row < n; row++) {
        rowStart = row * n;
        rowEnd = rowStart + n;
        vector<int> counts(41, 0);
        for (int i = rowStart; i < rowEnd; i++) {
            counts[arr[i] + 20]++;
        }
        int index = rowStart;
        for (int k = 0; k < 41; k++) {
            while (counts[k] > 0) {
                arr[index] = k - 20;
                index++;
                counts[k]--;
            }
        }
    }
}

void combSort(vector<int>& arr, int n){
    float gap = n/1.247;
    while (gap >= 1){
        if (gap < 1){
            gap = 1;
        }
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n - gap; j++){
                if ((j+1)%3 == 0){
                    if (arr[j * n + i] < arr[(j + gap) * n + i]){
                        swap(arr[j * n + i], arr[(j + gap) * n + i]);
                    }
                } else {
                    if (arr[j * n + i] > arr[(j + gap) * n + i]){
                        swap(arr[j * n + i], arr[(j + gap) * n + i]);
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

    vector<int> arr;
    int num;

    while (fileInput >> num) {
        arr.push_back(num);
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
