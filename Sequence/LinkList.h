#pragma once
#include<stdio.h>
#include<stdlib.h>
#define PRINT_STRING(x) printf("%s\n",x)

typedef enum Status{
    FALSE,
    TRUE,
}Status;

typedef int Element;    //Include到其他文件要修改该Element类型

#pragma region LinkList
/*双哨兵+双向链表*/
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

/*初始化LinkList*/
LinkList* InitLinkList()
{
    Node* m_Head = (Node*)malloc(sizeof(Node));
    if (m_Head == NULL) {
        PRINT_STRING("Node初始化动态分配内存失败");
        exit(-1);
    }

    LinkList* ret = (LinkList*)malloc(sizeof(LinkList));
    if (ret == NULL) {
        printf("LinkList动态分配内存失败\n");
        exit(-1);
    }
    m_Head->Next = NULL;
    m_Head->Front = NULL;
    ret->Head = m_Head;
    ret->Tail = m_Head;
    ret->Count = 0;
    return ret;
}

//手动输入初始化LinkList
void CreateLinkList_ByKeyCodeInput(LinkList * L)
{
    PRINT_STRING("请输入需要初始化元素的数量 :");
    int size;
    scanf_s("%d", &size);
    while (size < 0){
        PRINT_STRING("size不能为负值,请重新输入size的值：");
        scanf_s("%d", &size);
    }

    for (int i = 0; i < size; i++) {
        printf("请输入第%d个元素的value :", i);
        Element arg;
        scanf_s("%d", &arg);
        Append_LinkList(L, arg);
    }
    return;
}

//判断LinkList是否为空
Status IsEmptyLinkList(LinkList * L)
{
    if (L == NULL) {
        PRINT_STRING("List为NULL\n");
        exit(-1);
    }

    if (L->Count == 0) return TRUE;
    else return FALSE;


}

//LinkList追加
/*在LinkList的最后面添加新元素*/
void Append_LinkList(LinkList * L, Element value)
{
    if (L == NULL) {
        PRINT_STRING("List为NULL");
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

//LinkList插入
/*index：插入新元素的位置*/
void Insert_LinkList(LinkList * L, int index, Element value)
{
    if (L == NULL) {
        PRINT_STRING("L为NULL");
        return;
    }

    if (index < 0 || index >= L->Count) {
        printf("无法在第[%d]的位置插入元素\n", index);
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

//通过数组赋值存储int类型Element的LinkList
void CreateLinkList_ByInputArray(LinkList * L, int* arr, int size)
{
    if (arr == NULL || L == NULL) {
        PRINT_STRING("传入参数有NULL");
        return;
    }

    for (int i = 0; i < size; i++) {
        Append_LinkList(L, arr[i]);
    }
    return;
}

//遍历LinkList
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

//获取指定index的value
Element GetValue_LinkList(LinkList * L, int index)
{
    if (IsEmptyLinkList(L)) return NULL;

    if (index < 0 || index >= L->Count) {
        printf("无法获取第[%d]个位置的元素\n", index);
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

//获取第一个元素的value
Element GetFirst_LinkList(LinkList * L)
{
    if (IsEmptyLinkList(L)) return NULL;
    return L->Head->Next->Data;
}

//修改指定index的value
void SetValue_LinkList(LinkList * L, int index, Element value)
{
    if (IsEmptyLinkList(L)) return;
    if (index < 0 || index >= L->Count) {
        printf("无法修改第[%d]个位置的元素value\n", index);
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

//删除指定index的value
void DeleteNode_LinkList(LinkList * L, int index)
{
    if (IsEmptyLinkList(L)) return;

    if (index < 0 || index >= L->Count) {
        printf("无法删除第[%d]个位置的元素\n", index);
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

//删除最后一个value
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

/*清除LinkList ,返回一个空元素的LinkList*/
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

/*销毁LinkList,返回NULL*/
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

//LinkList倒置
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

//获取LinkList长度
int GetSize_LinkList(LinkList * L)
{
    if (IsEmptyLinkList(L)) return 0;
    return L->Count;
}
