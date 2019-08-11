#include<stdio.h>
#include<stdlib.h>
#define PRINT_STRING(x) printf("%s\n",x)


typedef int TElement;     //import�������ļ�ʱ����Ҫ�޸ĸ�����


/*Boolö��*/
typedef enum Status {
    FALSE,
    TRUE,
}Status;

/*LinkList����ö��*/
typedef enum LinkListType{
    SINGLEWAY,
    DOUBLEWAY,
}LinkListType;

/*���Node��������*/
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

/*��ʼ��LinkList.[Ĭ��˫��LinkList]*/
LinkList* InitLinkList()
{
    //��ʼ��ͷ�ڱ�
    Node* head = (Node*)malloc(sizeof(Node));
    if (head == NULL) {
        PRINT_STRING("node_head��ʼ����̬�����ڴ�ʧ��");
        exit(-1);
    }

    LinkList* ret = (LinkList*)malloc(sizeof(LinkList));
    if (ret == NULL) {
        PRINT_STRING("LinkList��̬�����ڴ�ʧ��");
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

/*�ж�LinkList�Ƿ�Ϊ��*/
Status IsEmpty_LinkList(LinkList * L)
{
    if (L == NULL) {
        PRINT_STRING("LinkListΪNULL");
        return TRUE;
    }

    if (L->count == 0) return TRUE;
    else return FALSE;
}

/*����LinkList*/
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

/*����LinkList��һ��Ԫ��ָ��*/
TElement* GetFirst_LinkList(LinkList * L)
{
    if (L->head->next == NULL) return NULL;
    return &(L->head->next->data);
}

/*����LinkList��index��Ԫ��ָ��*/
/*index:����ȡԪ�ص��±�*/
TElement* GetValue_LinkList(LinkList * L, int index)
{
    if (IsEmpty_LinkList(L)) return NULL;

    if (index >= L->count || index < 0) {
        printf("�޷��ڵ�[%d]��λ��GetValue\n", index);
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

/*׷��LinkList*/
void Append_LinkList(LinkList * L, TElement value)
{
    if (L == NULL) return;
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        PRINT_STRING("׷��node��̬�����ڴ�ʧ��");
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

/*�޸�LinkList��index��Ԫ��value*/
void SetValue_LinkList(LinkList * L, int index, TElement value)
{
    if (IsEmpty_LinkList(L)) return;

    if (index >= L->count || index < 0) {
        printf("�޷��ڵ�[%d]��λ��SetValue\n", index);
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

/*����LinkList��ǰԪ�ظ���*/
int GetSize_LinkList(LinkList * L)
{
    if (L == NULL) {
        PRINT_STRING("LinkListΪNULL");
        return 0;
    }
    return L->count;
}

/*����LinkList*/
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

/*����Ԫ��LinkList*/
void Insert_LinkList(LinkList * L, int index, TElement value)
{
    if (L == NULL) return;

    if (index >= L->count || index < 0) {
        printf("�޷��ڵ�[%d]��λ��Insert\n", index);
        return;
    }

    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        PRINT_STRING("����node��̬�����ڴ�ʧ��");
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

/*ɾ��LinkList��һ��Ԫ��*/
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

/*ɾ��LInkList��index��Ԫ��*/
/*index:Ҫɾ��Ԫ�ص��±�*/
void Delete_LinkList(LinkList * L, int index)
{
    if (L == NULL) return;

    if (index >= L->count || index < 0) {
        printf("�޷��ڵ�[%d]��λ��Delete\n", index);
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

/*���LinkList*/
/*[ͷ�ڱ���δfree��]*/
void Clear_LinkList(LinkList * L)
{
    if (L == NULL) return;

    int count = L->count;
    for (int i = 0; i < count; i++){
        Remove_LinkList(L);
    }
    return;
}

/*����LinkList*/
void Destroy_LinkList(LinkList** L)
{
    if (*L == NULL) return;
    Clear_LinkList(*L);
    free(((*L)->head));
    free(*L);
    *L = NULL;
    return;
}
