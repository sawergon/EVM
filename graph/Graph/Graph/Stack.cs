using System;

namespace Graph
{
    public class Stack
    {
        private int[] _data;
        private int _len, _capacity;

        public Stack()
        {
            _len = 0;
            _capacity = 1;
            _data = new int[_capacity];
        }

        public LinkedList<int> ToList()
        {
            var a = new LinkedList<int>();
            for (var i = 0; i < _len; i++)
            {
                a.Add(_data[i]);
            }

            return a;
        }

        public void Copy(Stack st)
        {
            while (this._capacity < st._len)
            {
                this._capacity *= 2;
            }

            Array.Resize(ref this._data, this._capacity);
            this._len = st._len;

            for (var i = 0; i < st._len; i++)
            {
                this._data[i] = st._data[i];
            }
        }

        public void Push(int value)
        {
            _data[_len++] = value;
            if (_len < _capacity) return;
            _capacity *= 2;
            Array.Resize(ref _data, _capacity);
        }

        public bool IsEmpty()
        {
            return _len == 0;
        }

        public int Size()
        {
            return _len;
        }

        public int Pop()
        {
            return _data[--_len];
        }

        public int Top()
        {
            return _data[_len - 1];
        }
    }
}