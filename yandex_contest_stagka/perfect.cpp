#include "iostream"

using namespace std;

void qsortRecursive(long long int *mas1, int *mas2, int size);

int main() {
    int k;
    long long int time, ideal;
    cin >> k >> ideal >> time;
    auto*sc = new long long int[k];
    int *sc_ind = new int[k];
    for (int i = 0; i < k; ++i) {
        cin >> sc[i];
        sc[i] = abs(sc[i] - ideal);
        sc_ind[i] = i + 1;
    }
    qsortRecursive(sc, sc_ind, k);
    long long int s = 0;
    int i = 0;
    for (int l = 0; l < k; ++l) {
        s += sc[i];
        if (s > time) {
            break;
        } else { i++;}
    }
    cout << i << endl;
    for (int j = i - 1; j >= 0; --j) {
        cout << sc_ind[j] << ' ';
    }
    delete [] sc;
    delete [] sc_ind;
}

void qsortRecursive(long long int *mas1, int *mas2, int size) {
    //Указатели в начало и в конец массива
    int i = 0;
    int j = size - 1;

    //Центральный элемент массива
    long long int mid = mas1[size / 2];

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
            long long int tmp1 = mas1[i];
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