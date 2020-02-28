// 并查集(size优化)
using namespace std;
const int N = 1e6 + 10  // 取决于数据范围

int p[N], sz[N];

// 初始化, 编号从1开始
void init(int n) 
{ 
    for (int i = 1; i <= n; i ++ ) {
        p[i] = i;
        sz[i] = 1;
    }
}

// 压缩路径
int find(int x) 
{
    return x == p[x] ? x : p[x] = find(x);
}

// 测试&&调用
int main()
{
    int T; cin >> T;

    while(T --) // T组测试
    {
        int a, b;
        cin >> a >> b;

        a = find(a), b = find(b);
        if (a == b) continue;  // 已经在同一个连通分量就不需要再连

        p[a] = b;
        sz[b] += a;
    }
}