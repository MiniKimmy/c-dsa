#pragma once
#include<stdio.h>
#include<stdlib.h>

typedef enum Boolean{
    FALSE,
    TRUE,
}Boolean;

#pragma region BFS
typedef struct BFS {
    Boolean* marked;  //记录是否与start连通
    int* from;        //记录上一个经过的顶点
    int start;        //起点
}BFS;
#pragma endregion

#include "sparsegraph.h"     //#include邻接表
#include "queue.h"           //#include队列(作BFS绑定marked[]和from[])
#include "stack.h"           //#include链栈(作GetPath用)

#pragma region Functions
BFS* InitBFS(Graph * G, int start);
void BondingConnect_bfs(BFS * S, Graph * G);
Stack* GetPath(BFS * S, int destination);
#pragma endregion

/*初始化BFS*/
/*G : 传入空数据的Graph指针*/
/*start : 起点（起点在BFS不需要被存储）*/
BFS* InitBFS(Graph * G, int start)
{
    if (G == NULL) {
        PRINT_STRING("Graph为NULL");
        return NULL;
    }

    if (start < 0) {
        PRINT_STRING("起点start不能为负数");
        return NULL;
    }

    //根据图的数据生成图
    CreateGraph_ByInputKeyCode(G);

    //再次检查图
    if (start > GetVerticesCount(G) 
        || GetVerticesCount(G) == 0 
        || GetEdgeCount(G) == 0) return NULL;

    BFS* ret = (BFS*)malloc(sizeof(BFS));
    if (ret == NULL) {
        PRINT_STRING("BFS初始化动态分配内存失败");
        exit(-1);
    }

    ret->marked = (Boolean*)malloc(sizeof(Boolean) * GetVerticesCount(G));
    if (ret->marked == NULL) {
        PRINT_STRING("marked[]初始化动态分配内存失败");
        exit(-1);
    }

    ret->from = (int*)malloc(sizeof(int) * GetVerticesCount(G));
    if (ret->from == NULL) {
        PRINT_STRING("from[]初始化动态分配内存失败");
        exit(-1);
    }

    //初始化marked[]全为FALSE,初始化from[]全为-1，-1只是标记该key未找到最近的上一个顶点
    for (int i = 0; i < GetVerticesCount(G); i++){
        ret->marked[i] = FALSE;
        ret->from[i] = -1;  
    }
    
    ret->start = start;        //记录start(GetPath时候需要用start)
    ret->marked[start] = TRUE; //自身和自身的连通的
    ret->from[start] = start;  //起点的上一个起点是自身

    //绑定连通marked[]和from[]
    BondingConnect_bfs(ret, G);
    return ret;
}

/*（内部方法）绑定连接构建marked[]和from[]*/
void BondingConnect_bfs(BFS * S, Graph * G)
{
    Queue* Q = InitQueue();
    EnterQueue(Q, S->start);
    while (!IsEmptyQueue(Q)){
        int key = *GetValue_Queue(Q);
        DeleteQueue(Q);
        GNode* p = GetGNode(G, key); 
        while (p->Next){
            p = p->Next;
            if (S->from[p->Key] == -1 && p->Key != S->start) {
                EnterQueue(Q, p->Key);
                S->from[p->Key] = key;
                S->marked[p->Key] = TRUE;
            }
        }
    }
}

/*获取路径,返回Stack*/
/*destination:终点*/
Stack* GetPath(BFS * S, int destination)
{
    if (S->marked[destination] == FALSE) return;
    
    Stack* ret = InitStack();
    for (int i = destination; i != S->start; i = S->from[i]){
        Push_Stack(ret, i);
    }
    Push_Stack(ret, S->start);
    return ret;
}
