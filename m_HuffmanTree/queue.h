#pragma once
//include已经有了就不需要重复声明了
//#include<stdio.h>
//#include<stdlib.h>

//[ 即根据外部导入需要修改该TElement类型 ]
typedef HuffmanTree TElement;

#pragma region Queue
typedef struct QNode
{
	TElement Data;
	struct QNode *Next;
}QNode;

/*修改队列内Node的Data类型(即根据外部导入需要修改该类型)*/
typedef struct LinkQueue {
	struct QNode * front;
	struct QNode * rear;
	int Count;
}Queue;
#pragma endregion

typedef enum Status {
	//标志位
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

/*队列初始化*/
Queue* InitQueue()
{
	QNode* p = (QNode*)malloc(sizeof(QNode));
	if (p == NULL) {
		printf("QNode 动态分配内存失败\n");
		exit(-1);
	}
	Queue* ret = (Queue*)malloc(sizeof(Queue));
	if (ret == NULL) {
		printf("Queue动态分配内存失败\n");
		exit(-1);
	}
	p->Next = NULL;
	ret->front = p;
	ret->rear = p;
	ret->Count = 0;
	return ret;
}

/*判断队列是否为空*/
Status IsEmptyQueue(Queue * Q)
{
	if (Q == NULL) {
		printf("无法操作NULL参数\n");
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

//获取队头
TElement* GetHeadValue(Queue * Q)
{
	if (IsEmptyQueue(Q)) {
		printf("空队列,无元素\n");
		return NULL;
	}
	return &(Q->front->Next->Data);
}

/*出队*/
void DeleteQueue(Queue * Q)
{
	if (IsEmptyQueue(Q)) {
		printf("空队列,无法出队操作\n");
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

/*清空队列*/
void ClearQueue(Queue * Q)
{
	if (IsEmptyQueue(Q)) {
		//printf("已经为空队列\n");
		return;
	}

	while (!IsEmptyQueue(Q)) {
		DeleteQueue(Q);
	}
	return;
}

/*销毁Queue所有内存,返回NULL*/
void DestroyQueue(Queue** Q)
{
	if (*Q == NULL) {
		printf("无法对NULL参数操作\n");
		return;
	}

	ClearQueue(*Q);
	free(*Q);
	*Q = NULL;
	return;
}