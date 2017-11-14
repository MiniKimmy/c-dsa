#pragma once
#include<stdlib.h>
#include<stdio.h>
#define PRINT_INT(x) printf("%d ",x)
#define PRINT_STRING(x) printf("%s\n",x)

#pragma region SparseGraph
typedef struct GNode {
    int Key;
    struct GNode *Next;    //存地址就ok
}GNode;

//是否重边
typedef enum EdgeType
{
    RepeatEdge,
    Non_RepeatEdge,
}EdgeType;

typedef struct Graph {
    int Vertices;        //顶点总个数
    int Edge;            //边的总个数
    int** pBase;        //存放GNode*地址的数组
    EdgeType EdgeType;    //是否重边
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

/*初始化Graph*/
/*V: 顶点总数; EdgeType枚举类型: 是否重边*/
/*RepeatEdge: 重边; Non_RepeatEdge: 不重边*/
Graph* InitGraph(int V, EdgeType edgetype)
{
    Graph* ret = (Graph*)malloc(sizeof(Graph));
    if (ret == NULL) {
        printf("Graph初始化动态分配内存失败\n");
        exit(-1);
    }
    ret->Vertices = V;
    ret->Edge = 0;
    ret->pBase = (int**)malloc(sizeof(int*) * V);
    ret->EdgeType = edgetype;

    //每一个int*都要赋值一个GNode*的地址
    for (int i = 0; i < ret->Vertices; i++) {
        ret->pBase[i] = (int*)malloc(sizeof(GNode));
        if (ret->pBase[i] == NULL) {
            printf("pBase[i]初始化动态分配内存失败\n");
            exit(-1);
        }
        ((GNode*)ret->pBase[i])->Next = NULL;
    }
    return ret;
}

/*把Grapth的顶点链接起来*/
void CreateGraph_ByInputKeyCode(Graph * G)
{
    Traverse_ALLKEY(G);
    printf("请输入需要添加Edge的个数 ： ");
    int m_Edge;
    scanf_s("%d", &m_Edge);
    for (int i = 0; i < m_Edge; i++)
    {
        PRINT_STRING("\n请输入需要连接的2个Node的KEY");
        int v, w;
        scanf_s("%d", &v);
        scanf_s("%d", &w);
        AddEdge(G, v, w);
        if (G->Edge > i) {
            printf("已连接了 %d 个链接\n", G->Edge);
        }
        else {
            i = i == 0 ? 0 : --i;
            PRINT_STRING("未链接成功,请重新输入");
        }
    }
    return;
}

/*链接两个顶点*/
/*v是当前的顶点，w是其他顶点*/
void AddEdge(Graph * G, int v, int w)
{
    if (v < G->Vertices && w < G->Vertices)
    {
        GNode* V = GetGNode(G, v);
        if (G->EdgeType == RepeatEdge) {
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
            int flag = 1;            //标志位
            GNode* p = V->Next;        //迭代Item
            for (int i = 0; i < GetSize(G->pBase[v]); i++) {
                if (p->Key == w) flag = 0;
            }
            if (flag) {
                GNode* NewV = (GNode*)malloc(sizeof(GNode));
                if (NewV == NULL) {
                    printf("NewV初始化动态分配内存失败\n");
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

/*以图的邻接表输出Graph*/
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

/*(内部方法)返回当前GNode的边数量*/
/*pBase_x ：传入G->pBase[i]的参数 */
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

/*(内部方法)返回Node*/
/*key ：需要获取对应Key的GNode*/
GNode* GetGNode(Graph * G, int key)
{
    if (key < G->Vertices) {
        return (GNode*)G->pBase[key];
    }
    return NULL;
}

/*图的顶点总数*/
int GetVerticesCount(Graph * G)
{
    if (G) return G->Vertices;
    else return 0;
}

/*图的边总数*/
int GetEdgeCount(Graph * G)
{
    if (G) return G->Edge;
    else return 0;
}

/*遍历图内所有顶点Key*/
void Traverse_ALLKEY(Graph * G)
{
    if (G == NULL) return;

    PRINT_STRING("以下的是所有顶点的KEY");
    for (int i = 0; i < G->Vertices; i++) {
        PRINT_INT(i);
    }
    PRINT_STRING("\n--------------------");
    return;


}
