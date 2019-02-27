#pragma once
#include<stdio.h>
#include<stdlib.h>
#define PRINT_STRING(x) printf("%s\n",x)

/*QNode_Data���� (�������ⲿ������Ҫ�޸ĸ�����)*/
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

/*Queue��ʼ��*/
Queue* InitQueue()
{
    QNode* p = (QNode*)malloc(sizeof(QNode));
    if (p == NULL) {
        PRINT_STRING("QNode��ʼ����̬�����ڴ�ʧ��");
        exit(-1);
    }
    Queue* ret = (Queue*)malloc(sizeof(Queue));
    if (ret == NULL) {
        PRINT_STRING("Queue��ʼ����̬�����ڴ�ʧ��");
        exit(-1);
    }
    p->Next = NULL;
    ret->front = p;
    ret->rear = p;
    ret->Count = 0;
    return ret;
}

/*�ж�Queue�Ƿ�Ϊ��*/
Status IsEmptyQueue(Queue * Q)
{
    if (Q == NULL) {
        PRINT_STRING("QueueΪNULL");
        exit(-1);
    }

    if (Q->front == Q->rear)  return TRUE;
    else return FALSE;
}

/*���*/
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

/*��ȡQueue��ͷ*/
TElement* GetHeadValue(Queue * Q)
{
    if (IsEmptyQueue(Q)) return NULL;
    return &(Q->front->Next->Data);
}

/*����*/
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

/*��ն���,����Queueͷ�ڱ�*/
void ClearQueue(Queue * Q)
{
    if (IsEmptyQueue(Q)) return;

    while (!IsEmptyQueue(Q)) {
        DeleteQueue(Q);
    }
    return;
}

/*����Queue,����NULL*/
void DestroyQueue(Queue** Q)
{
    if (*Q == NULL) {
        PRINT_STRING("QueueΪNULL");
        return;
    }

    ClearQueue(*Q);
    free(*Q);
    *Q = NULL;
    return;
}
