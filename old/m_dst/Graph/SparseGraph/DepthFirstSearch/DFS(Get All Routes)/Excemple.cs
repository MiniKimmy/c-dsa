using System;

namespace dfs
{
    class Program
    {
        static void Main(string[] args)
        {
            string xmlPath = @"C:\Users\ؼ���������\Desktop\vs\C\dfs\dfs\GraphData.xml";
            DFS D = new DFS(xmlPath, 0);

            //��ȡ����"5"��·��
            foreach (var item in D.GetRoute(5))
            {
                Console.WriteLine(item);
            }
            Console.ReadKey();
        }
    }
}
