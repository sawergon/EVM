#include <iostream>
#include <iomanip>
#include "static_analyzer.h"
using namespace std;

char *get_string(int *len) {
  *len = 0;
  int capacity = 1;
  char *str = (char *) malloc(capacity), c;
  c = getchar();
  while (c != '\n') {
    str[(*len)++] = c;
    if (*len >= capacity) {
      capacity *= 2;
      str = (char *) realloc(str, capacity * sizeof(char));
    }
    c = getchar();
  }
  str[(*len)] = '\0';
  return str;
}

void printTable1(const node *tree) {
  if (tree->left) {
    printTable1(tree->left);
  }
  cout << '|' << setw(15) << tree->key.name << '|' << setw(12) << tree->key.key << '|' << endl;
  if (tree->right) {
    printTable1(tree->right);
  }
}

void printTable2(const node *tree) {
  if (tree->left) {
    printTable2(tree->left);
  }
  cout << '|' << setw(15) << tree->key.name << '|' << setw(12) << global::data_field[tree->key.key] << '|' << endl;
  if (tree->right) {
    printTable2(tree->right);
  }
}

int main() {
  int len = 0;
  char *source = get_string(&len);
  if (translator(source, len) == AN_COMMAND_ACCEPT) {
    cout << "ACCEPT" << endl;
  } else {
    cout << "REJECT" << endl;
  }
  cout << "name        data field link" << endl;
  printTable1(global::var_table);
  cout << "name        data field value" << endl;
  printTable2(global::var_table);
  return 0;
}