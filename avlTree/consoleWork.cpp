//
// Created by Alex on 25.09.2023.
//

#include "consoleWork.h"

#include <iomanip>
#include <iostream>

using namespace std;

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
    if (cin.fail() || getchar() != '\n') {
        cin.clear(); // на случай, если предыдущий ввод завершился с ошибкой
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return repeat;
    }
    return ok;
}
int getNewData(tree_data &new_data) {
    cin >> new_data.name;
    cin >> new_data.key;
    if (cin.fail() || getchar() != '\n') {
        cin.clear(); // на случай, если предыдущий ввод завершился с ошибкой
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return repeat;
    }
    return ok;
}

void printTable(const node *tree) {
    if (tree->left) {
        printTable(tree->left);
    }
    cout << '|' << setw(15) << tree->key.name << '|' << setw(8) << tree->key.key << '|' << endl;
    if (tree->right) {
        printTable(tree->right);
    }
}
