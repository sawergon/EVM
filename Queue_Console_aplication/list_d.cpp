//
// Created by Alex on 14.02.2023.
//

#include "list_d.ipp"

/*
template<typename Type>
List_d<Type>::List_d() {
    beg = fin = cur = nullptr;
}

template<typename Type>
void List_d<Type>::add(const Type &el) {
    Node *obj = new Node;
    obj->value = el;
    if (not beg) {
        beg = fin = cur = obj;
    } else if (beg == fin) {
        beg->next = obj;
        obj->prev = beg;
        fin = obj;
    } else {
        fin->next = obj;
        obj->prev = fin;
        fin = obj;
    }
}

template<typename Type>
List_d<Type>::~List_d() {
    Node *p;
    for (p = beg; p->next; ++p) {
        p = p->next;
        delete p->prev;
    }
    delete p;
    beg = fin = cur = nullptr;
}

template<typename Type>
Type List_d<Type>::next() {
    if (cur->next) {
        cur = cur->next;
        return cur->prev->value;
    }
    cur = nullptr;
    return fin->value;
}

template<typename Type>
bool List_d<Type>::eol() {
    if (cur) return false;
    cur = beg;
    return true;
}

template<typename Type>
Type List_d<Type>::prev() {
    if (cur->prev) {
        cur = cur->prev;
        return cur->next->value;
    }
    cur = nullptr;
    return beg->value;
}

template<typename Type>
Type List_d<Type>::pop_cur() {
    if (not cur) {
        throw PointerOutOfRange();
    }
    auto v = cur->value;
    auto mem = cur->prev;
    if (not cur->next) {
        fin = fin->prev;
        delete cur;
        cur = nullptr;
        return v;
    } if (not cur->prev) {
        beg = beg->next;
        delete cur;
        cur = nullptr;
        return v;
    }
    cur->next->prev = cur->prev;
    cur->prev->next = cur->next;
    delete cur;
    cur = mem;
    return v;
}

template<typename Type>
bool List_d<Type>::empty() {
    return beg;
}

template<typename Type>
void List_d<Type>::set_beg() {
    cur = beg;
}

template<typename Type>
Type List_d<Type>::curr() {
    return cur->value;
}

template<typename Type>
Type List_d<Type>::pop() {
    if (not beg) {
        throw PointerOutOfRange();
    }
    auto v = beg->value;
    if (not beg->next) {
        delete beg;
        cur = beg = fin = nullptr;
        return v;
    }
    beg = beg->next;
    if (cur == beg->prev) {
        cur = beg;
    }
    delete beg->prev;
    return v;
}

template<typename Type>
void List_d<Type>::add_after_curr(const Type &el) {
    if (cur == fin) this->add(el);
    Node* p = new Node;
    p->value = el;
    p->prev = cur;
    p->next = cur->next;
    cur->next->prev = p;
    cur->next = p;
}*/
