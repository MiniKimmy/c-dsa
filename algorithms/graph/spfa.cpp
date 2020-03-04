// spfa算法
// 注:spfa算法不会用距离是正无穷的点来更新其他点，但bellman-ford算法会
#include <cstring>
using namespace std;

const int N = 1e6 + 10;            // 取决于点的数量
int h[N], ne[N], e[N], w[N], idx;  // 邻接表, 若是稀疏图
int d[N];                          // d[i] : 1->i 的距离
bool st[N];                        // st[i] : 队列中是否含有i，基于bellman-ford 中三角不等式 dist[b] = min(dist[b], dist[a] + w[a->b]), 存储所有能被更新点b

void spfa()
{
    memset(d, 0x3f, sizeof d);
    d[1] = 0;

    int q[N];
    int hh = 0, tt = 0;  // 队列
    q[tt] = 1;
    st[1] = true;
    
    while(hh <= tt)
    {
        int t = q[hh ++];
        st[t] = false;

        for(int i = h[t]; ~i; i = ne[i])
        {
            int j = e[i];
            if(d[j] > d[t] + w[i])
            {
                d[j] = d[t] + w[i];
                if (!st[j]) {     // 若当前点能被更新 && 不在队列中.
                    q[++ tt] = j;
                    st[j] = true;
                }
            }
        }
    }

    // 具体题目逻辑..
}