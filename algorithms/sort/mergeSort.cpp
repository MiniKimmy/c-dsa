// 归并排序
using namespace std;

const int N = 1e6; // 取决于数据量

void mergeSort(int q[], int l, int r){
    if (l >= r) return;

    int mid = l + r >> 1;
    mergeSort(q, l, mid);
    mergeSort(q, mid + 1, r);

    int i = l, j = mid + 1, k = 0;
    int tmp[N];

    while(i <= mid && j <= r) {
        if (q[i] < q[j]) tmp[k ++] = q[i ++];
        else tmp[k ++] = q[j ++];
    }

    while(i <= mid) tmp[k ++] = q[i ++];
    while(j <= r) tmp[k ++] = q[j ++];

    for(int i = l, j = 0; j < k; i ++, j ++) q[i] = tmp[j];
}