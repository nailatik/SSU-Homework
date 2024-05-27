#include <iostream>
using namespace std;

struct queue
{
    int inf;
    queue *next;
};

void push(queue *&h, queue *&t, int x){//элемент в конец
    queue *r = new queue;
    r->inf = x;
    r->next = NULL;
    if(!h && !t)
        h = t = r;
    else
    {
        t->next = r;
        t = r;
    }
}

int pop(queue *&h, queue*&t){//удаление из начала
    queue *r = h;
    int i = h->inf;
    h = h->next;
    if (!h)
        t = NULL;
    delete r;
    return i;
}

bool isPrime(int n){
    if (n <= 1){
        return 0;
    }
    for (int i = 2; i <= n / 2; i++){
        if (n % i == 0)
            return 0;
    }
    return 1;
}

void result(queue *&h, queue *&t)
{
    while (isPrime(h->inf) == 0)
    {
        push(h, t, pop(h, t));
    }
}
  

int main()
{
    queue *head = NULL;
    queue *tail = NULL;
    int x;
    cout << "Начните ввод чисел в очередь, конец обозначьте (0):\n" << "> ";
    while (cin >> x && x != 0){
        push(head, tail, x);
    }
    
    result(head, tail);
    cout << "Результат работы программы:\n" << "> ";
    while (head && tail)
        cout << pop(head, tail) << " ";

    cout << "\n";
    return 0;
}