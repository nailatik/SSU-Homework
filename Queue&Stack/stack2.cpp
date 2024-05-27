#include <iostream>

using namespace std;

struct stack {
	int inf;
	stack* next;
};

void push(stack*& h, int x) {
	stack* r = new stack;
	r->inf = x;
	r->next = h;
	h = r;
}

int pop(stack*& h) {
	int i = h->inf;
	stack* r = h;
	h = h->next;
	delete r;
	return i;
}

void reverse(stack*& h) {
	stack* head1 = NULL;
	while (h)
		push(head1, pop(h));
	h = head1;
}

stack* result(stack*& h, int mx) {
	bool first = true;
	stack * res = NULL;
	stack * h1 = NULL;

	while (h) {
		int x = pop(h);

		if (first && x == mx) {
			first = false;
			continue;
		}

		push(res, x); 

		while (h) {
			int y = pop(h);
			push(h1, y);
		}

		reverse(h1);
		h = h1;
		h1 = NULL;
	}

	reverse(res);
	return res;
}

int main() {
	int x, max = INT_MIN;
	stack * head = NULL; 
	cout << "Начните ввод чисел в очередь, конец обозначьте '#':\n" << "> ";
	while (cin >> x && x !='#'){ 
		if (x > max) {
			max = x;
		}

		push(head, x);
	}
	reverse(head);
	stack * res = result(head, max); 
	reverse(res);
	res = result(res, max);
	reverse(res);
    cout << "Результат работы программы:\n" << "> ";
	while (res){
		cout << pop(res) << " "; 
	}
	return 0;
}

