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

#include "queue.h"	//定义完RedBlackBST之后再Include


/*RedBlackBST初始化*/
RedBlackBST RedBlackBSTInit()
{
    return NULL;
}

/*通过手动输入KEY来赋值创建RedBlackBST*/
void CreateRedBlackBST_ByInputKeyCode(RedBlackBST * T)
{
    printf("KEY为-1则NULL,请输入KEY值 : ");
    KEY m_Key;
    scanf_s("%d", &m_Key);
    if (m_Key != -1) {
        printf("请输入该[%d]KEY对应的Value : ", m_Key);
        Element m_Value;
        scanf_s("%d", &m_Value);

        while (m_Key != -1)
        {
            *T = Put(T, m_Key, m_Value);
            (*T)->Color = BLACK;        //根Root保持BLACK

            printf("KEY为-1则NULL,请输入KEY值 : ");
            scanf_s("%d", &m_Key);
            if (m_Key != -1) {
                printf("请输入该[%d]KEY对应的Value : ", m_Key);
                scanf_s("%d", &m_Value);
            }
        }
    }
    return;
}

/*(内部方法)插入新元素*/
RedBlackBST Put(RedBlackBST * T, KEY key, Element value)
{
    /*生成新Node元素*/
    if (*T == NULL) {    
        (*T) = (RedBlackBST)malloc(sizeof(RedBlackBSNode));
        (*T)->Key = key;
        (*T)->Data = value;
        (*T)->Color = RED;
        (*T)->Left = NULL;
        (*T)->Right = NULL;
        return *T;
    }

    /*先找到对应新KEY的位置*/
    if ((*T)->Key ==  key) {
        (*T)->Data = value;
    }
    else if ((*T)->Key > key) {
        (*T)->Left = Put(&((*T)->Left), key, value);

    }else {
        (*T)->Right = Put(&((*T)->Right), key, value);
    }

    /*先插入完成之后，再根据RED/BLACK的颜色旋转操作*/
    /*反正T的Left或Right肯定插入了一个新Node*/

    //当插入(右Child)到2-结点(即当右链接红色)(左旋 X 1)
    if ((*T)->Right && (*T)->Right->Color == RED) {
        *T = RotateLeft(*T);
    }

    //当插入(右Child)的新KEY比原小二叉树树中3-结点都大(颜色翻转)
    if (( (*T)->Left  && (*T)->Left->Color  == RED )&&
        ( (*T)->Right && (*T)->Right->Color == RED))
    {
        FlipColors(*T);
    }

    //当插入(左Child)的新KEY比原小二叉树树中3-结点都小(右旋 X 1)
    if ( ((*T)->Left && (*T)->Left->Color == RED) &&
         ((*T)->Left->Left && (*T)->Left->Left->Color == RED))
    {
        *T = RotateRight(*T);
        FlipColors(*T);
    }

    //当插入(右Child)的新KEY在原小二叉树树中3-结点中间(右旋 X 1 + 左旋 X 1)
    if (((*T)->Left && (*T)->Left->Color == RED) &&
        ((*T)->Left->Right && (*T)->Left->Right->Color == RED))
    {
        (*T)->Left = RotateLeft((*T)->Left);
        *T = RotateRight(*T);
        FlipColors(*T);
    }
    return *T;
}

/*(内部方法)左旋*/
RedBlackBSNode* RotateLeft(RedBlackBSNode* node)
{
    RedBlackBSNode* p = node->Right;
    node->Right = p->Left;
    p->Left = node;
    p->Color = node->Color;
    node->Color = RED;
    return p;
}

/*(内部方法)右旋*/
RedBlackBSNode* RotateRight(RedBlackBSNode* node)
{
    RedBlackBSNode* p = node->Left;
    node->Left = p->Right;
    p->Right = node;
    p->Color = node->Color;
    node->Color = RED;
    return p;
}

/*(内部方法)颜色转变*/
/*左右Child红链接变BLACK,Root的Color变RED*/
void FlipColors(RedBlackBSNode* node)
{
    node->Color = RED;
    node->Left->Color = BLACK;
    node->Right->Color = BLACK;
    return;
}

/*树的深度*/
int GetDepth(RedBlackBST T)
{
    int i, j;
    if (T == NULL) return 0;
    i = GetDepth(T->Left);
    j = GetDepth(T->Right);
    return i > j ? i + 1 : j + 1;
}

#pragma region Traverse
/*前序遍历*/
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

/*中序遍历*/
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

/*后序遍历*/
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

/*层序遍历*/
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

