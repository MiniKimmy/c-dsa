// 快排
using namespace std;

void quickSort(int q[], int l, int r){
    if (l >= r) return;

    int x = q[l + r >> 1], i = l - 1, j = r + 1; // 若取q[l]或q[r]为分界点的话, 在升序序列会降为O(n²)
    while(i < j) {
        while(q[ ++ i] < x);
        while(q[ -- j] > x);
        if (i < j) swap(q[i], q[j]);
    }

    quickSort(q, l, j);
    quickSort(q, j + 1, r);
}