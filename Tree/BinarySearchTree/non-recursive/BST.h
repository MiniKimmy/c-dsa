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


#include "queue.h"	//��BST����֮����Include����


/*BSTree��ʼ��*/
BSTree InitBSTree()
{
    return NULL;
}

/*ͨ���ֶ���ֵ����һ������������*/
void CreateBSTree_ByInputKeyCode(BSTree * T)
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

/*������Ԫ��*/
/*T�������λ�ã�key�����õ�KEYֵ��value��ʵ�ʵ�Dataֵ*/
/*��KEYֵ��֮ǰ�ظ���ֱ���滻value*/
void Insert(BSTree * T, KEY key, Element value)
{
    if(*T == NULL){
        *T = (BSTree)malloc(sizeof(BSNode));
        if (*T == NULL) {
            printf("BSTree��ʼ����̬�����ڴ�ʧ��\n");
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

/*����Key�ҵ���Ӧ��value*/
/*T:��Root*/
Element* Search(BSTree T,KEY key)
{
    if (T == NULL) {
        printf("�޷�������BSTree\n");
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

/*���������½ǵ�Node*/
/*Min��ָ��С��KEYֵ*/
/*T������һ��Node��Min������ڸ�Node�������½�Node*/
BSNode* GetMin(BSTree T)
{
    if (T == NULL) {
        printf("�޷�������BSTree\n");
        return NULL;
    }

    BSTree p = T;
    while(p->Left) {
        p = p->Left;
    }
    return p;
}

/*���������½ǵ�Node*/
/*Max��ָ����KEYֵ*/
/*T������һ��Node��Max������ڸ�Node�������½�Node*/
BSNode* GetMax(BSTree T)
{
    if (T == NULL) {
        printf("�޷�������BSTree\n");
        return NULL;
    }

    BSTree p = T;
    while (p->Right) {
        p = p->Right;
    }
    return p;
}

/*ɾ��KEY��С��Node*/
/*T������һ��Node��KEY��С������ڸ�Node�������½�Node*/
void DeleteMin(BSTree * T)
{
    if (*T == NULL) {
        printf("�޷�������BSTree\n");
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

/*ɾ��KEY����Node*/
/*T������һ��Node��KEY�������ڸ�Node�������½�Node*/
void DeleteMax(BSTree * T)
{
    if (*T == NULL) {
        printf("�޷�������BSTree\n");
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

/*ɾ��ָ��KEY��Node*/
/*pre������NULL��BSTree*�������� */
void DeleteBSNode(BSTree * T, BSTree * pre ,KEY key)
{
    if (*T == NULL) {
        printf("�޷�������BSTress\n");
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

/*ɾ��BSTree*/
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

/*ǰ�����*/
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

/*�������*/
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

/*�������*/
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

/*�������*/
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

/*�������*/
int GetDepth(BSTree T)
{
    int i, j;
    if (T == NULL) return 0;
    i = GetDepth(T->Left);
    j = GetDepth(T->Right);
    return i > j ? i+1 : j+1;
}
