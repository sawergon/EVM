//
// Created by Alex on 15.02.2023.
//

#ifndef QUEUE_CONSOLE_APLICATION_HELP_AND_COMMANDS_H
#define QUEUE_CONSOLE_APLICATION_HELP_AND_COMMANDS_H

#include <string>

using namespace std;

enum Types {Int, Float, String, None};

const string STypes[] = {"Int", "Float", "String"};

enum Commands {close, help, add, pop, create, show, table, load, change, none};

const string SCommands[] = {"close", "help", "add", "pop", "create", "show", "table", "load", "change"};

const string HelpText[] = {"���������� ������ ����������.",
                     "������� ���������� ����������. ���� ��������:\nhelp <command>\n�� ������� ��������� � �������",
                     "���������� ��������� � �������. ���� ��������\nadd <��� �������> <��1> [<��1>]\n�� ������� � ������� n ��������� � �����������",
                     "��������� �������� �� �������. ���� ��������:\npop <��� �������>\n�� ������� ������� � ������������ �����������",
                     "�������� ������ �������. ���� ��������:\ncreate <��� �������>\n�� ��������� ������ �������. ����� ��������� �������� show.",
                     "�������������� ���������� �������� �� �������. ���� ��������:\nshow <���1> [<���2> ...]\n�� ��������� n ��������, ������ � ����� ������",
                     "��������� ������������� ���� ��������. ���� ��������:\ntable\n�� ��������� ������� ���� ��������",
                     "�������� ������������������ ������ �� �����. ���� ��������:\nload <��� �����>\n�� ���������� ��� ������� �� �����.\n������� ������� ���������� �� �������",
                     "����� ���� ��������. ���� ��������:\nchange <��� ����>\n�� �������� ��� � ����������� ��������"};

Commands get_com_f_s(const string &com);

Types get_type_f_s(const string &com);

void print_Readme();

void what(const string &com);

#endif //QUEUE_CONSOLE_APLICATION_HELP_AND_COMMANDS_H
