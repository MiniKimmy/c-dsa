#pragma once
#include<stdio.h>
#include<stdlib.h>

typedef enum { FALSE , TRUE } Status; //标志位

#pragma region Stack
typedef int Element;
typedef struct SNode {
	Element Data;
	struct SNode *Next;
}SNode;

typedef struct LinkStack {
	SNode *Top;		//栈顶
	SNode *Bottom;	//栈底
	int Count;		//元素个数
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

/*初始化Stack*/
Stack* StackInit()
{
	Stack* ret = (Stack*)malloc(sizeof(Stack));
	ret->Count = 0;
	ret->Top = NULL;
	ret->Bottom = NULL;
}

/*通过传入int数组的数据压栈*/
/*S：Stack*栈对象,arr：int数组，arrsize：数组长度 */
void CreateStack_ByArr(Stack * S,int *arr, int arrsize)
{
	if (S && arr && arrsize < 0) {
		printf("传入参数无效\n");
		return;
	}

	for (int i = 0; i < arrsize; i++){
		Push(S, arr[i]);
	}
	return;
}

/*堆栈*/
/*S：Stack*栈对象,value：压栈的具体数据*/
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

/*是否空栈*/
Status IsEmptyStack(Stack * S)
{
	if (S == NULL) {
		printf("无法操作NULL参数\n");
		exit(-1);
	}

	if (S->Bottom == NULL) return TRUE;
	else return FALSE;
}

/*获取Top元素的value*/
Element* GetTopValue(Stack * S)
{
	if (IsEmptyStack(S)) {
		printf("空栈、无元素\n");
		return NULL;
	}
	return &(S->Top->Data);
}

//出栈
/*直接删除Top的SNode*/
void Pop(Stack * S)
{
	if (IsEmptyStack(S)) {
		printf("空栈、无元素出栈\n");
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

/*清除所有的元素，Stack*对象不删除*/
void ClearStack(Stack * S)
{
	if (IsEmptyStack(S)) {
		printf("空栈，无需Clear\n");
		return;
	}

	while (S->Bottom){
		Pop(S);
	}
	return;
}

/*删除Stack所有内存，返回NULL*/
void DestroyStack(Stack** S)
{
	if (*S == NULL) {
		printf("无法操作NULL参数\n");
		return;
	}

	ClearStack(*S);
	*S = NULL;
	return;
}