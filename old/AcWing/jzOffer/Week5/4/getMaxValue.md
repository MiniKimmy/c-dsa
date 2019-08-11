## 60. 礼物的最大价值
[这里](https://www.acwing.com/problem/content/56/)

在一个m×n的棋盘的每一格都放有一个礼物，每个礼物都有一定的价值（价值大于0）。
你可以从棋盘的左上角开始拿格子里的礼物，并每次向右或者向下移动一格直到到达棋盘的右下角。
给定一个棋盘及其上面的礼物，请计算你最多能拿到多少价值的礼物？

**Note**
* m,n>0

**Example :**
```
Input:
[
  [2,3,1],
  [1,7,1],
  [4,6,1]
]
Output:19
Explanation:沿着路径 2→3→7→6→1 可以得到拿到最大价值礼物。
```
## hints
```
1.dp[0] = 0 默认从[1]开始，由于是二维矩阵，所以初始添加一行一列的0
    ex:
    0 0 0 0
    0 2 3 1
    0 1 7 1
    0 4 6 1
2.每次以正方形的形式遍历
    dp过程:
    0 0 0  0
    0 2 5  0
    0 3 12 0
    0 0 0  0
3.f[i][j] 状态转换 = “斜左上角的点” + max(←，↑)
    ex:
    f[1,1] = grid[0,0] + max(f[1,0],f[0,1]);
4.最后返回最右下角的f[n,m]即可
```

## Solution
``` c
int max(int a,int b){
    if(a>b) return a;
    return b;
}

int dp(int** grid,int** f,int n, int m){
    for(int i = 1;i<n+1;++i){
        for(int j = 1;j<m+1;++j){
            f[i][j] = grid[i-1][j-1] + max(f[i-1][j],f[i][j-1]);
        }
    }

    return f[n][m];
}

int getMaxValue(int** grid, int gridRowSize, int gridColSize) {
    if(!grid) return 0;

    int** f = (int**)malloc(sizeof(int*) * (gridRowSize+1));
    for(int i = 0;i<gridRowSize+1;++i){
        f[i] = (int*)malloc(sizeof(int) * (gridColSize+1));
    }

    for(int i = 0;i<gridRowSize + 1;++i) {
        for(int j = 0;j<gridColSize + 1;++j) {
            f[i][j] = 0;
        }
    }

    return dp(grid,f,gridRowSize,gridColSize);
}

/* TLE
void dfs(int** grid, int row, int col, int x, int y, int sum, int* ret) {
    if(x == row-1 && y==col-1 && *ret < sum){
        *ret = sum;
        return;
    }

    // → ↓
    int dx[2] = {0,1};
    int dy[2] = {1,0};

    for(int i = 0;i<2;++i){
        int a = x + dx[i];
        int b = y + dy[i];

        if(a>=0 && a<row && b>=0 && b<col){
            //printf("[%d][%d]=%d,sum=%d-next=%d\n",a,b,grid[a][b],sum,sum+grid[a][b]);
            dfs(grid,row,col,a,b,sum + grid[a][b], ret);
        }
    }
}

int getMaxValue(int** grid, int gridRowSize, int gridColSize) {
    int refRet = 0;
    dfs(grid,gridRowSize,gridColSize,0,0,grid[0][0],&refRet);
    return refRet;
}
*/
```