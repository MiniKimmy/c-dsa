// bellman-ford算法
#include <cstring>
using namespace std;
const int N = 510; // 取决于点的数量
const int M = 1e6; // 取决于边的数量
const int INF = 0x3f3f3f3f; 

struct Edge {
    int a, b, w;
}edge[M];

int d[N], backup[N]; // d[i] : 1->i的距离

// k : 最多走k条边
void bellman_ford(int k)
{
    memset(d, 0x3f, sizeof d);
    for (int i = 0; i < k; i ++ )
    {
        memcpy(backup, d, sizeof d);
        for (int j = 0; j < m; j ++ )  // 遍历所有边
        {
            Edge e = edge[j];
            int a = e.a, b = e.b, w = e.w;
            d[b] = min(d[b], backup[a] + w); 
        }
    }

    // 具体题目逻辑..
    // 注 d[i] 可能会被无穷大更新. 判断不存在需要 if (d[i] >= INF / 2) printf("INF")
}