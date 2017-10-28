#pragma once
#include <stdlib.h>
#include <stdio.h>

typedef int Element;	//BiNode_Data����
#pragma region BiTree
typedef struct BiNode {
	Element Data;
	struct BiNode *Left;
	struct BiNode *Right;
}BiNode, *BiTree;
#pragma endregion
  
#pragma region Functions
BiTree InitBiTree();
void CreatBiTree_ByInputKeyCode(BiTree * T);
void PreOrderTraverse(BiTree T);
void InOrderTraverse(BiTree T);
void PostOrderTraverse(BiTree T);
void LevelOrderTraverse(BiTree T);
void DestroyBiTree(BiTree * T);
BiTree GetFirst_BiNode(BiTree T, Element value);
BiTree Parent(BiTree T, Element value);
BiTree GetLeftChild(BiTree T, Element value);
BiTree GetRightChild(BiTree T, Element value);
int GetDepth(BiTree T);
#pragma endregion

#include "queue.h" //��BiTree����֮����Include

//��ʼ��BiTree
BiTree InitBiTree()
{
	return NULL;
}

/*ͨ���ֶ����븳ֵ����,��һ����ͨ�Ķ�����*/
/*���뵽-1��ΪNULL*/
void CreatBiTree_ByInputKeyCode(BiTree * T)
{
	printf("-1ΪNULL��������Value : ");
	Element arg;
	scanf_s("%d", &arg);
	if (arg == -1)
		*T = NULL;
	else {
		*T = (BiTree)malloc(sizeof(BiNode));
		if (!(*T)) {
			printf("BiTree ��̬�����ڴ�ʧ��\n");
			exit(-1);
		}
		(*T)->Data = arg;
		CreatBiTree_ByInputKeyCode(&((*T)->Left));
		CreatBiTree_ByInputKeyCode(&((*T)->Right));
	}
}

/*�������*/
void PreOrderTraverse(BiTree T)
{
	if (T)
	{
		printf("%d\n", T->Data);
		PreOrderTraverse(T->Left);
		PreOrderTraverse(T->Right);
	}
	return;
}

/*�������*/
void InOrderTraverse(BiTree T)
{
	if (T)
	{
		InOrderTraverse(T->Left);
		printf("%d\n", T->Data);
		InOrderTraverse(T->Right);
	}
	return;
}

/*�������*/
void PostOrderTraverse(BiTree T)
{
	if (T)
	{
		InOrderTraverse(T->Left);
		InOrderTraverse(T->Right);
		printf("%d\n", T->Data);
	}
	return;
}

/*�������*/
void LevelOrderTraverse(BiTree T)
{
	Queue* q = InitQueue();
	if (T)
	{
		EnterQueue(q, T);
		while (!IsEmptyQueue(q))
		{
			TElement result = *GetHeadValue(q);
			DeleteQueue(q);
			printf("%d\n", result->Data);
			if (result->Left)  EnterQueue(q, result->Left);
			if (result->Right) EnterQueue(q, result->Right);
		}
	}
	DestroyQueue(&q);
}

/*�������*/
int GetDepth(BiTree T)
{
	int i, j;
	if (T == NULL) return 0;
	i = GetDepth(T->Left);
	j = GetDepth(T->Right);
	return i > j ? i + 1 : j + 1;
}

/*��������*/
void DestroyBiTree(BiTree * T)
{
	if (*T)
	{
		DestroyBiTree(&((*T)->Left));
		DestroyBiTree(&((*T)->Right));
		BiTree* p = T;
		free(*p);
		*p = NULL;
	}
	return;
}

/*���ص�һ��ָ��valueƥ���BiNode*/
/*value����Ҫָ��ƥ���value*/
BiTree GetFirst_BiNode(BiTree T, Element value)
{
	Queue* q = InitQueue();
	if (T)
	{
		EnterQueue(q, T);
		while (!IsEmptyQueue(q))
		{
			TElement result = *GetHeadValue(q);
			DeleteQueue(q);
			if (result->Data == value) {
				DestroyQueue(&q);
				return result;
			}
			if (result->Left) EnterQueue(q, result->Left);
			if (result->Right) EnterQueue(q, result->Right);
		}	
	}
	DestroyQueue(&q);
	return NULL;
}

/*�ҵ���һ��ָ��valueƥ���BiNode��parent*/
/*value����Ҫָ��ƥ���value*/
BiTree Parent(BiTree T, Element value)
{
	Queue* q = InitQueue();
	if (T)
	{
		EnterQueue(q, T);
		while (!IsEmptyQueue(q))
		{
			TElement result = *GetHeadValue(q);
			DeleteQueue(q);
			if ((result->Left  && result->Left->Data  == value) || 
				(result->Right && result->Right->Data == value)) 
			{
				DestroyQueue(&q);
				return result;
			}
			if (result->Left) EnterQueue(q, result->Left);
			if (result->Right) EnterQueue(q, result->Right);
		}
	}
	DestroyQueue(&q);
	return NULL;
}

/*�ҵ���һ��ָ��valueƥ���BiNode��LeftChild*/
/*value����Ҫָ��ƥ���value*/
BiTree GetLeftChild(BiTree T, Element value)
{
	if (T)
	{
		BiTree p = GetFirst_BiNode(T, value);
		if (p && p->Left) return p->Left;
	}
	return NULL;
}

/*�ҵ���һ��ָ��valueƥ���BiNode��RightChild*/
/*value����Ҫָ��ƥ���value*/
BiTree GetRightChild(BiTree T, Element value)
{
	if (T)
	{
		BiTree p = GetFirst_BiNode(T, value);
		if (p && p->Right) return p->Right;
	}
	return NULL;
}