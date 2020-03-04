// 邻接矩阵-稠密图
#include <iostream>
#include <cstring>
using namespace std;

const int N = 510; // 取决于有多少个点
int g[N][N];       // 二维矩阵

// 调用&&测试
int main(){
    int T; cin >> T;

    memset(g, 0x3f, sizeof g);
    while(T --)
    {
        int a, b, w;
        g[a][b] = min(g[a][b], w); // 若有重边, 就保留最短的边即可.
    }
}