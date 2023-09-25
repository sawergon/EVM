#include <iostream>
#include "avlTree.h"
#include "consoleWork.h"
#include <clocale>
using namespace std;

int main() {
  setlocale(LC_ALL, "rus");
  std::cout << "Программа для работы с таблицей идентификаторов в виде сбалансированного дерева." << std::endl;
  node * tree = new node({1, "name 2"});
  tree = insert(tree, {2, "name 1"});
  tree = insert(tree, {-1, "name 3"});
  printTable(tree);
  delete_tree(&tree);
  return 0;
}
