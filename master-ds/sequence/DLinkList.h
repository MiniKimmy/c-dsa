#include<stdlib.h>
#include<stdio.h>

typedef struct DLNode {
    int data;
    struct DLNode* next;
    struct DLNode* prior;
}DLNode;

typedef struct {
    DLNode* head;
    DLNode* tail;
    int count;
}DLinkList;

#pragma region DLinkListFunctions
DLinkList* initDLinkList();
int Add(DLinkList* L, int value);
int* getValueDLinkList(DLinkList* L, int index);
int setValueDLinkList(DLinkList * L, int index, int value);
int insert(DLinkList* L, int index, int value);
int RemoveAt(DLinkList* L, int index);
int clearDLinkList(DLinkList* L);
int destroyDLinkList(DLinkList** L);
#pragma endregion


DLinkList* initDLinkList()
{
    DLinkList* dList = (DLinkList*)malloc(sizeof(DLinkList));
    DLNode* head = (DLNode*)malloc(sizeof(DLNode));
    head->next = NULL;
    head->prior = NULL;
    dList->head = head;
    dList->tail = head;
    dList->count = 0;
    return dList;
}

int Add(DLinkList* L, int value)
{
    if (L == NULL) return 0;

    DLNode* p = (DLNode*)malloc(sizeof(DLNode));
    p->data = value;
    p->next = NULL;
    if (L->tail == NULL) {
        L->tail = p;
        p->prior = L->head;
        L->head->next = p;
    }else {
        L->tail->next = p;
        p->prior = L->tail;
        L->tail = p;
    }

    L->count++;
    return 1;

}

int* getValueDLinkList(DLinkList* L, int index)
{
    if (L == NULL || L->count <= 0 || index >= L->count || index < 0) return NULL;

    DLNode* p;
    if (index >= L->count / 2) {
        p = L->tail;
        for (int i = L->count-1; i > index; i--) p = p->prior;
    }else {
        p = L->head;
        for (int i = 0; i < index; i++) p = p->next;
        p = p->next;
    }
    return &(p->data);
}

int setValueDLinkList(DLinkList * L, int index, int value)
{
    if (L == NULL || L->count <= 0 || index >= L->count || index < 0) return 0;

    DLNode* p;
    if (index >= L->count / 2) {
        p = L->tail;
        for (int i = L->count - 1; i > index; i--) p = p->prior;
    }else {
        p = L->head;
        for (int i = 0; i < index; i++) p = p->next;
        p = p->next;
    }

    p->data = value;
    return 1;
}

int insert(DLinkList* L, int index, int value)
{
    if (L == NULL || L->count <= 0 || index >= L->count || index < 0) return 0;

    DLNode* p;
    if (index >= L->count / 2) {
        p = L->tail;
        for (int i = L->count - 1; i > index; i--) p = p->prior;
        p = p->prior;
    }else {
        p = L->head;
        for (int i = 0; i < index; i++) p = p->next;
    }
    DLNode* q = (DLNode*)malloc(sizeof(DLNode));
    q->data = value;

    q->next = p->next;
    q->next->prior = q;
    q->prior = p;
    p->next = q;
    L->count++;
    return 1;
}

int RemoveAt(DLinkList* L, int index)
{
    if (L == NULL || L->count <= 0 || index >= L->count || index < 0) return 0;

    DLNode* p;
    if (index >= L->count / 2) {
        p = L->tail;
        for (int i = L->count - 1; i > index; i--) p = p->prior;
        p = p->prior;
    }else {
        p = L->head;
        for (int i = 0; i < index; i++) p = p->next;
    }

    DLNode* q = p->next;
    if (q == L->tail) {
        L->tail = q->prior;
        p->next = NULL;
    }else {
        p->next = q->next;
        q->next->prior = p;
    }

    free(q);
    q = NULL;
    L->count--;
    return 1;

}

int clearDLinkList(DLinkList* L)
{
    if (L == NULL) return 0;

    DLNode* p = L->tail;
    while (p != L->head) {
        DLNode* q = p;
        p = p->prior;
        free(q);
        q = NULL;
    }
    L->head->next = NULL;
    L->tail = L->head;
    L->count = 0;
    return 1;
}


int destroyDLinkList(DLinkList** L)
{
    if (clearDLinkList(*L) == 0) return 0;
    free((*L)->head);
    (*L)->head = NULL;    
    (*L)->tail = NULL;
    free(*L);
    *L = NULL;
    return 1;
}
