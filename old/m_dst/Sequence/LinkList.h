#include<stdio.h>
#include<stdlib.h>
#define PRINT_STRING(x) printf("%s\n",x)


typedef int TElement;     //import到其他文件时候需要修改该类型


/*Bool枚举*/
typedef enum Status {
    FALSE,
    TRUE,
}Status;

/*LinkList类型枚举*/
typedef enum LinkListType{
    SINGLEWAY,
    DOUBLEWAY,
}LinkListType;

/*结点Node数据类型*/
typedef struct Node {
    TElement data;
    struct Node* next;
    struct Node* front;
}Node;

typedef struct LinkList {
    int count;
    Node* head;
    Node* tail;
    LinkListType type;
}LinkList;

#pragma region Functions
LinkList* InitLinkList();
Status IsEmpty_LinkList(LinkList * L);
void Traverse_LinkList(LinkList * L);
TElement* GetFirst_LinkList(LinkList * L);
TElement* GetValue_LinkList(LinkList * L, int index);
void SetValue_LinkList(LinkList * L, int index, TElement value);
void Append_LinkList(LinkList * L, TElement value);
int GetSize_LinkList(LinkList * L);
void Inversion_LinkList(LinkList * L);
void Insert_LinkList(LinkList * L, int index, TElement value);
void Remove_LinkList(LinkList * L);
void Delete_LinkList(LinkList * L, int index);
void Clear_LinkList(LinkList * L);
void Destroy_LinkList(LinkList** L);
#pragma endregion

/*初始化LinkList.[默认双向LinkList]*/
LinkList* InitLinkList()
{
    //初始化头哨兵
    Node* head = (Node*)malloc(sizeof(Node));
    if (head == NULL) {
        PRINT_STRING("node_head初始化动态分配内存失败");
        exit(-1);
    }

    LinkList* ret = (LinkList*)malloc(sizeof(LinkList));
    if (ret == NULL) {
        PRINT_STRING("LinkList动态分配内存失败");
        exit(-1);
    }

    head->next = NULL;
    head->front = NULL;
    ret->head = head;
    ret->tail = head;
    ret->count = 0;
    ret->type = DOUBLEWAY;
    return ret;
}

/*判断LinkList是否为空*/
Status IsEmpty_LinkList(LinkList * L)
{
    if (L == NULL) {
        PRINT_STRING("LinkList为NULL");
        return TRUE;
    }

    if (L->count == 0) return TRUE;
    else return FALSE;
}

/*遍历LinkList*/
void Traverse_LinkList(LinkList * L)
{
    if (IsEmpty_LinkList(L)) return;

    Node* node = L->head->next;
    for (int i = 0; i < L->count; i++){
        printf("%d ",node->data);
        node = node->next;
    }
    PRINT_STRING("");
}

/*返回LinkList第一个元素指针*/
TElement* GetFirst_LinkList(LinkList * L)
{
    if (L->head->next == NULL) return NULL;
    return &(L->head->next->data);
}

/*返回LinkList该index的元素指针*/
/*index:所获取元素的下标*/
TElement* GetValue_LinkList(LinkList * L, int index)
{
    if (IsEmpty_LinkList(L)) return NULL;

    if (index >= L->count || index < 0) {
        printf("无法在第[%d]的位置GetValue\n", index);
        return NULL;
    }

    Node* ret = NULL;
    if (L->type == DOUBLEWAY && index >= L->count / 2) {
        ret = L->tail;
        int pos = L->count - 1 - index;
        while (pos-- > 0) ret = ret->front;
    }else {
        ret = L->head->next;
        int pos = 0;
        while (pos++ < index) ret = ret->next;
    }

    return ret == NULL? NULL : &(ret->data);
}

/*追加LinkList*/
void Append_LinkList(LinkList * L, TElement value)
{
    if (L == NULL) return;
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        PRINT_STRING("追加node动态分配内存失败");
        exit(-1);
    }

    node->data = value;
    node->front = L->tail;
    node->next = NULL;
    L->tail->next = node;
    L->tail = node;
    L->count++;
    return;
}

/*修改LinkList该index的元素value*/
void SetValue_LinkList(LinkList * L, int index, TElement value)
{
    if (IsEmpty_LinkList(L)) return;

    if (index >= L->count || index < 0) {
        printf("无法在第[%d]的位置SetValue\n", index);
        return;
    }

    Node* ret = NULL;
    if (L->type == DOUBLEWAY && index >= L->count / 2) {
        ret = L->tail;
        int pos = L->count - 1 - index;
        while (pos-- > 0) ret = ret->front;
    }else {
        ret = L->head->next;
        int pos = 0;
        while (pos++ < index) ret = ret->next;
    }

    ret->data = value;
    return;
}

/*返回LinkList当前元素个数*/
int GetSize_LinkList(LinkList * L)
{
    if (L == NULL) {
        PRINT_STRING("LinkList为NULL");
        return 0;
    }
    return L->count;
}

/*倒置LinkList*/
void Inversion_LinkList(LinkList * L)
{
    if (IsEmpty_LinkList(L)) return;

    Node* h_node = L->head->next;
    Node* t_node = L->tail;
    for (int i = 0; i < L->count/2 && h_node != t_node; i++){
        TElement temp = h_node->data;
        h_node->data = t_node->data;
        t_node->data = temp;
        h_node = h_node->next;
        t_node = t_node->front;
    }
    return;
}

/*插入元素LinkList*/
void Insert_LinkList(LinkList * L, int index, TElement value)
{
    if (L == NULL) return;

    if (index >= L->count || index < 0) {
        printf("无法在第[%d]的位置Insert\n", index);
        return;
    }

    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        PRINT_STRING("插入node动态分配内存失败");
        exit(-1);
    }

    Node* p = NULL;
    if (L->type == DOUBLEWAY && index >= L->count / 2) {
        p = L->tail;
        int pos = L->count - 1 - index;
        while (pos-- > 0) p = p->front;
    }else {
        p = L->head->next;
        int pos = 0;
        while (pos++ < index) p = p->next;
    }

    node->data = value;
    node->next = p;
    node->front = p->front;
    p->front->next = node;
    p->front = node;
    L->count++;
    return;
}

/*删除LinkList第一个元素*/
void Remove_LinkList(LinkList * L)
{
    if (IsEmpty_LinkList(L)) return;
    Node* node = L->head->next;

    if (node->next == NULL) {
        L->tail = node->front;
    }else {
        node->next->front = node->front;
    }
    node->front->next = node->next;

    node->front = NULL;
    node->next = NULL;
    free(node);
    L->count--;
    return;
}

/*删除LInkList该index的元素*/
/*index:要删除元素的下标*/
void Delete_LinkList(LinkList * L, int index)
{
    if (L == NULL) return;

    if (index >= L->count || index < 0) {
        printf("无法在第[%d]的位置Delete\n", index);
        return;
    }

    Node* p = NULL;
    if (L->type == DOUBLEWAY && index >= L->count / 2) {
        p = L->tail;
        int pos = L->count - 1 - index;
        while (pos-- > 0) p = p->front;
    }else {
        p = L->head->next;
        int pos = 0;
        while (pos++ < index) p = p->next;
    }

    if (p->next == NULL) {
        L->tail = p->front;
    }else {
        p->next->front = p->front;
    }
    p->front->next = p->next;

    p->front = NULL;
    p->next = NULL;
    free(p);
    L->count--;
    return;
}

/*清空LinkList*/
/*[头哨兵并未free掉]*/
void Clear_LinkList(LinkList * L)
{
    if (L == NULL) return;

    int count = L->count;
    for (int i = 0; i < count; i++){
        Remove_LinkList(L);
    }
    return;
}

/*销毁LinkList*/
void Destroy_LinkList(LinkList** L)
{
    if (*L == NULL) return;
    Clear_LinkList(*L);
    free(((*L)->head));
    free(*L);
    *L = NULL;
    return;
}
