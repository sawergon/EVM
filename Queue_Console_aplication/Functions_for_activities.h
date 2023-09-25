//
// Created by Alex on 16.02.2023.
//

#ifndef QUEUE_CONSOLE_APLICATION_FUNCTIONS_FOR_ACTIVITIES_H
#define QUEUE_CONSOLE_APLICATION_FUNCTIONS_FOR_ACTIVITIES_H

#include "list_d.ipp"
#include "pr_queue.ipp"
#include <iostream>
#include <sstream>

using namespace std;
template <typename Type>
bool help_find(List_d<ElQueue<Type>> list, const string &name) {
    for (auto el = list.curr(); not list.eol(); el = list.next()) {
        if (el.name == name) {
            return true;
        }
    }
    return false;
}

template <typename Type>
bool help_add(List_d<ElQueue<Type>> &list, istringstream &ins, const string &name) {
    int priority;
    Type data;
    auto *p = new ElQueue<Type>;
    bool flag = false;
    for (auto el = list.curr(); not list.eol(); el = list.next()) {
        if (el.name == name) {
            flag = true;
            p->name = el.name;
            while (ins >> data >> priority) {
                p->queue.add(data, priority);
            }
            list.pop_cur();
            list.set_beg();
            list.add(*p);
            break;
        }
    }
    return flag;
}

template <typename Type>
bool help_pop(List_d<ElQueue<Type>> &list, istringstream &ins, const string &name) {
    ElQueue<Type> p;
    for (auto el = list.curr(); not list.eol(); el = list.next()) {
        if (el.name == name) {
            p = list.pop_cur();
            cout << p.queue.pop() << endl;
            list.add(p);
            return true;
        }
    }
    list.set_beg();
    return false;
}

template <typename Type>
void help_create(List_d<ElQueue<Type>> &list, istringstream &ins) {
    ElQueue<Type> a;
    ins >> a.name;
    list.add(a);
}

void help_error_com(const string &com);

#endif //QUEUE_CONSOLE_APLICATION_FUNCTIONS_FOR_ACTIVITIES_H
