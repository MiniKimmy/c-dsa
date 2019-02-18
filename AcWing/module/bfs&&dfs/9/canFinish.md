## 207. Course Schedule
[这里](https://leetcode.com/problems/course-schedule/)
拓扑排序问题。

## hints
```
    邻接矩阵+拓扑排序bfs
1.判断是否为DAG（有向无环图），有环则return false.
2.拓扑排序bfs
    (1).首先将入度为0的点放进queue
    (2).pop出队头。
    (3).队头紧接着的顶点，都入度-1,继续将入读为0的入队
    (4).记录pop出了哪些点，还有点没pop出来表示有环
    * 注：把入度理解为“距离”会好点。两个顶点相连经过1条边等价于距离1
```

## Solution
``` c
typedef struct adjMatrix{
    int** arr;
    int* size;
}adjMatrix;

/// 实例化adjMatrix
adjMatrix* createGraph(int v) {
    adjMatrix* ret = (adjMatrix*)malloc(sizeof(adjMatrix));
    ret->arr = (int**)malloc(sizeof(int*) * v);
    ret->size = (int*)malloc(sizeof(int) * v);
    for(int i = 0;i<v;++i){
        (ret->arr)[i] = (int*)malloc(sizeof(int) * v);
        (ret->size)[i] = 0;
    }

    for(int i = 0;i<v;++i){
        for(int j = 0;j<v;++j){
            (ret->arr)[i][j] = 0;
        }
    }

    return ret;
}

/// 销毁adjMatrix
void disposeGraph(adjMatrix** g, int vCount){
    for(int i = 0;i<vCount;++i){
        free( ((*g)->arr)[i] );
    }

    free( (*g)->size );
    free(*g);
    return;
}

bool canFinish(int numCourses, int** prerequisites, int prerequisitesRowSize, int *prerequisitesColSizes) {
    if(!numCourses || !prerequisites || !prerequisitesRowSize) return true;

    /// 入读用dist[]来存储，是distance的缩写
    int* dist = (int*)malloc(sizeof(int) * numCourses);
    adjMatrix* g = createGraph(numCourses);

    int* sqQueue = (int*)malloc(sizeof(int) * numCourses);
    int front = 0;
    int rear = 0;

    for(int i = 0;i<numCourses;++i){
        dist[i] = 0;
    }

    for(int i = 0;i<prerequisitesRowSize;++i){
        int first = prerequisites[i][0];
        int second = prerequisites[i][1];

        dist[first] ++;
        (g->arr)[second][first] = 1;
        (g->size)[second] ++;
    }

    /// 首先入度为0的放入队列
    for(int i = 0;i<numCourses;++i){
        if(!dist[i]){
            sqQueue[rear] = i;
            rear++;
        }
    }

    /// 标记是否已经访问过. st[i]=0默认未访问
    int* st = (int*)malloc(sizeof(int) * numCourses);
    for(int i = 0;i<numCourses;++i){
        st[i] = 0;
    }

    while(front != rear){
        int v = sqQueue[front];
        front++;

        st[v] = 1;  // 记录已访问过v点
        if((g->size)[v]){
            for(int i=0;i<numCourses;++i)
            {
                if((g->arr)[v][i] == 1)
                {
                    dist[i]--;
                    if(!dist[i]) {
                        sqQueue[rear] = i;
                        rear++;
                    }
                }
            }
        }
    }

    free(sqQueue);
    free(dist);
    disposeGraph(&g,numCourses);

    /// 判断哪个点未访问过.
    for(int i = 0;i<numCourses;++i){
        if(!st[i]){
            free(st);
            return false;
        }
    }

    free(st);
    return true;
}
```

## hints2
```
    邻接表+拓扑排序bfs
1.将上面“记录访问过哪些点存到int[]”，优化为“记录有多少个点被访问存到int-->最后只需判断点数目是否等于总课程数目”
2.使用邻接表
    (1).自定义单链表类型<data,*next>
        * 需要自定义构造函数
        * 默认一个空参的构造函数 + 带参的构造函数
        * c#特有，使用自动属性get/set
    (2).邻接表简单理解为“MyList[]”
        * 最外层数组，内部数据对象是链表结构
        * 因为顶点数目是固定的，所以可以用数组作为最外层
        * 而内部是链表结构，连边 -->添加顶点到链表
    (3).由于是自定义数组[]，所以需要手动实例化，for一遍
        * MyList[] a = new MyList[100]; 它只是开拓了空间，并未对a[0],a[1]...实例化
        * 而int[]、string[]这些基本数据类型的数组[]会自动赋默认值0,null。
```
## Solution2
``` csharp
class MyList {
    private int data = 0;
    private MyList next = null;

    public int Data { get => data; set => data = value; }
    internal MyList Next { get => next; set => next = value; }

    public MyList() { }
    public MyList(int data) {
        this.data = data;
        this.next = null;
    }
}

public class Solution {
    public bool CanFinish(int numCourses, int[,] prerequisites) {
        if(numCourses<=0 || prerequisites == null || prerequisites.GetLength(0)<=0) return true;

        int[] dist = new int[numCourses];
        MyList[] g = new MyList[numCourses];

        for(int i = 0;i< numCourses;++i){
            g[i] = new MyList(i);
        }

        int n = prerequisites.GetLength(0);
        for (int i = 0;i<n;++i)
        {
            int first = prerequisites[i, 0];
            int second = prerequisites[i, 1];
            dist[first]++;

            MyList v = new MyList(first);
            v.Next = g[second].Next;
            g[second].Next = v;
        }

        int st = 0;
        Queue<int> que = new Queue<int>();
        for(int i = 0;i<numCourses;++i){
            if(dist[i] == 0){
                que.Enqueue(i);
            }
        }

        while(que.Count>0)
        {
            int t = que.Dequeue();
            st++;
            var item = g[t].Next;
            while(item != null) {
                dist[item.Data]--;
                if(dist[item.Data] == 0){
                    que.Enqueue(item.Data);
                }
                item = item.Next;
            }
        }

        return st != numCourses ? false:true;
    }
}
```