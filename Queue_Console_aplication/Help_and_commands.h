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

const string HelpText[] = {"Завершение работы приложения.",
                     "Выводит поясняющую информацию. Если написать:\nhelp <command>\nТо выведет пояснение к команде",
                     "Добавление элементов в очередь. Если написать\nadd <имя очереди> <зн1> [<пр1>]\nТо добавит в очередь n элементов с приоритетом",
                     "Получение элемента из очереди. Если написать:\npop <имя очереди>\nТо выведет элемент с максимальным приоритетом",
                     "Создание пустой очереди. Если написать:\ncreate <имя очереди>\nТо создастся пустая очередь. Можно проверить командой show.",
                     "Распечатывание нескольких очередей по строкам. Если написать:\nshow <имя1> [<имя2> ...]\nТо выведется n очередей, каждая в своей строке",
                     "Табличное представление всех очередей. Если написать:\ntable\nТо выведется таблица всех очередей",
                     "Загрузка последовательности команд из файла. Если написать:\nload <имя файла>\nТо выполнятся все команды из файла.\nКоманды следует записывать по строчно",
                     "Смена типа очередей. Если написать:\nchange <имя типа>\nТо сменится тип в обработчике очередей"};

Commands get_com_f_s(const string &com);

Types get_type_f_s(const string &com);

void print_Readme();

void what(const string &com);

#endif //QUEUE_CONSOLE_APLICATION_HELP_AND_COMMANDS_H
