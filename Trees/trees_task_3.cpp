#include <iostream>
using namespace std;

struct tree {
    int inf;
    tree* right;
    tree* left;
    tree* parent;
};

tree* node(int x) { // начальный узел
    tree* n = new tree;
    n->inf = x;
    n->left = n->right = nullptr;
    n->parent = nullptr;
    return n;
}

void insert(tree*& tr, int x) { // вставка
    tree* n = node(x);
    if (!tr) tr = n; // если дерево пустое - корень
    else {
        tree* y = tr;
        while (y) { // ищем куда вставлять
            if (n->inf > y->inf) { // правая ветка
                if (y->right)
                    y = y->right;
                else {
                    n->parent = y; // узел становится правым ребенком
                    y->right = n;
                    break;
                }
            } else if (n->inf < y->inf) { // левая ветка
                if (y->left)
                    y = y->left;
                else {
                    n->parent = y; // узел становится левым ребенком
                    y->left = n;
                    break;
                }
            } else {
                delete n;
                break;
            }
        }
    }
}

void preorder(tree* tr) { // симметричный обход
    if (tr) {
        cout << tr->inf << " ";
        preorder(tr->left);
        preorder(tr->right);
    }
}

tree* Min(tree* tr) { // поиск min
    if (!tr->left) return tr; // нет левого ребенка
    else return Min(tr->left); // идем по левой ветке до конца
}

// Функция для подсчета суммы листьев
int sumOfLeaves(tree* tr) {
    if (!tr) return 0;
    if (!tr->left && !tr->right) return tr->inf; // если это лист
    return sumOfLeaves(tr->left) + sumOfLeaves(tr->right);
}

int main() {
    tree* tr = nullptr;
    string input;
    cout << "Начните ввод элементов дерева, конец обозначьте (#): ";

    while (true) {
        cin >> input;
        if (input == "#") break;
        insert(tr, stoi(input));
    }

    cout << "Ваше дерево после симметричного обхода: ";
    preorder(tr);
    cout << endl;

    int sumLeaves = sumOfLeaves(tr);
    cout << "Сумма всех листьев: " << sumLeaves << endl;

    return 0;
}