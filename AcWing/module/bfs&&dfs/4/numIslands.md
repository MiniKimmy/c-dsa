## 200. Number of Islands
[这里](https://leetcode.com/problems/number-of-islands/)
1表示连通的区域，数一下有多少个区域连通

**Example 1:**
```
Input:
11110
11010
11000
00000

Output: 1
```
**Example 2:**
```
Input:
11000
11000
00100
00011

Output: 3
```
## hints
```
    4方向dfs+暴搜
    1.把连通区域里的'1'减少到剩余1个‘1’
    2.最后遍历矩形，数有多少个1就代表有多少个连通区域
```

## Solution
``` c
void dfs(char** grid, int row, int col, int x, int y)
{
    int dx[4] = {-1,0,1,0};
    int dy[4] = {0,1,0,-1};

    for(int i = 0;i<4;++i){
        int a = x + dx[i];
        int b = y + dy[i];
        if(a>=0 && a<row&& b>=0 && b<col && grid[a][b] == '1'){
            grid[a][b] = '0';
            dfs(grid,row,col,a,b);
        }
    }
}

int numIslands(char** grid, int gridRowSize, int gridColSize) {
    int ret = 0;
    for(int i = 0;i<gridRowSize;++i)
    {
        for(int j = 0;j<gridColSize;++j)
        {
            if(grid[i][j] == '1'){
                ret++;
                dfs(grid, gridRowSize, gridColSize,i,j);
            }
        }
    }

    return ret;
}

/* 使用'*'特殊符号保留连通区域里的1个‘1’，最后再恢复现场
  for(int i = 0;i<gridRowSize;++i)
    {
        for(int j = 0;j<gridColSize;++j)
        {
            if(grid[i][j] == '1'){
                int t = grid[i][j];
                grid[i][j] = '*';
                dfs(grid, gridRowSize, gridColSize,i,j);
                grid[i][j] = t;
            }
        }
    }

    int ret = 0;
    for(int i = 0;i<gridRowSize;++i)
    {
        for(int j = 0;j<gridColSize;++j)
        {
            if(grid[i][j] == '1'){
                ret++;
            }
        }
    }
    return ret;

 */
```

## Solution
``` csharp
public class Solution {
    public int NumIslands(char[,] grid) {
        int ret = 0;
        int n = grid.GetLength(0); int m = grid.GetLength(1);
        for(int i = 0;i<n;++i){
            for(int j = 0;j<m;++j)
            {
                if(grid[i,j] == '1'){
                    ret++;
                    dfs(grid,i,j);
                }
            }
        }

        return ret;
    }

    void dfs(char[,] grid, int x, int y)
    {
        grid[x,y] = '0';
        int n = grid.GetLength(0);
        int m = grid.GetLength(1);
        int[] dx = {-1,0,1,0}; int[] dy = {0,1,0,-1};
        for(int i = 0;i<4;++i)
        {
            int a = x + dx[i];
            int b = y + dy[i];
            if(a>=0 && a<n && b>=0 && b < m && grid[a,b] == '1'){
                dfs(grid,a,b);
            }
        }
    }
}
```