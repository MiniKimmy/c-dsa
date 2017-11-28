namespace Sort_csharp
{
    public partial class Sort
    {
        private static void Exch<T>(T[] a, int i, int j)
        {
            var temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }
    
}
