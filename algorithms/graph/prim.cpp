// prim算法
// 最小生成树定义不能有环, 正负权都可以, d[]是存储所有点离集合的最短距离(起码2个点以上, 没有起点的概念)
#include <cstring>
using namespace std;

const int N = 510;  // 取决于点的数量
int g[N][N];        // 若是稠密图, 邻接矩阵
int d[N];           // d[i]  : 点i到集合的距离(点i与集合相连的所有边中最小的边, 定义为i到集合的距离)
bool st[N];         // st[i] : 记录i是否已添加到集合

void prim()
{
    memset(d, 0x3f, sizeof d);

    int sum = 0; // 累加最小生成树集合中所有边的权重.
    for (int i = 0; i < n; i ++ )
    {
        // 在集合外, 找到离集合最近的点t O(n)
        int t = -1;
        for (int j = 1; j <= n; j ++)
            if (!st[j] && (t == -1 || d[t] > d[j]))
                t = j;
        
        // 不是第1个点 && t与集合没有连边
        if(i && d[t] == INF) return;
        
        // 不是第1个点才累加
        if(i) sum += d[t];

        // 更新t所有出边 O(n)
        for (int j = 1; j <= n; j ++ )
            d[j] = min(d[j], g[t][j]);
        
        // 标记t已添加到集合
        st[t] = true;
    }

    // 具体题目逻辑 ..

}