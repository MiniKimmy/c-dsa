#include <vector>
using namespace std;
const int N = 1e6 + 10; // 取决于数据量

int h[N], sz;   // 堆

// 下沉
void down(int t)
{
    int u = t;
    if(t + t <= sz && h[t + t] < a[u]) u = t + t;
    if(t + t + 1 <= sz && h[t + t + 1] < a[u]) u = t + t + 1;
    if(u != t)
    {
        swap(a[u], a[t]);
        down(u);
    }
}

// 堆排序
vector<int> heapSort(int q[], int n){
    vector<res> res;
    sz = n;

    for(int i = 0; i < n; i ++) h[i + 1] = q[i];
    for(int i = i / 2; i >= 1; i --) down(i);

    for(int i = 0; i < n; i ++)
    {
        res.push_back(h[i]);
        h[1] = h[sz --];
        down(1);
    }

    return res;
}