## 210. Course Schedule II
[这里](https://leetcode.com/problems/course-schedule-ii/description/)

## hints
* [上一题hints](https://leetcode.com/problems/course-schedule/description/)
```
1.只是后面使用一个数组记录访问过哪个点，其余不变。
```

## Solution
``` c
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

typedef struct Node{
    int data;
    struct Node* next ;
}Node;

Node* createNode(int data){
    Node* ret = (Node*)malloc(sizeof(Node));
    ret->data = data;
    ret->next = NULL;
    return ret;
}

int* findOrder(int numCourses, int** prerequisites, int prerequisitesRowSize, int *prerequisitesColSizes, int* returnSize) {
    if(numCourses<=0) return NULL;

    int* dist = (int*)malloc(sizeof(int) * numCourses);
    struct Node** g = (Node**)malloc(sizeof(struct Node*) * numCourses);
    for(int i = 0;i<numCourses;++i) {
        dist[i] = 0;
        g[i] = NULL;  // 必须清空Node[]
    }

    for(int i = 0;i<prerequisitesRowSize;++i) {
        int first = prerequisites[i][0];
        int second = prerequisites[i][1];

        dist[first]++;
        if(!g[second]){
            g[second] = createNode(second);
        }


        Node* k = g[second]->next;
        Node* item = createNode(first);
        item->next = k;
        g[second]->next = item;
    }

    int front = 0; int rear = 0;
    int* sqQueue  = (int*)malloc(sizeof(int) * numCourses);
    for(int i = 0;i<numCourses;++i)
    {
        if(!dist[i]){
            sqQueue[rear] = i;
            rear++;
        }
    }

    int* ret = (int*)malloc(sizeof(int) * numCourses);
    int index= 0;
    while(front != rear){
        int v = sqQueue[front];
        front++;
        ret[index++] = v;
        Node* p = g[v]?g[v]->next:NULL;
        while(p){
            dist[p->data]--;
            if(!dist[p->data])
            {
                sqQueue[rear] = p->data;
                rear++;
            }
            p = p->next;
        }
    }


    free(sqQueue);
    free(dist);
    if(index != numCourses){
        *returnSize = 0;
        free(ret);
        return NULL;
    }else{
        *returnSize = numCourses;
         return  ret;
    }
}
```
## hints
```
1.使用List<List<int>>来当作邻接表
    (1).在第一层实例化之后还必须for一遍初始化list.Add(null),否则会报错数组越界
2.在返回空数组时候是返回new int[0] 而不是 null.
```
## Solution
``` csharp
public class Solution {
    public int[] FindOrder(int numCourses, int[,] prerequisites) {
        if(numCourses<=0) return null;
        int n = prerequisites.GetLength(0);

        List<List<int>> g = new List<List<int>>();
        int[] dist = new int[numCourses];
        for(int i = 0;i<numCourses;++i){
            g.Add(null);  //初始化graph
        }

        for(int i = 0; i<n; ++i){
            var first = prerequisites[i,0];
            var second = prerequisites[i,1];

            dist[first]++;
            if(g[second] == null){
                g[second] = new List<int>();
            }

            g[second].Add(first);
        }

        Queue<int> que = new Queue<int>();
        for(int i = 0;i<numCourses;++i){
            if(dist[i] == 0){
                que.Enqueue(i);
            }
        }


        int[] ret = new int[numCourses];
        int index = 0;
        while(que.Count>0){
            var t = que.Dequeue();
            ret[index++] = t;
            int len = g[t]==null?0:g[t].Count;
            for(int i = 0;i<len;++i)
            {
                dist[g[t][i]]--;
                if(dist[g[t][i]] == 0)
                {
                    que.Enqueue(g[t][i]);
                }
            }
        }

        return index!=numCourses?new int[0]: ret;
    }
}

```