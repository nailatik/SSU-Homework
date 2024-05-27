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


void result(queue *&h, queue *&t)
{
    int minNum = INT_MAX;
    int lastOdd = 0;
    queue *temp = h;
    queue *prev = NULL;

    // Находим минимальное число и последний нечетный элемент
    while (temp)
    {
        if (temp->inf < minNum)
            minNum = temp->inf;
        
        if (temp->inf % 2 != 0)
            lastOdd = temp->inf;

        prev = temp;
        temp = temp->next;
    }
    // Вставляем последний нечетный элемент после всех чисел, равных минимальному числу
    temp = h;
    while (temp)
    {
        if (temp->inf == minNum)
        {
            queue *r = new queue;
            r->inf = lastOdd;
            r->next = temp->next;
            temp->next = r;

            if (temp == t) // Если последний элемент в очереди, обновляем указатель на хвост
                t = r;

            temp = r; // Продвигаемся на следующий элемент после вставленного нечетного числа
        }

        temp = temp->next;
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