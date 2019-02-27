#include<stdio.h>
#include<stdlib.h>
#define PRINT_STRING(x) printf("%s\n",x)

typedef int BSTData;  //import到其他文件时候需要修改该类型,Destroy/Delete等方法是否需要free该BSTData
typedef int KEY;      //import到其他文件时候需要修改该类型,Destroy/Delete等方法是否需要free该KEY

typedef struct BSTNode {
    KEY key;
    BSTData data;
    struct BSTNode* lchild;
    struct BSTNode* rchild;
}BST;

#pragma region Functions
BST* InitBST();
void Insert_BST(BST** T, KEY key, BSTData value);
BST* Search_BST(BST* T, KEY key);
BST* GetMin_BST(BST* T);
BST* GetMax_BST(BST* T);
void DeleteMin_BST(BST** T);
void DeleteMax_BST(BST** T);
void Delete_BST(BST** T, KEY key);
void Destroy_BST(BST** T);
int GetDepth_BST(BST* T);
#pragma region Traverse
    void InOrderTraverse(BST* T);
    void PreOrderTraverse(BST* T);
    void PostOrderTraverse(BST* T);
    void LevelOrderTraverse(BST* T);
#pragma endregion
#pragma endregion

#include "queue.h"   //在BST定义之后再include


/*初始化BST*/
BST* InitBST()
{
    return NULL;
}

/*插入新的树node*/
/*key:插入的键*/
/*value:该键对应的数据*/
/*若key与之前相同则覆盖value*/
void Insert_BST(BST** T, KEY key, BSTData value)
{
    //如果树node为NULL
    if ((*T) == NULL) {
        (*T) = (BST*)malloc(sizeof(BST));
        if ((*T) == NULL) {
            PRINT_STRING("BSTnode初始化动态分配内存失败");
        }

        (*T)->key = key;
        (*T)->data = value;
        (*T)->lchild = NULL;
        (*T)->rchild = NULL;
        return;
    }

    //如果树node不为NULL
    if ((*T)->key == key) {
        (*T)->data = value;
        return;
    }else if ((*T)->key < key) {
        Insert_BST(&((*T)->rchild), key, value);
    }else {
        Insert_BST(&((*T)->lchild), key, value);
    }
}

/*根据key搜索树node*/
BST* Search_BST(BST* T, KEY key)
{
    if (T == NULL) return NULL;

    if (T->key == key) return T;
    else if (T->key > key) {
        return Search_BST(T->lchild, key);
    }else {
        return Search_BST(T->rchild, key);
    }
}

/*获取最小的key的树node*/
BST* GetMin_BST(BST* T)
{
    if (T == NULL) return NULL;
    else if (T->lchild != NULL) return GetMin_BST(T->lchild);
    else return T;
}

/*获取最大的key的树node*/
BST* GetMax_BST(BST* T)
{
    if (T == NULL) return NULL;
    else if (T->rchild != NULL) return GetMax_BST(T->rchild);
    else return T;
}

/*删除最小的key的树node*/
void DeleteMin_BST(BST** T)
{
    if ((*T) == NULL) return;
    else if ((*T)->lchild != NULL && ((*T)->lchild && (*T)->lchild->lchild != NULL ) ) return DeleteMin_BST(&((*T)->lchild));
    else {
        //如果是树root
        if ((*T)->lchild == NULL){
            BST* temp = *T;
            *T = (*T)->rchild;
            //free(temp->key)
            //free(temp->data)
            temp->rchild = NULL;
            free(temp);
            temp = NULL;
        }else {
            BST* temp = (*T)->lchild;
            (*T)->lchild = temp->rchild;
            //free(temp->key)
            //free(temp->data)
            free(temp);
            temp = NULL;
        }
    return;
    }
}

/*删除最大的key的树node*/
void DeleteMax_BST(BST** T)
{
    if ((*T) == NULL) return;
    else if ((*T)->rchild != NULL && ((*T)->rchild && (*T)->rchild->rchild != NULL)) return DeleteMax_BST(&((*T)->rchild));
    else {
        //如果是树root
        if ((*T)->rchild == NULL) {
            BST* temp = *T;
            *T = (*T)->lchild;
            //free(temp->key)
            //free(temp->data)
            temp->lchild = NULL;
            free(temp);
            temp = NULL;
        }
        else {
            BST* temp = (*T)->rchild;
            (*T)->rchild = temp->lchild;
            //free(temp->key)
            //free(temp->data)
            free(temp);
            temp = NULL;
        }
        return;
    }
}

/*删除指定key的树node*/
void Delete_BST(BST** T, KEY key)
{
    if ((*T) == NULL) return;
    if ((*T)->key > key) {
        Delete_BST(&((*T)->lchild), key);
    }else if((*T)->key < key) {
        Delete_BST(&((*T)->rchild), key);
    }
    else {
        //如果有RChild,就用RChild的Min交换，
        if ((*T)->rchild) {
            BST* r_Min = (BST*)malloc(sizeof(BST));
            if (r_Min == NULL) {
                PRINT_STRING("Delete方法的r_Min动态分配内存失败");
                exit(-1);
            }

            //把RChild的Min先Copy再free
            BST* Copy_min = GetMin_BST((*T)->rchild);
            r_Min->key = Copy_min->key;
            r_Min->data = Copy_min->data;
            r_Min->lchild = NULL;
            r_Min->rchild = NULL;

            //二次递归free掉Min, Copy_min = NULL可以不写
            Delete_BST(T, Copy_min->key);
            Copy_min = NULL;

            (*T)->key = r_Min->key;
            (*T)->data = r_Min->data;
        }


        //如果没有RChild就用LChind的Max交换
        else if ((*T)->lchild){
            BST* l_Max = (BST*)malloc(sizeof(BST));
            if (l_Max == NULL) {
                PRINT_STRING("Delete方法的l_Max动态分配内存失败");
                exit(-1);
            }

            //把LChild的Man先Copy再free
            BST* Copy_max = GetMax_BST((*T)->lchild);
            l_Max->key = Copy_max->key;
            l_Max->data = Copy_max->data;
            l_Max->lchild = NULL;
            l_Max->rchild = NULL;

            //二次递归free掉Man, Copy_max = NULL可以不写
            Delete_BST(T, Copy_max->key);
            Copy_max = NULL;

            (*T)->key = l_Max->key;
            (*T)->data = l_Max->data;
        }

        //如果L/RChild都没有,就直接free掉
        else {
            free(*T);
            *T = NULL;
        }
    }
}

/*销毁BST*/
void Destroy_BST(BST** T)
{
    if (*T != NULL) {
        Destroy_BST(&((*T)->lchild));
        Destroy_BST(&((*T)->rchild));
        //free((*T)->data)
        //free((*T)->key)
        free(*T);
        *T = NULL;
    }
    return;
}

/*前序Traverse*/
void PreOrderTraverse(BST* T)
{
    if (T != NULL)
    {
        printf("key = %d data = %d\n", T->key, T->data);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
    return;
}

/*中序Traverse*/
void InOrderTraverse(BST* T)
{
    if (T != NULL)
    {
        PreOrderTraverse(T->lchild);
        printf("key = %d data = %d\n", T->key, T->data);
        PreOrderTraverse(T->rchild);
    }
    return;
}

/*后序Traverse*/
void PostOrderTraverse(BST* T)
{
    if (T != NULL)
    {
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
        printf("key = %d data = %d\n", T->key, T->data);
    }
    return;
}

/*层序Traverse*/
void LevelOrderTraverse(BST* T)
{
    if (T == NULL) return;

    Queue* Q = InitQueue();
    En_Queue(Q, T);
    while (!IsEmpty_Queue(Q)) {
        BST* temp = *GetValue_Queue(Q);
        De_Queue(Q);
        printf("key = %d data = %d\n", temp->key,temp->data);
        if (temp->lchild) En_Queue(Q, temp->lchild);
        if (temp->rchild) En_Queue(Q, temp->rchild);
    }
    Destroy_Queue(&Q);
    return;
}

/*获取树的深度*/
int GetDepth_BST(BST* T)
{
    if (T == NULL) return 0;

    int i = 0;
    int j = 0;
    i = GetDepth_BST(T->lchild);
    j = GetDepth_BST(T->rchild);
    return i > j ? i + 1 : j + 1;
}
