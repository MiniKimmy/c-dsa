#pragma once
#include<stdio.h>
#include<stdlib.h>
#define PRINT_STRING(x) printf("%s\n",x)

/*QNode_Data类型 (即根据外部导入需要修改该类型)*/
typedef BSTree TElement;

typedef enum Status {
    FALSE,
    TRUE,
}Status;

#pragma region Queue
typedef struct QNode {
    TElement Data;
    struct QNode *Next;
}QNode;

typedef struct LinkQueue {
    struct QNode * front;
    struct QNode * rear;
    int Count;
}Queue;
#pragma endregion

#pragma region Functions
Queue* InitQueue();
Status IsEmptyQueue(Queue * Q);
void EnterQueue(Queue * Q, TElement value);
TElement* GetHeadValue(Queue * Q);
void DeleteQueue(Queue * Q);
void ClearQueue(Queue * Q);
void DestroyQueue(Queue** Q);
#pragma endregion

/*Queue初始化*/
Queue* InitQueue()
{
    QNode* p = (QNode*)malloc(sizeof(QNode));
    if (p == NULL) {
        PRINT_STRING("QNode初始化动态分配内存失败");
        exit(-1);
    }
    Queue* ret = (Queue*)malloc(sizeof(Queue));
    if (ret == NULL) {
        PRINT_STRING("Queue初始化动态分配内存失败");
        exit(-1);
    }
    p->Next = NULL;
    ret->front = p;
    ret->rear = p;
    ret->Count = 0;
    return ret;
}

/*判断Queue是否为空*/
Status IsEmptyQueue(Queue * Q)
{
    if (Q == NULL) {
        PRINT_STRING("Queue为NULL");
        exit(-1);
    }

    if (Q->front == Q->rear)  return TRUE;
    else return FALSE;
}

/*入队*/
void EnterQueue(Queue * Q, TElement value)
{
    QNode* q = (QNode*)malloc(sizeof(QNode));
    q->Data = value;
    q->Next = NULL;
    Q->rear->Next = q;
    Q->rear = q;
    Q->Count++;
    return;
}

/*获取Queue队头*/
TElement* GetHeadValue(Queue * Q)
{
    if (IsEmptyQueue(Q)) return NULL;
    return &(Q->front->Next->Data);
}

/*出队*/
void DeleteQueue(Queue * Q)
{
    if (IsEmptyQueue(Q)) return;

    QNode* p = Q->front->Next;
    if (p == Q->rear) {
        Q->rear = Q->front;
        Q->front->Next = NULL;
        free(p);
        p->Next = NULL;
    }
    else {
        Q->front->Next = p->Next;
        free(p);
        p->Next = NULL;
    }
    Q->Count--;
    return;
}

/*清空队列,返回Queue头哨兵*/
void ClearQueue(Queue * Q)
{
    if (IsEmptyQueue(Q)) return;

    while (!IsEmptyQueue(Q)) {
        DeleteQueue(Q);
    }
    return;
}

/*销毁Queue,返回NULL*/
void DestroyQueue(Queue** Q)
{
    if (*Q == NULL) {
        PRINT_STRING("Queue为NULL");
        return;
    }

    ClearQueue(*Q);
    free(*Q);
    *Q = NULL;
    return;
}
