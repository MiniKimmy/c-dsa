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

#include "queue.h"	//在BiThrTree定义之后Include


//初始化BiThrTree
BiThrTree InitBiThrTree()
{
	return NULL;
}

/*通过手动输入赋值BiThrTree*/
void CreateBiThrTree_ByInputKeyCode(BiThrTree * T)
{
	printf("请输入value,-1为空value : ");
	Element arg;
	scanf_s("%d", &arg);
	if (arg == -1) {
		*T = NULL;
		return;
	}
	*T = (BiThrTree)malloc(sizeof(BiThrNode));
	if (*T == NULL) {
		printf("BiThrTree初始化动态分配内存失败\n");
		exit(-1);
	}
	(*T)->Data = arg;
	(*T)->LTag = LINK;
	(*T)->RTag = LINK;
	CreateBiThrTree_ByInputKeyCode(&((*T)->Left));
	CreateBiThrTree_ByInputKeyCode(&((*T)->Right));
	return;
}

/*（内部方法）绑定线索*/
/*pre：局部闭包指针，指向T刚刚访问过的结点，T：树对象*/
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

/*绑定线索并转化成双哨兵循环LinkList*/
/*若T为NULL，也return初始化好的LinkList*/
BiThrTree TransfromLinkList(BiThrTree T)
{
	BiThrTree ret = (BiThrTree)malloc(sizeof(BiThrNode));
	if (ret == NULL) {
		printf("LinkList头哨兵动态分配内存失败\n");
		exit(-1);
	}

	if (T)
	{
		BiThrTree p = NULL;	//局部指针，最后指向最右下角的树Node
		InThreading(&p, T);	//最右下角的树Node的RTag未绑定Thread
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

/*遍历线索二叉树*/
/*T：已转化为LinkList的头哨兵树Node*/
void ThreadOrderTraverse(BiThrTree T)
{
	if (T == NULL){
		printf("无法操作NULL参数\n");
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

/*在最右下角添加元素*/
/*value：所添加新元素的具体值*/
void Append(BiThrTree T, Element value)
{
	if (T == NULL) {
		printf("无法操作NULL参数\n");
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

/*返回BiThrTree最左下角的Node*/
BiThrTree GetLeftCornorBiThrNode(BiThrTree T)
{
	if (T == NULL) {
		printf("无法操作NULL参数\n");
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

/*返回BiThrTree最右下角的Node*/
BiThrTree GetRightCornorBiThrNode(BiThrTree T)
{
	if (T == NULL) {
		printf("无法操作NULL参数\n");
		return NULL;
	}

	if (T->Left){
		return T->Right;
	}
	return NULL;
}

/*返回当前Node相对最左下角的Node*/
BiThrTree GetLeftBiThrNode(BiThrNode* Node)
{
	if (Node == NULL) {
		printf("无法操作NULL参数\n");
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

/*返回当前Node相对最右下角的Node*/
BiThrTree GetRightBiThrNode(BiThrNode* Node)
{
	if (Node == NULL) {
		printf("无法操作NULL参数\n");
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

/*返回指定Node的Parent*/
/*value：匹配到第一个的树Node*/
BiThrTree Parent(BiThrTree T, Element value)
{
	Queue *q;
	if (T == NULL) {
		printf("无法操作空BiThrTree\n");
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

/*p:插入新Node的位置(原来树里的存在结点的位置)*/
void InsertBiThrNode(BiThrTree T, BiThrNode* p, Element value)
{
	if (T == NULL) {
		printf("无法操作空BiThrTree\n");
		return;
	}

	if (T == p) {
		printf("无法在LinkList头哨兵插入新元素\n");
		return;
	}

	BiThrNode* Item = (BiThrNode*)malloc(sizeof(BiThrNode));
	if (Item == NULL) {
		printf("新元素Node动态分配内存失败\n");
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

/*p:需要Delete的Node的位置*/
void DeleteBiThrNode(BiThrTree T, BiThrNode* p)
{
	if (T == NULL || p == NULL) {
		printf("无法操作空参数\n");
		return;
	}

	if (T == p) {
		printf("无法在删除LinkList头哨兵\n");
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

/*把整个LinkList销毁*/
void DestroyBiThrTree(BiThrTree * T)
{
	if (*T == NULL ) {
		printf("无法操作空参数\n");
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