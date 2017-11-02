#pragma once
/*brief An implementation of HuffmanTree,  including insert ,delete,traverse,*/

/*Causion:*/
/*只有一个Node就不弄编码了*/
/*重复权的话，LinkList从小到大排序之后，排在前的优先级比后的低（weight越高排在LinkList越后），那么即树右Child比树左Child优先级高*/



#include <stdio.h>
#include <stdlib.h>
#define PRINT_INT(x) printf("%d\n",x)
#define PRINT_String(x) printf("%s\n",x)

//即根据外部导入需要修改该HFElement类型
typedef int HFElement;

#pragma region HuffmanTree
//字符串String
typedef char* String;

/*修改HuffmanTree内HFElement类型(即根据外部导入需要修改该类型)*/
typedef struct  HuffmanNode {
	int Weight;			//本身的权
	HFElement Data;
	struct  HuffmanNode *Left;
	struct  HuffmanNode *Right;
	String HuffmanCode;	//赫夫曼编码
}HuffmanNode, *HuffmanTree;
#pragma endregion


#include "queue.h"		//在定义HuffmanTree之后Include
#include"linklist.h"	//在定义HuffmanTree之后Include


#pragma region Functions
HuffmanTree InitHuffmanTree();
void CreateInitHuffmanTree_ByInputKeyCode(HuffmanTree * T);
void Build_HuffmanTree(HuffmanTree * T, LinkList * L);
void Build_HuffmanCode(HuffmanTree T, String code, int count, int size);
void InsertHuffmanNode(HuffmanTree * T, int weight, HFElement value);
void HuffmanTreeToLinkList(HuffmanTree T, LinkList* L, int weight);
void SetValueHuffmanNode(HuffmanTree T, int weight, HFElement value);
void DeleteHuffmanNode(HuffmanTree * T, int weight);
void DestroyHuffmanTree(HuffmanTree * T);
int GetDepth(HuffmanTree T);
#pragma region Traverse
	void PreOrderTraverse(HuffmanTree T);
	void InOrderTraverse(HuffmanTree T);
	void PostOrderTraverse(HuffmanTree T);
	void LevelOrderTraverse(HuffmanTree T);
#pragma endregion
#pragma endregion

/*初始化HuffmanTree*/
HuffmanTree InitHuffmanTree()
{
	return NULL;
}

/*(外部方法)通过手动输入赋值HuffmanTree*/
/*内部调用了Build_HuffmanTree和Build_HuffmanCode*/
void CreateInitHuffmanTree_ByInputKeyCode(HuffmanTree * T)
{
	printf("Weight为-1则NULL,请输入添加的Weight值 :");
	int m_Weight;
	scanf_s("%d", &m_Weight);

	if (m_Weight != -1) {
		printf("请输入权[%d]元素对应的value值：", m_Weight);
		HFElement m_value;
		scanf_s("%d", &m_value);

		LinkList* L =  LinkListInit();	//temp_List
		while (m_Weight != -1)
		{
			//先把树Node写入LinkList,LinkList用来方便排序weight权值
			Element HF_Node = (Element)malloc(sizeof(HuffmanNode));
			HF_Node->Data = m_value;
			HF_Node->Weight = m_Weight;
			HF_Node->Left = NULL;
			HF_Node->Right = NULL;
			AppendLinkList(L, HF_Node);

			printf("Weight为-1则NULL,请输入添加的Weight值 :");
			scanf_s("%d", &m_Weight);
			if (m_Weight != -1) {
				printf("请输入权[%d]元素对应的value值：", m_Weight);
				scanf_s("%d", &m_value);
			}
		}
		/*LinkList从小到大排序*/
		LinkList_InsertSort(L);

		/*调用内部方法，创建HuffmanTree*/
		Build_HuffmanTree(T,L);

		/*调用内部方法，创建HuffmanCode,Code作为局部变量*/
		String Code = (String)calloc(L->Count, sizeof(char));
		Build_HuffmanCode(*T, Code,0, L->Count);
		
		//销毁LinkList和字符串Code局部变量
		DestroyLinkList(&L);
		free(Code);
	}
	return;
}

/*（内部方法）创建HuffmanTree*/
/*L:已经排好序,T:树Root*/
void Build_HuffmanTree(HuffmanTree * T,LinkList * L)
{
	if (L == NULL && L->Count > 0) {
		printf("空LinkList,未成功创建赫夫曼树\n");
		return;
	}

	Node* p = L->Head->Next;
	if (L->Count == 1){
		*T = (HuffmanTree)malloc(sizeof(HuffmanNode));
		(*T)->Left = p->Data;
	}

	else {
		*T = p->Data;

		Node* pre = (Node*)malloc(sizeof(Node));//局部变量(不要指向其他地址,只要使用Data）
		pre->Data = *T;	//记录第[0]个
		p = p->Next;	//第[1]个开始
		
		for (int i = 0; i < L->Count - 1; i++)
		{
			Element NewRoot = (HuffmanTree)malloc(sizeof(HuffmanNode));
			if (p->Data->Weight >= pre->Data->Weight) {
				NewRoot->Left = pre->Data;
				NewRoot->Right = p->Data;
			}
			else {
				NewRoot->Left = p->Data;
				NewRoot->Right = pre->Data; 
			}
			NewRoot->Weight = pre->Data->Weight + p->Data->Weight;
			*T = NewRoot;
			if (p->Next && p->Next->Next && NewRoot->Weight > p->Next->Next->Data->Weight) {
				InsertLinkList(L, i+4, NewRoot);	//跳过中间2个 + 1个前面跳过 +1个的位置上
				LinkList_InsertSort(L);
				pre->Data = p->Next->Data;
				p = p->Next;
				L->Count--; //不能死循环,没必要+数量，insert的是为了创建树方便，最后还是会销毁
			}else {
				pre->Data = *T;//这里修改了L
			}
			p = p->Next;
		}
		free(pre);
		pre = NULL;
	}
	return;
}

/*(内部方法)创建HuffmanCode*/
/*T:已创建好的Tree  
code :传入初始已calloc的NULL的String*
count :传常数0，用于Code的赋值遍历次数（即记录当前递归的次数）
size :LinkList的元数个数Count*/
void Build_HuffmanCode(HuffmanTree T, String code,int count,int size)
{
	if (T == NULL) return;

	if (T->Left){
		code[count] = '0';	
		Build_HuffmanCode(T->Left, code, count + 1,size);
	}

	if (T->Right){
		code[count] = '1';
		Build_HuffmanCode(T->Right, code, count + 1,size);
	}
	else {
		T->HuffmanCode = (String)calloc(size, sizeof(char));
		int j = 0;
		for (int i = 0; i < count; i++)
		{
			if (code[i]) {
				T->HuffmanCode[j] = code[i];
				++j;
			}
		}
	}
}

/*插入新HuffmanNode到HuffmanTree*/
/*T : 已创建成功的Tree
weight : 新Node的权值
value ： 新Node的value值*/
void InsertHuffmanNode(HuffmanTree * T, int weight, HFElement value)
{
	//把树的叶结点都存到LinkList，把树Destroy重新Build
	LinkList* L = LinkListInit();
	HuffmanTreeToLinkList(*T, L,-1);
	DestroyHuffmanTree(T);
	
	//外部添加新的树Node
	Element HF_Node = (Element)malloc(sizeof(HuffmanNode));
	HF_Node->Data = value;
	HF_Node->Weight = weight;
	HF_Node->Left = NULL;
	HF_Node->Right = NULL;
	AppendLinkList(L, HF_Node);

	//重新Build赫夫曼树
	LinkList_InsertSort(L);
	Build_HuffmanTree(T,L);
	String Code = (String)calloc(L->Count, sizeof(char));
	Build_HuffmanCode(*T, Code, 0, L->Count);

	//销毁LinkList和字符串Code局部变量
	DestroyLinkList(&L);
	free(Code);
	return;
}

/*(内部方法)把HuffmanTree的叶结点都装进LinkList[ 前中后序都一样 ]*/
/*weight:-1表示全部都装，指定weight就表示该weight不装*/
void HuffmanTreeToLinkList(HuffmanTree T,LinkList* L,int weight)
{
	if (T)
	{
		HuffmanTreeToLinkList(T->Left,L,weight);
		HuffmanTreeToLinkList(T->Right,L, weight);
		if (T->Left == NULL && T->Weight != weight) {
			//因为LinkList只是过渡，避免Tree销毁而访问不了Node就malloc
			Element HF_Node = (Element)malloc(sizeof(HuffmanNode));
			HF_Node->Data = T->Data;
			HF_Node->Weight = T->Weight;
			HF_Node->Left = NULL;
			HF_Node->Right = NULL;
			AppendLinkList(L, HF_Node);
		}
	}
	return;
}

/*删除HuffmanNode(根据权值匹配)*/
/*T : 已创建成功的Tree
weight : 删除Node匹配的权值*/
void DeleteHuffmanNode(HuffmanTree * T, int weight)
{
	//把树的叶结点（除了匹配的weight之外)都存到LinkList，把树Destroy重新Build
	LinkList* L = LinkListInit();
	HuffmanTreeToLinkList(*T, L, weight);
	DestroyHuffmanTree(T);

	//重新Build赫夫曼树
	LinkList_InsertSort(L);
	Build_HuffmanTree(T,L);
	String Code = (String)calloc(L->Count, sizeof(char));
	Build_HuffmanCode(*T, Code, 0, L->Count);

	//销毁LinkList和字符串Code局部变量
	DestroyLinkList(&L);
	free(Code);
	return;
}

/*修改HuffmanNode(根据权值匹配[ 前中后序都一样 ])*/
/*T : 已创建成功的Tree
weight : 需要修改Node匹配的权值(有重复权值则全部替换)
value : 新的value值*/
void SetValueHuffmanNode(HuffmanTree T, int weight, HFElement value)
{
	if (T)
	{
		SetValueHuffmanNode(T->Left, weight, value);
		SetValueHuffmanNode(T->Right, weight, value);
		if (T->Left == NULL && T->Weight == weight){
			T->Data = value;
		}
	}
	return;
}

/*销毁HuffmanTree 返回NULL*/
void DestroyHuffmanTree(HuffmanTree * T)
{
	if (*T)
	{
		DestroyHuffmanTree(&((*T)->Left));
		DestroyHuffmanTree(&((*T)->Right));
		free(*T);
		*T = NULL;
	}
	return;
}

/*树的深度*/
int GetDepth(HuffmanTree T)
{
	int i, j;
	if (T == NULL) return 0;
	i = GetDepth(T->Left);
	j = GetDepth(T->Right);
	return i > j ? i + 1 : j + 1;
}

#pragma region Traverse[前中后序效果都一样]
/*前序遍历*/
void PreOrderTraverse(HuffmanTree T)
{
	if (T)
	{
		if (T->Left == NULL) {
			PRINT_INT(T->Data);
			PRINT_String(T->HuffmanCode);
		}
		InOrderTraverse(T->Left);
		InOrderTraverse(T->Right);
	}
	return;
}

/*中序遍历*/
void InOrderTraverse(HuffmanTree T)
{
	if (T)
	{
		InOrderTraverse(T->Left);
		if (T->Left == NULL) {
			PRINT_INT(T->Data);
			PRINT_String(T->HuffmanCode);
		}
		InOrderTraverse(T->Right);
	}
	return;
}

/*后序遍历*/
void PostOrderTraverse(HuffmanTree T)
{
	if (T)
	{
		InOrderTraverse(T->Left);
		InOrderTraverse(T->Right);
		if (T->Left == NULL) {
			PRINT_INT(T->Data);
			PRINT_String(T->HuffmanCode);
		}
	}
	return;
}

/*层序遍历*/
void LevelOrderTraverse(HuffmanTree T)
{
	Queue* q = InitQueue();
	if (T)
	{
		EnterQueue(q, T);
		while (!IsEmptyQueue(q))
		{
			TElement result = *GetHeadValue(q);
			DeleteQueue(q);
			if (result->Left == NULL) {
				PRINT_INT(result->Data);
				PRINT_String(result->HuffmanCode);
			}
			if (result->Left)  EnterQueue(q, result->Left);
			if (result->Right) EnterQueue(q, result->Right);
		}
	}
	DestroyQueue(&q);
}
#pragma endregion






