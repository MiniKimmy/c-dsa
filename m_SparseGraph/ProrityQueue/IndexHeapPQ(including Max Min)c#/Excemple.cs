using System;
using System.ComponentModel;

namespace m_pq
{
    class Myclass_Test : IComparable<Myclass_Test>
    {
        int age;
        string name;

        public Myclass_Test(string name = null, int age = 0)
        {
            this.age = age;
            this.name = name;
        }

        public int CompareTo(Myclass_Test other)
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

    [Description("索引堆IndexHeapExcemple")]
    class Excemple02
    {
        static void Main(string[] args)
        {
            IndexPriorityQueue<Myclass_Test> Q = new IndexPriorityQueue<Myclass_Test>(IndexPQType.IndexMinPQ);
            Q.Insert(new Myclass_Test("aaa", 8));
            //Q.Insert(new Myclass_Test("aaa", 9));
            Q.Insert(new Myclass_Test("aaa", 10));
            Q.Insert(new Myclass_Test("aaa", 12));
            Q.Insert(new Myclass_Test("aaa", 9));
            Console.WriteLine(Q);

            Console.WriteLine("---delete\n");
            Q.Delete();

            Console.WriteLine(Q);

        }
    }
}
