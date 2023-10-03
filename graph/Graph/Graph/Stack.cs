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