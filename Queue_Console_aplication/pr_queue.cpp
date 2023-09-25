//
// Created by Alex on 14.02.2023.
//

#include "pr_queue.ipp"
#include "string"
#include "sstream"

using namespace std;

/*
template<typename Type>
void Pr_queue<Type>::add(const Type &el, const int &pr) {
    Node addable;
    addable.value = el;
    switch (priority_mode) {
        case Manual:
            addable.priority = pr;
            break;
        case Num:
            addable.priority = el;
            break;
        case String:
            addable.priority = el.length();
            break;
        default:
            throw ModeException();
            break;
    }
    queue.set_beg();
    bool flag = false;
    for(auto elem = queue.curr(); (not queue.eol()) and (not flag); elem = queue.next()) {
        if (elem.priority > addable.priority) flag = true;
    }
    if (flag) {
        queue.prev();
        queue.add_after_curr(addable);
    } else {
        queue.add(addable);
    }
}
*/

//template<typename Typee>
//ostream &operator<<(ostream &os, const Pr_queue<Typee> &list) {
//    for (auto *p = list.beg; p != list.fin; p = p->next) {
//        os << p->value << ", ";
//    }
//    os << list.fin->value;
//    return os;
//}

//template<typename Typee>
//istream &operator>>(istream &is, Pr_queue<Typee> &list) {
//    string buf;
//    Typee input;
//    getline(is, buf);
//    istringstream ssin(buf);
//    while (ssin >> input) {
//        list.add(input);
//    }
//    return is;
//}

