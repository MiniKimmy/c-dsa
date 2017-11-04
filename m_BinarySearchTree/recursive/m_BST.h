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

#include "queue.h"    //在BST定义之后再Include队列


/*BST初始化*/
BST InitBSTree()
{
    return NULL;
}

/*通过手动赋值创建一棵搜索二叉树*/
void CreateBSTree_ByInputKeyCode(BST * T)
{
    printf("Key为-1则NULL,请输入添加的KEY值：");
    KEY m_Key;
    scanf_s("%d", &m_Key);
    if (m_Key != -1) {
        printf("请输入该[%d]元素对应的value值：", m_Key);
        Element m_value;
        scanf_s("%d", &m_value);

        while (m_Key != -1)
        {
            Insert(T, m_Key, m_value);
            printf("Key为-1则NULL,请输入添加的KEY值：");
            scanf_s("%d", &m_Key);
            if (m_Key != -1) {
                printf("请输入该[%d]元素对应的value值：", m_Key);
                scanf_s("%d", &m_value);
            }
        }
    }
    return;
}

/*插入新元素,若KEY值与之前重复，直接替换value*/
/*T：插入的位置，key：设置的KEY值，value：实际的Data值*/
void Insert(BST * T, KEY key, Element value)
{
    if (*T == NULL) {
        *T = (BST)malloc(sizeof(BSNode));
        if (*T == NULL) {
            printf("BST初始化动态分配内存失败\n");
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

/*根据Key找到对应的value*/
Element* Search(BST T, KEY key)
{
    if (T == NULL) {
        printf("无法操作空BST\n");
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

/*返回最左下角的Node,Min是指最小的KEY值*/
BSNode* GetMin(BST T)
{
    if (T == NULL) {
        printf("无法操作空BST\n");
        return    NULL;
    }

    if (T->Left != NULL) {
        return GetMin(T->Left);
    }else if (T->Left == NULL) {
        return T;
    }
}

/*返回最右下角的Node,Max是指最大的KEY值*/
BSNode* GetMax(BST T)
{
    if (T == NULL) {
        printf("无法操作空BST\n");
        return    NULL;
    }

    if (T->Right != NULL) {
        return GetMax(T->Right);
    }else if (T->Right == NULL) {
        return T;
    }
}

/*(内部方法)删除KEY最小的Node*/
BST DeleteMin(BST * T)
{
    if (*T == NULL) {
        printf("无法操作空BST\n");
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

/*(内部方法)删除KEY最大的Node*/
BST DeleteMax(BST * T)
{
    if (*T == NULL) {
        printf("无法操作空BST\n");
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

/*(内部方法)删除指定KEY的Node[默认优先把右Child拉上去]*/
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
                printf("Min_Copy初始化动态分配内存失败\n");
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

/*(外部方法)DeleteMin*/
void DeleteMinNode(BST * T) 
{
    *T = DeleteMin(T);
    return;
}

/*(外部方法)DeleteMin*/
void DeleteMaxNode(BST * T)
{
    *T = DeleteMax(T);
    return;
}

/*(外部方法)Delete*/
void DeleteNode(BST * T, KEY key)
{
    *T = Delete(T, key);
    return;
}

/*销毁BST*/
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

/*树的深度*/
int GetDepth(BST T)
{
    int i, j;
    if (T == NULL) return 0;
    i = GetDepth(T->Left);
    j = GetDepth(T->Right);
    return i > j ? i + 1 : j + 1;
}

#pragma region Traverse
/*前序遍历*/
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

/*中序遍历*/
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

/*后序遍历*/
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

/*层序遍历*/
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
