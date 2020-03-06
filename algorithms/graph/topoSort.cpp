// 拓扑排序
#include <iostream>
#include <cstring>
using namespace std;

const int N = 1e6;          // 取决于点的数量
const int M = 1e5;          // 取决于边的数量
int h[N], e[M], ne[M], idx; // 若是稀疏图， 邻接表
int d[N];                   // 入度
int n, m;                   // n : 总点数量, m : 总边数量

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void topoSort()
{
    int q[M];           // 数组模拟队列, 也可以用stl的queue
    int hh = 0, tt = -1;

    // 将所有入度为0的入队
    for (int i = 1; i <= n; i ++)
        if (!d[i]) q[++ tt] = i;

    while (hh <= tt)
    {
        int t = q[hh ++];
        
        for (int i = h[t]; ~i; i = ne[i])
        {
            int j = e[i];
            d[j] --;
            if (!d[j]) q[++ tt] = j;
        }
    }

    // 具体题目逻辑 ..
    if (tt < n - 1) return; // 不存在拓扑序
    // for (int i = 0; i < n; i ++) printf("%d ", q[i]);  // 拓扑序
}

// 测试&&调用
int main(){
    cin >> n >> m;

    memset(h, -1, sizeof h); // 初始化邻接表
    while(m --)
    {
        int a, b;
        cin >> a >> b;
        add(a, b);           // 必须是有向图
        d[b] ++;     
    }

    topoSort();
    return 0;
}