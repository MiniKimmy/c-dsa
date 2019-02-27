#include<stdio.h>
#include<stdlib.h>
#define PRINT_STRING(x) printf("%s\n",x)

typedef int BiTreeData;  //import�������ļ�ʱ����Ҫ�޸ĸ�����,Destroy�Ƿ���Ҫfree��BiTreeData

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

#include "queue.h" //��BiTree����֮����Include

/*��ʼ��BiTree*/
BiTree* InitBiTree()
{
    return NULL;
}

/*�����BiNode*/
void Insert_BiTree(BiTree** T,BiTreeData value)
{
    //�����node��NULL
    if ((*T) == NULL) {
        (*T) = (BiTree*)malloc(sizeof(BiTree));
        if ((*T) == NULL) {
            PRINT_STRING("Binode��ʼ����̬�����ڴ�ʧ��");
        }
        (*T)->data = value;
        (*T)->lchild = NULL;
        (*T)->rchild = NULL;
        return;
    }

    //�����node��ΪNULL
    if ((*T)->data <= value) {
        Insert_BiTree(&((*T)->rchild), value);
    }else {
        Insert_BiTree(&((*T)->lchild), value);
    }
}

/*����ƥ��value�ĵ�һ����node*/
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

/*����ƥ��value�ĵ�һ����node��LChild*/
BiTree* GetLeftChild_BiTree(BiTree* T, BiTreeData value)
{
    BiTree* result = GetBiNode(T, value);
    if (result == NULL) return NULL;
    else return result->lchild;
}

/*����ƥ��value�ĵ�һ����node��RChild*/
BiTree* GetRightChild_BiTree(BiTree* T, BiTreeData value)
{
    BiTree* result = GetBiNode(T, value);
    if (result == NULL) return NULL;
    else return result->rchild;
}

/*����ƥ��value�ĵ�һ����node��Parent*/
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

/*����BiTree*/
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

/*ǰ��Traverse*/
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

/*����Traverse*/
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

/*����Traverse*/
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

/*����Traverse*/
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

/*��ȡ�������*/
int GetDepth_BiTree(BiTree* T)
{
    if (T == NULL) return 0;

    int i = 0;
    int j = 0;
    i = GetDepth(T->lchild);
    j = GetDepth(T->rchild);
    return i > j ? i + 1 : j + 1;
}
