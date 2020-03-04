// 邻接表-稀疏图
// 使用邻接表不用考虑重边情况
#include <cstring>
#include <iostream>
using namespace std;

const int N = 1e6 + 10;           // 取决于点的数量
int h[N], ne[N], e[N], w[N], idx; // 单链表

// a -> b 连边, 权值为c
void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

// 初始化邻接表
void init()
{
    memset(h, -1, sizeof h);
}

// 调用&&测试
int main(){
    int T; cin >> T;
    init();

    while(T --)
    {
        int a, b, w;
        cin >> a >> b >> w;
        add(a, b, w);
        // add(b, c); 若是无向图则加上这行.
    }
}