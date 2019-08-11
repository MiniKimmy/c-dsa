#include<stdio.h>
#include<stdlib.h>
#define PRINT_STRING(x) printf("%s\n",x)

typedef int BiTreeData;  //import到其他文件时候需要修改该类型,Destroy是否需要free掉BiTreeData

typedef struct BiNode {
    BiTreeData data;
    struct BiNode* lchild;
    struct BiNode* rchild;
}BiTree;

#pragma region Functions
BiTree* InitBiTree();
void Insert_BiTree(BiTree** T,BiTreeData value);
BiTree* GetParent_BiTree(BiTree* T, BiTreeData value);
BiTree* GetLeftChild_BiTree(BiTree* T, BiTreeData value);
BiTree* GetRightChild_BiTree(BiTree* T, BiTreeData value);
BiTree* GetBiNode(BiTree* T, BiTreeData value);
void Destroy_BiTree(BiTree** T);
int GetDepth_BiTree(BiTree* T);
#pragma region Traverse
    void PreOrderTraverse(BiTree* T);
    void InOrderTraverse(BiTree* T);
    void PostOrderTraverse(BiTree* T);
    void LevelOrderTraverse(BiTree* T);
#pragma endregion
#pragma endregion

#include "queue.h" //在BiTree定义之后再Include

/*初始化BiTree*/
BiTree* InitBiTree()
{
    return NULL;
}

/*添加子BiNode*/
void Insert_BiTree(BiTree** T,BiTreeData value)
{
    //如果树node是NULL
    if ((*T) == NULL) {
        (*T) = (BiTree*)malloc(sizeof(BiTree));
        if ((*T) == NULL) {
            PRINT_STRING("Binode初始化动态分配内存失败");
        }
        (*T)->data = value;
        (*T)->lchild = NULL;
        (*T)->rchild = NULL;
        return;
    }

    //如果树node不为NULL
    if ((*T)->data <= value) {
        Insert_BiTree(&((*T)->rchild), value);
    }else {
        Insert_BiTree(&((*T)->lchild), value);
    }
}

/*返回匹配value的第一个树node*/
BiTree* GetBiNode(BiTree* T, BiTreeData value)
{
    if (T == NULL) return NULL;

    if (T->data == value) return T;
    else if (T->data > value) {
        return GetBiNode(T->lchild,value);
    }else {
        return GetBiNode(T->rchild,value);
    }
}

/*返回匹配value的第一个树node的LChild*/
BiTree* GetLeftChild_BiTree(BiTree* T, BiTreeData value)
{
    BiTree* result = GetBiNode(T, value);
    if (result == NULL) return NULL;
    else return result->lchild;
}

/*返回匹配value的第一个树node的RChild*/
BiTree* GetRightChild_BiTree(BiTree* T, BiTreeData value)
{
    BiTree* result = GetBiNode(T, value);
    if (result == NULL) return NULL;
    else return result->rchild;
}

/*返回匹配value的第一个树node的Parent*/
BiTree* GetParent_BiTree(BiTree* T, BiTreeData value)
{
    if (T == NULL || (T->lchild == NULL && T->rchild == NULL) || (T->data == value) ) return NULL;

    if ((T->lchild && T->lchild->data == value) || (T->rchild && T->rchild->data == value) ) return T;
    else if (T->data > value) {
        return GetParent_BiTree(T->lchild, value);
    }else {
        return GetParent_BiTree(T->rchild, value);
    }

}

/*销毁BiTree*/
void Destroy_BiTree(BiTree** T)
{
    if (*T != NULL){
        Destroy_BiTree(&((*T)->lchild));
        Destroy_BiTree(&((*T)->rchild));
        //free((*T)->data)
        free(*T);
        *T = NULL;
    }
    return;
}

/*前序Traverse*/
void PreOrderTraverse(BiTree* T)
{
    if (T != NULL)
    {
        printf("%d\n", T->data);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
    return;
}

/*中序Traverse*/
void InOrderTraverse(BiTree* T)
{
    if (T != NULL)
    {
        PreOrderTraverse(T->lchild);
        printf("%d\n", T->data);
        PreOrderTraverse(T->rchild);
    }
    return;
}

/*后序Traverse*/
void PostOrderTraverse(BiTree* T)
{
    if (T != NULL)
    {
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
        printf("%d\n", T->data);
    }
    return;
}

/*层序Traverse*/
void LevelOrderTraverse(BiTree* T)
{
    if (T == NULL) return;

    Queue* Q = InitQueue();
    En_Queue(Q, T);
    while (!IsEmpty_Queue(Q)){
        BiTree* temp = *GetValue_Queue(Q);
        De_Queue(Q);
        printf("%d\n", temp->data);
        if (temp->lchild) En_Queue(Q, temp->lchild);
        if (temp->rchild) En_Queue(Q, temp->rchild);
    }
    Destroy_Queue(&Q);
    return;
}

/*获取树的深度*/
int GetDepth_BiTree(BiTree* T)
{
    if (T == NULL) return 0;

    int i = 0;
    int j = 0;
    i = GetDepth(T->lchild);
    j = GetDepth(T->rchild);
    return i > j ? i + 1 : j + 1;
}
