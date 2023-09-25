//
// Created by Alex on 25.09.2023.
//

#ifndef AVLTREE__CONSOLEWORK_H_
#define AVLTREE__CONSOLEWORK_H_

#include "avlTree.h"

enum console_code {repeat, out_table, add_data, remove_data, find_data, end_work, ok};

void printMenu();
int getCode(int &new_code);
int getNewData(tree_data &new_data);
void printTable(const node *tree);

#endif //AVLTREE__CONSOLEWORK_H_


/*/home/alex/../../usr/bin/valgrind
/home/alex/../../usr/libexec/valgrind
/home/alex/../../usr/lib/valgrind
/home/alex/../../usr/lib/x86_64-linux-gnu/valgrind
/home/alex/../../usr/include/valgrind
/home/alex/../../usr/share/doc-base/valgrind
/home/alex/../../usr/share/lintian/overrides/valgrind
/home/alex/../../usr/share/doc/valgrind
/home/alex/../../usr/share/glib-2.0/valgrind
/home/alex/../../usr/share/bash-completion/completions/valgrind
*/