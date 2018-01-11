#include<stdio.h>
#include<stdlib.h>
#define PRINT_STRING(x) printf("%s\n",x)

typedef int BSTData;  //import�������ļ�ʱ����Ҫ�޸ĸ�����,Destroy/Delete�ȷ����Ƿ���Ҫfree��BSTData
typedef int KEY;      //import�������ļ�ʱ����Ҫ�޸ĸ�����,Destroy/Delete�ȷ����Ƿ���Ҫfree��KEY

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

#include "queue.h"   //��BST����֮����include


/*��ʼ��BST*/
BST* InitBST()
{
    return NULL;
}

/*�����µ���node*/
/*key:����ļ�*/
/*value:�ü���Ӧ������*/
/*��key��֮ǰ��ͬ�򸲸�value*/
void Insert_BST(BST** T, KEY key, BSTData value)
{
    //�����nodeΪNULL
    if ((*T) == NULL) {
        (*T) = (BST*)malloc(sizeof(BST));
        if ((*T) == NULL) {
            PRINT_STRING("BSTnode��ʼ����̬�����ڴ�ʧ��");
        }

        (*T)->key = key;
        (*T)->data = value;
        (*T)->lchild = NULL;
        (*T)->rchild = NULL;
        return;
    }

    //�����node��ΪNULL
    if ((*T)->key == key) {
        (*T)->data = value;
        return;
    }else if ((*T)->key < key) {
        Insert_BST(&((*T)->rchild), key, value);
    }else {
        Insert_BST(&((*T)->lchild), key, value);
    }
}

/*����key������node*/
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

/*��ȡ��С��key����node*/
BST* GetMin_BST(BST* T)
{
    if (T == NULL) return NULL;
    else if (T->lchild != NULL) return GetMin_BST(T->lchild);
    else return T;
}

/*��ȡ����key����node*/
BST* GetMax_BST(BST* T)
{
    if (T == NULL) return NULL;
    else if (T->rchild != NULL) return GetMax_BST(T->rchild);
    else return T;
}

/*ɾ����С��key����node*/
void DeleteMin_BST(BST** T)
{
    if ((*T) == NULL) return;
    else if ((*T)->lchild != NULL && ((*T)->lchild && (*T)->lchild->lchild != NULL ) ) return DeleteMin_BST(&((*T)->lchild));
    else {
        //�������root
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

/*ɾ������key����node*/
void DeleteMax_BST(BST** T)
{
    if ((*T) == NULL) return;
    else if ((*T)->rchild != NULL && ((*T)->rchild && (*T)->rchild->rchild != NULL)) return DeleteMax_BST(&((*T)->rchild));
    else {
        //�������root
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

/*ɾ��ָ��key����node*/
void Delete_BST(BST** T, KEY key)
{
    if ((*T) == NULL) return;
    if ((*T)->key > key) {
        Delete_BST(&((*T)->lchild), key);
    }else if((*T)->key < key) {
        Delete_BST(&((*T)->rchild), key);
    }
    else {
        //�����RChild,����RChild��Min������
        if ((*T)->rchild) {
            BST* r_Min = (BST*)malloc(sizeof(BST));
            if (r_Min == NULL) {
                PRINT_STRING("Delete������r_Min��̬�����ڴ�ʧ��");
                exit(-1);
            }

            //��RChild��Min��Copy��free
            BST* Copy_min = GetMin_BST((*T)->rchild);
            r_Min->key = Copy_min->key;
            r_Min->data = Copy_min->data;
            r_Min->lchild = NULL;
            r_Min->rchild = NULL;

            //���εݹ�free��Min, Copy_min = NULL���Բ�д
            Delete_BST(T, Copy_min->key);
            Copy_min = NULL;

            (*T)->key = r_Min->key;
            (*T)->data = r_Min->data;
        }


        //���û��RChild����LChind��Max����
        else if ((*T)->lchild){
            BST* l_Max = (BST*)malloc(sizeof(BST));
            if (l_Max == NULL) {
                PRINT_STRING("Delete������l_Max��̬�����ڴ�ʧ��");
                exit(-1);
            }

            //��LChild��Man��Copy��free
            BST* Copy_max = GetMax_BST((*T)->lchild);
            l_Max->key = Copy_max->key;
            l_Max->data = Copy_max->data;
            l_Max->lchild = NULL;
            l_Max->rchild = NULL;

            //���εݹ�free��Man, Copy_max = NULL���Բ�д
            Delete_BST(T, Copy_max->key);
            Copy_max = NULL;

            (*T)->key = l_Max->key;
            (*T)->data = l_Max->data;
        }

        //���L/RChild��û��,��ֱ��free��
        else {
            free(*T);
            *T = NULL;
        }
    }
}

/*����BST*/
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

/*ǰ��Traverse*/
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

/*����Traverse*/
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

/*����Traverse*/
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

/*����Traverse*/
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

/*��ȡ�������*/
int GetDepth_BST(BST* T)
{
    if (T == NULL) return 0;

    int i = 0;
    int j = 0;
    i = GetDepth_BST(T->lchild);
    j = GetDepth_BST(T->rchild);
    return i > j ? i + 1 : j + 1;
}
