// dijkstra(堆优化版)
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
typedef pair<int, int> PII;

const int N = 1e6 + 10;           // 取决于点的数量
int h[N], ne[N], e[N], w[N], idx; // 若是稀疏图
bool st[N];                       // 记录哪个点已确定好.
int d[N];                         // d[i]表示 1 -> i 的距离

void dijkstra()
{
    memset(d, 0x3f, sizeof d);
    d[1] = 0;

    priority_queue<PII, vector<PII>, greater<PII>> heap; // 小根堆<编号, 距离>
    heap.push({0, 1});

    while(heap.size())
    {
        auto t = heap.top();
        heap.pop();

        int ver = t.second, distance = t.first;

        if(st[ver]) continue;

        for (int i = h[ver]; ~i; i = ne[i] )
        {
            int j = e[i];
            if (d[j] > distance + w[i])
            {
                d[j] = distance + w[i];
                heap.push({d[j], j});
            }
        }

        st[ver] = true;
    }

    // 具体题目逻辑..

}