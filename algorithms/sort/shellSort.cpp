// 希尔排序
using namespace std;

void shellSort(int q[], int n){
    int h = 1;
    while (h < n / 3) h = 3 * h + 1;

    while (h >= 1)
    {
        for (int i = h; i < n; i++) {
            int pos = i, val = q[i];
            for (int j = i - h; j >= h - 1 && q[j] > val; j -= h) {
                pos = j;
                q[j + h] = q[j];
            }
            
            if (pos != i) q[pos] = val;
        }

        h /= 3;
    }
}

/* 对比插入排序
void insertSort(int q[], int n){
    for(int i = 1; i < n; i ++){
        int pos = i, val = q[i];
        for(int j = i - 1; j >= 0 && q[j] > val; j --) {
            q[j + 1] = q[j];
            pos = j;
        }

        if (pos != i) q[pos] = val;
    }
}
*/ 