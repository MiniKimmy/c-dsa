#pragma once
#include<stdio.h>
#include<stdlib.h>

typedef enum { FALSE , TRUE } Status; //��־λ

#pragma region Stack
typedef int Element;
typedef struct SNode {
	Element Data;
	struct SNode *Next;
}SNode;

typedef struct LinkStack {
	SNode *Top;		//ջ��
	SNode *Bottom;	//ջ��
	int Count;		//Ԫ�ظ���
}Stack;
#pragma endregion

#pragma region Functions
Stack* StackInit();
void CreateStack_ByArr(Stack * S,int *arr, int stacksize);
void Push(Stack * S, Element value);
Status IsEmptyStack(Stack * S);
Element* GetTopValue(Stack * S);
void Pop(Stack * S);
void ClearStack(Stack * S);
void DestroyStack(Stack** S);
#pragma endregion

/*��ʼ��Stack*/
Stack* StackInit()
{
	Stack* ret = (Stack*)malloc(sizeof(Stack));
	ret->Count = 0;
	ret->Top = NULL;
	ret->Bottom = NULL;
}

/*ͨ������int���������ѹջ*/
/*S��Stack*ջ����,arr��int���飬arrsize�����鳤�� */
void CreateStack_ByArr(Stack * S,int *arr, int arrsize)
{
	if (S && arr && arrsize < 0) {
		printf("���������Ч\n");
		return;
	}

	for (int i = 0; i < arrsize; i++){
		Push(S, arr[i]);
	}
	return;
}

/*��ջ*/
/*S��Stack*ջ����,value��ѹջ�ľ�������*/
void Push(Stack* S, Element value)
{
	SNode* p = (SNode*)malloc(sizeof(SNode));
	p->Data = value;
	p->Next = S->Top;
	if (S->Bottom == NULL){
		S->Bottom = p;
	}
	S->Top = p;
	S->Count++;
	return;
}

/*�Ƿ��ջ*/
Status IsEmptyStack(Stack * S)
{
	if (S == NULL) {
		printf("�޷�����NULL����\n");
		exit(-1);
	}

	if (S->Bottom == NULL) return TRUE;
	else return FALSE;
}

/*��ȡTopԪ�ص�value*/
Element* GetTopValue(Stack * S)
{
	if (IsEmptyStack(S)) {
		printf("��ջ����Ԫ��\n");
		return NULL;
	}
	return &(S->Top->Data);
}

//��ջ
/*ֱ��ɾ��Top��SNode*/
void Pop(Stack * S)
{
	if (IsEmptyStack(S)) {
		printf("��ջ����Ԫ�س�ջ\n");
		return;
	}

	SNode* p = S->Top;
	if (p == S->Bottom) {
		S->Bottom = NULL;
	}
	S->Top = S->Top->Next;
	S->Count--;
	free(p);
	return;
}

/*������е�Ԫ�أ�Stack*����ɾ��*/
void ClearStack(Stack * S)
{
	if (IsEmptyStack(S)) {
		printf("��ջ������Clear\n");
		return;
	}

	while (S->Bottom){
		Pop(S);
	}
	return;
}

/*ɾ��Stack�����ڴ棬����NULL*/
void DestroyStack(Stack** S)
{
	if (*S == NULL) {
		printf("�޷�����NULL����\n");
		return;
	}

	ClearStack(*S);
	*S = NULL;
	return;
}