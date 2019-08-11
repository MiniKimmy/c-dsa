#define VERSIZE 20
#define EXITTAG -2018
#define DOUBLEDIR 1    //0��ʾ����ͼ,1��ʾ����ͼ
#include"linklist.h"

typedef struct {
    int v;
    int e;
    SLinkList** vertexs;
}AGraph;

#pragma region AGraphFunctions
AGraph* initAGraph(int v);
void createAGraphByKeys(AGraph* G);
int addEdgeAGraph(AGraph* G, int w, int v);
SLinkList* getVNodeAgraph(AGraph* G, int v);
void descAGraph(AGraph* G);
int checkCollectedAGraph(AGraph* G, int w, int v);
int checkEdgesAGraph(AGraph* G, int e);
int checkvertexsAGraph(AGraph* G, int v);
void traverseAGraph(AGraph* G);
#pragma endregion

AGraph* initAGraph(int v) {
    if (v <= 0) return NULL;

    AGraph* graph = (AGraph*)malloc(sizeof(AGraph));
    graph->v = v;
    graph->e = 0;
    graph->vertexs = (SLinkList**)malloc(sizeof(SLinkList*) * v);
    for (int i = 0; i < v; i++) {
        graph->vertexs[i] = initSLinkList();
        graph->vertexs[i]->head->v = i + 1;
    }

    return graph;
}

void createAGraphByKeys(AGraph* G) {
    if (G == NULL) return;
    descAGraph(G);

    int e;
    printf("(����-2018�˳�)��������Ҫ���ӵ��ܱ���edge: ");
    scanf_s("%d", &e);

    while (!checkEdgesAGraph(G, e)) {
        scanf_s("%d", &e);
    }

    int w, v;
    for (int i = 0; i < e; i++) {
        printf("�������[%d]������Ҫ���ӵĵ�1������: ", i);
        scanf_s("%d", &w);
        while (!checkvertexsAGraph(G, w)) {
            printf("\t���ٴ�������Ҫ���ӵĵ�1������: ");
            scanf_s("%d", &w);
        }

        printf("�������[%d]������Ҫ���ӵĵ�2������: ", i);
        scanf_s("%d", &v);
        while (!checkvertexsAGraph(G, v)) {
            printf("\t����������Ҫ���ӵĵ�2������,�յ�1��������\'%d\',: ", w);
            scanf_s("%d", &v);
        }

        if (addEdgeAGraph(G, w, v) == 1) {
            printf("-->> connect sucessfully! <<-- %d-%d\n", w, v);
        }
        else {
            printf("-->> %d-%d�Ѿ�����,����������2������ <<--\n", w, v);
            --i;
        }
    }

    G->e = e;
    return;
}

int checkEdgesAGraph(AGraph* G, int e) {
    if (e == EXITTAG || G == NULL) exit(0);

    if (e < 0) {
        printf("%d<0, ���������0���ܱ���edge: ", e);
        return 0;
    }
#if DOUBLEDIR == 1
    int maxEdges = G->v * 2;
#endif  

#if DOUBLEDIR == 0
    int maxEdges = 0;
    for (int i = G->v - 1; i > 0; i--)
        maxEdges += i;
#endif 

    if (e > maxEdges) {
#if DOUBLEDIR == 0
        printf("����ͼ: ");
#endif
#if DOUBLEDIR == 1
        printf("����ͼ: ");
#endif
        printf("%d��������������:%d,�����������ܱ���edge: ", G->v, maxEdges);
        return 0;
    }

    return 1;
}

int checkvertexsAGraph(AGraph* G, int v) {
    if (G == NULL || v == EXITTAG) exit(0);

    if (v > G->v || v <= 0) {
        printf("\n----------------\nֻ������[1]~[%d]��Χ�Ķ���,��\'%d\'����\n", G->v, v);
        return 0;
    }
    return 1;
}

int addEdgeAGraph(AGraph* G, int w, int v) {
    if (G == NULL) {
        printf("NullReferenceException. method:'addEdgeMGraph' ");
        return -1;
    }

    if (w == v) return 0;
    if (!checkCollectedAGraph(G, w, v)) {
        SLinkList* w_list = getVNodeAgraph(G, w);
        add(w_list, v);
#if DOUBLEDIR == 0
        return 1;
#endif
    }

#if DOUBLEDIR == 1
    if (!checkCollectedAGraph(G, v, w)) {
        SLinkList* v_list = getVNodeAgraph(G, v);
        add(v_list, w);
        return 1;
    }
#endif
    return 0;
}

int checkCollectedAGraph(AGraph* G, int w, int v) {
    if (G == NULL) exit(0);
    return hasElement(getVNodeAgraph(G, w), v);
}

SLinkList* getVNodeAgraph(AGraph* G, int v) {
    if (G == NULL || v > G->v || v <= 0) return NULL;
    else return G->vertexs[v - 1];
}

void descAGraph(AGraph* G) {
    if (G == NULL) return;

    printf("KEY: ");
    for (int i = 0; i < G->v; i++) {
        printf("%d ", i + 1);
    }
    printf("\n");
}


void traverseAGraph(AGraph* G) {
    if (G == NULL) return;

    for (int i = 0; i < G->v; i++) {
        SLinkList* list = getVNodeAgraph(G, i + 1);
        printf("KEY[%d]: ", list->head->v);
        ArcNode* p = list->head;
        while (p->next) {
            p = p->next;
            printf("[%d], ", p->v);
        }
        printf("\n");
    }
}
