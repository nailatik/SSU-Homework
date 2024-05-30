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
            }
        }
    }
}

void inorder(tree* tr) { // симметричный обход
    if (tr) {
        inorder(tr->left);
        cout << tr->inf << " ";
        inorder(tr->right);
    }
}

tree* find(tree* tr, int x) { // поиск
    if (!tr || x == tr->inf) // нашли или дошли до конца ветки
        return tr;
    if (x < tr->inf)
        return find(tr->left, x); // ищем по левой ветке
    else
        return find(tr->right, x); // ищем по правой ветке
}

tree* Min(tree* tr) { // поиск min
    if (!tr->left) return tr; // нет левого ребенка
    else return Min(tr->left); // идем по левой ветке до конца
}

int main() {
    tree* tr = nullptr;
    string input;
    cout << "Enter the elements of the tree, end with #: ";

    while (true) {
        cin >> input;
        if (input == "#") break;
        insert(tr, stoi(input));
    }

    cout << "Original tree (in-order): ";
    inorder(tr);
    cout << endl;

    return 0;
}