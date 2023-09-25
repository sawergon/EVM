#ifndef QUEUE_CONSOLE_APLICATION_PR_QUEUE_IPP
#define QUEUE_CONSOLE_APLICATION_PR_QUEUE_IPP

#include "Exceptions.h"
#include <iostream>

using namespace std;

template<typename Type>
class Pr_queue {
private:
    // структура элемента списка
    struct Node {
        // значение
        Type value;
        // приоритет
        int priority = 0;
        // указатели на следующий и предыдущий
        Node *next = nullptr, *prev = nullptr;;
    };
    // указатели начала, конца и текущего элемента обработки
    Node *beg, *fin, *cur;

    // удаление текущего элемента
    Type pop_cur();

    // добавление элемента после текущего
    void add_after_curr(const Type &el);

    // переход к следующему элементу
    Type next();

    // переход к предыдущему элементу
    Type prev();

    // текущий элемент
    Type curr();

    // проверка на достижения конца списка
    bool eol() const;

    // установка cur на позицию beg
    void set_beg();

public:
    // конструктор
    Pr_queue();

    // удаление из начала
    Type pop();

    // добавление элемента в конец
    void add(const Type &el, const int &pr);

    // проверка на пустоту
    bool empty();

    // вывод на экран
    void print(bool with_pr = false) const;

    Pr_queue<Type>& operator=(const Pr_queue<Type> &queue);

    bool operator==(const Pr_queue<Type> &queue) const;

    // деструктор
    ~Pr_queue();
};

template<typename Type>
Pr_queue<Type>::Pr_queue() {
    beg = fin = cur = nullptr;
}

template<typename Type>
void Pr_queue<Type>::add(const Type &el, const int &pr) {
    Node *obj = new Node;
    obj->value = el;
    obj->priority = pr;
    if (not beg) {
        beg = fin = cur = obj;
//    } else if (beg == fin) {
//        if (beg->priority >= obj->priority) {
//            beg->next = obj;
//            obj->prev = beg;
//            fin = obj;
//        } else {
//            beg->prev = obj;
//            obj->next = beg;
//            fin = beg;
//            beg = obj;
//            cur = beg;
//        }
    } else {
        bool flag = false;
        auto p = beg;
        for (auto elem = beg; (elem) and (not flag);) {
            if (elem->priority < obj->priority) {
                flag = true;
                p = elem;
            }
            elem = elem->next;
        }
        if (flag) {
            if (p == beg) {
                beg->prev = obj;
                obj->next = beg;
                fin = beg;
                beg = obj;
                cur = beg;
            } else {
                p->prev->next = obj;
                obj->prev = p->prev;
                obj->next = p;
                p->prev = obj;
            }
        } else {
            fin->next = obj;
            obj->prev = fin;
            fin = obj;
        }
    }
}

template<typename Type>
Pr_queue<Type>::~Pr_queue() {
    if (not beg) {
        return;
    }
    Node *p;
    for (p = beg; p->next; p = p->next) {
        delete p->prev;
    }
    delete p;
    beg = fin = cur = nullptr;
}

template<typename Type>
Type Pr_queue<Type>::next() {
    if (cur->next) {
        cur = cur->next;
        return cur->value;
    }
    cur = nullptr;
    return fin->value;
}

template<typename Type>
bool Pr_queue<Type>::eol() const {
    if (cur) return false;

    return true;
}

template<typename Type>
Type Pr_queue<Type>::prev() {
    if (cur->prev) {
        cur = cur->prev;
        return cur->next->value;
    }
    cur = nullptr;
    return beg->value;
}

template<typename Type>
Type Pr_queue<Type>::pop_cur() {
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
    }
    if (not cur->prev) {
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
bool Pr_queue<Type>::empty() {
    return not beg;
}

template<typename Type>
void Pr_queue<Type>::set_beg() {
    cur = beg;
}

template<typename Type>
Type Pr_queue<Type>::curr() {
    return cur->value;
}

template<typename Type>
Type Pr_queue<Type>::pop() {
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
void Pr_queue<Type>::add_after_curr(const Type &el) {
    if (cur == fin) this->add(el);
    Node *p = new Node;
    p->value = el;
    p->prev = cur;
    p->next = cur->next;
    cur->next->prev = p;
    cur->next = p;
}

template<typename Type>
void Pr_queue<Type>::print(const bool pr) const {
    if (not beg) {
        cout << "empty" << endl;
        return;
    }
    for (auto el = beg; el ; ) {
        if (not pr) {
            cout << el->value << ' ';
        } else {
            cout << '(' <<  el->value << ", " << el->priority << ')' << ' ';
        }
        el = el->next;
    }
    cout << endl;
}

template<typename Type>
Pr_queue<Type>& Pr_queue<Type>::operator=(const Pr_queue<Type> &queue) {
    if (*this == queue) {
        return *this;
    }
    for (auto p = queue.beg; not queue.eol(); p = p->next) {
        this->add(p->value, p->priority);
    }
    return *this;
}

template<typename Type>
bool Pr_queue<Type>::operator==(const Pr_queue<Type> &queue) const {
    auto self_p = this->beg;
    auto el_p = queue.beg;
    for (; (not this->eol()) and (queue.cur);) {
        if ((self_p->value != el_p->value) or (self_p->priority != el_p->priority)) {
            return false;
        }
        self_p = self_p->next;
        el_p = el_p->next;
    }
    return true;
}


/*
template<typename Type>
class Pr_queue : public List_d<Type> {
private:
    struct Node {
        Type value;
        int priority = 0;
    };
    List_d<Node> queue;
public:
    Pr_queue() = default;

    void add(const Type &el, const int &pr = 0);

    void print();

    ~Pr_queue() = default;
//    template<typename Typee>
//    friend ostream &operator<<(ostream &os, const Pr_queue<Typee> &list);

//    template<typename Typee>
//    friend istream &operator>>(istream &is, Pr_queue<Typee> &list);
};

template<typename Type>
void Pr_queue<Type>::add(const Type &el, const int &pr) {
    Node addable;
    addable.value = el;
    addable.priority = pr;
    queue.set_beg();
    if (queue.empty()) {
        queue.add(addable);
        return;
    }
    bool flag = false;
    for (auto elem = queue.curr(); (not queue.eol()) and (not flag);) {
        if (elem.priority > addable.priority) flag = true;
        elem = queue.next();
    }
    if (flag) {
        queue.prev();
        queue.add_after_curr(addable);
    } else {
        queue.add(addable);
    }
}

template<typename Type>
void Pr_queue<Type>::print() {
    queue.set_beg();
    for (auto elem = queue.curr(); not queue.eol(); elem = queue.next()) {
        cout << elem.value << ' ';
    }
}
*/
template <typename Type>
class ElQueue {
public:
        string name;
        Pr_queue<Type> queue;
        ElQueue<Type>& operator=(const ElQueue<Type> &el);
        bool operator==(const ElQueue<Type> &el);
    };

template<typename Type>
ElQueue<Type>& ElQueue<Type>::operator=(const ElQueue<Type> &el) {
    if (*this == el) {
        return *this;
    }
    (*this).queue = el.queue;
    (*this).name = el.name;
    return *this;
}

template<typename Type>
bool ElQueue<Type>::operator==(const ElQueue<Type> &el) {
    return ((*this).name == el.name) and ((*this).queue == el.queue);
}

#endif //QUEUE_CONSOLE_APLICATION_PR_QUEUE_IPP