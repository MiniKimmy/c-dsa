#include<stdio.h>
#include<stdlib.h>
#define PRINT_STRING(x) printf("%s\n",x)


typedef int TElement;  //import到其他文件时候需要修改该类型

/*Bool枚举*/
typedef enum Status {
    FALSE,
    TRUE,
}Status;

/*结点Node数据类型*/
typedef struct Node {
    TElement data;
    struct Node* next;
}Node;

typedef struct Queue {
    Node* front;    //头哨兵[不存data]
    Node* rear;     //尾哨兵
    int count;
}Queue;

#pragma region Functions
Queue* InitQueue();
Status IsEmpty_Queue(Queue * Q);
void En_Queue(Queue * Q, TElement value);
TElement* GetValue_Queue(Queue* Q);
void De_Queue(Queue * Q);
void Clear_Queue(Queue * Q);
void Destroy_Queue(Queue** Q);
int GetSize_Queue(Queue * Q);
#pragma endregion


/*初始化Queue*/
Queue* InitQueue()
{
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        PRINT_STRING("node初始化动态分配内存失败");
        exit(-1);
    }

    Queue* ret = (Queue*)malloc(sizeof(Queue));
    if (ret == NULL) {
        PRINT_STRING("Queue初始化动态分配内存失败");
        exit(-1);
    }

    node->next = NULL;
    ret->front = node;
    ret->rear = node;
    ret->count = 0;
    return ret;
}

/*判断Queue是否为空*/
Status IsEmpty_Queue(Queue* Q)
{
    if (Q == NULL) {
        PRINT_STRING("Queue为NULL");
        return TRUE;
    }

    if (Q->front == Q->rear)  return TRUE;
    else return FALSE;
}

/*入队*/
void En_Queue(Queue* Q, TElement value)
{
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        PRINT_STRING("入队node初始化动态分配内存失败");
        exit(-1);
    }

    node->data = value;
    node->next = NULL;
    Q->rear->next = node;
    Q->rear = node;
    Q->count++;
    return;
}

/*返回队头元素的指针*/
TElement* GetValue_Queue(Queue* Q)
{
    if (IsEmpty_Queue(Q)) return NULL;
    return &(Q->front->next->data);
}

/*出队*/
void De_Queue(Queue* Q)
{
    if (IsEmpty_Queue(Q)) return;
    Node* node = Q->front->next;

    //如果出队最后的队头元素
    if (node == Q->rear){
        Q->rear = Q->front;
    }

    Q->front->next = node->next;
    free(node);
    node = NULL;
    Q->count--;
    return;
}

/*清除Queue所有元素*/
/*头哨兵保留*/
void Clear_Queue(Queue* Q)
{
    while (!IsEmpty_Queue(Q)){
        De_Queue(Q);
    }
    return;
}

/*返回Queue当前元素个数*/
int GetSize_Queue(Queue* Q)
{
    if (Q == NULL) return;
    else return Q->count;
}

/*销毁Queue*/
void Destroy_Queue(Queue** Q)
{
    if (*Q == NULL) return;

    Clear_Queue(*Q);
    free(*Q);
    *Q = NULL;
    return;
}