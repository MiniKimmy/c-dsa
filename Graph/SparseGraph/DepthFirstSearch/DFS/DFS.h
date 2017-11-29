#pragma once
#include<stdio.h>
#include<stdlib.h>
#define PRINT_STRING(x) printf("%s\n",x)

//bool����
typedef enum Boolean {   
    FALSE,
    TRUE,
}Boolean;

#pragma region DFS 
typedef struct DFS {
    Boolean* marked;    //��¼�Ƿ���ͨ��FALSEδ��ͨ��TRUE��ͨ��
    int* from;          //��¼��һ������
    int start;          //���
}DFS;
#pragma endregion

#include"m_sparsegraph.h"   //#include �ڽӱ�
#include"stack.h"           //#include ��ջ

#pragma region Functions
DFS* InitDFS(Graph * G, int start);
void BondingConnect(DFS* S, Graph * G, int start);
Stack* GetPath(DFS * S, int destination);
#pragma endregion


/*��ʼ��DFS*/
/*G������ն����ͼָ��*/
/*start�����*/
DFS* InitDFS(Graph * G, int start)
{
    if (G == NULL) {
        PRINT_STRING("GraphΪNULL");
        return NULL;
    }

    if (start < 0) {
        PRINT_STRING("��㲻��Ϊ����");
        return NULL;
    }

    //����ͼ�Ķ���
    CreateGraph_ByInputKeyCode(G);

    //���ͼ������
    if (start > GetVerticesCount(G) || GetVerticesCount(G) == 0) return NULL;

    DFS* ret = (DFS*)malloc(sizeof(DFS));
    if (ret == NULL) {
        PRINT_STRING("DFS��ʼ����̬�����ڴ�ʧ��");
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

    //��ʼ��marked[]��ΪFALSE
    for (int i = 0; i < GetVerticesCount(G); i++){
        ret->marked[i] = FALSE;
    }

    ret->start = start;             //��¼���
    BondingConnect(ret, G, start);  //����marked[]��from[]
    ret->from[start] = start;       //����form������
    return ret;
}

/*(�ڲ�����)��¼��ͨ*/
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

/*��ȡ·��,����Stack*/
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
