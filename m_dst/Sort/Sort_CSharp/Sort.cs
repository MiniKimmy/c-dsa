using System;
using System.Linq;

namespace Sort_csharp
{
    public static partial class Sort
    {
        /// <summary>
        /// ð������
        /// </summary>
        public static void BubbleSort<T>(T[] a)
            where T : IComparable<T>
        {
            int N = a.Count();
            for (int i = 0; i < a.Count() - 1; i++)
            {
                for (int j = i + 1; j < a.Count(); j++)
                {
                    if (a[i].CompareTo(a[j]) == 1)
                    {
                        Exch(a, i, j);
                    }
                }
            }
        }

        /// <summary>
        /// ѡ������
        /// </summary>
        public static void SelectSort<T>(T[] a)
            where T : IComparable<T>
        {
            int N = a.Count();
            for (int i = 0; i < N - 1; i++)
            {
                int temp = i;
                for (int j = i + 1; j < N; j++)
                {
                    if (a[i].CompareTo(a[j]) == 1)
                    {
                        temp = j;
                    }
                }
                if (temp != i)
                {
                    Exch(a, i, temp);
                }
            }
        }

        /// <summary>
        /// ��������
        /// </summary>
        public static void InsertSort<T>(T[] a)
            where T : IComparable<T>
        {
            for (int i = 1; i < a.Count() - 1; i++)
            {
                var temp = a[i];
                int j = i - 1;
                for (; j >= 0 && a[j+1].CompareTo(temp) == -1; j--)
                {
                    a[j + 1] = a[j];
                }
                a[j + 1] = temp;                
            }
        }

        /// <summary>
        /// ϣ������
        /// </summary>
        public static void ShellSort<T>(T[] a)
            where T : IComparable<T>
        {
            int N = a.Count();
            int h = 1;
            while (h < N / 3)   h = 3 * h + 1;

            while (h >= 1)
            {
                for (int i = h; i < N; i++)
                {
                    var temp = a[i];
                    int j = i - h;
                    for (; j >= h && a[i].CompareTo(a[j]) == -1; j -= h)
                    {
                        a[j + h] = a[j];
                    }
                    a[j + h] = temp;
                }
                h = h / 3;
            }
        }

        /// <summary>
        /// �鲢���򣨷�װtemp[]��
        /// </summary>
        public static void MergeSort<T>(T[] a)
             where T : IComparable<T>
        {
            int N = a.Count();
            T[] temp = new T[N];
            _MergeSort(a, 0, N - 1, temp);
        }

        /// <summary>
        /// �鲢����
        /// </summary>
        private static void _MergeSort<T>(T[] a,int left,int right,T[] temp)
            where T : IComparable<T>
        {
            if (right <= left) return;

            int mid = left + (right - left) / 2;//�ҵ������е����һ��Ԫ�ص�index
            _MergeSort(a, left, mid, temp);
            _MergeSort(a, mid + 1, right, temp);
            Merge(a, left, right,mid,temp);
        }

        //�鲢
        private static void Merge<T>(T[] a,int left,int right, int mid,T[] temp)
            where T : IComparable<T>
        {
            int i = left;
            int j = mid + 1;

            //Copy����������
            for (int k = left; k < left + (right - left + 1); k++)
            {
                temp[k] = a[k];
            }

            for (int k = left; k < left + (right - left + 1); k++)
            {
                if (i > mid) a[k] = temp[j++];
                else if (j > right) a[k] = temp[i++];
                else if (temp[i].CompareTo(temp[j]) == 1) a[k] = temp[j++];
                else a[k] = temp[i++];
            }
        }

        /// <summary>
        /// ˫·����
        /// </summary>
        public static void QuickSort2Way<T>(T[] a)
            where T : IComparable<T>
        {
            int N = a.Count();
            if (N < 5)
            {
                _QuickSort_InsertSort(a, 0, N - 1);
            }else{
                _QuickSort2Way(a, 0, N - 1);
            }
        }

        /// <summary>
        /// ˫·���ţ����Ż���
        /// </summary>
        private static void _QuickSort2Way<T>(T[] a,int left,int right)
            where T : IComparable<T>
        {
            //����Ԫ�������ò�������
            if (right <= left + 5)              
            {
                _QuickSort_InsertSort(a, left, right);
                return;
            }

            Exch(a, left, (left + right) / 2);      //ÿ�ζ��������[left]Ԫ��
            int j = partion(a, left, right);
            _QuickSort2Way(a, left, j - 1);
            Exch(a, j + 1, (j + 1 + right) / 2);    //ÿ�ζ��������[j+1]Ԫ��
            _QuickSort2Way(a, j + 1, right);
        }

        /// <summary>
        /// �����Ż�--InsertSort
        /// </summary>
        private static void _QuickSort_InsertSort<T>(T[] a, int left, int right)
            where T : IComparable<T>
        {
            if (right <= left) return;
            
            for (int i = left + 1; i <= right; i++)
            {
                var temp = a[i];
                int j = i - 1;
                for (; j >= left && a[j].CompareTo(temp) == 1; j--)
                {
                    a[j + 1] = a[j];
                }
                a[j + 1] = temp;
            }
        }
         
        /// <summary>
        /// �зֺ���
        /// </summary>
        private static int partion<T>(T[] a,int left,int right)
            where T : IComparable<T>
        {
            int j = right + 1;

            for (int i = left + 1; i < j; i++)
            {
                if(a[i].CompareTo(a[left]) >= 0)
                {
                    while (j > i && a[--j].CompareTo(a[left]) >= 0) ;
                    if (i >= j) break;
                    Exch(a, i, j);
                }
            }

            j--;
            Exch(a, left, j);
            return j;
        }

        /// <summary>
        /// ��·����
        /// </summary>
        public static void QuickSort3Way<T>(T[] a)
            where T : IComparable<T>
        {
            int N = a.Count();
            //����Ԫ���ò�������
            if (N < 15){
                _QuickSort_InsertSort(a, 0, N - 1);
            }else{
                _QuickSort3Way(a, 0, N - 1);
            }
        }

        /// <summary>
        /// ��·����
        /// </summary>
        private static void _QuickSort3Way<T>(T[] a, int left, int right)
            where T : IComparable<T>
        {
            if (right <= left) return;

            int i = left;
            int j = left + 1;
            int k = right;
            var temp = a[left];

            while (j <= k)
            {
                int cmp = a[j].CompareTo(temp);
                if(cmp == -1)
                {
                    Exch(a, i++, j++);
                }else if(cmp == 1){
                    Exch(a, j, k--);
                }
                else
                {
                    j++;
                }
            }
            _QuickSort3Way(a, left, i - 1);
            _QuickSort3Way(a, k + 1, right);
        }
    }
}
