using System;

namespace phoneBook;

internal enum Codes
{
    Add = 1,
    Del = 2,
    Show = 3,
    Exit = 4
}

class Program
{
    static void Main()
    {
        var book = new UnderBook();
        Console.WriteLine("Начало работы программы");
        var code = "s";
        while (code[0] != '6')
        {
            Console.WriteLine("Меню");
            Console.WriteLine("1. Добавить элемент");
            Console.WriteLine("2. Удалить элемент");
            Console.WriteLine("3. Вывести книгу");
            Console.WriteLine("4. Найти человека");
            Console.WriteLine("5. Удалить подкнигу");
            Console.WriteLine("6. Закончить работу");
            code = Console.ReadLine();
            if (code.Length > 1)
            {
                Console.WriteLine("Повторите ввод");
                continue;
            }
            switch (code[0])
            {
                case '1':
                {
                    Console.WriteLine(
                        "Введите имя подкниги для добавления или оставьте поле пустым для добавления в основную книгу");
                    var subBookName = Console.ReadLine();


                    Console.WriteLine(
                        "Ведите: имя, фамилию, отчество и номер телефона.\n После каждого ввода нажмите Enter");
                    var name = Console.ReadLine();
                    var surname = Console.ReadLine();
                    var secondName = Console.ReadLine();
                    var phone = Convert.ToInt32(Console.ReadLine());
                    var per = new Person(name, surname, secondName, phone);
                    if (subBookName.Length > 0)
                    {
                        if (!book.AddPersonToSubBook(per, subBookName))
                        {
                            book.AddSubBook(subBookName);
                            book.AddPersonToSubBook(per, subBookName);
                        }
                    }
                    else
                    {
                        book.AddNewPerson(per);
                    }

                    break;
                }
                case '2':
                {
                    Console.WriteLine(
                        "Введите имя для удаления");
                    var name = Console.ReadLine();
                    var subBookName = "";
                    if (book.Count > 1)
                    {
                        Console.WriteLine(
                            "Из какой подкниги удалить. Оставьте поле пустым если удалить из книги");
                        subBookName = Console.ReadLine();
                    }

                    if (subBookName.Length > 0)
                    {
                        Console.WriteLine(
                            book.DelPersonFromSubBook(name, subBookName)
                                ? "Успешное удаление"
                                : "Такого человека нет в подкниге. или она не существует");
                    }
                    else
                    {
                        Console.WriteLine(book.DelPerson(name) ? "Успешное удаление" : "Такого человека нет");
                    }

                    break;
                }
                case '3':
                {
                    book.Display();
                    break;
                }
                case '4':
                {
                    Console.WriteLine("Введите имя для поиска");
                    var name = Console.ReadLine();
                    var p = new Person();
                    if (book.FindPerson(name, ref p))
                        p.Display();
                    else
                        Console.WriteLine("Такого человека нет");
                    break;
                }
                case '5':
                {
                    Console.WriteLine("Введите имя подкниги для удаления");
                    var subBookName = Console.ReadLine();
                    Console.WriteLine(book.DelSubBook(subBookName) ? "Успешное удаление" : "Такой подкниги нет");
                    break;
                }
                default:
                {
                    Console.WriteLine(code[0] == '6'?"Завершение работы":"Повторите ввод");
                    break;
                }
            }
        }
    }
}