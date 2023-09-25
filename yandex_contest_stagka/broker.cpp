#include "iostream"

using namespace std;

int min(const int* arr, int len, int from = 0) {
    int t = arr[from], ind = from;
    for (int i = from; i < len; ++i) {
        if (arr[i] < t) {
            t = arr[i];
            ind = i;
        }
    }
    return ind;
}

int max(const int* arr, int len, int from = 0) {
    int t = arr[from], ind = from;
    for (int i = from; i < len; ++i) {
        if (arr[i] > t) {
            t = arr[i];
            ind = i;
        }
    }
    return ind;
}

int main() {
    int k;
    cin >> k;
    int *ac = new int[k];
    for (int i = 0; i < k; ++i) {
        cin >> ac[i];
    }
    int first = min(ac, k);
    int second = max(ac, k, first);
    int third = min(ac, k, second);
    int fourth = max(ac, k, third);
    cout << first << second << endl;
    cout << third << fourth << endl;
    delete [] ac;
}