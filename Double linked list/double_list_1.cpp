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

void print(list* h, list* t) {
	list* p = h;
	while (p) {
		cout << p->inf << " ";
		p = p->next;
	}
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
    cout << "Начните ввод вашей последовательности:\n" << "> ";
	list* head = NULL;
	list* tail = NULL;
	int maximum, last_odd;
	bool have_odd = false;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		push(head, tail, x);
		if (i == 0)
			maximum = x;
		else
			maximum = max(maximum, x);
		if (x % 2 != 0) {
			last_odd = x;
			have_odd = true;
		}
	}

	list* temp_head = NULL;
	list* temp_tail = NULL;

	if (have_odd) {
		while (head) {
			push(temp_head, temp_tail, head->inf);
			if (head->inf == maximum)
				push(temp_head, temp_tail, last_odd);
			head = head->next;
		}
        cout << "Итоговая последовательность:\n" << "> ";
		print(temp_head, temp_tail);
	}


	return 0;
}