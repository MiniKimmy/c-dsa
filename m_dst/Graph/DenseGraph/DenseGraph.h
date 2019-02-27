#pragma once
#include<stdlib.h>
#include<stdio.h>
#define PRINT_INT(x) printf("%d ",x)
#define PRINT_STRING(x) printf("%s\n",x)

#pragma region DenseGraph
typedef struct DenseGraph {
    int Vertices;        //�����ܸ���
    int Edge;            //�ߵ��ܸ���
    int** pBase;        //bool���͵Ķ�ά����
}DenseGraph;
#pragma endregion

#pragma region Functions
DenseGraph* InitGraph(int V);
void CreateGraph_ByInputKeyCode(DenseGraph * G);
void AddEdge(DenseGraph * G, int v, int w);
void ToString(DenseGraph * G);
void Traverse_ALLKEY(DenseGraph * G);
//int GetVerticesCount(DenseGraph * G);
#pragma endregion

/*��ʼ��DenseGraph*/
DenseGraph* InitGraph(int V)
{
    DenseGraph* ret = (DenseGraph*)malloc(sizeof(DenseGraph));
    if (ret == NULL){
        PRINT_STRING("DenseGraph��ʼ����̬�����ڴ�ʧ��\n");
        exit(-1);
    }
    ret->Edge = 0;
    ret->Vertices = V;
    ret->pBase = (int**)malloc(sizeof(int*) * V);
    for (int i = 0; i < ret->Vertices; i++)
    {
        ret->pBase[i] = (int*)malloc(sizeof(int) * V);
        for (int j = 0; j < ret->Vertices; j++)
        {
            ret->pBase[i][j] = 0;
        }
    }
    return ret;
}

/*�ֶ������ͼ�Ķ�������*/
void CreateGraph_ByInputKeyCode(DenseGraph * G)
{
    Traverse_ALLKEY(G);
    printf("��������Ҫ���Edge�ĸ��� �� ");
    int m_Edge;
    scanf_s("%d", &m_Edge);
    for (int i = 0; i < m_Edge; i++)
    {
        PRINT_STRING("\n��������Ҫ���ӵ�2��Node��KEY");
        int v, w;
        scanf_s("%d", &v);
        scanf_s("%d", &w);
        AddEdge(G, v, w);
        if (G->Edge > i) {
            printf("�������� %d ������\n", G->Edge);
        }
        else {
            i = i == 0 ? 0 : --i;
            PRINT_STRING("δ���ӳɹ�,����������");
        }
    }
    return;
}

/*��ӱ�v->w*/
void AddEdge(DenseGraph * G, int v, int w)
{
    if (v < G->Vertices && w < G->Vertices)
    {
        if (G->pBase[v][w]) return;
        G->pBase[v][w] = 1;
        G->pBase[w][v] = 1;
        G->Edge++;
    }
    return;
}

/*��ӡ�ڽӾ���*/
void ToString(DenseGraph * G)
{
    //debug
    for (int i = 0; i < G->Vertices; i++)
    {
        printf("%d : ", i);
        for (int j = 0; j < G->Vertices; j++)
        {
            PRINT_INT(G->pBase[i][j]);
        }
        PRINT_STRING("");
    }
}

/*��ӡ���еĶ���*/
void Traverse_ALLKEY(DenseGraph * G)
{

    for (int i = 0; i < G->Vertices; i++)
    {
        PRINT_INT(i);
    }
    PRINT_STRING("\n-----------------------");
}
