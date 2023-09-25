#include "Polynomial.h"

Polynomial::Values &Polynomial::Values::operator=(const Polynomial::Values &values) {
    if (*this == values) {
        return *this;
    }
    for (int i = 0; i < len; ++i) {
        this->deg[i] = values.deg[i];
    }
    this->coef = values.coef;
    return *this;
}


void Polynomial::add(const double &coef, const int *deg) {
    auto val = new Values;
    for (int i = 0; i < 27; ++i) {
        val->deg[i] = deg[i];
    }
    val->coef = coef;
    Values data_c[kol];
    for (int i = 0; i < kol; ++i) {
        data_c[i] = data[i];
    }
    delete[]data;
    data = new Values[kol + 1];
    for (int i = 0; i < kol; ++i) {
        data[i] = data_c[i];
    }
    data[kol] = *val;
    kol++;
}

Polynomial::Polynomial() {
    data = nullptr;
    kol = 0;
}

Polynomial::~Polynomial() {
    delete[]data;
    data = nullptr;
    kol = 0;
}

istream &operator>>(istream &is, Polynomial &v) {
    cout << "enter quantity of monomial" << endl;
    int q;
    is >> q;
    is.ignore(100, '\n');
    for (int i = 0; i < q; ++i) {
        cout << "enter coef and degrees" << endl;
        string buf;
        getline(is, buf);
        istringstream ssin(buf);
        Polynomial::Values val{};
        ssin >> val.coef;
        int j = 0;
        while ((ssin >> val.deg[j]) and (j < len)) {
            j++;
        }
        v.add(val.coef, val.deg);
    }
    return is;
}

ostream &operator<<(ostream &os, const Polynomial &v) {
    if (v.data[0].coef < 0) {
        os << '-' << v.data[0];
    } else if ((v.data[0].deg[0] == 0) and (v.data[0].coef == 0)) {
        os << '0';
    } else {
        os << v.data[0];
    }

    for (int i = 1; i < v.kol; ++i) {
        if (v.data[i].coef < 0) {
            os << "- " << v.data[i];
        } else if (v.data[i].coef > 0) {
            os << "+ " << v.data[i];
        } else {
            continue;
        }
    }
    return os;
}

Polynomial operator*(const Polynomial &p1, const Polynomial &p2) {
    Polynomial result;
    for (int i = 0; i < p1.kol; ++i) {
        for (int j = 0; j < p2.kol; ++j) {
            int dat[len];
            for (int k = 0; k < len; ++k) {
                dat[k] = p1.data[i].deg[k] + p2.data[j].deg[k];
            }
            double coe = p1.data[i].coef * p2.data[j].coef;
            result.add(coe, dat);
        }
    }
    return result;
}

void Polynomial::diff(const int times, const int var) {
    for (int i = 0; i < times; ++i) {
        for (int j = 0; j < kol; ++j) {
            if (this->data[j].coef == 0) {
                continue;
            }
            if (this->data[j].deg[var] == 0) {
                this->data[j].coef = 0;
            } else {
                this->data[j].coef *= this->data[j].deg[var];
                this->data[j].deg[var]--;
            }
        }
    }

}

Polynomial &Polynomial::operator=(const Polynomial &pol) {
    if (*this == pol) {
        return *this;
    }
    delete[] this->data;
    this->kol = pol.kol;
    this->data = new Values[pol.kol];
    for (int i = 0; i < pol.kol; ++i) {
        this->data[i] = pol.data[i];
    }
    return *this;
}

bool operator==(const Polynomial &pol1, const Polynomial &pol2) {
    if (pol1.kol != pol2.kol) {
        return false;
    }
    for (int i = 0; i < pol1.kol; ++i) {
        if (not(pol1.data[i] == pol2.data[i])) {
            return false;
        }
    }
    return true;
}

void Polynomial::collector() {
    for (int i = 0; i < kol - 1; ++i) {
        for (int j = i + 1; j < kol; ++j) {
            if (data[i] == data[j]) {
                data[i].coef += data[j].coef;
                data[j].coef = 0;
            }
        }
    }
}

Polynomial *create_add(Polynomial *pol, int &quantity) {
    auto pol_n = new Polynomial;
    cin >> *pol_n;
    pol_n->collector();
    Polynomial pol_c[quantity];
    for (int i = 0; i < quantity; ++i) {
        pol_c[i] = pol[i];
    }
    if (quantity != 0) {
        delete[] pol;
    }
    quantity++;
    pol = new Polynomial[quantity];
    for (int i = 0; i < quantity - 1; ++i) {
        pol[i] = pol_c[i];
    }
    pol[quantity - 1] = *pol_n;
    return pol;
}

Polynomial *del_help(Polynomial *pol, int &quantity, const int &ind) {
    Polynomial pol_c[quantity];
    for (int i = 0; i < quantity; ++i) {
        pol_c[i] = pol[i];
    }
    if (quantity != 0) {
        delete[] pol;
    }
    quantity--;
    pol = new Polynomial[quantity];
    for (int i = 0; i < ind; ++i) {
        pol[i] = pol_c[i];
    }
    for(int i = ind+1; i < quantity+1; ++i) {
        pol[i - 1] = pol_c[i];
    }
    return pol;
}