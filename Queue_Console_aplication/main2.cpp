#include "iostream"
#include "sstream"
#include "pr_queue.ipp"
#include "clocale"

using namespace std;

enum codes {add, pop, print, end_work};

int main() {
    setlocale(LC_ALL, "rus");
    cout << "Начало работы" << endl;
    bool run = true;
    Pr_queue<int> queue;
    while (run) {
        cout << "выберете пункт меню" << endl;
        cout << "1. добавить элемент в очередь" << endl;
        cout << "2. изъять элемент из очереди" << endl;
        cout << "3. вывести очередь" << endl;
        cout << "4. выход" << endl;
        cout << '$';
        int code;
        cin >> code;
        switch (code-1) {
            case end_work:
                run = false;
                break;
            case add: {
                cout << "введите значения <data> <pr> через пробел" << endl;
                string buf;
                getchar();
                getline(cin, buf);
                istringstream ssin(buf);
                int data, pr;
                while (ssin >> data >> pr) {
                    queue.add(data, pr);
                }
                break;
            }
            case pop: {
                if (queue.empty()) {
                    cout << "очередь пуста" << endl;
                } else {
                    cout << queue.pop() << endl;
                }
                break;
            }
            case print: {
                cout << "1. с приоритетом" << endl;
                cin >> code;
                if (code == 1) {
                    queue.print(true);
                } else {
                        queue.print();
                }
                break;
            }
            default:
                cout << "error" << endl;
                run = false;
        }
    }
    getchar();
}