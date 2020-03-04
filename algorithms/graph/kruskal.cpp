// kruskal算法
#include <algorithm>
using namespace std;

const int N = 510;      // 取决于点的数量
const int M = 1e6 + 10; // 取决于边的数量
int n, m;               // n : 点的总数量, m : 边的总数量

struct Edge {
    int a, b, w;

    bool operator< (const Edge &other) const {
        return w < other.w;
    }
}edge[M];
int p[N]; // union-find

// 并查集-路径压缩
int find(int x) 
{
    return x == p[x] ? x : p[x] = find(p[x]);
}

// 初始化并查集. 编号从1开始要根据题目.
void init()
{
    for (int i = 1; i <= n; i ++ ) p[i] = i;
}

void kruskal()
{
    init();
    sort(edge, edge + m); // 快排 O(mlogm)

    int sum = 0; // 累计最小生成树所有边的权重.
    int cnt = 0; // 记录已添加到集合的点的数量.
    for(int i = 0; i < m; i ++) // 遍历所有边
    {
        Edge e = edge[i];
        int a = find(e.a), b = find(e.b);

        if(a != b)
        {
            p[a] = b;
            cnt ++;
            sum += e.w;
        }
    }

    // 具体题目逻辑..

}