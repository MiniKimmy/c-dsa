typedef struct LNode {
    int data;
    struct LNode* next;
}LNode;

typedef struct {
    LNode* head;
    LNode* tail;
    int count;
} SLinkList;

#pragma region SLinkListFunctions
SLinkList* initSLinkList();
int Add(SLinkList* L, int value);
int* getValueSLinkList(SLinkList* L, int index);
int setValueSLinkList(SLinkList * L, int index, int value);
int insert(SLinkList* L, int index, int value);
int RemoveAt(SLinkList* L, int index);
int clearSLinkList(SLinkList* L);
int destroySLinkList(SLinkList** L);
#pragma endregion

SLinkList* initSLinkList()
{
    LNode* node = (LNode*)malloc(sizeof(LNode));
    SLinkList* sLinkList = (SLinkList*)malloc(sizeof(SLinkList));
    node->next = NULL;
    sLinkList->head = node;
    sLinkList->tail = node;
    sLinkList->count = 0;

    return sLinkList;
}

int Add(SLinkList* L, int value)
{
    if (L == NULL) return 0;

    LNode* node = (LNode*)malloc(sizeof(LNode));
    node->data = value;
    node->next = NULL;
    if (L->head == L->tail) {
        L->tail = node;
        L->head->next = node;
    }
    else {
        L->tail->next = node;
        L->tail = node;
    }

    L->count++;
    return 1;
}

int* getValueSLinkList(SLinkList* L, int index)
{
    if (L == NULL || L->count <= 0 || index >= L->count || index < 0) return NULL;
    LNode* node = L->head;
    for (int i = 0; i < L->count; i++)
    {
        node = node->next;
        if (i == index) {
            return &(node->data);
        }
    }
}

int setValueSLinkList(SLinkList* L, int index, int value)
{
    if (L == NULL || L->count <= 0 || index >= L->count || index < 0) return 0;
    LNode* node = L->head;
    for (int i = 0; i < L->count; i++)
    {
        node = node->next;
        if (i == index) {
            node->data = value;
            return 1;
        }
    }
    return -1;
}

int insert(SLinkList* L, int index, int value)
{
    if (L == NULL || L->count <= 0 || index >= L->count || index < 0) return 0;

    LNode* p = L->head;
    for (int i = 0; i < index; i++) {
        p = p->next;
    }

    LNode* q = (LNode*)malloc(sizeof(LNode));
    q->data = value;
    q->next = p->next;
    p->next = q;
    L->count++;
    return 1;
}

int RemoveAt(SLinkList* L, int index)
{
    if (L == NULL || L->count <= 0 || index >= L->count || index < 0) return 0;

    LNode* p = L->head;
    for (int i = 0; i < index; i++) {
        p = p->next;
    }

    if (p->next == L->tail) L->tail = p;

    LNode* q = p->next;
    p->next = q->next;
    free(q);
    L->count--;
    return 1;
}

int clearSLinkList(SLinkList* L)
{
    if (L == NULL || L->count <= 0) return 0;

    void** arr = (void**)malloc(sizeof(LNode**) * L->count);
    LNode* node = L->head;
    for (int i = 0; i < L->count; i++) {
        node = node->next;
        arr[i] = (void*)node;
    }

    for (int i = 0; i < L->count; i++) {
        free((LNode*)arr[i]);
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
