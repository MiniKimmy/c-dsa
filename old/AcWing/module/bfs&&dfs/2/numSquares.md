## 279. Perfect Squares
[这里](https://leetcode.com/problems/perfect-squares/)

**Example 1:**
```
Input: n = 12
Output: 3
Explanation: 12 = 4 + 4 + 4.（12有3个平方数相加得到）
```
**Example 2:**
```
Input: n = 13
Output: 2
Explanation: 13 = 4 + 9.（13有2个平方数相加得到）
```
## hints
```
    图:从0点到n点最短距离【bfs】
    1.权值=1，距离即边的条数，这个边是通过“平方数的和”连接
    2.ex:12=4+4+4，距离即平方数数量=3
    [0~12]个点: 0 1 2 3 4 5 6 7 8 9 10 11 12
          dis[] 0 1     1         1
                    2     2     2    2
                      3       ...         3
    3.一层一层距离，层与层之间的距离即权值=1
        * bfs每次找出距离为0、1、2、3..
        * 距离更新:dis[new] = dis[当前] + weight
            * ex: dis[2] = dis[1] + 1
                  dis[4] = dis[0] + 1
        * 队列每次存上一层更新完毕的点
    4.外衣：dis[i]表示第[i]号点到0点的距离
            * dis表示规则，法则
    5.初始值添加[0]号:dis[0] = 0，dis[其他]=﹢∞
        * 因为找的是最小距离，所以更新距离是越小就越要更新
    6.注：csharp尽量使用int[]而不用List<>
```
## Solution
``` c
int numSquares(int n) {

    int* dis = (int*)malloc(sizeof(int) * (n+1));
    for(int i = 0;i<n+1;++i) {
        dis[i] = n+1; //最大距离不会超过n+1
    }

    int SIZE = 10000;
    int* sqQueue = (int*)malloc(sizeof(int) * SIZE);
    int front = 0;
    int rear = 0;

    sqQueue[rear] = 0;
    rear = (rear+1) % SIZE;
    dis[0] = 0;

    while(front != rear){
        int t = sqQueue[front];
        front = (front+1)%SIZE;

        if(t == n) return dis[t];
        for(int i = 1;i*i+t<=n;++i)
        {
            int j = i*i + t;
            if(dis[j] > dis[t] + 1)  //weight = 1
            {
                dis[j] = dis[t] + 1;

                sqQueue[rear] = j;
                rear = (rear+1) % SIZE;
            }
        }
    }

    return 0;
}
```

## Solution
``` csharp
public class Solution {
    public int NumSquares(int n) {
        Queue<int> q = new Queue<int>();
        q.Enqueue(0);

        int[] dis = new int[n+1];
        for (int i = 0; i < n+1; i++) {
            dis[i] = n + 1;
        }

        dis[0] = 0;
        while(q.Count>0)
        {
            int t = q.Dequeue();

            if (t == n) return dis[t];
            for (int i = 0; i * i + t <= n; i++)
            {
                int j = i * i + t;
                if(dis[j] > dis[t] + 1)
                {
                    dis[j] = dis[t] + 1;
                    q.Enqueue(j);
                }
            }
        }

        return 0;
    }
}
```