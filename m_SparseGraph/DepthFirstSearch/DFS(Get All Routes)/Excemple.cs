using System;

namespace dfs
{
    class Program
    {
        static void Main(string[] args)
        {
            string xmlPath = @"C:\Users\丶香草玛琦垛\Desktop\vs\C\dfs\dfs\GraphData.xml";
            DFS D = new DFS(xmlPath, 0);

            //获取到达"5"的路线
            foreach (var item in D.GetRoute(5))
            {
                Console.WriteLine(item);
            }
            Console.ReadKey();
        }
    }
}
