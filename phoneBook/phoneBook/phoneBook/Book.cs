using System.ComponentModel.DataAnnotations;

namespace phoneBook;

public class Person
{
    public string Name { get; set; }

    public string SurName { get; set; }

    public string SecondName { get; set; }

    public int Phone { get; set; }

    public Person()
    {
        Name = "";
        SurName = "";
        SecondName = "";
        Phone = 0;
    }

    public Person(string name, string surname, string secondName, int phone)
    {
        Name = name;
        SurName = surname;
        SecondName = secondName;
        Phone = phone;
    }

    public void Display()
    {
        Console.WriteLine(Name + " " + SurName + " " + SecondName + " " + Phone);
    }

    public static bool operator ==(Person a, Person b)
    {
        return a.Name == b.Name && a.SurName == b.SurName && a.SecondName == b.SecondName && a.Phone == b.Phone;
    }

    public static bool operator !=(Person a, Person b)
    {
        return !(a == b);
    }
}

public class Book
{
    private LinkedList<Person> _data;

    public int Len => _data.Count;

    public string Name { get; set; }

    public Book()
    {
        Name = "main";
        _data = new LinkedList<Person>();
    }

    public Book(Person newPerson, string name = "main")
    {
        Name = name;
        _data = new LinkedList<Person>();
    }

    public void AddNewPerson(Person newPerson)
    {
        foreach (var p in _data)
        {
            if (String.Compare(p.Name, newPerson.Name) < 0) 
                continue;
            _data.AddBefore(p, newPerson);
            return;
        }
        _data.Add(newPerson);
    }

    public bool DelPerson(string delName)
    {
        foreach (var p in _data)
        {
            if (p.Name != delName) continue;
            _data.Remove(p);
            return true;
        }

        return false;
    }

    public bool FindPerson(string name, ref LinkedList<Person> p)
    {
        bool res = false;
        foreach (var per in _data)
        {
            if (per.Name != name) continue;
            if (p.Any(pe => per == pe))
            {
                res = true;
            }
            p.Add(per);
            res = true;
        }

        return res;
    }

    public void Display(bool isSub)
    {
        if (isSub)
            Console.Write("\tПодкнига {0}:", Name);
        else
            Console.Write("Книга:");
        if (_data.IsEmpty && isSub)
        {
            Console.Write(" пуста");
        }
        Console.WriteLine();
        var i = 1;
        foreach (var p in _data)
        {
            Console.Write(isSub?"\t\t{0}. ":"\t{0}. ", i++);
            p.Display();
        }
    }
}

public class UnderBook
{
    private LinkedList<UnderBook> _dataBook;
    private Book _dataPerson;

    public int Count => _dataBook.Count + _dataPerson.Len;
    public int CountUnderBook => _dataBook.Count;
    private string Name
    {
        get => _dataPerson.Name;
        set => _dataPerson.Name = value;
    }

    public UnderBook()
    {
        _dataBook = new LinkedList<UnderBook>();
        _dataPerson = new Book();
        Name = "main";
    }

    public void AddSubBook(string b)
    {
        var book = new UnderBook
        {
            Name = b
        };
        foreach (var boo in _dataBook)
        {
            if (String.Compare(boo.Name, b) < 0) continue;
            _dataBook.AddBefore(boo, book);
            return;
        }
        _dataBook.Add(book);
    }

    public void AddNewPerson(Person p)
    {
        _dataPerson.AddNewPerson(p);
    }

    public bool AddPersonToSubBook(Person p, string subBookName = "main")
    {
        foreach (var book in _dataBook)
        {
            if (book.Name != subBookName) continue;
            book.AddNewPerson(p);
            return true;
        }

        return false;
    }

    public bool DelPerson(string p)
    {
        return _dataPerson.DelPerson(p);
    }

    public bool DelPersonFromSubBook(string p, string subBookName)
    {
        return (from book in _dataBook where book.Name == subBookName select book.DelPerson(p)).FirstOrDefault();
    }

    public bool DelSubBook(string delName)
    {
        foreach (var book in _dataBook)
        {
            if (book.Name != delName) continue;
            _dataBook.Remove(book);
            return true;
        }

        return false;
    }

    public bool FindPerson(string name, ref LinkedList<Person> persons)
    {
        bool res = _dataPerson.FindPerson(name, ref persons);
        foreach (var book in _dataBook)
        {
            if (book.FindPerson(name, ref persons)) res = true;
        }

        return res;
    }
    
    public void Display(bool isSub = false)
    {
        if (_dataBook.IsEmpty && _dataPerson.Len == 0 && !isSub)
            Console.WriteLine("Книга пуста");
        else
        {
            _dataPerson.Display(isSub);
            if (_dataBook.Count == 0) return;
            foreach (var book in _dataBook)
            {
                book.Display(true);
            }
        }
    }
}