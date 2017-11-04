#pragma once
#include<stdio.h>
#include<stdlib.h>
#define PRINT_INT(x) printf("%d\n",x);

typedef int KEY;
typedef int Element;

#pragma region BST
typedef struct BinarySearchNode {
    KEY Key;
    Element Data;
    struct BinarySearchNode *Left;
    struct BinarySearchNode *Right;
}BSNode, *BSTree;
#pragma endregion

#pragma region Functions
BSTree InitBSTree();
void Insert(BSTree * T, KEY key, Element value);
Element* Search(BSTree T, KEY key);
BSNode* GetMin(BSTree T);
BSNode* GetMax(BSTree T);
void DeleteMin(BSTree * T);
void DeleteMax(BSTree * T);
void DeleteBSNode(BSTree * T, BSTree * pre, KEY key);
void DestroyBSTree(BSTree * T);
void InOrderTraverse(BSTree T);
void PreOrderTraverse(BSTree T);
void PostOrderTraverse(BSTree T);
void LevelOrderTraverse(BSTree T);
int GetDepth(BSTree T);
#pragma endregion


#include "queue.h"	//在BST定义之后再Include队列


/*BSTree初始化*/
BSTree InitBSTree()
{
    return NULL;
}

/*通过手动赋值创建一棵搜索二叉树*/
void CreateBSTree_ByInputKeyCode(BSTree * T)
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

/*插入新元素*/
/*T：插入的位置，key：设置的KEY值，value：实际的Data值*/
/*若KEY值与之前重复，直接替换value*/
void Insert(BSTree * T, KEY key, Element value)
{
    if(*T == NULL){
        *T = (BSTree)malloc(sizeof(BSNode));
        if (*T == NULL) {
            printf("BSTree初始化动态分配内存失败\n");
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
            Insert(&((*T)->Left),key, value);
        }
        else {
            Insert(&((*T)->Right),key, value);
        }
    }
    return;
}

/*根据Key找到对应的value*/
/*T:树Root*/
Element* Search(BSTree T,KEY key)
{
    if (T == NULL) {
        printf("无法操作空BSTree\n");
        return NULL;
    }

    if (T->Key == key){
        return &(T->Data);
    }
    if (T->Key > key) {
        return Search(T->Left, key);
    }
    else {
        return Search(T->Right, key);
    }
}

/*返回最左下角的Node*/
/*Min是指最小的KEY值*/
/*T：任意一个Node，Min即相对于该Node的最左下角Node*/
BSNode* GetMin(BSTree T)
{
    if (T == NULL) {
        printf("无法操作空BSTree\n");
        return NULL;
    }

    BSTree p = T;
    while(p->Left) {
        p = p->Left;
    }
    return p;
}

/*返回最右下角的Node*/
/*Max是指最大的KEY值*/
/*T：任意一个Node，Max即相对于该Node的最右下角Node*/
BSNode* GetMax(BSTree T)
{
    if (T == NULL) {
        printf("无法操作空BSTree\n");
        return NULL;
    }

    BSTree p = T;
    while (p->Right) {
        p = p->Right;
    }
    return p;
}

/*删除KEY最小的Node*/
/*T：任意一个Node，KEY最小即相对于该Node的最左下角Node*/
void DeleteMin(BSTree * T)
{
    if (*T == NULL) {
        printf("无法操作空BSTree\n");
        return;
    }

    BSTree p = *T;
    BSTree parent = NULL;
    while (p->Left) {
        parent = p;
        p = p->Left;
    }

    if (parent == NULL){
        *T = p->Right;
    }
    else {
        parent->Left = p->Right;
    }
    free(p);
    p = NULL;
    return;
}

/*删除KEY最大的Node*/
/*T：任意一个Node，KEY最大即相对于该Node的最右下角Node*/
void DeleteMax(BSTree * T)
{
    if (*T == NULL) {
        printf("无法操作空BSTree\n");
        return;
    }

    BSTree p = *T;
    BSTree parent = NULL;
    while (p->Right) {
        parent = p;
        p = p->Right;
    }

    if (parent == NULL) {
        *T = p->Left;
    }
    else {
        parent->Right = p->Left;
    }
    free(p);
    p = NULL;
    return;
}

/*删除指定KEY的Node*/
/*pre：传入NULL的BSTree*参数即可 */
void DeleteBSNode(BSTree * T, BSTree * pre ,KEY key)
{
    if (*T == NULL) {
        printf("无法操作空BSTress\n");
        return;
    }

    if ((*T)->Key == key) {
        if (*pre == NULL) {
            *pre = *T;
            *T = (*T)->Left;
            if ((*pre)->Right) {
                (*T)->Right = (*pre)->Right;
            }
            free(*pre);
            *pre = NULL;
        }
        else {
            BSTree p = *T;
            BSTree l = p->Left;
            BSTree r = p->Right;
            if (r)
            {
                BSTree r_parent = p;
                while (r->Left) {
                    r_parent = r;
                    r = r->Left;
                }
                r->Left = p->Left;
                if (r_parent != p) {
                    r->Right = p->Right;
                    r_parent->Left = NULL;
                }
                if ((*pre)->Left == p) {
                    (*pre)->Left = r;
                }else {
                    (*pre)->Right = r;
                }
            }
            else {
                if ((*pre)->Left == p) {
                    (*pre)->Left = l;
                }else {
                    (*pre)->Right = l;
                }
            }
            free(p);
            p = NULL;
        }
        return;
    }

    else if ((*T)->Key > key) {
        *pre = *T;
        return DeleteBSNode(&((*T)->Left), pre, key);
    }

    else if((*T)->Key < key){
        *pre = *T;
        return DeleteBSNode(&((*T)->Right), pre, key);
    }
}

/*删除BSTree*/
void DestroyBSTree(BSTree * T)
{
    if (*T)
    {
        DestroyBSTree(&((*T)->Left));
        DestroyBSTree(&((*T)->Right));
        free(*T);
        *T = NULL;
    }
}

/*前序遍历*/
void PreOrderTraverse(BSTree T)
{
    if (T)
    {
        PRINT_INT(T->Data);
        PreOrderTraverse(T->Left);
        PreOrderTraverse(T->Right);
    }
    return;
}

/*中序遍历*/
void InOrderTraverse(BSTree T)
{
    if (T)
    {
        InOrderTraverse(T->Left);
        PRINT_INT(T->Data);
        InOrderTraverse(T->Right);
    }
    return;
}

/*后序遍历*/
void PostOrderTraverse(BSTree T)
{
    if (T)
    {
        PostOrderTraverse(T->Left);
        PostOrderTraverse(T->Right);
        PRINT_INT(T->Data);
    }
    return;
}

/*层序遍历*/
void LevelOrderTraverse(BSTree T)
{
    Queue* q = InitQueue();
    if (T)
    {
        EnterQueue(q, T);
        while (!IsEmptyQueue(q))
        {
            TElement result = *GetHeadValue(q);
            DeleteQueue(q);
            PRINT_INT(result->Data);
            if (result->Left)  EnterQueue(q, result->Left);
            if (result->Right) EnterQueue(q, result->Right);
        }
    }
    DestroyQueue(&q);
}

/*树的深度*/
int GetDepth(BSTree T)
{
    int i, j;
    if (T == NULL) return 0;
    i = GetDepth(T->Left);
    j = GetDepth(T->Right);
    return i > j ? i+1 : j+1;
}
