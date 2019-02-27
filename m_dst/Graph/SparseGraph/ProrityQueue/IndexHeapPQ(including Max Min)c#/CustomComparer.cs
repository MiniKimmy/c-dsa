using System.Collections.Generic;

namespace m_pq
{
    /// <summary>
    /// �Զ���Ƚ���
    /// </summary>
    static class CustomComparer
    {
        public static int? Compare<T>(T first, T second, IComparer<T> comparer = null)
        {
            if(comparer == null)
            {
                comparer = Comparer<T>.Default;
            }

            int ret = comparer.Compare(first, second);
            return ret == 0 ? new int?() : ret;
        }

        public static int? ReferenceComparer<T>(T first, T second)
            where T : class
        {
            return first == second ? 0
                 : first == null ? -1
                 : second == null ? 1
                 : new int?();
        }

        //------------------ģ������Comparerд�����Equal(�ڶ��������ʱ����Ҫ��Equal)------------------

        public static bool? Equals<T>(T first, T second, IEqualityComparer<T> comparer = null)
        {
            if (comparer == null)
            {
                comparer = EqualityComparer<T>.Default;
            }

            bool ret = comparer.Equals(first, second);
            return ret == true ? new bool?() : ret;
        }

        public static bool? ReferenceEquals<T>(T first, T second)
           where T : class
        {
            return first == second ? true
                  : first == null ? false
                  : second == null ? false
                  : new bool?();
        }
    }
}
