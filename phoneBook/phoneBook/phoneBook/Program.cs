using System;

namespace phoneBook
{
    class Program
    {
        static void Main(string[] args)
        {
            Person a = new Person("a", "b", "c", 53);
            Person ab = new Person("ab", "bd", "cf", 55);
            // a.display();
            Book b = new Book(a);
            b.display();
            b.addNewPerson(ab);
            b.display();
        }
    }
}