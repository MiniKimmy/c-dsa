## 130. Surrounded Regions
[这里](https://leetcode.com/problems/surrounded-regions/)

## hints
```
    1.将4条边界的‘O’找到，从4条边界的点切入dfs遍历
    2.从边界切入的按4个方向去让附近的‘O’都变成‘Y’
    3.然后现在有3种字母‘X'、'Y'、'O'，遍历矩形一遍
        (1).将'O'全部变成‘X’
        (2).将'Y'全部变成‘O’
```
## Solution
``` c
void dfs(char** board, int row, int col, int x, int y)
{
    board[x][y] = 'Y';

    int dx[4] = {-1,0,1,0};
    int dy[4] = {0,1,0,-1};
    for(int i = 0;i<4;++i)
    {
        int a = x + dx[i];
        int b = y + dy[i];

        if(a>=0 && a<row && b>=0 && b<col && board[a][b] == 'O'){
            dfs(board,row,col,a,b);
        }
    }
}

void solve(char** board, int boardRowSize, int boardColSize) {

    // 左右两个边界
    for(int i = 0;i<boardRowSize;++i)
    {
        if(board[i][0] == 'O') dfs(board,boardRowSize,boardColSize,i,0);
        if(board[i][boardColSize-1] == 'O') dfs(board,boardRowSize,boardColSize,i,boardColSize-1);
    }

    // 上下两个边界
    for(int i = 0;i<boardColSize;++i)
    {
        if(board[0][i] == 'O') dfs(board,boardRowSize,boardColSize,0,i);
        if(board[boardRowSize-1][i] == 'O') dfs(board,boardRowSize,boardColSize,boardRowSize-1,i);
    }

    // 遍历整个矩形一遍
    for(int i = 0;i<boardRowSize;++i)
    {
        for(int j = 0;j<boardColSize;++j)
        {
            if(board[i][j] == 'O'){
                board[i][j] = 'X';
            }

            if(board[i][j] == 'Y'){
                board[i][j] = 'O';
            }
        }
    }
}
```

## Solution
``` csharp
public class Solution {
    public void Solve(char[,] board) {
        int n = board.GetLength(0);
        int m = board.GetLength(1);

        for(int i = 0;i<n;++i)
        {
            if(board[i,0] == 'O') dfs(board,i,0);
            if(board[i,m-1] == 'O') dfs(board,i,m-1);
        }


        for(int i = 0;i<m;++i)
        {
            if(board[0,i] == 'O') dfs(board,0,i);
            if(board[n-1,i] == 'O') dfs(board,n-1,i);
        }

        for(int i = 0;i<n;++i){
            for(int j = 0; j<m;++j)
            {
                if(board[i,j] == 'O'){
                    board[i,j] = 'X';
                }

                else if(board[i,j] == 'Y'){
                    board[i,j] = 'O';
                }
            }
        }
    }

    void dfs(char[,] board, int x, int y)
    {
        int n = board.GetLength(0); int m = board.GetLength(1);
        board[x,y] = 'Y';
        int[] dx = {-1,0,1,0}; int[] dy = {0,1,0,-1};
        for(int i = 0;i<4;++i){
            int a = x + dx[i];
            int b = y + dy[i];
            if(a >= 0 && a<n && b>=0 && b<m && board[a,b] == 'O'){
                dfs(board,a,b);
            }
        }
    }
}
```