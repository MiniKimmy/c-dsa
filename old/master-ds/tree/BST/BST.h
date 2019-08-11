typedef struct BNode {
    int key;
    int data;
    struct BNode* lchild;
    struct BNode* rchild;
}BST;

#define EXITTAG -2018
#define ARRAYSIZE 10
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
void levelOrderBST_SqQueue(BST* T);
void inOrderNonrecursion(BST* T);
void preOrderNonrecursion(BST* T);
void postOrderNonrecursion(BST* T);
#pragma endregion


BST* initBST(){
    BST* ret = NULL;
    return ret;
}

BST* createBSTByKeys(){
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
        if (key == EXITTAG) exit(0);

        printf("请输入第[%d]个的结点value: ", i);
        scanf_s("%d", &value);
        if (value == EXITTAG) exit(0);

        insertBST(&root, key, value);
    }

    return root;
}

int insertBST(BST** T, int key, int value){
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

BST* getParentBST(BST* T ,int key){
    if (T == NULL || (T && T->key == key)) return NULL;
    if ((T->lchild && T->lchild->key == key) || (T->rchild &&T->rchild->key == key) ) return T;
    else if (T->key > key) {
        return getParentBST(T->lchild, key);
    }else if (T->key < key) {
        return getParentBST(T->rchild, key);
    }
    return NULL;
}

BST* getLChildBST(BST* T, int key){
    BST* p = searchBST(T, key);
    return p?p->lchild:NULL;
}

BST* getRChildBST(BST* T, int key){
    BST* p = searchBST(T, key);
    return p?p->rchild:NULL;
}

BST* getMaxBST(BST* T){
    if (T == NULL) return T;
    if (T->rchild) {
        return getMaxBST(T->rchild);
    }else {
        return T;
    }
}

BST* getMinBST(BST* T){
    if (T == NULL) return T;
    if (T->lchild) {
        return getMinBST(T->lchild);
    }else {
        return T;
    }
}

int deleteMinBST(BST** T){
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

int deleteMaxBST(BST** T){
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

int deleteBST(BST** T, int key){
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
            return 1;
        }else {
            //若无左右Child直接free,使用**指针ref,所删掉即与原Souce同步删除.
            free(*T);
            *T = NULL;
            return 1;
        }
    }
    return 0;
}

BST* searchBST(BST* T, int key){
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

int getDepthBST(BST* T){
    int i,j = 0;
    i = T->lchild? getDepthBST(T->lchild) : 0;
    j = T->rchild? getDepthBST(T->rchild) : 0;
    return i > j ? ++i : ++j;
}

int destroyBST(BST** T){
    if (*T == NULL) return 0;

    destroyBST(&((*T)->lchild));
    destroyBST(&((*T)->rchild));
    free(*T);
    *T = NULL;
    return 1;
}

void inOrderBST(BST* T){
    if (T == NULL) return;

    inOrderBST(T->lchild);
    printf("%d\n", T->data);
    inOrderBST(T->rchild);
    return;
}

void preOrderBST(BST* T){
    if (T == NULL) return;

    printf("%d\n", T->data);
    preOrderBST(T->lchild);
    preOrderBST(T->rchild);
    return;
}

void postOrderBST(BST* T){
    if (T == NULL) return;

    postOrderBST(T->lchild);
    postOrderBST(T->rchild);
    printf("%d\n", T->data);
    return;
}

void levelOrderBST(BST* T){
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

void levelOrderBST_SqQueue(BST* T) {

    if (T == NULL) return;
    int front = 0;
    int rear = 0;

    BST** sqQueue = (BST**)malloc(sizeof(BST*) * ARRAYSIZE);
    sqQueue[rear] = T;
    rear = (rear + 1) % ARRAYSIZE;

    while (rear != front) {
        BST* t = sqQueue[front];
        front = (front + 1) % ARRAYSIZE;
        printf("[%d]=%d, ", t->key,t->data);

        if (t->lchild) {
            sqQueue[rear] = t->lchild;
            rear = (rear + 1) % ARRAYSIZE;
        }
        if (t->rchild) {
            sqQueue[rear] = t->rchild;
            rear = (rear + 1) % ARRAYSIZE;
        }
    }

    free(sqQueue);
    return;
}

void preOrderNonrecursion(BST* T) {

    if (T == NULL) return;
    BST** stack = (BST**)malloc(sizeof(BST*) * ARRAYSIZE);
    int top = -1;
    stack[++top] = T;

    while (top != -1) {
        BST* t = stack[top--];
        printf("[%d]=%d, ", t->key, t->data);
        if (t->rchild) stack[++top] = t->rchild;
        if (t->lchild) stack[++top] = t->lchild;
    }

    free(stack);
    return;
}

void inOrderNonrecursion(BST* T) {

    if (T == NULL) return;
    BST** stack = (BST**)malloc(sizeof(BST*) * ARRAYSIZE);
    int top = -1;

    BST* t = T; //root视作无parent的左Child
    while (top != -1 || t != NULL) {
        while (t != NULL) {
            stack[++top] = t;
            t = t->lchild;
        }

        if (top != -1) {
            t = stack[top--]; //重置上一个左Child
            printf("[%d]=%d, ", t->key, t->data);
            t = t->rchild;   //右移一下,然后把左边的树都先输出~
        }
    }

    free(stack);
    return;
}

void postOrderNonrecursion(BST* T) {
    //先序(非递归)的左Child/右Child进栈顺序相反-->获得逆后续遍历(非递归)-->再重新堆栈逆一遍则是后续遍历(非递归)
    if (T == NULL) return;
    BST** stack1 = (BST**)malloc(sizeof(BST*) * ARRAYSIZE);
    int top1 = -1;

    BST** stack2 = (BST**)malloc(sizeof(BST*) * ARRAYSIZE);
    int top2 = -1;

    stack1[++top1] = T;
    while (top1 != -1) {
        BST* t1 = stack1[top1--];

        stack2[++top2] = t1;
        if (t1->lchild) stack1[++top1] = t1->lchild;
        if (t1->rchild) stack1[++top1] = t1->rchild;
    }

    while (top2 != -1) {
        BST* t2 = stack2[top2--];
        printf("[%d]=%d, ", t2->key,t2->data);
    }

    free(stack1);
    free(stack2);
    return;
}
