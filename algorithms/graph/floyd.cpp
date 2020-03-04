// floyd算法
using namespace std;
const int N = 210, INF = 0x3f3f3f3f;
int d[N][N];  // 邻接矩阵

void floyd()
{
    for (int k = 1; k <= n; k ++ )
        for(int i = 1; i <= n; i ++ )
            for(int j = 1; j <= m; j ++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][k]); 
}

// a->a 初始化为0, a->b 初始化为INF
void init(){
    for (int i = 0; i < N; i ++ )
        for (int j = 0; j < N; j ++ )
            if (i == j) d[i][j] = 0;
            else d[i][j] = INF;
}