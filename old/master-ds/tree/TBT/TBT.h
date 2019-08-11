#include<stdlib.h>
#include<stdio.h>

#define LINK 0
#define THREAD 1
#define EXITTAG -2018

typedef struct TBTNode {
    int key;
    int data;
    int tagL;
    int tagR;
    struct TBTNode* lchild;
    struct TBTNode* rchild;
}TBT;

#pragma region TBTFunctions
TBT* initTBT();
TBT* createTBTByKeys();
void insertTBT(TBT** T, int key, int value);
void inThread(TBT* T, TBT** pre);
void inOrderTBT(TBT* T);
TBT* getNextTBNode(TBT* T);
TBT* getLeftTBNode(TBT* T);
TBT* getRightTBNode(TBT* T);
void inOrderTBT(TBT* T);
#pragma endregion

TBT* initTBT() {
    TBT* ret = NULL;
    return ret;
}

TBT* createTBTByKeys() {
    int n;
    printf("��������Ҫ��ӵĽ������(����-2018�˳�): ");
    scanf_s("%d", &n);
    if (n == EXITTAG) exit(0);

    while (n <= 0) {
        printf("input:\'%d\'<0,������>0������:", n);
        scanf_s("%d", &n);
        if (n == EXITTAG) exit(0);
    }

    TBT* root = initTBT();

    int value;
    int key;
    for (int i = 0; i < n; i++)
    {
        printf("�������[%d]���Ľ��key: ", i);
        scanf_s("%d", &key);
        if (key == EXITTAG) exit(0);

        printf("�������[%d]���Ľ��value: ", i);
        scanf_s("%d", &value);
        if (value == EXITTAG) exit(0);

        insertBST(&root, key, value);
        insertTBT(&root, key, i+1);
    }

    TBT* pre = (TBT*)malloc(sizeof(TBT));
    pre = NULL;
    inThread(root, &pre); 

    //pre->rchild = root; ˫�ڱ��Ű�������root����
    return root;
}

void insertTBT(TBT** T, int key, int value) {
    if (*T == NULL) {
        *T = (TBT*)malloc(sizeof(TBT));
        (*T)->key = key;
        (*T)->data = value;
        (*T)->lchild = NULL;
        (*T)->rchild = NULL;
        (*T)->tagL = LINK; //Ĭ����LINK (Ĭ����LChild)
        (*T)->tagR = LINK; //Ĭ����LINK (Ĭ����RChild)
        return;
    }
    else if ((*T)->key > key) {
        insertTBT(&((*T)->lchild), key, value);
    }else {
        insertTBT(&((*T)->rchild), key, value);
    }
}

void inThread(TBT* T, TBT** pre){
    if (T) {
        inThread(T->lchild, pre);

        if (T->lchild == NULL) {
            T->lchild = *pre;
            T->tagL = THREAD;
        }

        if (T->rchild == NULL) {
            T->tagR = THREAD;
        }
        
        if ((*pre) && (*pre)->rchild == NULL) {
            (*pre)->rchild = T;
        }

        *pre = T; 
        inThread(T->rchild, pre);
    }
}

TBT* getLeftTBNode(TBT* T){
    if (T == NULL) return;

    TBT* ret = T;
    while (ret->tagL == LINK) {
        ret = ret->lchild;
    }

    return ret;
}

TBT* getRightTBNode(TBT* T){
    if (T == NULL) return;

    TBT* ret = T;
    while (ret->tagR == LINK) {
        ret = ret->rchild;
    }

    return ret;
}

TBT* getNextTBNode(TBT* T){
    if (T == NULL) return;

    if (T->tagR == THREAD) {
        return getLeftTBNode(T);
    }else {
        return T->rchild;
    }
}

void inOrderTBT(TBT* T) {
    if (T == NULL) return;

    TBT* t = getLeftTBNode(T);
    while (t != NULL) {
        printf("[%d]=%d, ", t->key, t->data);

        if (t->tagR == LINK) {
            t = getLeftTBNode(t->rchild);
        }else {
            t = t->rchild;
        }
    }
}
