// 并查集
#include <iostream>
using namespace std;

const int N = 1e6 + 10;  // 取决于数据范围
int n;                   // n : 编号的总数量
int p[N];

// 初始化, 编号从0 or 1开始, 具体看题目编号是从几开始
void init() 
{ 
    for (int i = 0; i < n; i ++ ) p[i] = i;
}

// 压缩路径
int find(int x) 
{
    return x == p[x] ? x : p[x] = find(p[x]); // 注: 写p[x] = find(x) 会死循环.
}

// 测试&&调用
int main(){
    int T; 
    cin >> n >> T;

    init();
    while(T --) // T组测试
    {
        int a, b;
        cin >> a >> b;

        a = find(a), b = find(b);
        if (a == b) continue;  // 已经在同一个连通分量就不需要再连

        p[a] = b;
    }
}