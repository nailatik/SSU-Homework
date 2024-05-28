#include <iostream>

struct list {
    int inf;
    list *next;
    list *prev;
};

void push(list *&h, list *&t, int x){//вставка в конец списка
    list *r = new list; // создаём новый элемент
    r->inf = x;
    r->next = NULL;
    if (!h && !t){
        r -> prev = NULL;
        h = r;
    } else {
        t->next = r;
        r->prev = t;
    }
    t = r; //хвост t будет указыавть на r
}