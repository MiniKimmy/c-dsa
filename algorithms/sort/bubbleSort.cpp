// 冒泡排序
using namespace std;

void bubbleSort(int q[], int n){
    for (int i = 0; i < n; i ++ )
        for (int j = i + 1; j < n; j ++ )
            if (q[i] > q[j])
                swap(q[i], q[j]);
}