#pragma once
#include<stdlib.h>
#include<stdio.h>
#define PRINT_INT(x) printf("%d ",x)
#define PRINT_STRING(x) printf("%s\n",x)

#pragma region SparseGraph
typedef struct GNode {
    int Key;
    struct GNode *Next;    //���ַ��ok
}GNode;

//�Ƿ��ر�
typedef enum EdgeType
{
    RepeatEdge,
    Non_RepeatEdge,
}EdgeType;

typedef struct Graph {
    int Vertices;        //�����ܸ���
    int Edge;            //�ߵ��ܸ���
    int** pBase;        //���GNode*��ַ������
    EdgeType EdgeType;    //�Ƿ��ر�
}Graph;
#pragma endregion

#pragma region Functions
Graph* InitGraph(int V, EdgeType edgetype);
void CreateGraph_ByInputKeyCode(Graph * G);
void AddEdge(Graph * G, int v, int w);
void ToString(Graph * G);
int GetSize(int* pBase_x);
GNode* GetGNode(Graph * G, int key);
void Traverse_ALLKEY(Graph * G);
int GetVerticesCount(Graph * G);
#pragma endregion

/*��ʼ��Graph*/
/*V: ��������; EdgeTypeö������: �Ƿ��ر�*/
/*RepeatEdge: �ر�; Non_RepeatEdge: ���ر�*/
Graph* InitGraph(int V, EdgeType edgetype)
{
    Graph* ret = (Graph*)malloc(sizeof(Graph));
    if (ret == NULL) {
        printf("Graph��ʼ����̬�����ڴ�ʧ��\n");
        exit(-1);
    }
    ret->Vertices = V;
    ret->Edge = 0;
    ret->pBase = (int**)malloc(sizeof(int*) * V);
    ret->EdgeType = edgetype;

    //ÿһ��int*��Ҫ��ֵһ��GNode*�ĵ�ַ
    for (int i = 0; i < ret->Vertices; i++) {
        ret->pBase[i] = (int*)malloc(sizeof(GNode));
        if (ret->pBase[i] == NULL) {
            printf("pBase[i]��ʼ����̬�����ڴ�ʧ��\n");
            exit(-1);
        }
        ((GNode*)ret->pBase[i])->Next = NULL;
    }
    return ret;
}

/*��Grapth�Ķ�����������*/
void CreateGraph_ByInputKeyCode(Graph * G)
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

/*������������*/
/*v�ǵ�ǰ�Ķ��㣬w����������*/
void AddEdge(Graph * G, int v, int w)
{
    if (v < G->Vertices && w < G->Vertices)
    {
        GNode* V = GetGNode(G, v);
        if (G->EdgeType == RepeatEdge) {
            GNode* NewV = (GNode*)malloc(sizeof(GNode));
            if (NewV == NULL) {
                printf("NewV��ʼ����̬�����ڴ�ʧ��\n");
                exit(-1);
            }
            GNode* NewW = (GNode*)malloc(sizeof(GNode));
            if (NewW == NULL) {
                printf("NewW��ʼ����̬�����ڴ�ʧ��\n");
                exit(-1);
            }
            GNode* W = GetGNode(G, w);

            NewV->Key = w;
            NewW->Key = v;

            GNode* p = V->Next;
            NewV->Next = p;
            V->Next = NewV;

            p = W->Next;
            NewW->Next = p;
            W->Next = NewW;
            G->Edge++;
        }
        else {
            int flag = 1;            //��־λ
            GNode* p = V->Next;        //����Item
            for (int i = 0; i < GetSize(G->pBase[v]); i++) {
                if (p->Key == w) flag = 0;
            }
            if (flag) {
                GNode* NewV = (GNode*)malloc(sizeof(GNode));
                if (NewV == NULL) {
                    printf("NewV��ʼ����̬�����ڴ�ʧ��\n");
                    exit(-1);
                }
                NewV->Key = w;
                p = V->Next;
                NewV->Next = p;
                V->Next = NewV;
                G->Edge++;
            }
        }
    }
    return;
}

/*��ͼ���ڽӱ����Graph*/
void ToString(Graph * G)
{
    if (G == NULL) return;
    for (int i = 0; i < G->Vertices; i++)
    {
        printf("%d : ", i);
        GNode* p = GetGNode(G, i);
        for (int j = 0; j < GetSize(G->pBase[i]); j++)
        {
            p = p->Next;
            PRINT_INT(p->Key);
        }
        PRINT_STRING("");
    }
    return;
}

/*(�ڲ�����)���ص�ǰGNode�ı�����*/
/*pBase_x ������G->pBase[i]�Ĳ��� */
int GetSize(int* pBase_x)
{
    GNode* p = ((GNode*)pBase_x);
    int ret = 0;
    while (p->Next) {
        p = p->Next;
        ret++;
    }
    return ret;
}

/*(�ڲ�����)����Node*/
/*key ����Ҫ��ȡ��ӦKey��GNode*/
GNode* GetGNode(Graph * G, int key)
{
    if (key < G->Vertices) {
        return (GNode*)G->pBase[key];
    }
    return NULL;
}

/*ͼ�Ķ�������*/
int GetVerticesCount(Graph * G)
{
    if (G) return G->Vertices;
    else return 0;
}

/*ͼ�ı�����*/
int GetEdgeCount(Graph * G)
{
    if (G) return G->Edge;
    else return 0;
}

/*����ͼ�����ж���Key*/
void Traverse_ALLKEY(Graph * G)
{
    if (G == NULL) return;

    PRINT_STRING("���µ������ж����KEY");
    for (int i = 0; i < G->Vertices; i++) {
        PRINT_INT(i);
    }
    PRINT_STRING("\n--------------------");
    return;


}
