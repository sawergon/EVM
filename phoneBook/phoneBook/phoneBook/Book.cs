namespace phoneBook
{
    public class Person
    {
        private string name, surName, secondName;
        private int phone;

        public string Name
        {
            get { return name; }
            set { name = value; }
        }

        public string SurName
        {
            get { return surName; }
            set { surName = value; }
        }

        public string SecondName
        {
            get { return secondName; }
            set { secondName = value; }
        }

        public int Phone
        {
            get { return phone; }
            set { phone = value; }
        }

        public Person(string name, string surname, string secondName, int phone)
        {
            this.name = name;
            surName = surname;
            this.secondName = secondName;
            this.phone = phone;
        }

        public void display()
        {
            Console.WriteLine(name + " " + surName + " " + secondName + " " + phone);
        }
    }

    public class Book
    {
        private Person[] data;
        private int capacity, len;

        public Book(Person newPerson)
        {
            capacity = len = 1;
            data = new Person [capacity];
            data[0] = newPerson;
        }

        public void addNewPerson(Person newPerson)
        {
            if (len >= capacity)
            {
                capacity *= 2;
                Person [] newData = new Person[len];
                for (int i = 0; i < len; ++i)
                {
                    newData[i] = data[i];
                }

                data = new Person [capacity];
                for (int i = 0; i < len; i++)
                {
                    data[i] = newData[i];
                }
            }
            data[len++] = newPerson;
        }

        public void display()
        {
            for (int i = 0; i < capacity; ++i)
            {
                data[i].display();
            }
        }
    }
}