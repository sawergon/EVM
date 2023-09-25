//
// Created by Alex on 14.02.2023.
//

#ifndef QUEUE_CONSOLE_APLICATION_EXCEPTIONS_H
#define QUEUE_CONSOLE_APLICATION_EXCEPTIONS_H

#include <string>

using namespace std;

class Base : public exception {
protected:
    string text;
public:
    virtual string what() = 0;
};

class ListExceptions : public Base {
public:
    ListExceptions() {
        text = "Ошибка в списке";
    }

    explicit ListExceptions(const string &user_text) {
        text = user_text;
    }

    string what() override {
        return text;
    }
};

class PointerOutOfRange : ListExceptions {
public:
    PointerOutOfRange() {
        text += ": Удаление элемента за концом списка. Переведите указатель в начальное положение с помощью list.set_beg()";
    }
    explicit PointerOutOfRange(const string& user_text) {
        text += ": " + user_text;
    }

    string what() override {return text;}
};class QueueExceptions : public Base {
public:
    QueueExceptions() {
        text = "Ошибка в очереди";
    }

    explicit QueueExceptions(const string &user_text) {
        text = user_text;
    }

    string what() override {
        return text;
    }
};

class EmptyQueue : QueueExceptions {
public:
    EmptyQueue() {
        text += ": Удаление элемента из пустой очереди";
    }
    explicit EmptyQueue(const string& user_text) {
        text += ": " + user_text;
    }

    string what() override {return text;}
};

class ModeException : QueueExceptions {
public:
    ModeException() {
        text += ": Неправильный режим приоритета";
    }
    explicit ModeException(const string& user_text) {
        text += ": " + user_text;
    }

    string what() override {return text;}
};


/*
class ValueTypeException : public Base {
public:
    ValueTypeException() {
        text = "Несоответствие типов";
    }
    explicit ValueTypeException(const string& user_text) {
        text = user_text;
    }

    string what() override { return text;}
};

class NegativeLengthException : public Base {
public:
    NegativeLengthException() {
        text = "Длинна массива меньше 0";
    }
    explicit NegativeLengthException(const string& user_text) {
        text = user_text;
    }

    string what() override { return text;}
};



class AmountOfValuesException : public Base {
public:
    AmountOfValuesException() {
        text = "Количество элементов в файле недостаточно";
    }
    explicit AmountOfValuesException(const string& user_text) {
        text = user_text;
    }

    string what() override { return text;}
};
*/

#endif //QUEUE_CONSOLE_APLICATION_EXCEPTIONS_H
