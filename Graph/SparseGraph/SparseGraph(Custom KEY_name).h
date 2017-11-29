#pragma once
#include<stdlib.h>
#include<stdio.h>
#define PRINT_INT(x) printf("%d ",x)
#define PRINT_STRING(x) printf("%s\n",x)


typedef struct GNode {
    int Key;
    struct GNode *Next;    //���ַ��ok
}GNode;

typedef struct Graph {
    int VerticesCount;    //�����ܸ���
    int EdgeCount;        //�ߵ��ܸ���
    int** pBase;          //var����
}Graph;


#pragma region Functions
Graph* InitGraph(int V);
void CreateGraph_ByInputKeyCode(Graph* G);
void AddEdge(Graph* G, int v, int w);
void ToString(Graph * G);
void Traverse_ALLKEY(Graph* G);
void InsertGNode(GNode* v, GNode* w);
int GetSize(int* pBaseValue);
GNode* GetGNode(Graph* G, int key);
int GetKey(int* pBaseValue);
#pragma endregion


/*��ʼ��Graph*/
/*�����հ׶��㣬���ֶ���ֵKEY��δ����*/
Graph* InitGraph(int V)
{
    Graph* ret = (Graph*)malloc(sizeof(Graph));
    if (ret == NULL) {
        printf("Graph��ʼ����̬�����ڴ�ʧ��\n");
        exit(-1);
    }
    ret->VerticesCount = V;
    ret->EdgeCount = 0;
    //�����Ŷ���ָ������飨���ٸ������ Ҫ���ٸ�int*)
    ret->pBase = (int**)malloc(sizeof(int*) * V);
    //�����Ŷ���ָ���ֵ������
    *(ret->pBase) = (int*)malloc(sizeof(int));

    //Ϊÿ���հ׶��㸳ֵKEY
    int m_Key;
    int temp = 0;
    for (int i = 0; temp < ret->VerticesCount; i++){
        GNode* NewNode = (GNode*)malloc(sizeof(GNode));
        if (NewNode == NULL) {
            printf("NewNode��ʼ����̬�����ڴ�ʧ��\n");
            exit(-1);
        }
        NewNode->Next = NULL;
        printf("�������[%d]�������KEY : ", i);
        scanf_s("%d", &m_Key);
        while (temp != 0 && m_Key == GetKey(ret->pBase[i - 1]))
        {
            printf("�����ظ�KEY,���������[%d]�������KEY : ", i);
            scanf_s("%d", &m_Key);
        }
        NewNode->Key = m_Key;
        temp++;
        ret->pBase[i] = (int*)(NewNode);
    }
    return ret;
}

/*��Grapth�Ķ�����������*/
void CreateGraph_ByInputKeyCode(Graph * G)
{
    Traverse_ALLKEY(G);
    printf("��������Ҫ���Edge�ĸ��� �� ");
    int m_Edge;
    scanf_s("%d",&m_Edge);
    for (int i = 0; i < m_Edge; i++)
    {
        PRINT_STRING("\n��������Ҫ���ӵ�2��Node��KEY");
        int v, w;
        scanf_s("%d", &v);
        scanf_s("%d", &w);
        AddEdge(G, v, w);

        if (G->EdgeCount > i) {
            printf("�������� %d ������\n", G->EdgeCount);
        }else {
            i = i == 0 ? 0 : --i;
            PRINT_STRING("δ���ӳɹ�,����������");
        }
    }
    return;
}

/*������������*/
/*v�ǵ�ǰ�Ķ��㣬w����������*/
void AddEdge(Graph * G,int v, int w)
{
    GNode* V = GetGNode(G, v);
    GNode* W = GetGNode(G, w);
    if (V && W) {
        InsertGNode(V, W);
        G->EdgeCount++;
    }
    return;
}

/*����ͼ�����ж���Key*/
void Traverse_ALLKEY(Graph * G)
{
    if (G == NULL) return;

    PRINT_STRING("���µ������ж����KEY");
    for (int i = 0; i < G->VerticesCount; i++){
        PRINT_INT(GetKey(G->pBase[i]));
    }
    PRINT_STRING("\n--------------------");
    return;
}

/*��ͼ���ڽӱ����Graph*/
void ToString(Graph * G)
{
    if (G == NULL) return;
    for (int i = 0; i < G->VerticesCount; i++)
    {
        int m_key = GetKey(G->pBase[i]);
        printf("%d : ", m_key);
        GNode* p = GetGNode(G, m_key);
        for (int j = 0; j < GetSize(G->pBase[i]); j++)
        {
            p = p->Next;
            PRINT_INT(p->Key);
        }
        printf("\n");
    }
    return;
}

/*���ڲ���������������ǰ������µ�GNode*/
void InsertGNode(GNode* v, GNode* w)
{
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
    NewV->Key = w->Key;
    NewW->Key = v->Key;

    GNode* p = v->Next;
    NewV->Next = p;
    v->Next = NewV;
    p = w->Next;
    NewW->Next = p;
    w->Next = NewW;
    return;
}

/*(�ڲ�����)���ص�ǰGNode�ı�����*/
/*pBaseValue ������G->pBase[i]�Ĳ��� */
int GetSize(int* pBaseValue)
{
    GNode* p = ((GNode*)pBaseValue);
    int ret = 0;
    while (p->Next){
        p = p->Next;
        ret++;
    }
    return ret;
}

/*(�ڲ�����)����key*/
/*pBaseValue ������G->pBase[i]�Ĳ��� */
int GetKey(int* pBaseValue)
{
    return ((GNode*)pBaseValue)->Key;
}

/*(�ڲ�����)����Node*/
/*key ����Ҫ��ȡ��ӦKey��GNode*/
GNode* GetGNode(Graph * G,int key)
{
    for (int i = 0; i < G->VerticesCount; i++)
    {
        if (GetKey(G->pBase[i]) == key) {
            return (GNode*)G->pBase[i];
        }
    }
    return NULL;
}
