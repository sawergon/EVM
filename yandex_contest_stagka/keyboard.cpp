#include "iostream"
#include "vector"
#include "algorithm"

using namespace std;

bool sr(const int &ch1, const int &ch2, const int *keyboard, const int &len_keyboard,
        const int *keyboard_ind);

void qsortRecursive(int *mas1, int *mas2, int size);

int bs(const int *arr, int key, int len) {
    bool flag = false;
    int l = 0; // левая граница
    int r = len; // правая граница
    int mid;

    while ((l <= r) && !flag) {
        mid = (l + r) / 2; // считываем срединный индекс отрезка [l,r]

        if (arr[mid] == key) flag = true; //проверяем ключ со серединным элементом
        if (arr[mid] > key) r = mid - 1; // проверяем, какую часть нужно отбросить
        else l = mid + 1;
    }
    if (flag) {
        return mid;
    }
    return -1;
}

int main() {
    int len_keyboard;
    cin >> len_keyboard;
//    vector<int> keyboard(len_keyboard);
//    vector<int> keyboard_ind(len_keyboard);
    int *keyboard = new int[len_keyboard];
    int *keyboard_ind = new int[len_keyboard];
    for (int i = 0; i < len_keyboard; ++i) {
        cin >> keyboard[i];
    }
    for (int i = 0; i < len_keyboard; ++i) {
        cin >> keyboard_ind[i];
    }
    int len_text;
    cin >> len_text;
    int text1, text2;
    cin >> text1;
    int answer = 0;
    qsortRecursive(keyboard, keyboard_ind, len_keyboard);
    for (int i = 1; i < len_text; ++i) {
        cin >> text2;
        if (sr(text1, text2, keyboard, len_keyboard, keyboard_ind)) {
            answer++;
        }
        text1 = text2;
    }
    cout << answer;
}

bool sr(const int &ch1, const int &ch2, const int *keyboard, const int &len_keyboard,
        const int *keyboard_ind) {
    int ind_1 = -1, ind_2 = -1;
//    for (int i = 0; (ind_1 == -1) || (ind_2 == -1); ++i) {
//        if (keyboard[i] == ch1) {
//            ind_1 = keyboard_ind[i];
//        }
//        if (keyboard[i] == ch2) {
//            ind_2 = keyboard_ind[i];
//        }
//    }
    ind_1 = keyboard_ind[bs(keyboard, ch1, len_keyboard)];
    ind_2 = keyboard_ind[bs(keyboard, ch2, len_keyboard)];
    if ((ind_1 == -1) || (ind_2 == -1)) {
        return false;
    }
    if (ind_2 != ind_1) {
        return true;
    }
    return false;
}

void qsortRecursive(int *mas1, int *mas2, int size) {
    //Указатели в начало и в конец массива
    int i = 0;
    int j = size - 1;

    //Центральный элемент массива
    int mid = mas1[size / 2];

    //Делим массив
    do {
        //Пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
        //В левой части массива пропускаем(оставляем на месте) элементы, которые меньше центрального
        while (mas1[i] < mid) {
            i++;
        }
        //В правой части пропускаем элементы, которые больше центрального
        while (mas1[j] > mid) {
            j--;
        }

        //Меняем элементы местами
        if (i <= j) {
            int tmp1 = mas1[i];
            int tmp2 = mas2[i];
            mas1[i] = mas1[j];
            mas2[i] = mas2[j];
            mas1[j] = tmp1;
            mas2[j] = tmp2;

            i++;
            j--;
        }
    } while (i <= j);


    //Рекурсивные вызовы, если осталось, что сортировать
    if (j > 0) {
        //"Левый кусок"
        qsortRecursive(mas1, mas2, j + 1);
    }
    if (i < size) {
        //"Првый кусок"
        qsortRecursive(&mas1[i], &mas2[i], size - i);
    }
}