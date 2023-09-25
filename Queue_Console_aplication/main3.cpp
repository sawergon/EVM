#include "iostream"
#include "sstream"
#include "Polynomial.h"

using namespace std;

enum codes {create, multiply, print, diff, del, end_work};

int main() {
    cout << "Begin work" << endl;
    Polynomial *pol = nullptr;
    int quantity = 0;
    bool run = true;
    while (run) {
        cout << "chose menu item" << endl;
        cout << "1. create polynomial" << endl;
        cout << "2. multiply polynomials" << endl;
        cout << "3. print polynomial" << endl;
        cout << "4. differentiate polynomial" << endl;
        cout << "5. delete polynomial" << endl;
        cout << "6. exit" << endl;
        cout << '$';
        int code;
        cin >> code;
        switch (code-1) {
            case end_work:
                run = false;
                break;
            case create: {
                pol = create_add(pol, quantity);
                break;
            }
            case multiply: {
                cout << "what polynomials do you want to multiply" << endl;
                for (int i = 0; i < quantity; ++i) {
                    cout << i + 1 << ". " << pol[i] << endl;
                }
                string  buf;
                cin.ignore(100, '\n');
                getline(cin, buf);
                istringstream ssin(buf);
                int next, prev;
                ssin >> prev >> next;
                Polynomial p = pol[prev - 1] * pol[next - 1];
                while (ssin >> next) {
                    p = p * pol[next - 1];
                }
                p.collector();
                cout << p << endl;
                cout << "do you want to save result? y/n" << endl;
                char answer;
                cin >> answer;
                if (answer == 'y') {
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
                    pol[quantity - 1] = p;
                }
                break;
            }
            case print: {
                for (int i = 0; i < quantity; ++i) {
                    cout << i+1 << ". " << pol[i] << endl;
                }
                break;
            }
            case diff: {
                cout << "what polynomials do you want to differentiate?" << endl;
                for (int i = 0; i < quantity; ++i) {
                    cout << i + 1 << ". " << pol[i] << endl;
                }
                cout << "write <number of the polynomial> <times> <number of variable>" << endl;
                string  buf;
                cin.ignore(100, '\n');
                getline(cin, buf);
                istringstream ssin(buf);
                int element, times, var;
                while (ssin >> element >> times >> var) {
                    pol[element - 1].diff(times, var - 1);
                    pol[element - 1].collector();
                    cout << pol[element - 1] << endl;
                }
                break;
            }
            case del: {
                cout << "enter number of the polynomial you want to delete" << endl;
                int num;
                cin >> num;
                num--;
                pol = del_help(pol, quantity, num);
                break;
            }
            default:
                cout << "error" << endl;
                run = false;
        }
    }
    system("pause");
}