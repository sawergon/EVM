#include <stdio.h>
#include <stdlib.h>

#include <clocale>
#include <iomanip>
#include <iostream>

#include "avlTree.h"
#include "consoleWork.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");
    std::cout << "Программа для работы с таблицей идентификаторов в виде сбалансированного дерева." << std::endl;
    int code = ok;
    node *tree = nullptr;
    while (code != end_work) {
        printMenu();
        if (!getCode(code)) {
            code = repeat;
        }
        system("clear");
        switch (code) {
            case repeat: {
                cout << "Повторите ввод" << endl;
                break;
            }
            case out_table: {
                if (tree == nullptr) {
                    cout << "Таблица пуста добавте элементы" << endl;
                } else {
                    cout << '|' << setw(18) << "Имя" << '|' << setw(15) << "Атрибут" << '|' << endl;
                    cout << "--------------------------" << endl;
                    printTable(tree);
                }
                break;
            }
            case add_data: {
                tree_data d;
                cout << "Введите данные в формате имя enter атрибут enter" << endl;
                if (getNewData(d) == repeat) {
                    cout << "Введены некоретные данные" << endl;
                } else {
                    tree = insert(tree, d);
                }
                break;
            }
            case remove_data: {
                if (tree) {
                    string name;
                    cout << "Ведите имя эдемента для удаления" << endl;
                    cin >> name;
                    if (cin.fail()) {
                        cin.clear();// на случай, если предыдущий ввод завершился с ошибкой
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Неверный ввод" << endl;
                    }
                    tree = remove(tree, name);
                } else {
                    cout << "Таблица пуста. Нечего удалять" << endl;
                }
                break;
            }
            case find_data: {
                if (tree) {
                    string name;
                    cout << "Ведите имя эдемента для поиска" << endl;
                    cin >> name;
                    if (cin.fail()) {
                        cin.clear();// на случай, если предыдущий ввод завершился с ошибкой
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Неверный ввод" << endl;
                    }
                    node *f = find_name(tree, name);
                    if (f) {
                        cout << "Найденый элемент" << endl;
                        cout << "имя: " << f->key.name << " атрибут: " << f->key.key << endl;
                    } else {
                        cout << "Такого элемента нет в таблице" << endl;
                    }
                } else {
                    cout << "Таблица пуста. Нечего искать" << endl;
                }
                break;
            }
        }
    }
    if (tree) {
        delete_tree(&tree);
    }
    return 0;
}
