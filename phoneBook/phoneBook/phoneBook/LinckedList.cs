namespace phoneBook;
using System.Collections;
using System.Collections.Generic;

public class Node<T>
{
    public Node(T data)
    {
        Data = data;
    }
    public T Data { get; set; }
    public Node<T>? Next { get; set; }
}


public class LinkedList<T> : IEnumerable<T>  // односвязный список
{
    private Node<T>? _head; // головной/первый элемент
    private Node<T>? _tail; // последний/хвостовой элемент

    // добавление элемента
    public void Add(T data)
    {
        Node<T> node = new Node<T>(data);
 
        if (_head == null)
            _head = node;
        else
            _tail!.Next = node;
        _tail = node;
 
        Count++;
    }
    // удаление элемента
    public bool Remove(T data)
    {
        var current = _head;
        Node<T>? previous = null;
 
        while (current != null && current.Data != null)
        {
            if (current.Data.Equals(data))
            {
                // Если узел в середине или в конце
                if (previous != null)
                {
                    // убираем узел current, теперь previous ссылается не на current, а на current.Next
                    previous.Next = current.Next;
 
                    // Если current.Next не установлен, значит узел последний,
                    // изменяем переменную tail
                    if (current.Next == null)
                        _tail = previous;
                }
                else
                {
                    // если удаляется первый элемент
                    // переустанавливаем значение head
                    _head = _head?.Next;
 
                    // если после удаления список пуст, сбрасываем tail
                    if (_head == null)
                        _tail = null;
                }
                Count--;
                return true;
            }
 
            previous = current;
            current = current.Next;
        }
        return false;
    }
 
    public int Count { get; private set; }

    public bool IsEmpty => Count == 0;

    // очистка списка
    public void Clear()
    {
        _head = null;
        _tail = null;
        Count = 0;
    }
    // содержит ли список элемент
    public bool Contains(T data)
    {
        var current = _head;
        while (current != null && current.Data !=null)
        {
            if (current.Data.Equals(data)) return true;
            current = current.Next;
        }
        return false;
    }
    // добвление в начало
    public void AppendFirst(T data)
    {
        var node = new Node<T>(data)
        {
            Next = _head
        };
        _head = node;
        if (Count == 0)
            _tail = _head;
        Count++;
    }
 
    IEnumerator<T> IEnumerable<T>.GetEnumerator()
    {
        var current = _head;
        while (current != null)
        {
            yield return current.Data;
            current = current.Next;
        }
    }
 
    // реализация интерфейса IEnumerable
    IEnumerator IEnumerable.GetEnumerator()
    {
        return ((IEnumerable<T>)this).GetEnumerator();
    }
}