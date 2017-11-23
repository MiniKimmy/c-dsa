using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace dfs1
{
    class Program
    {
        static void Main(string[] args)
        {
            string filename = @"C:\Users\Ø¼Ïã²ÝÂêçù¶â\Desktop\vs\C\dfs1\dfs1\Data.xml";
            DFS D = new DFS(filename, 0);

            Console.WriteLine(D.GetPath(0));
            Console.WriteLine(D.GetPath(1));
            Console.WriteLine(D.GetPath(2));
            Console.WriteLine(D.GetPath(3));
            Console.WriteLine(D.GetPath(4));
            Console.WriteLine(D.GetPath(5));
            Console.ReadKey();
        }
    }
}
