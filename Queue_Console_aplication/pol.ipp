#include "string"

using namespace std;

class Pol {
public:
    struct Coef {
        string name;
        double *deg = nullptr;
        double coef = 0;
    };
    Coef *data;
    int len;
private:
    Pol() {
        len = 0;
        data = nullptr;
    };

    void print();

    void add(string name, double *deg, double coef);

    ~Pol();
};

Pol::~Pol() {
    for (auto elem: data) {
        delete elem
    }
}

void Pol::add(string name, double *deg, double coef) {
    if (not data) {
        data = new Coef;
        data[0].name = name;
        data[0].coef = coef;
        data[0].deg = deg;
        len++;
    } else{
        Coef copy_data[len];
        for (int i = 0; i < len; ++i) {
            copy_data[i] = data[i];
        }
        delete data[];
        data = new Coef[len + 1];
        for (int i = 0; i < len; ++i) {

        }
    }
}
