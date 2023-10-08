using System.Linq;

namespace Graph
{
    public class Reb
    {
        public int Left, Right;
        public bool Marked;

        public Reb(int l, int r)
        {
            Left = l;
            Right = r;
            Marked = false;
        }
    }

    public abstract class GraphMain
    {
        public abstract int Len();

        public abstract bool IsLinked(int i, int j);

        public abstract int NextLinked(int v, int[] M, int L, int vk);

        public LinkedList<LinkedList<int>> FindAllWays(int vn, int vk)
        {
            var result = new LinkedList<LinkedList<int>>();
            var M = new int [Len()];
            for (var i = 0; i < Len(); ++i) M[i] = 0;
            int ks = 0, L = 0, len_min = -1;
            var St = new Stack();
            St.Push(vn);
            M[vn] = 1;
            while (ks >= 0)
            {
                int v = St.Top(), Pr = 0, j = NextLinked(v, M, L, vk);
                for (; j != -1;)
                {
                    if (j == vk)
                    {
                        St.Push(vk);
                        result.Add(St.ToList());
                        if (len_min > St.Size() || len_min == -1) len_min = St.Size();
                        St.Pop();
                    }
                    else
                    {
                        if (M[j] != 0) continue;
                        Pr = 1;
                        break;
                    }

                    j = NextLinked(v, M, j + 1, vk);
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

        public abstract bool IsInclude(LinkedList<int> list, Reb reb);

        public LinkedList<LinkedList<int>> FindPaths(Reb reb1, Reb reb2, int vn, int vk)
        {
            var tmp = FindAllWays(vn, vk);
            int maxLen = -1, sz = tmp.Count;
            var answer = new LinkedList<LinkedList<int>>();
            foreach (var way in tmp)
            {
                // way.Out();
                if (!IsInclude(way, reb1) && !IsInclude(way, reb2) && way.Count > maxLen)
                {
                    maxLen = way.Count;
                }
            }

            foreach (var way in tmp)
            {
                if (!IsInclude(way, reb1) && !IsInclude(way, reb2) && way.Count == maxLen)
                {
                    answer.Add(way);
                }
            }

            return answer;
        }
    }

    public class GraphList : GraphMain
    {
        private const int MaxSize = 100;

        // Класс графа на массиве связанных списков
        private readonly LinkedList<int>[] _data;
        private int _len;

        public override int Len()
        {
            return _len;
        }

        public GraphList(int quantity)
        {
            _data = new LinkedList<int>[MaxSize];
            _len = quantity;
            for (var i = 0; i < _len; i++)
            {
                _data[i] = new LinkedList<int>();
            }
        }

        public LinkedList<Reb> GetEdges()
        {
            var res = new LinkedList<Reb>();
            for (var i = 0; i < _len; i++)
            {
                for (var j = i+1; j < _len; j++)
                {
                    if (_data[i].Contains(j))
                    {
                        res.Add(new Reb(i, j));
                    }
                }
            }

            return res;
        }
        
        public override bool IsInclude(LinkedList<int> list, Reb reb)
        {
            var findLeftSide = false;
            foreach (var elem in list)
            {
                if (elem == reb.Left) findLeftSide = true;
                else if (findLeftSide) return elem == reb.Right;
            }

            return false;
        }

        public LinkedList<Reb> GetEdgesWithWay(LinkedList<int> way)
        {
            var res = GetEdges();
            foreach (var reb in res)
            {
                if (IsInclude(way, reb) || IsInclude(way, new Reb(reb.Right, reb.Left)))
                {
                    reb.Marked = true;
                }
            }

            return res;
        }

        public void AddLink(int i, int j)
        {
            if (!_data[i].Contains(j)) _data[i].Add(j);
            if (!_data[j].Contains(i)) _data[j].Add(i);
        }

        public override bool IsLinked(int i, int j)
        {
            return _data[i].Contains(j);
        }

        public override int NextLinked(int v, int[] M, int L, int vk)
        {
            for (var i = L; i < _len; i++)
            {
                if (_data[v].Contains(i) && (M[i] != 1 || i == vk))
                {
                    return i;
                }
            }

            return -1;
        }

        public void AddVertex()
        {
            if (_len + 1 <= MaxSize)
            {
                _data[_len++] = new LinkedList<int>();
            }
        }
    }
}