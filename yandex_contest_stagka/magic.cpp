#include "iostream"
#include "string"


using namespace std;

int alpha_len = 25;
string alphabet = "abcdefghijklmnopqrstuvwxyz";
int err = 97;

int main() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    int* pos = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> pos[i];
    }
    int* delta = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> delta[i];
    }
    int* read = new int[n];
    for (int i = 0; i < n; ++i) {
        read[i] = 0;
    }
    long long int sum = 0;
    for (int i = 0; i < n; ++i) {
        read[i] = 1;
        int b = 1;
        sum += b;
        for (int j = 1; j < k; ++j) {
            if (read[pos[j - 1]] == 0) {
                read[pos[j - 1]] = 1;
                b++;
                sum += b;
            } else {
                char ch = alphabet[(int)s[i] - err + (read[pos[j - 1]] - 1) * delta[j - 1]];
                if (read[s.find(ch)] == 1) {

                }
            }
        }
    }
    delete [] pos;
    delete [] delta;
    delete [] read;
}