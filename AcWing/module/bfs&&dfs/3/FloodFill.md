## 733. Flood Fill
[这里](https://leetcode.com/problems/flood-fill/)
**Example:**
```
Input:
[
    [1 1 1]
    [1 1 0]
    [1 0 1]
]
起点:(sr,sc)=(1,1)
newColor:新的val
Ouput:
[
    [2 2 2]
    [2 2 0]
    [2 0 1]
]
Explanation:从(1,1)开始，把所有附近（4个方向）的1都变成2.
```
## hints
```
    洪水灌溉法.
    1.定义↑→↓←四个方向，4路dfs:dx[4],dy[4]
        * 判断边界
        * 判断是否已经走过
    2.因为返回的矩阵和源矩阵是一模一样的，所以copy一下长宽即可.
```
## Solution
``` c
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
void dfs(int** image, int row, int col, int x, int y, int curColor, int newColor)
{
    image[x][y] = newColor;

    int dx[4] = {-1,0,1,0};int dy[4] = {0,1,0,-1};
    for(int i = 0;i<4;++i)
    {
        int a = x + dx[i];
        int b = y + dy[i];
        if(a>=0 && a<row && b>=0 && b<col && image[a][b] == curColor){
            dfs(image,row,col,a,b,curColor,newColor);
        }
    }
}

int** floodFill(int** image, int imageRowSize, int imageColSize, int sr, int sc, int newColor, int** columnSizes, int* returnSize) {
    if(!image){
        *columnSizes = NULL;
        *returnSize = 0;
        return NULL;
    }

    if(newColor != image[sr][sc]){
        dfs(image,imageRowSize,imageColSize,sr,sc,image[sr][sc],newColor);
    }


    *columnSizes = (int*)malloc(sizeof(int) * imageRowSize);
    for(int i = 0;i<imageRowSize;++i)
    {
        (*columnSizes)[i] = imageColSize;
    }

    *returnSize = imageRowSize;
    return image;
}
```
## hints
```
    1.int[a,b]是c#里的二维数组
    2.获取第几维的长度: GetLength(n)
        * GetLength(0) = a  //[0]表示第一维
        * GetLength(1) = b
    3.属性Length = a * b
    4.赋值arr[x,y] = val;
```
## Solution
``` csharp
public class Solution {
    private void dfs(ref int[,] image, int x, int y, int curColor, int newColor)
    {
        image[x,y] = newColor;
        int[] dx = {-1,0,1,0};
        int[] dy = {0,1,0,-1};
        for(int i = 0;i<4;++i){
            int a = x + dx[i];
            int b = y + dy[i];
            if(a>=0&&a<image.GetLength(0) && b>=0 && b<image.GetLength(1) && image[a,b] == curColor)
            {
                dfs(ref image,a,b,curColor,newColor);
            }
        }
    }

    public int[,] FloodFill(int[,] image, int sr, int sc, int newColor) {
        if(image == null || image[sr,sc] == newColor) return image;
        dfs(ref image,sr,sc,image[sr,sc],newColor);
        return image;
    }
}
```