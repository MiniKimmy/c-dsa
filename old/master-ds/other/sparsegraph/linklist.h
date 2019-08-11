#include<stdlib.h>
#include<stdio.h>

typedef struct ArcNode {
    int v;
    struct ArcNode* next;
}ArcNode;

typedef struct SLinkList {
    ArcNode* head;
    ArcNode* tail;
    int count;
}SLinkList;

#pragma region SLinkListFunctions
SLinkList* initSLinkList();
int add(SLinkList* L, int value);
int* getValueSLinkList(SLinkList* L, int index);
int setValueSLinkList(SLinkList * L, int index, int value);
int insert(SLinkList* L, int index, int value);
int removeAt(SLinkList* L, int index);
int hasElement(SLinkList* L, int value);
int clearSLinkList(SLinkList* L);
int destroySLinkList(SLinkList** L);
#pragma endregion

SLinkList* initSLinkList()
{
    ArcNode* node = (ArcNode*)malloc(sizeof(ArcNode));
    SLinkList* sLinkList = (SLinkList*)malloc(sizeof(SLinkList));
    node->next = NULL;
    sLinkList->head = node;
    sLinkList->tail = node;
    sLinkList->count = 0;

    return sLinkList;
}

int add(SLinkList* L, int value)
{
    if (L == NULL) return 0;

    ArcNode* node = (ArcNode*)malloc(sizeof(ArcNode));
    node->v = value;
    node->next = NULL;
    if (L->head == L->tail) {
        L->tail = node;
        L->head->next = node;
    }else {
        L->tail->next = node;
        L->tail = node;
    }

    L->count++;
    return 1;
}

int* getValueSLinkList(SLinkList* L, int index)
{
    if (L == NULL || L->count <= 0 || index >= L->count || index < 0) return NULL;

    ArcNode* node = L->head;
    for (int i = 0; i < L->count; i++)
    {
        node = node->next;
        if (i == index) {
            return &(node->v);
        }
    }

    return NULL;
}

int setValueSLinkList(SLinkList* L, int index, int value)
{
    if (L == NULL || L->count <= 0 || index >= L->count || index < 0) return 0;
    ArcNode* node = L->head;
    for (int i = 0; i < L->count; i++)
    {
        node = node->next;
        if (i == index) {
            node->v = value;
            return 1;
        }
    }
    return -1;
}

int insert(SLinkList* L, int index, int value)
{
    if (L == NULL || L->count <= 0 || index >= L->count || index < 0) return 0;

    ArcNode* p = L->head;
    for (int i = 0; i < index; i++) {
        p = p->next;
    }

    ArcNode* q = (ArcNode*)malloc(sizeof(ArcNode));
    q->v = value;
    q->next = p->next;
    p->next = q;
    L->count++;
    return 1;
}

int removeAt(SLinkList* L, int index)
{
    if (L == NULL || L->count <= 0 || index >= L->count || index < 0) return 0;

    ArcNode* p = L->head;
    for (int i = 0; i < index; i++) {
        p = p->next;
    }

    if (p->next == L->tail) L->tail = p;

    ArcNode* q = p->next;
    p->next = q->next;
    free(q);
    L->count--;
    return 1;
}

int hasElement(SLinkList* L, int value) {
    if (L == NULL || L->count == 0) return 0;

    ArcNode* p = L->head;
    while (p->next) {
        p = p->next;
        if (p->v == value) {
            return 1;
        }
    }
    return 0;
}

int clearSLinkList(SLinkList* L)
{
    if (L == NULL || L->count <= 0) return 0;

    void** arr = (void**)malloc(sizeof(ArcNode**) * L->count);
    ArcNode* node = L->head;
    for (int i = 0; i < L->count; i++) {
        node = node->next;
        arr[i] = (void*)node;
    }

    for (int i = 0; i < L->count; i++) {
        free((ArcNode*)arr[i]);
        arr[i] = NULL;
    }

    L->count = 0;
    L->tail = L->head;
    return 1;
}


int destroySLinkList(SLinkList** L)
{
    if (*L == NULL) return 0;
    clearSLinkList(*L);

    free((*L)->head); // don't free((*L)->tail) again --because same point.
    (*L)->head = NULL;
    (*L)->tail = NULL;
    free(*L);
    *L = NULL;
    return 1;
}
