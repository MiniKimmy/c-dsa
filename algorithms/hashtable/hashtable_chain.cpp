// 散列表(拉链法)
#include <cstring>
using namespace std;

const int N = 1e5; // 取决于数据量.没有额外浪费
int h[N], e[N], ne[N], idx;

// 初始化, 默认链表尾结点都是-1
int init()(
    memset(h, -1, sizeof h); 
)

// 添加一个元素x
void insert(int x)
{
    int k = (x % N + N) % N;
    e[idx] = x;
    ne[idx] = h[k];
    h[k] = idx ++;    
}

// 查询是否有元素x
bool query(int x)
{
    int k = (x % N + N) % N;
    for (int i = h[k]; ~i; i = ne[i]) 
        if (e[i] == x) return true;

    return false;
}