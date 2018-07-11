#include<stdlib.h>
#include<stdio.h>

typedef struct QNode {
    int data;
    struct QNode* next;
}QNode;

typedef struct {
    QNode* front;
    QNode* rear;
    int count;
}Queue;

#pragma region QueueFuntions
Queue* initQueue();
int enQueue(Queue* Q, int value);
int deQueue(Queue* Q, int* topValue);
int* peek(Queue* Q);
int destroyQueue(Queue** Q);
#pragma endregion

Queue* initQueue()
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->count = 0;
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}


int enQueue(Queue* Q, int value)
{
    if (Q == NULL) return 0;

    QNode* p = (QNode*)malloc(sizeof(QNode));
    p->data = value;
    p->next = NULL;

    if (Q->count == 0) {
        Q->front = p;
        Q->rear = p;
    }else {
        Q->rear->next = p;
        Q->rear = p;
    }
    Q->count++;
    return 1;
}

int deQueue(Queue* Q, int* topValue)
{
    if (Q == NULL || Q->count == 0) return 0;

    *topValue = Q->front->data;
    if (Q->front == Q->rear) {
        free(Q->front);
        Q->front = NULL;
        Q->rear = NULL;
    }else {
        QNode* p = Q->front;
        Q->front = Q->front->next;
        free(p);
        p = NULL;
    }

    Q->count--;
    return 1;
}

int* peek(Queue* Q)
{
    if (Q == NULL || Q->count == 0) return NULL;
    else return &(Q->front->data);
}

int destroyQueue(Queue** Q)
{
    if (*Q == NULL) return 0;

    QNode* p = NULL;
    while ((*Q)->front != (*Q)->rear){
        p = (*Q)->front;
        (*Q)->front = p->next;
        free(p);
        p = NULL;
    }
    free((*Q)->front);
    (*Q)->front = NULL;
    (*Q)->front = NULL;
    (*Q)->count = 0;
    *Q = NULL;
    return 1;
}
