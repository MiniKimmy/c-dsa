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
    while(front != rear)
    {
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