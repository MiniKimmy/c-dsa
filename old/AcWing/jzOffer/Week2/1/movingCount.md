## 24. 机器人的运动范围
[这里](https://www.acwing.com/problem/content/22/)
地上有一个 m 行和 n 列的方格，横纵坐标范围分别是 0~m−1 和 0~n−1。
一个机器人从坐标0,0的格子开始移动，每一次只能向左，右，上，下四个方向移动一格。
但是不能进入行坐标和列坐标的数位之和大于k的格子。
请问该机器人能够达到多少个格子？

**Example 1**
```
Input:k=7, m=4, n=5
Output:20
```
**Example 2**
```
Input:k=18, m=40, n=40
Output:1484
Explanation:当k为18时，机器人能够进入方格（35,37），
因为3+5+3+7 = 18。但是，它不能进入方格（35,38），因为3+5+3+8 = 19。
```

**Note:**
* 0<=m<=50
* 0<=n<=50
* 0<=k<=100

## hints
```
    1.4方向bfs（这与4方向dfs是一样的道理）
        (1).如果数据量较大时候，bfs可以避免dfs爆栈
        (2).1秒能遍历1E个点，所以几千几w对于bfs来说是小case了
        (3).dfs爆栈主要看这个运行程序的限制了
    2.记录行踪
        在入队的时候就记录
    3.记录每个位的和就mod一个个拿出来div逐嘅消掉个位
```

## Solution
``` c
typedef struct Point{
    int x;
    int y;
}Point;

/// new一个点(x,y)
Point* createPoint(int x,int y){
    Point* ret = (Point*)malloc(sizeof(Point));
    ret->x = x;
    ret->y = y;
    return ret;
}

/// 数字n的各个位相加
int getEachBit(int n){
    int ret = 0;
    while(n>0){
        ret += n%10;
        n=n/10;
    }
    return ret;
}

int movingCount(int threshold, int rows, int cols){
    // 开始，简单安全判断
    if(rows<=0 || cols<=0) return 0;
    if(threshold >= ((rows-1) * (cols-1)) ) return rows*cols;

    // 标志位矩阵初始化
    int** matrix = (int**)malloc(sizeof(int*) * rows);
    for(int i = 0;i<rows;++i){
        matrix[i] = (int*)malloc(sizeof(int) * cols);
    }

    for(int i = 0;i<rows;++i){
        for(int j = 0;j<cols;++j){
            matrix[i][j] = 0;
        }
    }

    // 队列初始化
    int size = 1000;
    Point** queue = (Point**)malloc(sizeof(Point*) * size);
    int front = 0;
    int rear = 0;
    queue[rear] = createPoint(0,0);
    rear = (rear+1)%size;

    // 局部变量初始化
    int ret = 0;
    int dx[4] = {-1,0,1,0};
    int dy[4] = {0,1,0,-1};
    matrix[0][0] = 1;
    while(front != rear)
    {
        Point* p = queue[front];
        front = (front + 1)%size;

        //4个方向bfs
        for(int i = 0;i<4;++i){
            int a = p->x + dx[i];
            int b = p->y + dy[i];
            if(a>=0 && a< rows && b>=0 && b<cols && matrix[a][b] == 0 && getEachBit(a) + getEachBit(b) <= threshold){
                queue[rear] = createPoint(a,b);
                rear = (rear + 1) % size;
                matrix[a][b] = 1;
            }
        }

        free(p);  //用完Point就可以free了
        ret++;
    }

    // free掉内存
    for(int i = 0;i<rows;++i) free(matrix[i]);
    free(queue);
    free(matrix);

    return ret;
}
```