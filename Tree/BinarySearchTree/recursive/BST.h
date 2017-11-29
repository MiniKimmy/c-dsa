#pragma once
#include<stdio.h>
#include<stdlib.h>
#define PRINT_INT(x) printf("%d\n",x);
#define PRINT_KEY_VALUE(x,y) printf("{KEY = %d, VALUE = %d}\n",x,y)

typedef int KEY;
typedef int Element;

#pragma region BST
typedef struct BinarySearchNode {
    KEY Key;
    Element Data;
    struct BinarySearchNode *Left;
    struct BinarySearchNode *Right;
}BSNode, *BST;
#pragma endregion

#pragma region Functions
#pragma region PRIVATEFunctions
    BST DeleteMin(BST * T);
    BST DeleteMax(BST * T);
    BST Delete(BST * T, KEY key);
#pragma endregion
BST InitBSTree();
void Insert(BST * T, KEY key, Element value);
Element* Search(BST T, KEY key);
BSNode* GetMin(BST T);
BSNode* GetMax(BST T);
void DeleteNode(BST * T, KEY key);
void DeleteMinNode(BST * T);
void DeleteMaxNode(BST * T);
void DestroyBSTree(BST * T);
int GetDepth(BST T);
#pragma region Traverse
    void InOrderTraverse(BST T);
    void PreOrderTraverse(BST T);
    void PostOrderTraverse(BST T);
    void LevelOrderTraverse(BST T);
#pragma endregion
#pragma endregion

#include "queue.h"    //��BST����֮����Include����


/*BST��ʼ��*/
BST InitBSTree()
{
    return NULL;
}

/*ͨ���ֶ���ֵ����һ������������*/
void CreateBSTree_ByInputKeyCode(BST * T)
{
    printf("KeyΪ-1��NULL,��������ӵ�KEYֵ��");
    KEY m_Key;
    scanf_s("%d", &m_Key);
    if (m_Key != -1) {
        printf("�������[%d]Ԫ�ض�Ӧ��valueֵ��", m_Key);
        Element m_value;
        scanf_s("%d", &m_value);

        while (m_Key != -1)
        {
            Insert(T, m_Key, m_value);
            printf("KeyΪ-1��NULL,��������ӵ�KEYֵ��");
            scanf_s("%d", &m_Key);
            if (m_Key != -1) {
                printf("�������[%d]Ԫ�ض�Ӧ��valueֵ��", m_Key);
                scanf_s("%d", &m_value);
            }
        }
    }
    return;
}

/*������Ԫ��,��KEYֵ��֮ǰ�ظ���ֱ���滻value*/
/*T�������λ�ã�key�����õ�KEYֵ��value��ʵ�ʵ�Dataֵ*/
void Insert(BST * T, KEY key, Element value)
{
    if (*T == NULL) {
        *T = (BST)malloc(sizeof(BSNode));
        if (*T == NULL) {
            printf("BST��ʼ����̬�����ڴ�ʧ��\n");
            exit(-1);
        }
        (*T)->Key = key;
        (*T)->Data = value;
        (*T)->Left = NULL;
        (*T)->Right = NULL;
    }
    else {
        if (key == (*T)->Key) {
            (*T)->Data = value;
            return;
        }
        if (key < (*T)->Key) {
            Insert(&((*T)->Left), key, value);
        }
        else {
            Insert(&((*T)->Right), key, value);
        }
    }
    return;
}

/*����Key�ҵ���Ӧ��value*/
Element* Search(BST T, KEY key)
{
    if (T == NULL) {
        printf("�޷�������BST\n");
        return    NULL;
    }

    if (T->Key == key) {
        return &(T->Data);
    }
    if (T->Key > key) {
        return Search(T->Left, key);
    }
    else {
        return Search(T->Right, key);
    }
}

/*���������½ǵ�Node,Min��ָ��С��KEYֵ*/
BSNode* GetMin(BST T)
{
    if (T == NULL) {
        printf("�޷�������BST\n");
        return    NULL;
    }

    if (T->Left != NULL) {
        return GetMin(T->Left);
    }else if (T->Left == NULL) {
        return T;
    }
}

/*���������½ǵ�Node,Max��ָ����KEYֵ*/
BSNode* GetMax(BST T)
{
    if (T == NULL) {
        printf("�޷�������BST\n");
        return    NULL;
    }

    if (T->Right != NULL) {
        return GetMax(T->Right);
    }else if (T->Right == NULL) {
        return T;
    }
}

/*(�ڲ�����)ɾ��KEY��С��Node*/
BST DeleteMin(BST * T)
{
    if (*T == NULL) {
        printf("�޷�������BST\n");
        return;
    }

    if ((*T)->Left != NULL) {
        (*T)->Left = DeleteMin(&(*T)->Left);
    }else if ((*T)->Left == NULL) {
        BST ret = (*T)->Right;
        free(*T);
        (*T)->Left = NULL;
        return ret;
    }
}

/*(�ڲ�����)ɾ��KEY����Node*/
BST DeleteMax(BST * T)
{
    if (*T == NULL) {
        printf("�޷�������BST\n");
        return;
    }

    if ((*T)->Right != NULL) {
        (*T)->Right = DeleteMax(&(*T)->Right);
    }else if ((*T)->Right == NULL) {
        BST ret = (*T)->Left;
        free(*T);
        (*T)->Right = NULL;
        return ret;
    }
}

/*(�ڲ�����)ɾ��ָ��KEY��Node[Ĭ�����Ȱ���Child����ȥ]*/
BST Delete(BST * T, KEY key)
{
    if (*T == NULL) return NULL;
    if ((*T)->Key > key) {
        (*T)->Left = Delete(&((*T)->Left), key);
    }
    else if ((*T)->Key < key) {
        (*T)->Right = Delete(&((*T)->Right), key);
    }
    else {
        if ((*T)->Right) {
            BST p = GetMin((*T)->Right);
            if ((*T)->Right == p) {
                p->Left = (*T)->Left;
                return p;
            }
            BST Min_Copy = (BST)malloc(sizeof(BSNode));
            if (Min_Copy == NULL) {
                printf("Min_Copy��ʼ����̬�����ڴ�ʧ��\n");
                exit(-1);
            }
            Min_Copy->Data = p->Data;
            Min_Copy->Key = p->Key;
            Min_Copy->Left = (*T)->Left;
            Min_Copy->Right = Delete(&((*T)->Right), p->Key);
            free(*T);
            *T = NULL;
            return Min_Copy;
        }
        else if ((*T)->Left) {
            BST ret = (*T)->Left;
            free(*T);
            *T = NULL;
            return ret;
        }
        else {
            free(*T);
            *T = NULL;
            return NULL;
        }
    }
    return *T;
}

/*(�ⲿ����)DeleteMin*/
void DeleteMinNode(BST * T) 
{
    *T = DeleteMin(T);
    return;
}

/*(�ⲿ����)DeleteMin*/
void DeleteMaxNode(BST * T)
{
    *T = DeleteMax(T);
    return;
}

/*(�ⲿ����)Delete*/
void DeleteNode(BST * T, KEY key)
{
    *T = Delete(T, key);
    return;
}

/*����BST*/
void DestroyBSTree(BST * T)
{
    if (*T)
    {
        DestroyBSTree(&((*T)->Left));
        DestroyBSTree(&((*T)->Right));
        free(*T);
        *T = NULL;
    }
}

/*�������*/
int GetDepth(BST T)
{
    int i, j;
    if (T == NULL) return 0;
    i = GetDepth(T->Left);
    j = GetDepth(T->Right);
    return i > j ? i + 1 : j + 1;
}

#pragma region Traverse
/*ǰ�����*/
void PreOrderTraverse(BST T)
{
    if (T)
    {
        PRINT_KEY_VALUE(T->Key, T->Data);
        PreOrderTraverse(T->Left);
        PreOrderTraverse(T->Right);
    }
    return;
}

/*�������*/
void InOrderTraverse(BST T)
{
    if (T)
    {
        InOrderTraverse(T->Left);
        PRINT_KEY_VALUE(T->Key, T->Data);
        InOrderTraverse(T->Right);
    }
    return;
}

/*�������*/
void PostOrderTraverse(BST T)
{
    if (T)
    {
        PostOrderTraverse(T->Left);
        PostOrderTraverse(T->Right);
        PRINT_KEY_VALUE(T->Key, T->Data);
    }
    return;
}

/*�������*/
void LevelOrderTraverse(BST T)
{
    Queue* q = InitQueue();
    if (T)
    {
        EnterQueue(q, T);
        while (!IsEmptyQueue(q))
        {
            TElement result = *GetHeadValue(q);
            DeleteQueue(q);
            PRINT_KEY_VALUE(result->Key, result->Data);
            if (result->Left)  EnterQueue(q, result->Left);
            if (result->Right) EnterQueue(q, result->Right);
        }
    }
    DestroyQueue(&q);
}
#pragma endregion
