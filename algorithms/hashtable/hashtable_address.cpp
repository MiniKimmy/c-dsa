// 哈希表 | 散列表(开放寻址法)
#include <cstring>
using namespace std;

// N : 取决于数据量, 需要开2~3倍额外空间
// M : 大于N的最小质数
// null : 在值域外的值, 表示不存在
const int N = 2e6， M = 200003, null = 0x3f3f3f3f;
int h[M];

// 初始化单链表
int init()
(
    memset(h, 0x3f, sizeof h); 
)

// 查询是否有元素x, 有则返回对应h[]的下标
int find(int x)
{
    int k = (x % N + N) % N;
    while(h[k] != null && h[k] != x) 
    {
        k ++;
        if (k >= N) k = 0; // 到达边界重新0开始
    }

    return k;
}

// 查询是否有元素x
bool query(int x)
{
    if(h[find(x)] != null) return true;
    else return false;
}

// 插入一个元素x
void insert(int x)
{
    h[find(x)] = x;
}