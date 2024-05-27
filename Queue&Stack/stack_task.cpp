#include <iostream> 
#include <cctype> 
#include <cstring>

using namespace std; 

struct stack { 
    char c; 
    stack* next; 
}; 
 
void push(stack*& h, char x) {
    stack* r = new stack; 
    r->c = x; 
    r->next = h; 
    h = r;
} 
 
char pop(stack*& h) { 
    char c = h->c; 
    stack* r = h; 
    h = h->next; 
    delete r; 
    return c; 
} 

bool isVowel(char c) { 
    c = tolower(c); 
    return isalpha(c) && strchr("ouiea", c) != nullptr; 
} 

void task_func(stack*& h) { 
    stack* result = NULL; 
    stack* tempStack = NULL; 
    while (h) { 
        push(result, pop(h)); 
    } 
 
    bool foundVowel = false; 

    while (result) { 
    char curr = pop(result); 
    if (!foundVowel && isVowel(curr)) { 
        push(tempStack, curr); 
        push(tempStack, '?');
        foundVowel = true; 
    } 
    else { 
        push(tempStack, curr); 
        } 
    } 
    while (tempStack) { 
        push(h, pop(tempStack)); 
    } 
} 
 
int main() { 
    stack* head = nullptr; 
    char input;
    cout << "Начните ваш ввод букв латинского алфавита, конец обозначьте знаком (#):\n" << "> "; 
    while (cin >> input && input != '#') { 
        push(head, input);
    }
    task_func(head); 
    cout << "Результат работы программы:\n" << "> "; 
    stack* temp = head; 
    while (temp) { 
        cout << temp->c << " "; 
        temp = temp->next; 
    } 
    
    cout << endl; 
    
    return 0; 
}