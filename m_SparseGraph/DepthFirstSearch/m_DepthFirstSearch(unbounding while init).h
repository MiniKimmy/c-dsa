#pragma once
#include<stdio.h>
#include<stdlib.h>
#define PRINT_INT(x) printf("%d ",x)
#define PRINT_STRING(x) printf("%s\n",x)

#include "m_sparsegraph.h"

#pragma region DepthFirstSearch
typedef struct DFS {
    int* marked;      //��¼�Ƿ���ͨ,��ͨΪ1������ͨΪ0
    int* route;       //��¼·�߾�����key
    int count_marked; //��¼makredԪ�ظ���
    int count_route;  //route��Ԫ�ظ���
}DFS;
#pragma endregion


#pragma region Functions
DFS* InitDFS(Graph * G);
void DFS_CheckConnected(Graph * G, DFS * S, int start);
void CheckConnected(Graph * G, DFS * S, int start);
void DFS_GetPath(Graph * G, DFS * S, int start, int end);
void GetPath(Graph * G, DFS * S, int start, int end);
#pragma endregion


/*��ʼ��DFS*/
DFS* InitDFS(Graph * G)
{
    if (G) {
        DFS* ret = (DFS*)malloc(sizeof(int) * G->Vertices);
        if (ret == NULL) {
            PRINT_STRING("DFS��ʼ����̬�����ڴ�ʧ��");
            exit(-1);
        }

        ret->marked = (int*)malloc(sizeof(int) * G->Vertices);
        if (ret->marked == NULL) {
            PRINT_STRING("marked_Arr��ʼ����̬�����ڴ�ʧ��");
            exit(-1);
        }

        ret->route = (int*)malloc(sizeof(int) * G->Vertices);
        if (ret->route == NULL) {
            PRINT_STRING("route_Arr��ʼ����̬�����ڴ�ʧ��");
            exit(-1);
        }

        for (int i = 0; i < G->Vertices; i++) {
            ret->marked[i] = 0;
        }
        ret->count_route = 0;
        ret->count_marked = 0;
        return ret;
    }
    return NULL;
}

/*(�ⲿ����)CheckConnected*/
void DFS_CheckConnected(Graph * G, DFS * S, int start)
{
    if (G == NULL || S == NULL) {
        PRINT_STRING("��������NULL");
        return;
    }

    if (start < 0 || start > G->Vertices) {
        printf("�޷��ӵ�[%d]��λ�ÿ�ʼ��ѯ��ͨ\n", start);
        return;
    }

    CheckConnected(G, S, start);
    return;
}

/*(�ڲ�����)��ͨ��ѯ*/
void CheckConnected(Graph * G, DFS * S, int start)
{
    S->marked[start] = 1;
    S->count_marked++;
    GNode* p = GetGNode(G, start);
    for (int i = 0; i < GetSize(G->pBase[start]); i++) {
        p = p->Next;
        if (p == NULL) return;
        if (S->marked[p->Key] == 0) CheckConnected(G, S, p->Key);
    }
    return;
}


/*(�ⲿ����)GetPah*/
void DFS_GetPath(Graph * G, DFS * S, int start, int end)
{
    if (G == NULL || S == NULL) {
        PRINT_STRING("��������NULL");
        return;
    }

    if (start < 0 || start > G->Vertices || end < 0 || end > G->Vertices || G->Vertices == 0 || G->Edge == 0) return;

    GetPath(G, S, start, end);
    return;
}

/*(�ڲ�����)��ѯ·��*/
void GetPath(Graph * G, DFS * S, int start, int end)
{
    S->route[S->count_route++] = start;
    if (start == end) return;

    GNode* p = GetGNode(G, start);
    for (int i = 0; i < GetSize(G->pBase[start]); i++) {
        p = p->Next;
        if (p == NULL) return;
        int flag = 1;         //���λ
        for (int j = 0; j < S->count_route; j++) {
            if (p->Key == S->route[j]) {
                flag = 0;
                break;
            }
        }

        if (flag) {
            GetPath(G, S, p->Key, end);
            if (S->route[S->count_route - 1] == end) return;
            else S->count_route--;
        }
    }
}
