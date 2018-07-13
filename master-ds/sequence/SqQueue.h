#include<stdlib.h>
#include<stdio.h>

#define SqQueueInitSIZE 5  //normal size

typedef struct {
    int* data;
    int front;
    int rear;
    int capacity;
}SqQueue;

#pragma region SqQueueFunctions
SqQueue* initSqQueue();
SqQueue* createSqQueue(int size);
int enSqQueue(SqQueue* Q, int value);
int deSqQueue(SqQueue* Q);
int isEmptySqQueue(SqQueue* Q);
int isFullSqQueue(SqQueue* Q);
int* peek(SqQueue* Q);
int clearSqQueue(SqQueue* Q);
int destroySqQueue(SqQueue** Q);
#pragma endregion

SqQueue* initSqQueue()
{
    SqQueue* queue = (SqQueue*)malloc(sizeof(SqQueue));
    queue->front = 0;
    queue->rear = 0;
    queue->data = (int*)malloc(sizeof(int) * SqQueueInitSIZE);
    queue->capacity = SqQueueInitSIZE;
    return queue;
}

SqQueue* createSqQueue(int size)
{
    SqQueue* queue = (SqQueue*)malloc(sizeof(SqQueue));
    queue->front = 0;
    queue->rear = 0;
    queue->data = (int*)malloc(sizeof(int) * size);
    queue->capacity = size;
    return queue;
}

int isEmptySqQueue(SqQueue* Q)
{
    if (Q == NULL || Q->front == Q->rear) return 1;
    else return 0;
}

int isFullSqQueue(SqQueue* Q)
{
    if (Q == NULL) exit(-1);
    else if ((Q->rear + 1) % Q->capacity == Q->front) return 1;
    else return 0;
}

int enSqQueue(SqQueue* Q, int value)
{
    if (isFullSqQueue == 0) return 0;
    Q->data[Q->rear] = value;
    Q->rear = (Q->rear + 1) % Q->capacity;
    return 1;
}

int deSqQueue(SqQueue* Q)
{
    if (isEmptySqQueue(Q)) return 0;
    Q->front = (Q->front + 1) % Q->capacity;
    return 1;
}

int* peek(SqQueue* Q)
{
    if (isEmptySqQueue(Q)) return NULL;
    return &(Q->data[Q->front]);
}

int clearSqQueue(SqQueue* Q)
{
    if (Q == NULL || Q->front == Q->rear) return 0;
    Q->front = 0;
    Q->rear = 0;
    return 1;
}

int destroySqQueue(SqQueue** Q)
{
    if (clearSqQueue(*Q) == 0) return 0;
    free((*Q)->data);
    (*Q)->data = NULL;
    free(*Q);
    *Q = NULL;
    return 1;
}
