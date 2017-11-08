#pragma once
#include<stdlib.h>
#include<stdio.h>
#define PRINT_INT(x) printf("%d ",x)
#define PRINT_STRING(x) printf("%s\n",x)


typedef struct GNode {
    int Key;
    struct GNode *Next;    //存地址就ok
}GNode;

typedef struct Graph {
    int VerticesCount;    //顶点总个数
    int EdgeCount;        //边的总个数
    int** pBase;          //var数组
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


/*初始化Graph*/
/*创建空白顶点，需手动赋值KEY但未链接*/
Graph* InitGraph(int V)
{
    Graph* ret = (Graph*)malloc(sizeof(Graph));
    if (ret == NULL) {
        printf("Graph初始化动态分配内存失败\n");
        exit(-1);
    }
    ret->VerticesCount = V;
    ret->EdgeCount = 0;
    //分配存放顶点指针的数组（多少个顶点就 要多少个int*)
    ret->pBase = (int**)malloc(sizeof(int*) * V);
    //分配存放顶点指针的值的数组
    *(ret->pBase) = (int*)malloc(sizeof(int));

    //为每个空白顶点赋值KEY
    int m_Key;
    int temp = 0;
    for (int i = 0; temp < ret->VerticesCount; i++){
        GNode* NewNode = (GNode*)malloc(sizeof(GNode));
        if (NewNode == NULL) {
            printf("NewNode初始化动态分配内存失败\n");
            exit(-1);
        }
        NewNode->Next = NULL;
        printf("请输入第[%d]个顶点的KEY : ", i);
        scanf_s("%d", &m_Key);
        while (temp != 0 && m_Key == GetKey(ret->pBase[i - 1]))
        {
            printf("不可重复KEY,请再输入第[%d]个顶点的KEY : ", i);
            scanf_s("%d", &m_Key);
        }
        NewNode->Key = m_Key;
        temp++;
        ret->pBase[i] = (int*)(NewNode);
    }
    return ret;
}

/*把Grapth的顶点链接起来*/
void CreateGraph_ByInputKeyCode(Graph * G)
{
    Traverse_ALLKEY(G);
    printf("请输入需要添加Edge的个数 ： ");
    int m_Edge;
    scanf_s("%d",&m_Edge);
    for (int i = 0; i < m_Edge; i++)
    {
        PRINT_STRING("\n请输入需要连接的2个Node的KEY");
        int v, w;
        scanf_s("%d", &v);
        scanf_s("%d", &w);
        AddEdge(G, v, w);

        if (G->EdgeCount > i) {
            printf("已连接了 %d 个链接\n", G->EdgeCount);
        }else {
            i = i == 0 ? 0 : --i;
            PRINT_STRING("未链接成功,请重新输入");
        }
    }
    return;
}

/*链接两个顶点*/
/*v是当前的顶点，w是其他顶点*/
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

/*遍历图内所有顶点Key*/
void Traverse_ALLKEY(Graph * G)
{
    if (G == NULL) return;

    PRINT_STRING("以下的是所有顶点的KEY");
    for (int i = 0; i < G->VerticesCount; i++){
        PRINT_INT(GetKey(G->pBase[i]));
    }
    PRINT_STRING("\n--------------------");
    return;
}

/*以图的邻接表输出Graph*/
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

/*（内部方法）在链表最前面插入新的GNode*/
void InsertGNode(GNode* v, GNode* w)
{
    GNode* NewV = (GNode*)malloc(sizeof(GNode));
    if (NewV == NULL) {
        printf("NewV初始化动态分配内存失败\n");
        exit(-1);
    }
    GNode* NewW = (GNode*)malloc(sizeof(GNode));
    if (NewW == NULL) {
        printf("NewW初始化动态分配内存失败\n");
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

/*(内部方法)返回当前GNode的边数量*/
/*pBaseValue ：传入G->pBase[i]的参数 */
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

/*(内部方法)返回key*/
/*pBaseValue ：传入G->pBase[i]的参数 */
int GetKey(int* pBaseValue)
{
    return ((GNode*)pBaseValue)->Key;
}

/*(内部方法)返回Node*/
/*key ：需要获取对应Key的GNode*/
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
