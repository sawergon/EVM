#include "iostream"
#include "sstream"
#include "pr_queue.ipp"
#include "clocale"

using namespace std;

enum codes {add, pop, print, end_work};

int main() {
    setlocale(LC_ALL, "rus");
    cout << "������ ������" << endl;
    bool run = true;
    Pr_queue<int> queue;
    while (run) {
        cout << "�������� ����� ����" << endl;
        cout << "1. �������� ������� � �������" << endl;
        cout << "2. ������ ������� �� �������" << endl;
        cout << "3. ������� �������" << endl;
        cout << "4. �����" << endl;
        cout << '$';
        int code;
        cin >> code;
        switch (code-1) {
            case end_work:
                run = false;
                break;
            case add: {
                cout << "������� �������� <data> <pr> ����� ������" << endl;
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
                    cout << "������� �����" << endl;
                } else {
                    cout << queue.pop() << endl;
                }
                break;
            }
            case print: {
                cout << "1. � �����������" << endl;
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