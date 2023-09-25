//
// Created by Alex on 25.09.2023.
//

#include "consoleWork.h"
#include <iostream>

using namespace std;

enum console_code {repeat, out_table, add_data, remove_data, find_data, end_work, ok};

void printMenu() {
  cout << "Меню:" << endl;
  cout << "1. Вывести таблицу" << endl;
  cout << "2. Добавить данные" << endl;
  cout << "3. Убрать данные" << endl;
  cout << "4. Найти данные" << endl;
  cout << "5. Закончить работу" << endl;
}

int getCode(int &new_code) {
  cin >> new_code;
  if (cin.fail()) {
    return repeat;
  }
  return ok;
}
int getNewData(tree_data & new_data) {
  cin >> new_data.name;
  cin >> new_data.key;
  if (cin.fail()) {
    return repeat;
  }
  return ok;
}

void printTable(const node *tree) {
  if (tree->left) {
    printTable(tree->left);
  }
  cout << tree->key.name << endl;
  if(tree->right) {
    printTable(tree->right);
  }
}
