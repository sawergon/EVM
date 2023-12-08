//
// Created by Alex on 20.09.2023.
//

#ifndef AVLTREE_ALVTREE_H_
#define AVLTREE_ALVTREE_H_

#include <string>
#include <utility>

typedef struct s_data {
    int key{};
    char *name{};
} lexeme;

struct node// структура для представления узлов дерева
{
    lexeme key;
    unsigned char height;
    node *left;
    node *right;
    explicit node(lexeme k) {
        key = k;
        left = right = nullptr;
        height = 1;
    }
};

unsigned char height(node *p);

int bfactor(node *p);

void fixheight(node *p);

node *rotateright(node *p);

node *rotateleft(node *q);

node *balance(node *p);

node *insert(node *p, lexeme k);

node *findmin(node *p);

node *find_name(node *p, char *name);

node *removemin(node *p);

node *remove(node *p, char *k);

void delete_tree(node **tree);

node *insert_single(node *p, const lexeme & k);
#endif//AVLTREE_ALVTREE_H_
