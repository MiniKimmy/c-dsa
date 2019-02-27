#include<stdio.h>
#include<stdlib.h>
#define PRINT_STRING(x) printf("%s\n",x)


typedef int TElement;  //import�������ļ�ʱ����Ҫ�޸ĸ�����

/*Boolö��*/
typedef enum Status {
    FALSE,
    TRUE,
}Status;

/*���Node��������*/
typedef struct Node {
    TElement data;
    struct Node* next;
}Node;

typedef struct Queue {
    Node* front;    //ͷ�ڱ�[����data]
    Node* rear;     //β�ڱ�
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


/*��ʼ��Queue*/
Queue* InitQueue()
{
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        PRINT_STRING("node��ʼ����̬�����ڴ�ʧ��");
        exit(-1);
    }

    Queue* ret = (Queue*)malloc(sizeof(Queue));
    if (ret == NULL) {
        PRINT_STRING("Queue��ʼ����̬�����ڴ�ʧ��");
        exit(-1);
    }

    node->next = NULL;
    ret->front = node;
    ret->rear = node;
    ret->count = 0;
    return ret;
}

/*�ж�Queue�Ƿ�Ϊ��*/
Status IsEmpty_Queue(Queue* Q)
{
    if (Q == NULL) {
        PRINT_STRING("QueueΪNULL");
        return TRUE;
    }

    if (Q->front == Q->rear)  return TRUE;
    else return FALSE;
}

/*���*/
void En_Queue(Queue* Q, TElement value)
{
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        PRINT_STRING("���node��ʼ����̬�����ڴ�ʧ��");
        exit(-1);
    }

    node->data = value;
    node->next = NULL;
    Q->rear->next = node;
    Q->rear = node;
    Q->count++;
    return;
}

/*���ض�ͷԪ�ص�ָ��*/
TElement* GetValue_Queue(Queue* Q)
{
    if (IsEmpty_Queue(Q)) return NULL;
    return &(Q->front->next->data);
}

/*����*/
void De_Queue(Queue* Q)
{
    if (IsEmpty_Queue(Q)) return;
    Node* node = Q->front->next;

    //����������Ķ�ͷԪ��
    if (node == Q->rear){
        Q->rear = Q->front;
    }

    Q->front->next = node->next;
    free(node);
    node = NULL;
    Q->count--;
    return;
}

/*���Queue����Ԫ��*/
/*ͷ�ڱ�����*/
void Clear_Queue(Queue* Q)
{
    while (!IsEmpty_Queue(Q)){
        De_Queue(Q);
    }
    return;
}

/*����Queue��ǰԪ�ظ���*/
int GetSize_Queue(Queue* Q)
{
    if (Q == NULL) return;
    else return Q->count;
}

/*����Queue*/
void Destroy_Queue(Queue** Q)
{
    if (*Q == NULL) return;

    Clear_Queue(*Q);
    free(*Q);
    *Q = NULL;
    return;
}