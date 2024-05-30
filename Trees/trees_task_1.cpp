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
            } else { // на случай ввода одинаковых узлов
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

tree* Min(tree* tr) { // поиск min
    if (!tr->left) return tr; // нет левого ребенка
    else return Min(tr->left); // идем по левой ветке до конца
}

void deleteEvenNodes(tree*& tr) { // удаление четных узлов
    if (!tr) return;
    
    deleteEvenNodes(tr->left);
    deleteEvenNodes(tr->right);

    if (tr->inf % 2 == 0) {
        tree* temp;
        if (!tr->left) {
            temp = tr->right;
        } else if (!tr->right) {
            temp = tr->left;
        } else {
            tree* minNode = Min(tr->right);
            tr->inf = minNode->inf;
            deleteEvenNodes(tr->right);
            return;
        }
        delete tr;
        tr = temp;
    }
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
    inorder(tr);
    cout << endl;

    deleteEvenNodes(tr);

    cout << "Дерево, после удаления чётных элементов: ";
    inorder(tr);
    cout << endl;

    return 0;
}