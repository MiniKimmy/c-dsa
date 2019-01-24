## 23. 矩阵中的路径
[这里](https://www.acwing.com/problem/content/21/)
请设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有字符的路径。
路径可以从矩阵中的任意一个格子开始，每一步可以在矩阵中向左，向右，向上，向下移动一个格子。
如果一条路径经过了矩阵中的某一个格子，则之后不能再次进入这个格子。

**Note:**
* 输入的路径不为空；
* 所有出现的字符均为大写英文字母；

**Example :**
```
matrix=
[
  ["A","B","C","E"],
  ["S","F","C","S"],
  ["A","D","E","E"]
]

Input:"BCCE"
Output:true

Input:"ASAE"
Output:false
```

## hints
```
    1.使用枚举全部点，每一个点都进入递归
    2.4个方向递归的思想
        * 上右下左
            int dx[4] = {-1,0,1,0};
            int dy[4] = {0,1,0,-1};
            * 这个是习惯的方向，不一定按这个。
            * 记忆方式:2个数组有4个值,同样用"上右下左"的方式，x控制上下方向，y控制左右方向
            * 上下即代表行，行-1就是往上，行+1就是往下。x不控制左右，所以左右是0
            * 同理，左右表示列，以数组(i,j)某一点作为起点就能很快想到。
            * 最后，使用for来控制4个方向，恰好枚举i=0~3的下标对应的坐标点是“上右下左”
            * 注:我们的方向键↑→↓←。联想记忆
        * 假如当前坐标 x,y
        for(int i = 0;i<4;++i){
            往上/下: int a = x + dx[i];
            往左/右: int b = y + dy[i];
            4个方向:(a,b) = [0上]{x-1,y},[1右]{x,y+1},[2下]{x+1,y},[3左]{x,y-1}
            * i=0~3代表4个方向
        * 可以避免去写4个if情况（枚举4个方向）而使用2个数组来表示4个方向
    3.紧接着是处理边界来继续dfs
    4.这种dfs是非错的时候，继续dfs。（含返回值的dfs）
```
## Solution
``` c
int getLen(char* str){
    int len = 0;
    while(str[len]){
        len++;
    }
    return len;
}

bool dfs(char** matrix, int rows, int cols, char* str,int index, int len, int x, int y){
    if(matrix[x][y] != str[index]) return false;
    if(index == len-1) return true;

    char t = matrix[x][y];
    matrix[x][y] = '*';
    int dx[4] = {-1,0,1,0};
    int dy[4] = {0,1,0,-1};
    for(int i = 0;i<4;++i){
        int a = x + dx[i];
        int b = y + dy[i];
        if(a >= 0 && a<rows && b>=0 && b<cols){
            if(dfs(matrix, rows, cols, str, index+1, len, a, b)) return true;
        }
    }
    matrix[x][y] = t;
    return false;
}

bool hasPath(char** matrix, int rows, int cols, char* str) {
    int len = getLen(str);
    //printf("%d--len",len);
    for(int i = 0;i<rows;++i){
        for(int j = 0;j<cols;++j){
            if(dfs(matrix, rows, cols, str, 0, len, i, j))
                return true;
        }
    }

    return false;
}
```