#include "avlTree.h"
#include <cstring>
using namespace std;

unsigned char height(node *p) {
    return p ? p->height : 0;
}

int bfactor(node *p) {
    return height(p->right) - height(p->left);
}

void fixheight(node *p) {
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

node *rotateright(node *p)// правый поворот вокруг p
{
    node *q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

node *rotateleft(node *q)// левый поворот вокруг q
{
    node *p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

node *balance(node *p)// балансировка узла p
{
    fixheight(p);
    if (bfactor(p) == 2) {
        if (bfactor(p->right) < 0)
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if (bfactor(p) == -2) {
        if (bfactor(p->left) > 0)
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p;// балансировка не нужна
}



node *insert(node *p, lexeme k)// вставка ключа k в дерево с корнем p
{
    if (!p) return new node(k);
    if (strcmp(k.name, p->key.name) < 0)
        p->left = insert(p->left, k);
    else
        p->right = insert(p->right, k);
    return balance(p);
}

node *insert_single(node *p, const lexeme & k) {
    if (!p || !find_name(p, k.name)) return insert(p, k);
    else return p;
}

node *findmin(node *p)// поиск узла с минимальным ключом в дереве p
{
    return p->left ? findmin(p->left) : p;
}

node *find_name(node *p, char *name) {
    if (strcmp(name, p->key.name) == 0)
        return p;
    if (strcmp(name, p->key.name) < 0) {
        if (p->left)
            return find_name(p->left, name);
        else
            return nullptr;
    } else {
        if (p->right)
            return find_name(p->right, name);
        else
            return nullptr;
    }
}

node *removemin(node *p)// удаление узла с минимальным ключом из дерева p
{
    if (p->left == nullptr)
        return p->right;
    p->left = removemin(p->left);
    return balance(p);
}

node *remove(node *p, char *k)// удаление ключа k из дерева p
{
    if (!p) return nullptr;
    if (strcmp(k, p->key.name) < 0)
        p->left = remove(p->left, k);
    else if (k > p->key.name)
        p->right = remove(p->right, k);
    else//  k == p->key
    {
        node *q = p->left;
        node *r = p->right;
        free(p->key.name);
        delete p;
        if (!r) return q;
        node *min = findmin(r);
        min->right = removemin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}

void delete_tree(node **tree) {
    if ((*tree)->left) {
        delete_tree(&((*tree)->left));
    }
    if ((*tree)->right) {
        delete_tree(&((*tree)->right));
    }
    free((*tree)->key.name);
    delete *tree;
}