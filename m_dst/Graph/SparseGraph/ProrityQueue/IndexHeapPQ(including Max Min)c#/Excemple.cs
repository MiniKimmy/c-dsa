using System;

namespace m_pq
{
    class Myclass : IComparable<Myclass>
    {
        int age;
        string name;

        public Myclass(string name = null, int age = 0)
        {
            this.age = age;
            this.name = name;
        }

        public int CompareTo(Myclass other)
        {
            return CustomComparer.ReferenceComparer(this, other) ??
                CustomComparer.Compare(other.name, this.name) ??
                CustomComparer.Compare(this.age, other.age) ?? 0;
        }

        public override string ToString()
        {
            return String.Format("Name = {0}, Age = {1}", this.name, this.age);
        }
    }

    class Excemple
    {
        static void Main(string[] args)
        {
            IndexPriorityQueue<Myclass> Q = new IndexPriorityQueue<Myclass>(IndexPQType.IndexMinPQ);

            Q.Insert(new Myclass("aaa", 8));
            Q.Insert(new Myclass("aaa", 10));
            Q.Insert(new Myclass("aaa", 12));
            Q.Insert(new Myclass("aaa", 9));
            Console.WriteLine(Q);

            Console.WriteLine("---delete--\n");
            Q.Delete();
            Console.WriteLine(Q);
        }
    }
}
