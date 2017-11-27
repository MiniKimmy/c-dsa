#pragma once
#include<stdio.h>
#include<stdlib.h>
#define PRINT_STRING(x) printf("%s\n",x)

typedef enum Status{
    FALSE,
    TRUE,
}Status;

typedef int Element;    //Include�������ļ�Ҫ�޸ĸ�Element����

#pragma region LinkList
/*˫�ڱ�+˫������*/
typedef struct Node {
    Element Data;
    struct Node * Next;
    struct Node * Front;
}Node;

typedef struct LinkList {
    struct Node * Head;
    struct Node * Tail;
    int Count;
}LinkList;
#pragma endregion

#pragma region Functions;
LinkList* InitLinkList();
void CreateLinkList_ByKeyCodeInput(LinkList * L);
void CreateLinkList_ByInputArray(LinkList * L, int* arr, int size);
Status IsEmptyLinkList(LinkList * L);
void Append_LinkList(LinkList * L, Element value);
void Insert_LinkList(LinkList * L, int index, Element value);
void Traverse_LinkList(LinkList * L);
void DeleteNode_LinkList(LinkList * L, int index);
void Remove_LinkList(LinkList * L);
Element GetValue_LinkList(LinkList * L, int index);
Element GetFirst_LinkList(LinkList * L);
void SetValue_LinkList(LinkList * L, int index, Element value);
void Destroy_LinkList(LinkList** L);
void Clear_LinkList(LinkList * L);
void Inversion_LinkList(LinkList * L);
int GetSize_LinkList(LinkList * L);
#pragma endregion

/*��ʼ��LinkList*/
LinkList* InitLinkList()
{
    Node* m_Head = (Node*)malloc(sizeof(Node));
    if (m_Head == NULL) {
        PRINT_STRING("Node��ʼ����̬�����ڴ�ʧ��");
        exit(-1);
    }

    LinkList* ret = (LinkList*)malloc(sizeof(LinkList));
    if (ret == NULL) {
        printf("LinkList��̬�����ڴ�ʧ��\n");
        exit(-1);
    }
    m_Head->Next = NULL;
    m_Head->Front = NULL;
    ret->Head = m_Head;
    ret->Tail = m_Head;
    ret->Count = 0;
    return ret;
}

//�ֶ������ʼ��LinkList
void CreateLinkList_ByKeyCodeInput(LinkList * L)
{
    PRINT_STRING("��������Ҫ��ʼ��Ԫ�ص����� :");
    int size;
    scanf_s("%d", &size);
    while (size < 0){
        PRINT_STRING("size����Ϊ��ֵ,����������size��ֵ��");
        scanf_s("%d", &size);
    }

    for (int i = 0; i < size; i++) {
        printf("�������%d��Ԫ�ص�value :", i);
        Element arg;
        scanf_s("%d", &arg);
        Append_LinkList(L, arg);
    }
    return;
}

//�ж�LinkList�Ƿ�Ϊ��
Status IsEmptyLinkList(LinkList * L)
{
    if (L == NULL) {
        PRINT_STRING("ListΪNULL\n");
        exit(-1);
    }

    if (L->Count == 0) return TRUE;
    else return FALSE;


}

//LinkList׷��
/*��LinkList������������Ԫ��*/
void Append_LinkList(LinkList * L, Element value)
{
    if (L == NULL) {
        PRINT_STRING("ListΪNULL");
        return;
    }

    Node* p = (Node*)malloc(sizeof(Node));
    p->Data = value;
    p->Next = NULL;
    p->Front = L->Tail;
    L->Tail->Next = p;
    L->Tail = p;
    L->Count++;
    return;
}

//LinkList����
/*index��������Ԫ�ص�λ��*/
void Insert_LinkList(LinkList * L, int index, Element value)
{
    if (L == NULL) {
        PRINT_STRING("LΪNULL");
        return;
    }

    if (index < 0 || index >= L->Count) {
        printf("�޷��ڵ�[%d]��λ�ò���Ԫ��\n", index);
        return;
    }

    Node* p;
    if (index > L->Count / 2) {
        p = L->Tail;
        for (int i = L->Count - 1; i >= index; i--) {
            p = p->Front;
        }
    }else {
        p = L->Head;
        for (int i = 0; i < index; i++) {
            p = p->Next;
        }
    }

    Node* item = (Node*)malloc(sizeof(Node));
    item->Data = value;
    item->Next = p->Next;
    item->Front = p;
    p->Next->Front = item;
    p->Next = item;
    L->Count++;
    return;
}

//ͨ�����鸳ֵ�洢int����Element��LinkList
void CreateLinkList_ByInputArray(LinkList * L, int* arr, int size)
{
    if (arr == NULL || L == NULL) {
        PRINT_STRING("���������NULL");
        return;
    }

    for (int i = 0; i < size; i++) {
        Append_LinkList(L, arr[i]);
    }
    return;
}

//����LinkList
void Traverse_LinkList(LinkList * L)
{
    if (IsEmptyLinkList(L)) return;

    Node* p = L->Head->Next;
    while (p) {
        printf("%d\n", p->Data);
        p = p->Next;
    }
    return;
}

//��ȡָ��index��value
Element GetValue_LinkList(LinkList * L, int index)
{
    if (IsEmptyLinkList(L)) return NULL;

    if (index < 0 || index >= L->Count) {
        printf("�޷���ȡ��[%d]��λ�õ�Ԫ��\n", index);
        return NULL;
    }

    Node* p;
    if (index > L->Count / 2) {
        p = L->Tail;
        for (int i = L->Count - 1; i > index; i--) {
            p = p->Front;
        }
    }
    else {
        p = L->Head;
        for (int i = 0; i <= index; i++) {
            p = p->Next;
        }
    }
    return p->Data;
}

//��ȡ��һ��Ԫ�ص�value
Element GetFirst_LinkList(LinkList * L)
{
    if (IsEmptyLinkList(L)) return NULL;
    return L->Head->Next->Data;
}

//�޸�ָ��index��value
void SetValue_LinkList(LinkList * L, int index, Element value)
{
    if (IsEmptyLinkList(L)) return;
    if (index < 0 || index >= L->Count) {
        printf("�޷��޸ĵ�[%d]��λ�õ�Ԫ��value\n", index);
        return;
    }

    Node* p;
    if (index > L->Count / 2) {
        p = L->Tail;
        for (int i = L->Count - 1; i > index; i--) {
            p = p->Front;
        }
    }
    else {
        p = L->Head;
        for (int i = 0; i <= index; i++) {
            p = p->Next;
        }
    }
    p->Data = value;
    return;
}

//ɾ��ָ��index��value
void DeleteNode_LinkList(LinkList * L, int index)
{
    if (IsEmptyLinkList(L)) return;

    if (index < 0 || index >= L->Count) {
        printf("�޷�ɾ����[%d]��λ�õ�Ԫ��\n", index);
        return;
    }

    Node* p;
    if (index > L->Count / 2) {
        p = L->Tail;
        for (int i = L->Count - 1; i >= index; i--) {
            p = p->Front;
        }
    }else {
        p = L->Head;
        for (int i = 0; i < index; i++) {
            p = p->Next;
        }
    }

    Node* temp = p->Next;
    temp->Next->Front = p;
    p->Next = temp->Next;
    free(temp);
    temp->Next = NULL;
    temp->Front = NULL;
    L->Count--;
    return;
}

//ɾ�����һ��value
void Remove_LinkList(LinkList * L)
{
    if (IsEmptyLinkList(L)) return;

    Node * p = L->Tail;
    L->Tail = p->Front;
    free(p);
    p->Front = NULL;
    L->Tail->Next = NULL;
    L->Count--;
    return;
}

/*���LinkList ,����һ����Ԫ�ص�LinkList*/
void Clear_LinkList(LinkList * L)
{
    if (IsEmptyLinkList(L)) return;

    Node* p = L->Head->Next;
    while (p) {
        Node* q = p->Next;
        free(p);
        p->Front = NULL;
        p->Next = NULL;
        p = q;
    }
    L->Tail = L->Head;
    L->Head->Next = NULL;
    L->Head->Front = NULL;
    L->Count = 0;
    return;
}

/*����LinkList,����NULL*/
void Destroy_LinkList(LinkList** L)
{
    if (*L == NULL) return;

    Node* p = (*L)->Head;
    while (p) {
        Node* q = p->Next;
        free(p);
        p->Front = NULL;
        p->Next = NULL;
        p = q;
    }

    free(*L);
    (*L)->Tail = NULL;
    (*L)->Head = NULL;
    *L = NULL;
    return;
}

//LinkList����
void Inversion_LinkList(LinkList * L)
{
    if (IsEmptyLinkList(L)) return;

    Node* p = L->Head->Next;
    Node* q = L->Tail;
    for (int i = 0; i < L->Count / 2; i++)
    {
        int temp = p->Data;
        p->Data = q->Data;
        q->Data = temp;
        p = p->Next;
        q = q->Front;
    }
    return;
}

//��ȡLinkList����
int GetSize_LinkList(LinkList * L)
{
    if (IsEmptyLinkList(L)) return 0;
    return L->Count;
}
