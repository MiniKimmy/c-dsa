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


#include "queue.h"    //������RedBlackBST֮����Include


/*RedBlackBST��ʼ��*/
RedBlackBST RedBlackBSTInit()
{
    return NULL;
}

/*�Զ�����KEY��1��ָ��num�ĸ�ֵ����RedBlackBST*/
void CreateRedBlackBST_ByNum(RedBlackBST * T,int num)
{
    int key = 1;
    while (key <= num) {
        *T = Insert(T, key, 1);
        (*T)->Color = BLACK;         
        key++;
    }
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
            *T = Insert(T, m_Key, m_Value);
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

/*(�ڲ�����)������Ԫ��*/
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
    if (IsRed((*T)->Left) && IsRed((*T)->Left->Left)) *T= RotateRight(*T); //����������+�����Ĳ���
    if (IsRed((*T)->Right) && IsRed((*T)->Left)) FlipColors(*T);
    return *T;
}

/*���ڲ������������ɫ�Ƿ�ΪRED*/
/*��NULL�����Ǻ�ɫ����0���Ǻ�ɫ�򷵻�1*/
int IsRed(RedBlackBSNode* node) 
{
    if (node) return node->Color == RED;
    else return 0;
}

/*���ڲ��������Ƿ�ƥ�䵽�˶�Ӧ��KEY*/
/*NULL��δƥ�䵽�򷵻�0��ƥ��ɹ�����1*/
int IsKey(RedBlackBSNode* T, KEY key)
{
    if (T) return T->Key == key;
    else return 0;
}

/*(�ⲿ����)Delete*/
void DeleteNode(RedBlackBST * T, KEY key)
{
    //��������2��ʼ
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

/*(�ڲ�����)ɾ��ָ��KEY��Node*/
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

            //���Min�Ǻ�ɫ�Ϳ����������� ��Min�Ǿ�ͷ����ɫ������Sibling��
            if (Min_Copy->Color == RED) {
                Min_Copy->Left = (*T)->Left;
                Min_Copy->Right = (*T)->Right;
                Min_Copy->Color = (*T)->Color;
                p->Left = NULL;
                free(*T);
                *T = NULL;
                return Min_Copy;
            }else {
                //��Child��һ����������BSTԭʼ��ɾ��һ��
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
                //��Childֻ��1��
                else {

                    //����Child��������С������  
                    if (IsRed((*T)->Left->Left)) {
                        RedBlackBSNode* Max_Copy = (*T)->Left;
                        Max_Copy->Right = (*T)->Right;
                        Max_Copy->Color = (*T)->Color;
                        free(*T);
                        *T = NULL;
                        Max_Copy->Left->Color = BLACK;
                        return Max_Copy;
                    }

                    //��child��ɫ  
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
                    
                    //��Child��ɫ��BLACK��ɫ 
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

        //û����Child
        else if (IsRed((*T)->Left)) {
            RedBlackBSNode* p = (*T)->Left;
            p->Color = (*T)->Color;
            free(*T);
            *T = NULL;
            return p;
        }

        return *T;
    }
    
    //-------------������KEY��Child�����----------
    //----------ÿ�β��������ɫ���Ǳ���������------

    //ɾ��2-��㣨ɾ��ֻ��һ����Child ��Left��RED���Խ��)
    if (IsKey((*T)->Right, key) && IsRed((*T)->Left))
    {
        //����ɫ,��������ȥ����������ɾ��
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

    /*2-�����Childֱ��ɾ������ɫ + Left��BLACK,Ȼ������parent�����ת*/
    if (IsKey((*T)->Right, key) && !IsRed((*T)->Left))
    {
        (*T)->Left->Color = RED;
        (*T)->Color = BLACK;
        free((*T)->Right);
        (*T)->Right = NULL;
        return *T;
    }

    //ɾ��2-���������� [ ͨ���м�Root���εݹ� + �����ת ]
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

    //ɾ��2-��㣨ɾ��ֻ��һ����Child) || ������child��,
    if (IsKey((*T)->Left,key)) 
    {
        //ֻ��һ����Child
        if (IsRed((*T)->Left) && (*T)->Right == NULL) {
            free((*T)->Left);
            (*T)->Left = NULL;
        }
        //������child���У�ɾ��Child��������ת��Child��ɾ��Child(��ֱ��Delete��
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
            if (result->Left) EnterQueue(q, result->Left);
            if (result->Right) EnterQueue(q, result->Right);
        }
    }
    DestroyQueue(&q);
    return;
}

/*��ӡ��ͼ�������������*/
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

