namespace Graph
{
    public struct Reb
    {
        public int Left, Right;
    }

    public class Graph
    {
        private const int MaxSize = 100;

        // Класс графа на массиве связанных списков
        private readonly LinkedList<int>[] _data;
        private int _len;

        public Graph(int quantity)
        {
            _data = new LinkedList<int>[MaxSize];
            _len = quantity;
            for (int i = 0; i < _len; i++)
            {
                _data[i] = new LinkedList<int>();
            }
        }

        public void AddLink(int i, int j)
        {
            if (!_data[i].Contains(j))
            {
                _data[i].Add(j);
            }
        }

        public bool IsLinked(int i, int j)
        {
            return _data[i].Contains(j);
        }

        public void AddVertex()
        {
            if (_len + 1 <= MaxSize)
            {
                _data[_len++] = new LinkedList<int>();
            }
        }

        public LinkedList<LinkedList<int>> FindAllWays(int vn, int vk)
        {
            var result = new LinkedList<LinkedList<int>>();
            var M = new int [_len];
            for (var i = 0; i < _len; ++i) M[i] = 0;
            int ks = 0, L = 0, len_min = -1;
            var St = new Stack();
            St.Push(vn);
            while (ks >= 0)
            {
                var v = St.Top();
                var Pr = 0;
                int j;
                for (j = L; j < _len; j++)
                {
                    if (!_data[v].Contains(j)) continue;
                    if (j == vk)
                    {
                        St.Push(vk);
                        var helpSt = new Stack();
                        var list = new LinkedList<int>();
                        while (!St.IsEmpty())
                        {
                            var el = St.Pop();
                            list.Add(el);
                            helpSt.Push(el);
                        }

                        while (!helpSt.IsEmpty())
                        {
                            St.Push(helpSt.Pop());
                        }

                        result.Add(list);
                        if (len_min > St.Size() || len_min == -1) len_min = St.Size();
                        St.Pop();
                    }
                    else
                    {
                        if (M[j] == 0)
                        {
                            Pr = 1;
                            break;
                        }
                    }
                }

                if (Pr == 1)
                {
                    ks += 1;
                    St.Push(j);
                    L = 0;
                    M[j] = 1;
                }
                else
                {
                    L = v + 1;
                    M[v] = 0;
                    ks -= 1;
                    St.Pop();
                }
            }

            return result;
        }

        private bool IsInclude(LinkedList<int> list, Reb reb)
        {
            var findLeftSide = false;
            foreach (var elem in list)
            {
                if (elem == reb.Left) findLeftSide = true;
                else if (findLeftSide) return elem == reb.Right;
            }

            return false;
        }
        
        public LinkedList<LinkedList<int>> FindPaths(Reb reb1, Reb reb2, int vn, int vk)
        {
            var tmp = FindAllWays(vn, vk);
            int maxLen = -1, sz = tmp.Count;
            var answer = new LinkedList<LinkedList<int>>();
            foreach (var way in tmp)
            {
                if (IsInclude(way, reb1) && IsInclude(way, reb2))
                {
                    maxLen = way.Count;
                }
            }

            foreach (var way in tmp)
            {
                if (IsInclude(way, reb1) && IsInclude(way, reb2) && way.Count == maxLen)
                {
                    answer.Add(way);
                }
            }

            return answer;
        }
    }
}