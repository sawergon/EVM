#include "iostream"
#include "string"

using namespace std;


int main() {
    int county_len;
    cin >> county_len;
    int cmoney[200000];
    for (int i = 0; i < county_len; ++i) {
        cin >> cmoney[i];
    }
    int cedu[200000];
    for (int i = 0; i < county_len; ++i) {
        cin >> cedu[i];
    }
    int cparent[200000];
    for (int i = 0; i < county_len; ++i) {
        cin >> cparent[i];
    }
    int class_mates;
    cin >> class_mates;
    int mmoney[200000];
    for (int i = 0; i < class_mates; ++i) {
        cin >> mmoney[i];
    }
    int medu[200000];
    for (int i = 0; i < class_mates; ++i) {
        cin >> medu[i];
    }
    int mparent[200000];
    for (int i = 0; i < class_mates; ++i) {
        cin >> mparent[i];
        int country = 0;
        for (int j = 0; j < county_len; ++j) {
            ((*(cedu + j) - *(medu+i) <= 0) && (*(mmoney + i) >= *(cmoney+ j)) ||
                (*(cparent + j)) && (*(mparent+ i) == j + 1))? {country = j + 1; break;}: 
        }
        cout << country << ' ';
    }
}