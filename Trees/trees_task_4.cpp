#include <iostream>
#include <queue>
#include <iomanip>
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

void inorder(tree* tr) { // симметричный обход
    if (tr) {
        inorder(tr->left);
        cout << tr->inf << " ";
        inorder(tr->right);
    }
}

int heightOfNode(tree* root, int x) {
    if (!root) return -1; // Пустое поддерево имеет высоту -1

    if (root->inf == x) return 0; // Найденный узел имеет высоту 0

    int leftHeight = heightOfNode(root->left, x); // Рекурсивный вызов для левого поддерева
    int rightHeight = heightOfNode(root->right, x); // Рекурсивный вызов для правого поддерева

    // Высота узла - максимальная высота из высот левого и правого поддеревьев + 1
    return 1 + max(leftHeight, rightHeight);
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

    cout << "Ваше дерево после прямого обхода: ";
    inorder(tr);
    cout << endl;

    int x;
    cout << "Введите узел Х, длинну которого нужно определить: ";
    cin >> x;

    int height = heightOfNode(tr, x);
    if (height == -1)
        cout << "Узел " << x << " не найден на дереве." << endl;
    else
        cout << "Высота узла " << x << " составляет: " << height << endl;

    return 0;
}