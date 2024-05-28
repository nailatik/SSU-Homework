#include <iostream>
using namespace std;

struct list
{
    int inf;
    list *next;
    list *prev;
};

//добавление эл-та в список
void push(list *&h, list *&t, int x)
{
    list *r = new list;
    r->inf = x;
    r->next = NULL;
    if (!h && !t)
    {
        r->prev = NULL;
        h = r;
    }
    else
    {
        t->next = r;
        r->prev = t;
    }

    t = r;
}

//вывод списка
void print(list *h, list *t)
{
    list *p = h;
    while(p)
    {
        cout << p->inf << " ";
        p = p->next;
    }
}

//удаление списка
void del_list(list *&h, list *&t)
{
    list *current = h;
    list *next;
    while(current != NULL)
    {
        next = current->next;
        delete current;
        current = next;
    }

    h = NULL;
}

void result(list *&h, list *&t) 
{
    list *result_h = h;
    
    int sum = 0;
    float count = 0;
    
    // Находим сумму всех элементов и их количество
    list *temp = h;
    while (temp) {
        sum += temp->inf;
        count++;
        temp = temp->next;
    }
    
    double arifm = sum / count; // Считаем среднее арифметическое
    
    while (result_h) {
        if (result_h->inf > arifm) { // Если элемент больше среднего арифметического, удаляем его
            list* temp_2 = result_h;
            if (result_h->prev) {
                result_h->prev->next = result_h->next;
            } else {
                h = result_h->next;
            }
            if (result_h->next) {
                result_h->next->prev = result_h->prev;
            }
            result_h = result_h->next;
            delete temp_2;
        } else {
            result_h = result_h->next;
        }
    }
}

int main()
{
    int n;
    cout << "Введите размерность: "; cin >> n;
    list *head = NULL;
    list *tail = NULL;
    int x;

    cout << "Начните ввод ваших чисел:\n" << "> ";
    for (int i = 0; i < n; i++) //заполнение списка
    {
        cin >> x;
        push(head, tail, x);
    }

    result(head, tail);
    cout << "Ваш результат:\n" << "> ";
    print(head, tail);

    del_list(head, tail);
    return 0;
}