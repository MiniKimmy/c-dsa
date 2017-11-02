#pragma once
//include�Ѿ����˾Ͳ���Ҫ�ظ�������
//#include<stdio.h>
//#include<stdlib.h>

//[ �������ⲿ������Ҫ�޸ĸ�TElement���� ]
typedef HuffmanTree TElement;

#pragma region Queue
typedef struct QNode
{
	TElement Data;
	struct QNode *Next;
}QNode;

/*�޸Ķ�����Node��Data����(�������ⲿ������Ҫ�޸ĸ�����)*/
typedef struct LinkQueue {
	struct QNode * front;
	struct QNode * rear;
	int Count;
}Queue;
#pragma endregion

typedef enum Status {
	//��־λ
	FALSE,
	TRUE,
}Status;

#pragma region Functions
Queue* InitQueue();
Status IsEmptyQueue(Queue * Q);
void EnterQueue(Queue * Q, TElement value);
TElement* GetHeadValue(Queue* Q);
void DeleteQueue(Queue * Q);
void ClearQueue(Queue * Q);
void DestroyQueue(Queue** Q);
#pragma endregion

/*���г�ʼ��*/
Queue* InitQueue()
{
	QNode* p = (QNode*)malloc(sizeof(QNode));
	if (p == NULL) {
		printf("QNode ��̬�����ڴ�ʧ��\n");
		exit(-1);
	}
	Queue* ret = (Queue*)malloc(sizeof(Queue));
	if (ret == NULL) {
		printf("Queue��̬�����ڴ�ʧ��\n");
		exit(-1);
	}
	p->Next = NULL;
	ret->front = p;
	ret->rear = p;
	ret->Count = 0;
	return ret;
}

/*�ж϶����Ƿ�Ϊ��*/
Status IsEmptyQueue(Queue * Q)
{
	if (Q == NULL) {
		printf("�޷�����NULL����\n");
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

//��ȡ��ͷ
TElement* GetHeadValue(Queue * Q)
{
	if (IsEmptyQueue(Q)) {
		printf("�ն���,��Ԫ��\n");
		return NULL;
	}
	return &(Q->front->Next->Data);
}

/*����*/
void DeleteQueue(Queue * Q)
{
	if (IsEmptyQueue(Q)) {
		printf("�ն���,�޷����Ӳ���\n");
		return;
	}

	QNode* p = Q->front->Next;
	if (p == Q->rear)
	{
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

/*��ն���*/
void ClearQueue(Queue * Q)
{
	if (IsEmptyQueue(Q)) {
		//printf("�Ѿ�Ϊ�ն���\n");
		return;
	}

	while (!IsEmptyQueue(Q)) {
		DeleteQueue(Q);
	}
	return;
}

/*����Queue�����ڴ�,����NULL*/
void DestroyQueue(Queue** Q)
{
	if (*Q == NULL) {
		printf("�޷���NULL��������\n");
		return;
	}

	ClearQueue(*Q);
	free(*Q);
	*Q = NULL;
	return;
}