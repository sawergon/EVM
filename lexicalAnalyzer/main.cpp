//
// Created by alex on 03.10.23.
//
#include <iomanip>
#include <iostream>
#include <string.h>

#include "Analyzer.h"
#include "avlTree.h"

using namespace std;

const char *convert_code(int code) {
    switch (code) {
        case ID_NUM: return "ID_NUM\0";
        case ID_SET: return "ID_SET\0";
        case ID_NOT_EQ: return "ID_NOT_EQ\0";
        case ID_SUM: return "ID_SUM\0";
        case ID_DIF: return "ID_DIF\0";
        case ID_MUL: return "ID_MUL\0";
        case ID_DIV: return "ID_DIV\0";
        case ID_VAR: return "ID_VAR\0";
        case ID_IF: return "ID_IF\0";
        case ID_ELSE: return "ID_ELSE\0";
        case ID_REPEAT: return "ID_REPEAT\0";
        case ID_UNTIL: return "ID_UNTIL\0";
        case ID_LEFT: return "ID_LEFT\0";
        case ID_RIGHT: return "ID_RIGHT\0";
        case ID_BREAK: return "ID_BREAK\0";
        case ID_LESS: return "ID_LESS\0";
        case ID_MORE: return "ID_MORE\0";
        case ID_EQ: return "ID_EQ\0";
    }
    return "TYPE_TRASH";
}

void printTable(const node *tree) {
    if (tree->left) {
        printTable(tree->left);
    }
    cout << '|' << setw(15) << tree->key.name << '|' << setw(12) << convert_code(tree->key.key) << '|' << endl;
    if (tree->right) {
        printTable(tree->right);
    }
}

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
    str[(*len)++] = '\0';
    return str;
}

int main() {
    node *lexeme_table = nullptr;
    node *id_table = nullptr;
    int len = 0, pos = 0;
    char *source = get_string(&len);
    while (pos < len) {
        lexeme k;
        if (get_lexeme(source, pos, k) == CODE_ER) {
//            cout << "unknown symbol " << source[pos] << endl;
            pos++;
        } else {
            lexeme_table = insert(lexeme_table, k);
            if (((k.key == ID_NUM) || (k.key == ID_VAR)) && (!id_table || !find_name(id_table, k.name))) {
                lexeme d;
                d.name = (char *) malloc(strlen(k.name) + 1);
                strcpy(d.name, k.name);
                d.key = k.key;
                id_table = insert(id_table, d);
            }
        }
    }
    printTable(lexeme_table);
    cout << "---------------------------------" << endl;
    printTable(id_table);
    free(source);
    delete_tree(&lexeme_table);
    delete_tree(&id_table);
    return 0;
}