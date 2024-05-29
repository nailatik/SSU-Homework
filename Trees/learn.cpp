#include <iostream>

struct tree{
    int inf;
    tree *left;
    tree *right;
    tree *parent;
};

tree *node(int x){
    tree *n = new tree;
    n -> inf = x;
    n ->parent = NULL;
    n -> right = NULL;
    n -> left = NULL;
}