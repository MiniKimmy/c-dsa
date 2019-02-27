using System;

namespace Sort_csharp
{
    class Program
    {
        static void Main(string[] args)
        {
            int[] a = { 9, 8, 10, 6, 10, -1, 12,3 ,0,4,1,5,6,7,-1,-1,5,1,2,3,2,1,-1,9,7,10};

            foreach (var item in a)
            {
                Console.Write(item + " ");
            }

            Console.WriteLine("\n-----------BubbleSort------------");
            Sort.BubbleSort<int>(a);
            foreach (var item in a)
            {
                Console.Write(item + " ");
            }

            Console.WriteLine("\n-----------SelectSort------------");
            Sort.SelectSort<int>(a);
            foreach (var item in a)
            {
                Console.Write(item + " ");
            }

            Console.WriteLine("\n-----------InsertSort------------");
            Sort.InsertSort<int>(a);
            foreach (var item in a)
            {
                Console.Write(item + " ");
            }

            Console.WriteLine("\n-----------ShellSort------------");
            Sort.ShellSort<int>(a);
            foreach (var item in a)
            {
                Console.Write(item + " ");
            }

            Console.WriteLine("\n-----------MergeSort------------");
            Sort.MergeSort<int>(a);
            foreach (var item in a)
            {
                Console.Write(item + " ");
            }

            Console.WriteLine("\n-----------QuickSort2Way------------");
            Sort.QuickSort2Way<int>(a);
            foreach (var item in a)
            {
                Console.Write(item + " ");
            }

            Console.WriteLine("\n-----------QuickSort3Way------------");
            Sort.QuickSort3Way<int>(a);
            foreach (var item in a)
            {
                Console.Write(item + " ");
            }

            Console.WriteLine();
            Console.ReadKey();
        }
    }
}
