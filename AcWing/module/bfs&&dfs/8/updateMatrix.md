## 542. 01 Matrix
[这里](https://leetcode.com/problems/01-matrix/)
给一个矩阵，对矩阵的每一个点，查找最近的0的距离。

**Example 1:**
```
Input:
0 0 0
0 1 0
0 0 0

Output:
0 0 0
0 1 0
0 0 0
```
**Example 2:**
```
Input:
0 0 0
0 1 0
1 1 1

Output:
0 0 0
0 1 0
1 2 1
Explanation:中间的2是因为‘2’的距离才能找到最近的‘0’
```

## hints
```
    4方向dfs + st[]标记已访问(并且恢复现场)
1.‘0’本身不需要改变，只有‘1’的才需要去找最近的0
2.某个位置‘1’寻找0的时候，不要改变源matrix矩阵，会影响到别的位置上的‘1’找0
    (1).对于'1'的位置，一开始默认给一个最大值距离（因为是找最近）
3.dfs需要标记已经访问过，使用st[]数组标记，由于st[]是共用，所以需要恢复现场。
```
## Solution
``` c
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

void dfs(int** matrix, int row, int col, int** st, int count,int x, int y, int* ret){
    if(*ret < count) return;

    if(matrix[x][y] == 0 && *ret > count ){
        *ret = count;
    }

    st[x][y] = 1;

    int dx[4] = {-1,0,1,0};
    int dy[4] = {0,1,0,-1};

    for(int i = 0;i<4;++i)
    {
        int a = x + dx[i];
        int b = y + dy[i];
        if(a>= 0 && a<row && b>=0 && b<col && !st[a][b]){
            dfs(matrix, row, col, st, count+1, a, b, ret);
        }
    }
    st[x][y] = 0; //st[]恢复现场
}

int** updateMatrix(int** matrix, int matrixRowSize, int matrixColSize, int** columnSizes, int* returnSize) {
    if(!matrix){
        *returnSize = 0;
        *columnSizes = NULL;
        return NULL;
    }

    int** ret = (int**)malloc(sizeof(int*) * matrixRowSize);
    int** st = (int**)malloc(sizeof(int*) * matrixRowSize);
    for(int i = 0;i<matrixRowSize;++i){
       ret[i] = (int*)malloc(sizeof(int) * matrixColSize);
       st[i] = (int*)malloc(sizeof(int) * matrixColSize);
    }


    for(int i = 0;i<matrixRowSize;++i){
        for(int j = 0;j<matrixColSize;++j){
            st[i][j] = 0;
            ret[i][j] = 0;
        }
    }



    for(int i = 0;i<matrixRowSize;++i){
        for(int j = 0;j<matrixColSize;++j){
            if(matrix[i][j] != 0){
                ret[i][j] = matrixRowSize+matrixColSize;  // 假定的最大值距离
                dfs(matrix,matrixRowSize,matrixColSize,st,0,i,j,&ret[i][j]);
            }
        }
    }

    *columnSizes = (int*)malloc(sizeof(int) * matrixRowSize);
    for(int i = 0;i<matrixRowSize;++i){
       (*columnSizes)[i] = matrixColSize;
        free(st[i]);
    }

    *returnSize = matrixRowSize;
    free(st);
    return ret;
}
```