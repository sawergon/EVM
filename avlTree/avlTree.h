//
// Created by Alex on 20.09.2023.
//

#ifndef AVLTREE__ALVTREE_H_
#define AVLTREE__ALVTREE_H_

#include <string>

typedef struct s_data {
  int key;
  std::string name;
} tree_data;

struct node // структура для представления узлов дерева
{
  tree_data key;
  unsigned char height;
  node *left;
  node *right;
  node(tree_data k) {
    key = k;
    left = right = 0;
    height = 1;
  }
};

unsigned char height(node *p);

int bfactor(node *p);

void fixheight(node *p);

node *rotateright(node *p);

node *rotateleft(node *q);

node *balance(node *p);

node *insert(node *p, tree_data k);

node *findmin(node *p);

node *find_name(node *p, const std::string & name);

node *removemin(node *p);

node *remove(node *p, const std::string &k);

void delete_tree(node **tree);
#endif //AVLTREE__ALVTREE_H_
