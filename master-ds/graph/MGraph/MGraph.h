#define VERSIZE 20
#define EXITTAG -2018
#define SETINFO 0          //1��ʾ��������GNode.info,0��ʾ������GNode.info
#define STANDARDVARCHAR 50 //50��0~49��,����info������ַ�����
#define DOUBLEDIR 0        //0��ʾ����ͼ,1��ʾ����ͼ

#include<stdio.h>
#include<stdlib.h>
#if SETINFO==1
    #include"string.h"
#endif

typedef struct GNode{
    int key;   //Ĭ��Key��1��ʼ����
#if SETINFO==1
    String* info;
#endif
}GNode;

typedef struct {
    int v;
    int e;
    GNode* vertexs;
    int** edges;
}MGraph;

#pragma region MGraphFunctions
MGraph* initMGraph(int v);
void createMGraphByKeys(MGraph* G);
void descMGraph(MGraph* G);
int addEdgeMGraph(MGraph* G, int v, int w);
int checkCollectedMGraph(MGraph* G, int w, int v);
int checkEdgesMGraph(MGraph* G, int e);
int checkvertexsMGraph(MGraph* G, int v);
void traverseMGraph(MGraph* G);
#pragma endregion

MGraph* initMGraph(int v)
{
    if (v <= 0) return NULL;

    MGraph* graph = (MGraph*)malloc(sizeof(MGraph));
    graph->v = v;
    graph->e = 0;
    graph->vertexs = (GNode*)malloc(sizeof(GNode) * v);
    graph->edges = (int**)malloc(sizeof(int*) * v);

    for (int i = 0; i < v; i++) {
        graph->vertexs[i].key = i + 1;
        graph->edges[i] = (int*)malloc(sizeof(int) * v);
        for (int j = 0; j < v; j++){
            if (i == j)graph->edges[i][j] = 1; //Ĭ����������������
            else graph->edges[i][j] = 0;
        }
#if SETINFO==1
        char* s[STANDARDVARCHAR];
        printf("�������[%d]�����������info: ",i+1);
        gets_s(s, STANDARDVARCHAR-1);
        if (equalsStr(s, "-2018")) exit(0);
        graph->vertexs[i].info = charArrayToString(s);
#endif
    }

    return graph;
}

void createMGraphByKeys(MGraph* G)
{
    if (G == NULL) return;
    descMGraph(G);

    int e;
    printf("(����-2018�˳�)��������Ҫ���ӵ��ܱ���edge: ");
    scanf_s("%d", &e);

    while (!checkEdgesMGraph(G, e)) {
        scanf_s("%d", &e);
    }

    int w, v;
    for (int i = 0; i < e; i++){

        printf("�������[%d]������Ҫ���ӵĵ�1������: ",i);
        scanf_s("%d", &w);

        while (!checkvertexsMGraph(G, w)) {
            printf("\t���ٴ�������Ҫ���ӵĵ�1������: ");
            scanf_s("%d", &w);
        }

        printf("�������[%d]������Ҫ���ӵĵ�2������: ",i);
        scanf_s("%d", &v);
        while (!checkvertexsMGraph(G, v)) {
            printf("\t����������Ҫ���ӵĵ�2������,�յ�1��������\'%d\',: ", w);
            scanf_s("%d", &v);
        }

        if (addEdgeMGraph(G, w, v) == 1) {
            printf("-->> connect sucessfully! <<-- %d-%d\n", w, v);
        }else {
            printf("-->> %d-%d�Ѿ�����,����������2������ <<--\n", w, v);
            --i;
        }
    }

    G->e = e;
    return;
}

int addEdgeMGraph(MGraph* G, int w, int v)
{
    if (G == NULL) {
        printf("NullReferenceException. method:'addEdgeMGraph'.");
        return -1;
    }

    if (checkCollectedMGraph(G, w, v) == 0) {
        G->edges[w-1][v-1] = 1;
#if DOUBLEDIR == 1
        G->edges[v-1][w-1] = 1;
#endif
        return 1;
    }
    return 0;
}

int checkCollectedMGraph(MGraph* G, int w,int v)
{
    if (G == NULL || G->edges == NULL) exit(0);
    return G->edges[w-1][v-1];
}

int checkEdgesMGraph(MGraph* G, int e)
{
    if (e == EXITTAG || G==NULL) exit(0);

    if (e < 0) {
        printf("%d<0, ���������0���ܱ���edge: ", e);
        return 0;
    }
#if DOUBLEDIR == 1
    int maxEdges = G->v * 2;
#endif

#if DOUBLEDIR == 0
    int maxEdges = 0;
    for (int i=G->v-1; i > 0 ; i--)
        maxEdges += i;
#endif

    if (e > maxEdges) {
#if DOUBLEDIR == 0
        printf("����ͼ: ");
#endif

#if DOUBLEDIR == 1
        printf("����ͼ: ");
#endif
        printf("%d��������������:%d,�����������ܱ���edge: ", G->v,maxEdges);
        return 0;
    }

    return 1;
}

int checkvertexsMGraph(MGraph* G, int v) {

    if (G == NULL || v == EXITTAG) exit(0);

    if (v > G->v || v <= 0) {
        printf("\n----------------\nֻ������[1]~[%d]��Χ�Ķ���,��\'%d\'����\n", G->v, v);
        return 0;
    }

}

void descMGraph(MGraph* G) {
    if (G == NULL) return;

    printf("--------MGRAPH-------\n");
    printf("KEY:\n");
    for (int i = 0; i < G->v; i++){
#if SETINFO == 1
        printf("key[%d], info: %s\n", i + 1, G->vertexs[i].info->ch);
#endif

#if SETINFO == 0
        printf("[%d]\n",i);
#endif
    }

    printf("---------------------\n");
}

void traverseMGraph(MGraph* G)
{
    if (G == NULL) return;

    for (int i = 0; i < G->v; i++){
        printf("KEY[%d]: ", G->vertexs[i].key);
        for (int j = 0; j < G->v; j++)
        {
            printf("[%d][%d]=%d\t", G->vertexs[i].key, G->vertexs[j].key, G->edges[i][j]);
        }
        printf("\n");
    }
}
