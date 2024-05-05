#include <iostream>
#include <cmath>
#include <queue>

using namespace std;

bool prime_digital(int n){
    if (n < 2){
        return false;
    }
    for (int i = 2; i <= sqrt(n); i++){
        if (n % i == 0){
            return false;
        }
    }
    return true;
}

int main(){
    queue <int> q;
    int dig;
    cout << "Введите ваши числа (конец вводе обозначен '#'): ";
    while (cin >> dig){
        q.push(dig);
        if (cin.peek()=='#'){
            break;
        }
    }

    while(!q.empty() && !prime_digital(q.front())){
        q.push(q.front());
        q.pop();
    }

    while(!q.empty()){
        cout << q.front() << '\t';
        q.pop();
    }

    system("pause");
}

