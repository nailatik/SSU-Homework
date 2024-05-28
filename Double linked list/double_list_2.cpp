#include <iostream>

using namespace std;

struct list {
	int inf;
	list* next;
	list* prev;
};

void push(list*& h, list*& t, int x) {
	list* r = new list;
	r->inf = x;
	r->next = NULL;
	if (!h && !t) {
		r->prev = NULL;
		h = r;
	}
	else {
		t->next = r;
		r->prev = t;
	}
	t = r;
}

void insert(list*& h, list*& t, list*& r, int x) {
	list* p = new list;
	p->inf = x;
	if (r == t) {
		p->next = NULL;
		p->prev = r;
		r->next = p;
		t = p;
	}
	else {
		r->next->prev = p;
		p->next = r->next;
		p->prev = r;
		r->next = p;
	}
}

void print(list* h, list* t) {
	list* p = h;
	while (p) {
		cout << p->inf << " ";
		p = p->next;
	}
}

list* find(list* h, list* t, int x) {
	list* p = h;
	while (p) {
		if (p->inf == x) break;
		p = p->next;
	}
	return p;
}

void del(list*& h, list*& t, list* r) {
	if (r == h && r == t)
		h = t = NULL;
	else if (r == h) {
		h = h->next;
		h->prev = NULL;
	}
	else if (r == t) {
		t = t->prev;
		t->next = NULL;
	}
	else {
		r->next->prev = r->prev;
		r->prev->next = r->next;
	}
}

int main() {
	int n;
	cout << "Введите размерность: ";
	cin >> n;
	cout << "Начните ввод ваших чисел:\n" << "> ";

	list* head = NULL;
	list* tail = NULL;
	list* temp_head = NULL;
	list* temp_tail = NULL;

	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		if (x % 2 == 0)
			push(head, tail, x);
		else
			push(temp_head, temp_tail, x);
	}

	while (temp_head) {
		push(head, tail, temp_head->inf);
		del(temp_head, temp_tail, temp_head);
	}
    cout << "Ваш результат:\n" << "> ";
	print(head, tail);

	return 0;
}