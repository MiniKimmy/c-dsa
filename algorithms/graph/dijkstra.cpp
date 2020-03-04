// dijkstra(朴素版)
// 最短路问题不用考虑自环情况
#include <cstring>
#include <iostream>
using namespace std;

const int N = 510; // 取决于点的数量
int g[N][N];       // 若是稠密图, 邻接矩阵
bool st[N];        // 记录哪个点已确定好.
int d[N];          // d[i]表示 1 -> i 的距离
int n, m;          // n ： 点总数量, m ： 边总数量

void dijkstra()
{   
    memset(d, 0x3f, sizeof d);
    d[1] = 0;  // d[起点] = 0, 其余初始化正无穷, 一开始已经确定d[1] = 0

    for (int i = 1; i < n; i ++ ) // 总共n个点, 遍历n-1次, 每次可以确定一个点的最短距离.
    {
        // 找到不在集合当中的距离最短的点 O(n)
        int t = -1;
        for (int j = 1; j <= n; j ++ )
            if(!st[j] && (t == -1 || d[t] > d[j]))
                t = j;

        st[t] = true;

        // 用这个点更新所有出边 O(n)
        for (int j = 1; j <= n; j ++ )
            d[j] = min(d[j], d[t] + g[t][j]);
    }

    // 具体题目逻辑..

}

// 测试&&调用
int main(){
    cin >> n >> m;

    memset(g, 0x3f, sizeof g);      // 若存在重边.
    while(m --)
    {
        int a, b, w;
        cin >> a >> b >> w;
        g[a][b] = min(g[a][b], w); // 自环不受影响, 重边就只保留最短的那条边即可.
    }

    dijkstra();

    return 0;
}