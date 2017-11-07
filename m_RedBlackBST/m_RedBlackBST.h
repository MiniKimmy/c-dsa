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
void CreateRedBlackBST_ByNum(RedBlackBST * T, int num);
void CreateRedBlackBST_ByInputKeyCode(RedBlackBST * T);
RedBlackBSNode* RotateLeft(RedBlackBSNode* node);
RedBlackBSNode* RotateRight(RedBlackBSNode* node);
void FlipColors(RedBlackBSNode* node);
RedBlackBST Insert(RedBlackBST * T, KEY key, Element value);
int IsRed(RedBlackBSNode* node);
int IsKey(RedBlackBSNode* T, KEY key);
void DeleteNode(RedBlackBST * T, KEY key);
RedBlackBST Delete(RedBlackBST * T, KEY key);
int GetDepth(RedBlackBST T);
#pragma region TraverseFunctions
    void PreOrderTraverse(RedBlackBST T);
    void InOrderTraverse(RedBlackBST T);
    void PostOrderTraverse(RedBlackBST T);
    void LevelOrderTraverse(RedBlackBST T);
    void LevelOrderTraverse_TreeShape(RedBlackBST T);
#pragma endregion
#pragma endregion


#include "queue.h"    //定义完RedBlackBST之后再Include


/*RedBlackBST初始化*/
RedBlackBST RedBlackBSTInit()
{
    return NULL;
}

/*自动输入KEY从1到指定num的赋值创建RedBlackBST*/
void CreateRedBlackBST_ByNum(RedBlackBST * T,int num)
{
    int key = 1;
    while (key <= num) {
        *T = Insert(T, key, 1);
        (*T)->Color = BLACK;         
        key++;
    }
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
            *T = Insert(T, m_Key, m_Value);
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

/*(内部方法)插入新元素*/
RedBlackBST Insert(RedBlackBST * T, KEY key, Element value)
{
    if (*T == NULL) {    
        (*T) = (RedBlackBST)malloc(sizeof(RedBlackBSNode));
        (*T)->Key = key;
        (*T)->Data = value;
        (*T)->Color = RED;
        (*T)->Left = NULL;
        (*T)->Right = NULL;
        return *T;
    }

    if ((*T)->Key ==  key) {
        (*T)->Data = value;
    }else if ((*T)->Key > key) {
        (*T)->Left = Insert(&((*T)->Left), key, value);
    }else{
        (*T)->Right = Insert(&((*T)->Right), key, value);
    }

    if (IsRed((*T)->Right) && !IsRed((*T)->Left)) *T = RotateLeft(*T);
    if (IsRed((*T)->Left) && IsRed((*T)->Left->Left)) *T= RotateRight(*T); //隐藏了左旋+右旋的操作
    if (IsRed((*T)->Right) && IsRed((*T)->Left)) FlipColors(*T);
    return *T;
}

/*（内部方法）结点颜色是否为RED*/
/*是NULL或者是黑色返回0，是红色则返回1*/
int IsRed(RedBlackBSNode* node) 
{
    if (node) return node->Color == RED;
    else return 0;
}

/*（内部方法）是否匹配到了对应的KEY*/
/*NULL或未匹配到则返回0，匹配成功返回1*/
int IsKey(RedBlackBSNode* T, KEY key)
{
    if (T) return T->Key == key;
    else return 0;
}

/*(外部方法)Delete*/
void DeleteNode(RedBlackBST * T, KEY key)
{
    //层数大于2开始
    if ((*T)->Left || (*T)->Right) {
        *T = Delete(T, key);
        (*T)->Color = BLACK;
    }
    else {    
        if ((*T)->Key == key) {
            free(*T);
            *T = NULL;
        }
    }
    return;
}

/*(内部方法)删除指定KEY的Node*/
RedBlackBST Delete(RedBlackBST * T, KEY key)
{
    if (*T == NULL) return NULL;

    if ((*T)->Key > key) {
        (*T)->Left = Delete(&((*T)->Left), key);
    }else if ((*T)->Key < key) {
        (*T)->Right = Delete(&((*T)->Right), key);
    }else {
        if ((*T)->Right) {
            RedBlackBSNode* Min_Copy = (*T)->Right;
            RedBlackBSNode* p = NULL;
            while (Min_Copy->Left){
                p = Min_Copy;
                Min_Copy = Min_Copy->Left;
            }

            //如果Min是红色就可以立即交换 （Min是尽头，红色不会有Sibling）
            if (Min_Copy->Color == RED) {
                Min_Copy->Left = (*T)->Left;
                Min_Copy->Right = (*T)->Right;
                Min_Copy->Color = (*T)->Color;
                p->Left = NULL;
                free(*T);
                *T = NULL;
                return Min_Copy;
            }else {
                //右Child是一棵子树，跟BST原始的删除一样
                if (p != NULL) {
                    RedBlackBSNode* temp = (RedBlackBSNode*)malloc(sizeof(RedBlackBSNode));
                    temp->Data = Min_Copy->Data;
                    temp->Key = Min_Copy->Key;
                    (*T)->Right = Delete(&((*T)->Right), Min_Copy->Key);
                    temp->Left = (*T)->Left;
                    temp->Right = (*T)->Right;
                    temp->Color = (*T)->Color;
                    free(*T);
                    *T = NULL;
                    return temp;
                }
                //右Child只有1个
                else {

                    //若左Child不是完整小二叉树  
                    if (IsRed((*T)->Left->Left)) {
                        RedBlackBSNode* Max_Copy = (*T)->Left;
                        Max_Copy->Right = (*T)->Right;
                        Max_Copy->Color = (*T)->Color;
                        free(*T);
                        *T = NULL;
                        Max_Copy->Left->Color = BLACK;
                        return Max_Copy;
                    }

                    //左child红色  
                    if (IsRed((*T)->Left)) {
                        RedBlackBSNode* Max_Copy = (*T)->Left;
                        RedBlackBSNode* pre = NULL;
                        while (Max_Copy->Right) {
                            pre = Max_Copy;
                            Max_Copy = Max_Copy->Right;
                        }
                        Max_Copy->Left = (*T)->Left;
                        Max_Copy->Right = (*T)->Right;
                        Max_Copy->Color = (*T)->Color;
                        pre->Color = BLACK;
                        pre->Left->Color = RED;
                        pre->Right = NULL;
                        free(*T);
                        *T = NULL;
                        return Max_Copy;
                    }
                    
                    //左Child颜色是BLACK黑色 
                    if (!IsRed((*T)->Left)) {
                        Min_Copy->Left = (*T)->Left;
                        Min_Copy->Color = BLACK;
                        (*T)->Left->Color = RED;
                        free(*T);
                        *T = NULL;
                        return Min_Copy;
                    }
                }
            }
        }

        //没有右Child
        else if (IsRed((*T)->Left)) {
            RedBlackBSNode* p = (*T)->Left;
            p->Color = (*T)->Color;
            free(*T);
            *T = NULL;
            return p;
        }

        return *T;
    }
    
    //-------------下面是KEY无Child的情况----------
    //----------每次操作后的颜色都是保持完整的------

    //删除2-结点（删除只有一个右Child 而Left是RED可以借键)
    if (IsKey((*T)->Right, key) && IsRed((*T)->Left))
    {
        //换颜色,先右旋过去补个键，再删除
        if ((*T)->Left->Right) {
            (*T)->Left->Color = BLACK;
            (*T)->Left->Right->Color = RED;
        }
        *T = RotateRight(*T);
        (*T)->Right->Color = BLACK;
        free((*T)->Right->Right);
        (*T)->Right->Right = NULL;
        return *T;
    }

    /*2-结点右Child直接删除变颜色 + Left是BLACK,然后留给parent检测旋转*/
    if (IsKey((*T)->Right, key) && !IsRed((*T)->Left))
    {
        (*T)->Left->Color = RED;
        (*T)->Color = BLACK;
        free((*T)->Right);
        (*T)->Right = NULL;
        return *T;
    }

    //删除2-结点左边树底 [ 通过中间Root二次递归 + 检测旋转 ]
    if ((*T)->Left && (*T)->Left->Color == BLACK && 
        ( (*T)->Right && (*T)->Right->Right ) && 
        (*T)->Key > key && (*T)->Left->Right == NULL)
    {
        RedBlackBSNode* temp = (RedBlackBSNode*)malloc(sizeof(RedBlackBSNode));
        temp->Data = (*T)->Data;
        temp->Key = (*T)->Key;
        temp->Left = NULL;
        temp->Right = NULL;
        *T = Delete(T, (*T)->Key);
        (*T)->Left->Right = temp;
        FlipColors((*T)->Left);
        if ((*T)->Right->Right) {
            (*T)->Left->Color = BLACK;
        }
        return *T;
    }

    //删除2-结点（删除只有一个左Child) || 含左右child）,
    if (IsKey((*T)->Left,key)) 
    {
        //只有一个左Child
        if (IsRed((*T)->Left) && (*T)->Right == NULL) {
            free((*T)->Left);
            (*T)->Left = NULL;
        }
        //（左右child都有，删左Child），先旋转右Child再删左Child(先直接Delete）
        else {
            if ((*T)->Right->Left) {
                (*T)->Right = RotateRight((*T)->Right);
                (*T)->Right->Right->Color = BLACK;
            }
            *T = RotateLeft(*T);
            (*T)->Color = BLACK;
            if ((*T)->Right) {
                (*T)->Left->Color = BLACK;
            }
             
            free((*T)->Left->Left);
            (*T)->Left->Left = NULL;
        }
        return *T;
    }
    return *T;
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
            if (result->Left) EnterQueue(q, result->Left);
            if (result->Right) EnterQueue(q, result->Right);
        }
    }
    DestroyQueue(&q);
    return;
}

/*打印树图案（层序遍历）*/
void LevelOrderTraverse_TreeShape(RedBlackBST T)
{
    int arr[8] = { 1,2,4,8,16,32,64,128 };
    int level = 0;
    int num = 0;
    int depth = GetDepth(T);
    
    Queue* q = InitQueue();
    if (T)
    {
        EnterQueue(q, T);
        for (int i = 0; i < depth - level; i++){
            printf("     ");
        }
        while (!IsEmptyQueue(q))
        {
            TElement result = *GetHeadValue(q);
            DeleteQueue(q);
            if (level < 4) {
                printf("%d       ", result->Key);
            }
            else {
                printf("%d   ", result->Key);
            }
            
            num++;
            if (num == arr[level]) {
                level++;
                num = 0;
                printf("\n");
                for (int i = 0; i < depth - level ; i++) {
                    printf("     ");
                }
            }
            if (result->Left) EnterQueue(q, result->Left);
            if (result->Right) EnterQueue(q, result->Right);
        }
    }
    DestroyQueue(&q);
    printf("\n");
    return;
}
#pragma endregion

