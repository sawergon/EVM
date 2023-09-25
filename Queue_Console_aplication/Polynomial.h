//
// Created by Alex on 08.03.2023.
//

#ifndef QUEUE_CONSOLE_APLICATION_Polynomial_H
#define QUEUE_CONSOLE_APLICATION_Polynomial_H

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

static const int len = 27;
static const string names = "abcdefghijklmnopqrstuvwxyz";

class Polynomial {
private:

    struct Values {
        int deg[len];
        double coef;

        friend bool operator==(const Values &val1, const Values &val2) {
            for (int i = 0; i < len; ++i) {
                if (val1.deg[i] != val2.deg[i]) {
                    return false;
                }
            }
            return true;
        }

        friend ostream &operator<<(ostream &os, const Values &v) {
            if (v.coef == 0) {
                return os;
            } else if ((v.deg[0] != 0) and (abs(v.coef) != 1)) {
                os << abs(v.coef);
            } else if (v.deg[0] == 0) {
                os << abs(v.coef);
            }
            for (int i = 0; i < len; ++i) {
                if (v.deg[i] != 0) {
                    if (v.deg[i] == 1) {
                        os << names[i] << ' ';
                    } else {
                        os << names[i] << '^' << v.deg[i] << ' ';
                    }
                }
            }
            return os;
        }

        Values &operator=(const Values &values);

        ~Values() {
            coef = 0;
            for (int &i: deg) {
                i = 0;
            }
        }
    };

    Values *data;
    int kol;
public:

    Polynomial();

    void add(const double &coef, const int *deg);

    friend ostream &operator<<(ostream &os, const Polynomial &v);

    friend istream &operator>>(istream &is, Polynomial &v);

    friend Polynomial operator*(const Polynomial &p1, const Polynomial &p2);

    void diff(const int times = 1, const int var = 0);

    friend bool operator==(const Polynomial &pol1, const Polynomial &pol2);

    Polynomial &operator=(const Polynomial &pol);

    void collector();

    ~Polynomial();
};

Polynomial *create_add(Polynomial *pol, int &quantity);

Polynomial *del_help(Polynomial *pol, int &quantity, const int &ind);


#endif //QUEUE_CONSOLE_APLICATION_Polynomial_H
