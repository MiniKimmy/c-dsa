#pragma once
#include<stdio.h>
#include<stdlib.h>
#define PRINT_INT(x) printf("%d\n",x);

typedef int Element;
#pragma region BiThrTree
typedef enum PointerTag {
	LINK,
	Thread,
}PointerTag;

typedef struct BiThrNode {
	Element Data;
	struct BiThrNode *Left;
	struct BiThrNode *Right;
	PointerTag LTag;
	PointerTag RTag;
}BiThrNode, *BiThrTree;
#pragma endregion

#pragma region Functions
BiThrTree InitBiThrTree();
void CreateBiThrTree_ByInputKeyCode(BiThrTree * T);
void InThreading(BiThrTree * pre, BiThrTree T);
BiThrTree TransfromLinkList(BiThrTree T);
void ThreadOrderTraverse(BiThrTree T);
void Append(BiThrTree T, Element value);
BiThrTree GetLeftCornorBiThrNode(BiThrTree T);
BiThrTree GetRightCornorBiThrNode(BiThrTree T);
BiThrTree GetLeftBiThrNode(BiThrNode* Node);
BiThrTree GetRightBiThrNode(BiThrNode* Node);
BiThrTree Parent(BiThrTree T, Element value);
void InsertBiThrNode(BiThrTree T, BiThrNode* p, Element value);
void DeleteBiThrNode(BiThrTree T, BiThrNode* p);
void DestroyBiThrTree(BiThrTree * T);
#pragma endregion

#include "queue.h"	//��BiThrTree����֮��Include


//��ʼ��BiThrTree
BiThrTree InitBiThrTree()
{
	return NULL;
}

/*ͨ���ֶ����븳ֵBiThrTree*/
void CreateBiThrTree_ByInputKeyCode(BiThrTree * T)
{
	printf("������value,-1Ϊ��value : ");
	Element arg;
	scanf_s("%d", &arg);
	if (arg == -1) {
		*T = NULL;
		return;
	}
	*T = (BiThrTree)malloc(sizeof(BiThrNode));
	if (*T == NULL) {
		printf("BiThrTree��ʼ����̬�����ڴ�ʧ��\n");
		exit(-1);
	}
	(*T)->Data = arg;
	(*T)->LTag = LINK;
	(*T)->RTag = LINK;
	CreateBiThrTree_ByInputKeyCode(&((*T)->Left));
	CreateBiThrTree_ByInputKeyCode(&((*T)->Right));
	return;
}

/*���ڲ�������������*/
/*pre���ֲ��հ�ָ�룬ָ��T�ոշ��ʹ��Ľ�㣬T��������*/
void InThreading(BiThrTree * pre,BiThrTree T)
{
	if (T)
	{
		InThreading(pre, T->Left);
		if (T->Left == NULL) {
			T->Left = *pre;
			T->LTag = Thread;
		}

		if  ((*pre) && (*pre)->Right == NULL) {
			(*pre)->Right = T;
			(*pre)->RTag = Thread;
		}

		*pre = T;
		InThreading(pre, T->Right);
	}
	return;
}

/*��������ת����˫�ڱ�ѭ��LinkList*/
/*��TΪNULL��Ҳreturn��ʼ���õ�LinkList*/
BiThrTree TransfromLinkList(BiThrTree T)
{
	BiThrTree ret = (BiThrTree)malloc(sizeof(BiThrNode));
	if (ret == NULL) {
		printf("LinkListͷ�ڱ���̬�����ڴ�ʧ��\n");
		exit(-1);
	}

	if (T)
	{
		BiThrTree p = NULL;	//�ֲ�ָ�룬���ָ�������½ǵ���Node
		InThreading(&p, T);	//�����½ǵ���Node��RTagδ��Thread
		ret->Left = T;	
		ret->Right = p;
		p->Right = ret;
		p->RTag = Thread;
	}
	else {
		ret->Left = NULL;
		ret->Right = NULL;
	}
	return ret;
}

/*��������������*/
/*T����ת��ΪLinkList��ͷ�ڱ���Node*/
void ThreadOrderTraverse(BiThrTree T)
{
	if (T == NULL){
		printf("�޷�����NULL����\n");
		return;
	}

	if (T->Left)
	{
		BiThrTree p = T->Left;
		while (p != T)
		{
			while (p->LTag == LINK){
				p = p->Left;
			}
			PRINT_INT(p->Data);
			while (p->RTag == Thread && p->Right != T){
				p = p->Right;
				PRINT_INT(p->Data);
			}
			p = p->Right;
		}
	}
	return;
}

/*�������½����Ԫ��*/
/*value���������Ԫ�صľ���ֵ*/
void Append(BiThrTree T, Element value)
{
	if (T == NULL) {
		printf("�޷�����NULL����\n");
		return;
	}

	BiThrNode* p = (BiThrNode*)malloc(sizeof(BiThrNode));
	p->Data = value;
	p->LTag = Thread;
	p->RTag = Thread;

	if (T->Left){
		BiThrTree rear = T->Right;
		rear->RTag = LINK;
		rear->Right = p;
		p->Left = rear;
		p->Right = T;
		T->Right = p;
	}
	else {
		T->Left = p;
		T->Right = p;
		p->Left = NULL;
		p->Right = T;
	}
	return;
}

/*����BiThrTree�����½ǵ�Node*/
BiThrTree GetLeftCornorBiThrNode(BiThrTree T)
{
	if (T == NULL) {
		printf("�޷�����NULL����\n");
		return NULL;
	}

	if (T->Left)
	{
		BiThrTree ret = T->Left;	 
		while (ret && ret->Left) {
			ret = ret->Left;
		}
		return ret;
	}
	return NULL;
}

/*����BiThrTree�����½ǵ�Node*/
BiThrTree GetRightCornorBiThrNode(BiThrTree T)
{
	if (T == NULL) {
		printf("�޷�����NULL����\n");
		return NULL;
	}

	if (T->Left){
		return T->Right;
	}
	return NULL;
}

/*���ص�ǰNode��������½ǵ�Node*/
BiThrTree GetLeftBiThrNode(BiThrNode* Node)
{
	if (Node == NULL) {
		printf("�޷�����NULL����\n");
		return NULL;
	}

	if (Node->LTag == LINK)
	{
		BiThrTree ret = Node->Left;
		while (ret->LTag == LINK) {
			ret = ret->Left;
		}
		return ret;
	}
	return NULL;
}

/*���ص�ǰNode��������½ǵ�Node*/
BiThrTree GetRightBiThrNode(BiThrNode* Node)
{
	if (Node == NULL) {
		printf("�޷�����NULL����\n");
		return NULL;
	}

	if (Node->RTag == LINK)
	{
		BiThrTree ret = Node->Right;
		while (ret->RTag == LINK) {
			ret = ret->Right;
		}
		return ret;
	}
	return NULL;
}

/*����ָ��Node��Parent*/
/*value��ƥ�䵽��һ������Node*/
BiThrTree Parent(BiThrTree T, Element value)
{
	Queue *q;
	if (T == NULL) {
		printf("�޷�������BiThrTree\n");
		return;
	}

	if (T->Left)
	{
		q = InitQueue();
		EnterQueue(q, T->Left);
		while (!IsEmptyQueue(q))
		{
			TElement result = *GetHeadValue(q);
			DeleteQueue(q);

			if ((!result->LTag && result->Left->Data == value) || 
				(!result->RTag && result->Right->Data == value)) {
				DestroyQueue(&q);
				return result;
			}
			if (result->LTag == LINK)  EnterQueue(q, result->Left);
			if (result->RTag == LINK) EnterQueue(q, result->Right);
		}
		DestroyQueue(&q);
	}
	return NULL;
}

/*p:������Node��λ��(ԭ������Ĵ��ڽ���λ��)*/
void InsertBiThrNode(BiThrTree T, BiThrNode* p, Element value)
{
	if (T == NULL) {
		printf("�޷�������BiThrTree\n");
		return;
	}

	if (T == p) {
		printf("�޷���LinkListͷ�ڱ�������Ԫ��\n");
		return;
	}

	BiThrNode* Item = (BiThrNode*)malloc(sizeof(BiThrNode));
	if (Item == NULL) {
		printf("��Ԫ��Node��̬�����ڴ�ʧ��\n");
		return;
	}
	
	if (p) {
		BiThrNode* parent = Parent(T, p->Data);
		if (parent == NULL) {
			T->Left = Item;
		}
		else {
			if (parent->Left == p) {
				parent->Left = Item;
			}
			else {
				parent->Right = Item;
			}
		}
		Item->RTag = LINK;
		Item->Right = p;
	}
	else {
		T->Left = Item;
		T->Right = Item;
		Item->RTag = Thread;
		Item->Right = T;
	}
	Item->Data = value;
	Item->LTag = Thread;
	Item->Left = NULL;
	return;
}

/*p:��ҪDelete��Node��λ��*/
void DeleteBiThrNode(BiThrTree T, BiThrNode* p)
{
	if (T == NULL || p == NULL) {
		printf("�޷������ղ���\n");
		return;
	}

	if (T == p) {
		printf("�޷���ɾ��LinkListͷ�ڱ�\n");
		return;
	}

	BiThrTree parent = Parent(T, p->Data);
	if (parent == NULL) parent = T;
	BiThrTree l = NULL;
	BiThrTree l_parent = p;
	if (p->LTag == LINK) l = p->Left;
	while (l && l->RTag == LINK) {
		l_parent = l;
		l = l->Right;
	}

	if (p->RTag == LINK) {
		BiThrTree r = p->Right;
		BiThrTree r_parent = p;
		while (r->LTag == LINK){
			r_parent = r;
			r = r->Left;
		}
	
		if (l) {
			l->Right = r;
		}

		r->Left = p->Left;
		r->LTag = p->LTag;
		if (r_parent != p) {
			r->Right = p->Right;
			r->RTag = LINK;
			r_parent->LTag = Thread;
		}

		if (parent->Left == p) {
			parent->Left = r;
		}
		else {
			parent->Right = r;
		}
		free(p);
		p = NULL;
		return;
	}
	
	if (l) {
		l->Right = p->Right;
		if (l_parent != p) {
			l->Left = p->Left;
			l->LTag = LINK;
			l_parent->RTag = Thread;
		}
		if (parent->Left == p) {
			parent->Left = l;
		}
		else {
			parent->Right = l;
		}
		free(p);
		p = NULL;
		return;
	}

	if (parent->Left == p) {
		parent->Left = NULL;
		parent->LTag = Thread;
	}
	else {
		parent->Right = p->Right;
		parent->RTag = Thread;
	}
	free(p);
	p = NULL;
	return;
}

/*������LinkList����*/
void DestroyBiThrTree(BiThrTree * T)
{
	if (*T == NULL ) {
		printf("�޷������ղ���\n");
		return;
	}

	if ((*T)->Left)
	{
		Queue* q = InitQueue();
		BiThrTree p = (*T)->Left;
		while (p != *T)
		{
			while (p->LTag == LINK) {
				p = p->Left;
			}
			EnterQueue(q, p);
			
			while (p->RTag == Thread && p->Right != *T) {
				p = p->Right;
				EnterQueue(q, p);
			}
			p = p->Right;
		}
		while (!IsEmptyQueue(q))
		{
			TElement t = *GetHeadValue(q);
			DeleteQueue(q);
			DeleteBiThrNode(*T, t);
		}
	}
	free(*T);
	*T = NULL;
	return;
}