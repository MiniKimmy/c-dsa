#include<stdlib.h>
#include<stdio.h>
#include"queue.h"
#include"stack.h"
#include"AGraph.h"

typedef struct {
    int* from;
    int* mark;
    int start;
}BFS;

#pragma region BFSFunctions
BFS* initBFS(AGraph* G);
void bfsAGraph(BFS* bfs, AGraph* G, int start);
void setStartBFS(BFS* bfs, int start);
Stack* getBFSPath(BFS* bfs, int end);
#pragma endregion

BFS* initBFS(AGraph* G){
    if (G == NULL ) return NULL;

    BFS* bfs = (BFS*)malloc(sizeof(BFS));
    bfs->from = (int*)malloc(sizeof(int) * G->v);
    bfs->mark = (int*)malloc(sizeof(int) * G->v);

    for (int i = 0; i < G->v; i++){
        bfs->mark[i] = 0;
        bfs->from[i] = i + 1; // 默认Key从1开始
    }
    return bfs;
}

void setStartBFS(BFS* bfs, int start) {
    //PRIVATE METHOD.
    if (bfs == NULL) return;
    bfs->start = start;
}

void bfsAGraph(BFS* bfs, AGraph* G, int start) {
    if (G == NULL || start <= 0 || start > G->v) return;
    setStartBFS(bfs, start);

    Queue* q = initQueue();  //队列存的是Key
    enQueue(q, start);
    int front;
    while (q->count != 0) {
        deQueue(q, &front);
        if (bfs->mark[front - 1] == 1) continue;
        SLinkList* list = getVNodeAgraph(G, front);
        bfs->mark[front - 1] = 1;
        ArcNode* p = list->head;
        while (p->next) {
            p = p->next;
            if (bfs->mark[p->v - 1] == 0) {
                enQueue(q, p->v); 
                bfs->from[p->v - 1] = front;
            }
        }
    }
    bfs->from[start - 1] = start;
}

Stack* getBFSPath(BFS* bfs, int end){
    if (bfs == NULL || bfs->mark[end] == 0) return NULL;
    
    Stack* ret = initStack();
    for (int i = end; ret->top->v != bfs->start; i = bfs->from[i-1]){
        push(ret, i);
    }
    return ret;
}
