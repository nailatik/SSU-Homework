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


// Функция для поиска наименьшего общего предка (LCA)
tree* LCA(tree* root, int n1, int n2) {
    if (!root) return nullptr;

    if (root->inf > n1 && root->inf > n2)
        return LCA(root->left, n1, n2);

    if (root->inf < n1 && root->inf < n2)
        return LCA(root->right, n1, n2);

    return root;
}

// Функция для нахождения расстояния от предка до узла
int findDistance(tree* root, int k) {
    if (root->inf == k)
        return 0;
    else if (root->inf > k)
        return 1 + findDistance(root->left, k);
    return 1 + findDistance(root->right, k);
}

// Основная функция для вычисления длины пути от A до B
int findPathLength(tree* root, int a, int b) {
    tree* lca = LCA(root, a, b);

    int d1 = findDistance(lca, a);
    int d2 = findDistance(lca, b);

    return d1 + d2;
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

    cout << "Введите узлы А и Б для определение длины между ними (через пробел): ";
    int a, b;
    cin >> a >> b;

    int pathLength = findPathLength(tr, a, b);
    cout << "Длина от " << a << " до " << b << " равно: " << pathLength << endl;

    return 0;
}