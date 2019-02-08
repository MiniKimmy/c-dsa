## 40. 顺时针打印矩阵
[这里](https://www.acwing.com/problem/content/description/39/)
输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字。

**Example :**
```
Input:
[
  [1, 2, 3, 4],
  [5, 6, 7, 8],
  [9,10,11,12]
]
Output:[1,2,3,4,8,12,11,10,9,5,6,7]
```

## hints
```
    1.修改val，使用一个特殊的值来标记已访问过
    2.dx/dy的↑→↓←，调整为题目的→↓←↑
        (1).再定义一个dir[4] = {1,2,3,0}，
        (2).循环列表是根据本题只需要按同一种顺序枚举.
        (3).使用时候就dx[dir[i]]、dy[dir[i]]，
```

## Solution
``` c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* printMatrix(int** matrix, int matrixRowSize, int matrixColSize) {
    if(matrix == NULL || matrixRowSize<0 || matrixColSize<0) return NULL;

    int n = matrixRowSize * matrixColSize;
    int* ret = (int*)malloc(sizeof(int) * n);
    int index = 0;

    int x = 0;int y = -1;

    // ↑→↓←
    int dx[4] = {-1,0,1,0};
    int dy[4] = {0,1,0,-1};

    int dir[4] = {1,2,3,0}; //→↓←↑
    int k = 0;
    int size = 4; //循环列表

    while(index < n){
        int a = x + dx[dir[k]];
        int b = y + dy[dir[k]];
        if(a<0 || b<0 || a>=matrixRowSize || b>=matrixColSize || matrix[a][b] == 1000000){
            k = (k+1)%4;
        }else{
            ret[index++] = matrix[a][b];
            matrix[a][b] = 1000000;
            x = a; y = b;
        }
    }
    return ret;
}
```