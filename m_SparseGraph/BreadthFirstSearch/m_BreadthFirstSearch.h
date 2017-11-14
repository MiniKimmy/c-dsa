#pragma once
#include<stdio.h>
#include<stdlib.h>
#define PRINT_STRING(x) printf("%s\n",x)

typedef struct BreadthFirstSearch{
    int* marked;
    int* route;
    int count;
    int start;  //���
}BFS;

#include "graph.h"
#include "queue.h"

#pragma region Functions
BFS* InitBFS(Graph * G, int start);
void bfs(BFS* S, Graph * G, int start);
void GetPath(BFS * S, int end);
void Traverse_marked(BFS * s);

#pragma endregion

/*��ʼ��BFS*/
/*start:���*/
BFS* InitBFS(Graph * G,int start)
{
    if (G == NULL) {
        PRINT_STRING("GraphΪNULL");
        return NULL;
    }

    if (start < 0 || start > G->Vertices || G->Vertices == 0 || G->Edge == 0) return NULL;

    BFS* ret = (BFS*)malloc(sizeof(BFS));
    if (ret == NULL){
        PRINT_STRING("BFS��ʼ����̬�����ڴ�ʧ��");
        exit(-1);
    }

    ret->marked = (int*)malloc(sizeof(int) * G->Vertices);
    if (ret->marked == NULL) {
        PRINT_STRING("marked[]��ʼ����̬�����ڴ�ʧ��");
        exit(-1);

    }

    ret->route = (int*)malloc(sizeof(int) * G->Vertices);
    if (ret->route == NULL) {
        PRINT_STRING("route[]��ʼ����̬�����ڴ�ʧ��");
        exit(-1);
    }

    ret->count = G->Vertices;
    for (int i = 0; i < G->Vertices; i++){
        ret->marked[i] = 0;
        ret->route[i] = -1;
    }
    ret->start = start;
    ret->route[start] = start; //���ڵ�
    ret->marked[start] = 1;
    bfs(ret, G, start);
    return ret;
}

/*���ڲ�������BFS��ʼ����ǰstart����ͼ*/
void bfs(BFS* S, Graph * G, int start)
{
    Queue* Q = InitQueue();
    EnterQueue(Q, start);

    while (!IsEmptyQueue(Q)){
        int current_Key = *GetHeadValue(Q);
        DeleteQueue(Q);
        if (S->route[current_Key] != -1 || S->route[current_Key] == start) {
            GNode* p = GetGNode(G, current_Key);
            while (p->Next){
                p = p->Next;
                if (S->route[p->Key] == -1 && S->route[p->Key] != start) {
                    EnterQueue(Q, p->Key);
                    S->route[p->Key] = current_Key;
                    S->marked[p->Key] = 1;  //����Ѿ��߹�
                }
            }
        }
    }
    DestroyQueue(&Q);
    return;
}

void GetPath(BFS * S, int end)
{
    int p = S->route[end];
    printf("%d", end);
    while (p != S->start){
        printf("<-%d",p);
        p = S->route[p];
    }
    printf("<-%d\n",p);
    return;
}

void Traverse_marked(BFS * S)
{
    if (S == NULL) return;

    for (int i = 0; i < S->count; i++)
    {
        printf("%d ", S->marked[i]);
    }
    printf("\n");
    return;
}
