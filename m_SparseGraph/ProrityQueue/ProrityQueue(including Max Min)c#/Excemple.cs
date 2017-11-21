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
                CustomComparer.Compare(other.name, this.name) ?? //名字越靠近A 越拍前面
                CustomComparer.Compare(this.age, other.age) ?? 0;
        }

        public override string ToString()
        {
            return String.Format("Name = {0}, Age = {1}", this.name, this.age);
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            PriorityQueue<Myclass> Q = new PriorityQueue<Myclass>(PriorityQueueType.MaxPQ);
            Console.WriteLine(Q.GetSize());
            Q.Insert(new Myclass("Mike", 10));
            Q.Insert(new Myclass("Aikk", 12));
            Q.Insert(new Myclass("Mike", 1));            
            Q.Insert(new Myclass("Aikk", 15));
            Q.Insert(new Myclass("Mike", 19));
            Q.Insert(new Myclass("Mike", 6));
            Q.Insert(new Myclass("Mike", 8));
            Q.Insert(new Myclass("Aikk", 8));
            Q.Traverse();
            Console.WriteLine(Q.GetSize());
            Console.WriteLine("-----delete--------");
            Q.Delete();
            Q.Traverse();
            Console.WriteLine(Q.GetSize());
            Console.WriteLine("-----delete--------");
            Q.Delete();
            Q.Traverse();
            Console.WriteLine(Q.GetSize());
            Console.WriteLine("-----delete--------");
            Q.Delete();
            Q.Traverse();
            Console.WriteLine(Q.GetSize());
            Console.WriteLine("-----delete--------");
            Q.Delete();
            Q.Traverse();
            Console.WriteLine(Q.GetSize());
            Console.ReadKey();
        }
    }
}
