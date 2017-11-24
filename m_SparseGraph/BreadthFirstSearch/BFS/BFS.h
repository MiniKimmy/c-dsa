#pragma once
#include<stdio.h>
#include<stdlib.h>

typedef enum Boolean{
    FALSE,
    TRUE,
}Boolean;

#pragma region BFS
typedef struct BFS {
    Boolean* marked;  //��¼�Ƿ���start��ͨ
    int* from;        //��¼��һ�������Ķ���
    int start;        //���
}BFS;
#pragma endregion

#include "sparsegraph.h"     //#include�ڽӱ�
#include "queue.h"           //#include����(��BFS��marked[]��from[])
#include "stack.h"           //#include��ջ(��GetPath��)

#pragma region Functions
BFS* InitBFS(Graph * G, int start);
void BondingConnect_bfs(BFS * S, Graph * G);
Stack* GetPath(BFS * S, int destination);
#pragma endregion

/*��ʼ��BFS*/
/*G : ��������ݵ�Graphָ��*/
/*start : ��㣨�����BFS����Ҫ���洢��*/
BFS* InitBFS(Graph * G, int start)
{
    if (G == NULL) {
        PRINT_STRING("GraphΪNULL");
        return NULL;
    }

    if (start < 0) {
        PRINT_STRING("���start����Ϊ����");
        return NULL;
    }

    //����ͼ����������ͼ
    CreateGraph_ByInputKeyCode(G);

    //�ٴμ��ͼ
    if (start > GetVerticesCount(G) 
        || GetVerticesCount(G) == 0 
        || GetEdgeCount(G) == 0) return NULL;

    BFS* ret = (BFS*)malloc(sizeof(BFS));
    if (ret == NULL) {
        PRINT_STRING("BFS��ʼ����̬�����ڴ�ʧ��");
        exit(-1);
    }

    ret->marked = (Boolean*)malloc(sizeof(Boolean) * GetVerticesCount(G));
    if (ret->marked == NULL) {
        PRINT_STRING("marked[]��ʼ����̬�����ڴ�ʧ��");
        exit(-1);
    }

    ret->from = (int*)malloc(sizeof(int) * GetVerticesCount(G));
    if (ret->from == NULL) {
        PRINT_STRING("from[]��ʼ����̬�����ڴ�ʧ��");
        exit(-1);
    }

    //��ʼ��marked[]ȫΪFALSE,��ʼ��from[]ȫΪ-1��-1ֻ�Ǳ�Ǹ�keyδ�ҵ��������һ������
    for (int i = 0; i < GetVerticesCount(G); i++){
        ret->marked[i] = FALSE;
        ret->from[i] = -1;  
    }
    
    ret->start = start;        //��¼start(GetPathʱ����Ҫ��start)
    ret->marked[start] = TRUE; //������������ͨ��
    ret->from[start] = start;  //������һ�����������

    //����ͨmarked[]��from[]
    BondingConnect_bfs(ret, G);
    return ret;
}

/*���ڲ������������ӹ���marked[]��from[]*/
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

/*��ȡ·��,����Stack*/
/*destination:�յ�*/
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
