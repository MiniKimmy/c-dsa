using System;

namespace bfs1
{
    class Program
    {
        static void Main(string[] args)
        {
            string file = @"C:\Users\Ø¼Ïã²ÝÂêçù¶â\Desktop\vs\C\bfs1\bfs1\Data.xml";
            BFS bfs = new BFS(file, 0);

            var k = bfs.GetPath(5);
            Console.Write("0->5 : ");
            foreach (var item in k)
            {
                Console.Write(item + " ");
            }
            Console.WriteLine();

            k = bfs.GetPath(4);
            Console.Write("0->4 : ");
            foreach (var item in k)
            {
                Console.Write(item + " ");
            }
            Console.WriteLine();

            k = bfs.GetPath(3);
            Console.Write("0->3 : ");
            foreach (var item in k)
            {
                Console.Write(item + " ");
            }
            Console.WriteLine();

            k = bfs.GetPath(2);
            Console.Write("0->2 : ");
            foreach (var item in k)
            {
                Console.Write(item + " ");
            }
            Console.WriteLine();

            k = bfs.GetPath(1);
            Console.Write("0->1 : ");
            foreach (var item in k)
            {
                Console.Write(item + " ");
            }
            Console.WriteLine();

            Console.ReadKey();
        }
    }
}
