typedef struct BNode {
    int key;
    int data;
    struct BNode* lchild;
    struct BNode* rchild;
}BST;

#define EXITTAG -2018
#include"queue.h"

#pragma region BSTFunctions
BST* initBST();
BST* createBSTByKeys();
int insertBST(BST** T, int key, int value);
BST* searchBST(BST* T, int key);
BST* getMinBST(BST* T);
BST* getMaxBST(BST* T);
int getDepthBST(BST* T);
BST* getParentBST(BST* T, int key);
BST* getLChildBST(BST* T, int key);
BST* getRChildBST(BST* T, int key);
int deleteBST(BST** T, int key);
int deleteMinBST(BST** T);
int deleteMaxBST(BST** T);
int destroyBST(BST** T);
void inOrderBST(BST* T);
void preOrderBST(BST* T);
void postOrderBST(BST* T);
void levelOrderBST(BST* T);
#pragma endregion


BST* initBST()
{
    BST* ret = NULL;
    return ret;
}

BST* createBSTByKeys()
{
    int n;
    printf("请输入需要添加的结点总数(输入-2018退出): ");
    scanf_s("%d", &n);
    if (n == EXITTAG) exit(0);

    while (n <= 0) {
        printf("input:\'%d\'<0,请输入>0的数字:",n);
        scanf_s("%d", &n);
        if (n == EXITTAG) exit(0);
    }

    BST* root = initBST();

    int value; 
    int key;
    for (int i = 0; i < n; i++)
    {
        printf("请输入第[%d]个的结点key: ", i);
        scanf_s("%d", &key);
        printf("请输入第[%d]个的结点value: ", i);
        scanf_s("%d", &value);

        if (key == EXITTAG) exit(0);
        insertBST(&root, key, i + 1);
    }

    return root;
}

int insertBST(BST** T, int key, int value)
{
    if (*T == NULL) {
        *T = (BST*)malloc(sizeof(BST));
        (*T)->lchild = NULL;
        (*T)->rchild = NULL;
        (*T)->data = value;
        (*T)->key = key;
        return 1;
    }else if ((*T)->key > key) {
        insertBST(&((*T)->lchild), key, value);
    }else if((*T)->key <= key){
        insertBST(&((*T)->rchild), key, value);
    }

    return 0 ;
}

BST* getParentBST(BST* T ,int key)
{
    if (T == NULL || (T && T->key == key)) return NULL;
    if ((T->lchild && T->lchild->key == key) || (T->rchild &&T->rchild->key == key) ) return T;
    else if (T->key > key) {
        return getParentBST(T->lchild, key);
    }else if (T->key < key) {
        return getParentBST(T->rchild, key);
    }
    return NULL;
}

BST* getLChildBST(BST* T, int key)
{
    BST* p = searchBST(T, key);
    return p?p->lchild:NULL;
}

BST* getRChildBST(BST* T, int key)
{
    BST* p = searchBST(T, key);
    return p?p->rchild:NULL;
}

BST* getMaxBST(BST* T)
{
    if (T == NULL) return T;
    if (T->rchild) {
        return getMaxBST(T->rchild);
    }else {
        return T;
    }
}

BST* getMinBST(BST* T)
{
    if (T == NULL) return T;
    if (T->lchild) {
        return getMinBST(T->lchild);
    }else {
        return T;
    }
}

int deleteMinBST(BST** T)
{
    if (*T == NULL) return 0;

    if ((*T)->lchild && (*T)->lchild->lchild == NULL) {
        BST* p = (*T)->lchild;
        (*T)->lchild = p->rchild;
        free(p);
        return 1;
    }else if ((*T)->lchild) {
        return deleteMinBST((*T)->lchild);
    }else {
        BST* p = (*T);
        *T = p->rchild;
        free(p);
        return 1;
    }
}

int deleteMaxBST(BST** T)
{
    if (*T == NULL) return 0;

    if ((*T)->rchild && (*T)->rchild->rchild == NULL) {
        BST* p = (*T)->rchild;
        (*T)->rchild = p->lchild;
        free(p);
        return 1;
    }else if ((*T)->rchild) {
        return deleteMaxBST((*T)->rchild);
    }else {
        BST* p = (*T);
        *T = p->lchild;
        free(p);
        return 1;
    }
}

int deleteBST(BST** T, int key)
{
    if ((*T) == NULL) return 0;

    if ((*T)->key > key) {
        return deleteBST(&((*T)->lchild), key);
    }
    else if ((*T)->key < key) {
        return deleteBST(&((*T)->rchild), key);
    }else {

        //如果有RChild
        if ((*T)->rchild) {
            BST* rChild_min = getMinBST((*T)->rchild);
            struct BNode* mark_rChild = (struct BNode*)malloc(sizeof(struct BNode));
            mark_rChild->key = rChild_min->key;
            mark_rChild->data = rChild_min->data;
            mark_rChild->lchild = NULL;
            mark_rChild->rchild = NULL;

            deleteBST(T, rChild_min->key);
            rChild_min = NULL;
            (*T)->data = mark_rChild->data;
            (*T)->key = mark_rChild->key;
            return 1;
        }
        
        //如果只有LChild
        else if((*T)->lchild){
            BST* lChild_max = getMaxBST((*T)->lchild);
            struct BNode* mark_lChild = (struct BNode*)malloc(sizeof(struct BNode));
            mark_lChild->key = lChild_max->key;
            mark_lChild->data = lChild_max->data;
            mark_lChild->lchild = NULL;
            mark_lChild->rchild = NULL;

            deleteBST(T, lChild_max->key);
            lChild_max = NULL;
            (*T)->data = mark_lChild->data;
            (*T)->key = mark_lChild->key;
        }else {
            //若无左右Child直接free,使用**指针ref,所删掉即与原Souce同步删除.
            free(*T);
            *T = NULL;
        }
    }
    return 0;
}

BST* searchBST(BST* T, int key)
{
    if (T == NULL) return NULL;

    if (T->key > key) {
        return searchBST(T->lchild, key);
    }else if (T->key < key) {
        return searchBST(T->rchild, key);
    }else {
        return T;
    }
    return NULL;
}

int getDepthBST(BST* T)
{
    int i,j = 0;
    i = T->lchild? getDepthBST(T->lchild) : 0;
    j = T->rchild? getDepthBST(T->rchild) : 0;
    return i > j ? ++i : ++j;
}

int destroyBST(BST** T)
{
    if (*T == NULL) return 0;
    
    destroyBST(&((*T)->lchild));
    destroyBST(&((*T)->rchild));
    free(*T);
    *T = NULL;
    return 1;
}

void inOrderBST(BST* T)
{
    if (T == NULL) return;

    inOrderBST(T->lchild);
    printf("%d\n", T->data);
    inOrderBST(T->rchild);
    return;
}

void preOrderBST(BST* T)
{
    if (T == NULL) return;

    printf("%d\n", T->data);
    preOrderBST(T->lchild);
    preOrderBST(T->rchild);
    return;
}

void postOrderBST(BST* T)
{
    if (T == NULL) return;

    postOrderBST(T->lchild);
    postOrderBST(T->rchild);
    printf("%d\n", T->data);
    return;
}

void levelOrderBST(BST* T)
{
    if (T == NULL) return;
    Queue* q = initQueue();
    enQueue(q, T);
    
    while (q->count != 0) {
        BST* t = *peek(q);
        deQueue(q);
        printf("[%d]=%d, ", t->key,t->data);
        if (t->lchild) enQueue(q, t->lchild);
        if (t->rchild) enQueue(q, t->rchild);
    }

    destroyQueue(&q);
    return;
}
