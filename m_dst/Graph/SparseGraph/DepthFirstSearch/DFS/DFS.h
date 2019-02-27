#pragma once
#include<stdio.h>
#include<stdlib.h>
#define PRINT_STRING(x) printf("%s\n",x)

//bool类型
typedef enum Boolean {   
    FALSE,
    TRUE,
}Boolean;

#pragma region DFS 
typedef struct DFS {
    Boolean* marked;    //记录是否连通（FALSE未连通，TRUE连通）
    int* from;          //记录上一个顶点
    int start;          //起点
}DFS;
#pragma endregion

#include"m_sparsegraph.h"   //#include 邻接表
#include"stack.h"           //#include 链栈

#pragma region Functions
DFS* InitDFS(Graph * G, int start);
void BondingConnect(DFS* S, Graph * G, int start);
Stack* GetPath(DFS * S, int destination);
#pragma endregion


/*初始化DFS*/
/*G：传入空顶点的图指针*/
/*start：起点*/
DFS* InitDFS(Graph * G, int start)
{
    if (G == NULL) {
        PRINT_STRING("Graph为NULL");
        return NULL;
    }

    if (start < 0) {
        PRINT_STRING("起点不能为负数");
        return NULL;
    }

    //生成图的顶点
    CreateGraph_ByInputKeyCode(G);

    //检测图的数据
    if (start > GetVerticesCount(G) || GetVerticesCount(G) == 0) return NULL;

    DFS* ret = (DFS*)malloc(sizeof(DFS));
    if (ret == NULL) {
        PRINT_STRING("DFS初始化动态分配内存失败");
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

    //初始化marked[]都为FALSE
    for (int i = 0; i < GetVerticesCount(G); i++){
        ret->marked[i] = FALSE;
    }

    ret->start = start;             //记录起点
    BondingConnect(ret, G, start);  //构建marked[]和from[]
    ret->from[start] = start;       //起点的form即自身
    return ret;
}

/*(内部方法)记录连通*/
void BondingConnect(DFS * S,Graph * G, int start)
{
    S->marked[start] = TRUE;
    
    GNode* p = GetGNode(G, start);
    while (p->Next){
        p = p->Next;
        int index = p->Key;
        if (S->marked[index] == FALSE) {
            S->from[index] = start;
            BondingConnect(S, G, index);
        }
    }
}

/*获取路径,返回Stack*/
Stack* GetPath(DFS * S, int destination)
{
    if (S->marked[destination] == FALSE) return NULL;

    Stack* ret = InitStack();
    for (int i = destination; i != S->start ; i = S->from[i]){
        Push_Stack(ret, i);
    }
    Push_Stack(ret, S->start);
    return ret;
}
