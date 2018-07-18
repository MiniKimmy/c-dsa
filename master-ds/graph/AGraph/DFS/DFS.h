#define USEAGRAPH 0  // 1表示使用邻接表 0表示不用邻接表
#define ARRAYSIZE 10 // 数组初始默认长度 10
#include<stdio.h>
#include<stdlib.h>

#if USEAGRAPH==0
#include"linklist.h"
#endif

#if USEAGRAPH==1
#include"AGraph.h"
#endif


typedef struct {
    int* mark;  //0表示未连,1表示连通
    int* from;
    int start;  
}DFS;

#pragma region DFSFunctions
#if USEAGRAPH==1
    DFS* initDFS(AGraph* G, int start);
    void dfsAgraph(DFS* dfs, AGraph* G, int start);
#endif
#if USEAGRAPH==0
    DFS* initDFS(SLinkList* L);
    void dfsList(DFS* dfs, SLinkList* L, int start);
    void setStartDFS(DFS* dfs, int start);
    ArcNode* getLNode(DFS* dfs, int index);
#endif
void traverseDFS(DFS* dfs, int end);
int* getDFSPath(DFS* dfs, int end, int* returnSize);

#pragma endregion

#if USEAGRAPH==1
DFS* initDFS(AGraph* G, int start){
    if (G == NULL || start <= 0 || start > G->v) return NULL;

    DFS* dfs = (DFS*)malloc(sizeof(DFS));
    dfs->from = (int*)malloc(sizeof(int) * G->v);
    dfs->start = start;
    dfs->mark = (int*)malloc(sizeof(int) * G->v);
    for (int i = 0; i < G->v; i++){
        dfs->mark[i] = 0;
        dfs->from[i] = i + 1; //Graph的key默认从1开始
    }
    dfs->mark[start-1] = 1;
    return dfs;
}

void dfsAgraph(DFS* dfs, AGraph* G, int start){
    if (dfs == NULL) return;

    SLinkList* list = getVNodeAgraph(G, start);
    dfs->mark[start-1] = 1;
    ArcNode* p = list->head;
    while (p->next) {
        p = p->next;
        if (dfs->mark[p->v - 1] == 0) {
            dfs->from[p->v -1] = start;
            dfsAgraph(dfs, G, p->v);
        }
    }
}
#endif



#if USEAGRAPH == 0
DFS* initDFS(SLinkList* L) {
    if (L == NULL) return NULL;

    DFS* dfs = (DFS*)malloc(sizeof(DFS));

    dfs->from = (int*)((ArcNode**)malloc(sizeof(ArcNode*) * L->count));
    dfs->start = 0;      //默认开始下标是0
    dfs->mark = (int*)malloc(sizeof(int) * L->count);

    ArcNode* p = L->head;
    for (int i = 0; i < L->count; i++) {
        dfs->mark[i] = 0;
        p = p->next;
        ((ArcNode**)dfs->from)[i] = p;
    }

    return dfs;
}

void setStartDFS(DFS* dfs, int start) {
    if (dfs == NULL) exit(0);
    dfs->start = start;
}

void dfsList(DFS* dfs, SLinkList* L, int start) {
    if (dfs == NULL || L == NULL) return;
    dfs->mark[start] = 1;
    ArcNode* p = getLNode(dfs, start);
    int i = start;
    while (p->next) {
        dfs->mark[i + 1] = i;
        p = p->next;
        i++;
    }
}

ArcNode* getLNode(DFS* dfs, int index) {
    if (dfs == NULL || index < 0 )  return NULL;
    return (ArcNode*)(((ArcNode**)dfs->from)[index]);
}

#endif // USEAGRAPH == 0


void traverseDFS(DFS* dfs, int end){
    if (dfs == NULL || end <= 0 ) return;
    
    int pre = end;
    while (pre != dfs->start) {
#if USEAGRAPH == 1
        printf("%d->", pre);
        pre = dfs->from[pre - 1];
#endif // USEAGRAPH == 1

#if USEAGRAPH == 0
        printf("%c->", getLNode(dfs, pre)->v);
        pre --;
#endif // USEAGRAPH == 0
    }
#if USEAGRAPH == 1
    printf("%d\n",dfs->start);
#endif
#if USEAGRAPH == 0
    printf("%c\n", getLNode(dfs, pre)->v);
#endif
    return;
}

int* getDFSPath(DFS* dfs, int end , int* returnSize) {
    if (dfs == NULL || end <= 0) return NULL;

    int len = 0;
    int* arr = (int*)malloc(sizeof(int) * ARRAYSIZE);

    int pre = end;
    while (pre != dfs->start) {
        arr[len++] = pre;
        pre = dfs->from[pre - 1];
    }

    *returnSize = len + 1;
    int* ret = (int*)malloc(sizeof(int) * (len + 1));
    for (int i = 0; i < len + 1; i++){
        ret[i] = arr[i];
    }

    ret[len] = dfs->start;
    return ret;
}
