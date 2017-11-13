#pragma once
/*brief An implementation of DepthFirstSearch,  including InitDFS,Getpath,*/
#include<stdio.h>
#include<stdlib.h>
#define PRINT_INT(x) printf("%d ",x)
#define PRINT_STRING(x) printf("%s\n",x)

#include"m_sparsegraph.h"

typedef struct DFS {
    int* route;   //路线arr  
    int count;    //路线数组的元素个数
}DFS;

#pragma region Functions
DFS* InitDFS(Graph * G);
void DFS_GetPath(Graph* G, DFS* S, int start, int end);
void GetPath(Graph* G, DFS* S, int start, int end);
#pragma endregion


/*初始化DFS*/
DFS* InitDFS(Graph * G)
{
    DFS* ret = (DFS*)malloc(sizeof(DFS));
    if (ret == NULL) {
        PRINT_STRING("DFS初始化动态分配内存失败");
        exit(-1);
    }
    
    ret->route = (int*)malloc(sizeof(int) * G->Vertices);
    if (ret->route == NULL) {
        PRINT_STRING("Route_Arr初始化动态分配内存失败");
        exit(-1);
    }

    ret->count = 0;
    return ret;
}

/*(外部方法)GetPath*/
void DFS_GetPath(Graph* G, DFS* S, int start, int end)
{
    if (G == NULL || S == NULL) {
        PRINT_STRING("参数存在NULL");
        return;
    }

    if (start < 0 || end < 0 || start > G->Vertices || end > G->Vertices || G->Vertices == 0 || G->Edge == 0) return;
    GetPath(G, S, start, end);
}

/*(内部方法)查询路径*/
void GetPath(Graph* G, DFS* S, int start, int end)
{
    GNode* Current = GetGNode(G, start);
    S->route[S->count] = start;
    S->count++;

    if (start == end) return;
    else {
        while (Current)
        {
            Current = Current->Next;
            if (Current){
                for (int i = 0; i < S->count; i++){
                    if (Current->Key == S->route[i]) break;

                    if (i >= S->count - 1 && Current->Key != S->route[i]) {
                        GetPath(G, S, Current->Key, end);
                        if (S->route[S->count - 1] == end) return;
                        else S->count--;
                    }
                }
            }
        }
    }
}
