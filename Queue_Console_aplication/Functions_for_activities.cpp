#include <windows.h>
#include "Functions_for_activities.h"

void help_error_com(const string &com) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, FOREGROUND_RED);
    cout << "������� -> " << com
         << " �� ����������. �������������� help ����� ���������� ��� �������" << endl;
    SetConsoleTextAttribute(handle, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
}