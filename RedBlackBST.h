#pragma once
#include<stdlib.h>
#include<stdio.h>
#define PRINT_INT(x) printf("%d\n",x)
#define PRINT_KEY_VALUE(x,y) printf("{KEY = %d, VALUE = %d}\n",x,y)

typedef int KEY;
typedef int Element;
#pragma region RedBlackBST
typedef enum Color {
    BLACK,
    RED,
}Color;

typedef struct RedBlackBSNode
{
    KEY Key;
    Element Data;
    Color Color;
    struct RedBlackBSNode *Left;
    struct RedBlackBSNode *Right;
}RedBlackBSNode, *RedBlackBST;
#pragma endregion

#pragma region Functions
RedBlackBST RedBlackBSTInit();
RedBlackBST Put(RedBlackBST * T, KEY key, Element value);
RedBlackBSNode* RotateLeft(RedBlackBSNode* node);
RedBlackBSNode* RotateRight(RedBlackBSNode* node);
void FlipColors(RedBlackBSNode* node);
int GetDepth(RedBlackBST T);

#pragma region TraverseFunctions
    void PreOrderTraverse(RedBlackBST T);
    void InOrderTraverse(RedBlackBST T);
    void PostOrderTraverse(RedBlackBST T);
    void LevelOrderTraverse(RedBlackBST T);
#pragma endregion
#pragma endregion

#include "queue.h"	//������RedBlackBST֮����Include


/*RedBlackBST��ʼ��*/
RedBlackBST RedBlackBSTInit()
{
    return NULL;
}

/*ͨ���ֶ�����KEY����ֵ����RedBlackBST*/
void CreateRedBlackBST_ByInputKeyCode(RedBlackBST * T)
{
    printf("KEYΪ-1��NULL,������KEYֵ : ");
    KEY m_Key;
    scanf_s("%d", &m_Key);
    if (m_Key != -1) {
        printf("�������[%d]KEY��Ӧ��Value : ", m_Key);
        Element m_Value;
        scanf_s("%d", &m_Value);

        while (m_Key != -1)
        {
            *T = Put(T, m_Key, m_Value);
            (*T)->Color = BLACK;        //��Root����BLACK

            printf("KEYΪ-1��NULL,������KEYֵ : ");
            scanf_s("%d", &m_Key);
            if (m_Key != -1) {
                printf("�������[%d]KEY��Ӧ��Value : ", m_Key);
                scanf_s("%d", &m_Value);
            }
        }
    }
    return;
}

/*(�ڲ�����)������Ԫ��*/
RedBlackBST Put(RedBlackBST * T, KEY key, Element value)
{
    /*������NodeԪ��*/
    if (*T == NULL) {    
        (*T) = (RedBlackBST)malloc(sizeof(RedBlackBSNode));
        (*T)->Key = key;
        (*T)->Data = value;
        (*T)->Color = RED;
        (*T)->Left = NULL;
        (*T)->Right = NULL;
        return *T;
    }

    /*���ҵ���Ӧ��KEY��λ��*/
    if ((*T)->Key ==  key) {
        (*T)->Data = value;
    }
    else if ((*T)->Key > key) {
        (*T)->Left = Put(&((*T)->Left), key, value);

    }else {
        (*T)->Right = Put(&((*T)->Right), key, value);
    }

    /*�Ȳ������֮���ٸ���RED/BLACK����ɫ��ת����*/
    /*����T��Left��Right�϶�������һ����Node*/

    //������(��Child)��2-���(���������Ӻ�ɫ)(���� X 1)
    if ((*T)->Right && (*T)->Right->Color == RED) {
        *T = RotateLeft(*T);
    }

    //������(��Child)����KEY��ԭС����������3-��㶼��(��ɫ��ת)
    if (( (*T)->Left  && (*T)->Left->Color  == RED )&&
        ( (*T)->Right && (*T)->Right->Color == RED))
    {
        FlipColors(*T);
    }

    //������(��Child)����KEY��ԭС����������3-��㶼С(���� X 1)
    if ( ((*T)->Left && (*T)->Left->Color == RED) &&
         ((*T)->Left->Left && (*T)->Left->Left->Color == RED))
    {
        *T = RotateRight(*T);
        FlipColors(*T);
    }

    //������(��Child)����KEY��ԭС����������3-����м�(���� X 1 + ���� X 1)
    if (((*T)->Left && (*T)->Left->Color == RED) &&
        ((*T)->Left->Right && (*T)->Left->Right->Color == RED))
    {
        (*T)->Left = RotateLeft((*T)->Left);
        *T = RotateRight(*T);
        FlipColors(*T);
    }
    return *T;
}

/*(�ڲ�����)����*/
RedBlackBSNode* RotateLeft(RedBlackBSNode* node)
{
    RedBlackBSNode* p = node->Right;
    node->Right = p->Left;
    p->Left = node;
    p->Color = node->Color;
    node->Color = RED;
    return p;
}

/*(�ڲ�����)����*/
RedBlackBSNode* RotateRight(RedBlackBSNode* node)
{
    RedBlackBSNode* p = node->Left;
    node->Left = p->Right;
    p->Right = node;
    p->Color = node->Color;
    node->Color = RED;
    return p;
}

/*(�ڲ�����)��ɫת��*/
/*����Child�����ӱ�BLACK,Root��Color��RED*/
void FlipColors(RedBlackBSNode* node)
{
    node->Color = RED;
    node->Left->Color = BLACK;
    node->Right->Color = BLACK;
    return;
}

/*�������*/
int GetDepth(RedBlackBST T)
{
    int i, j;
    if (T == NULL) return 0;
    i = GetDepth(T->Left);
    j = GetDepth(T->Right);
    return i > j ? i + 1 : j + 1;
}

#pragma region Traverse
/*ǰ�����*/
void PreOrderTraverse(RedBlackBST T)
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
void InOrderTraverse(RedBlackBST T)
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
void PostOrderTraverse(RedBlackBST T)
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
void LevelOrderTraverse(RedBlackBST T)
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
    return;
}
#pragma endregion

