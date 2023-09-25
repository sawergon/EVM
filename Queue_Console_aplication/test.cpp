#include "iostream"

using namespace std;

int count_eq(const char x[]) {
    int result = 1;
    for (int i = 0; x[i] != '\0'; ++i) {
        int res = 1;
        for (; (x[i] == x[i + 1]) and (x[i] != '\0'); ++i) {
            res++;
        }
        if (res > result) {
            result = res;
        }
    }
    return result;
}


const int Size = 100;

void input(int x[Size][Size], int &m, int &n) {
    cin >> m >> n;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> x[i][j];
        }
    }
}

int main() {
    int num_max = 1, res = 1, cur_max = 1, col;
    char str[Size];
    cout << "введите колво строк" << endl;
    cin >> col;
    while (cur_max < col + 1) {
        int res_cur = 1;
        gets(str);
        res_cur = count_eq(str);
        if (res_cur > res) {
            res = res_cur;
            num_max = cur_max;
        }
        cur_max++;
    }
    cout << "макс колво повт симв равно = " << res << endl;
    cout << "в строке под номером = " << num_max << endl;
}























//#include "iostream"
//#include "pr_queue.ipp"
//#include "list_d.ipp"
//
//using namespace std;
//
//int main() {
//    List_d<ElQueue<int>> a;
//
//    a.add;
//    cout << a.pop() << endl;
//}
