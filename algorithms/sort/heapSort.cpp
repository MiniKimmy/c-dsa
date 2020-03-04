// 堆排序
#include <vector>
using namespace std;

const int N = 1e6 + 10; // 取决于数据量

int h[N], sz;   // 堆, sz是堆的元素个数. 下标从1开始

// 下沉
void down(int t)
{
    int u = t;
    if(t + t <= sz && h[t + t] < h[u]) u = t + t;
    if(t + t + 1 <= sz && h[t + t + 1] < h[u]) u = t + t + 1;
    if(u != t)
    {
        swap(h[u], h[t]);
        down(u);
    }
}

vector<int> heapSort(int q[], int n){
    vector<int> res;
    sz = n;

    for (int i = 0; i < n; i ++ ) h[i + 1] = q[i];
    for (int i = i / 2; i >= 1; i -- ) down(i);

    for (int i = 0; i < n; i ++){
        res.push_back(h[1]);
        h[1] = h[sz --];
        down(1);
    }

    return res;
}