#pragma once
/*brief An implementation of HuffmanTree,  including insert ,delete,traverse,*/

/*Causion:*/
/*ֻ��һ��Node�Ͳ�Ū������*/
/*�ظ�Ȩ�Ļ���LinkList��С��������֮������ǰ�����ȼ��Ⱥ�ĵͣ�weightԽ������LinkListԽ�󣩣���ô������Child������Child���ȼ���*/



#include <stdio.h>
#include <stdlib.h>
#define PRINT_INT(x) printf("%d\n",x)
#define PRINT_String(x) printf("%s\n",x)

//�������ⲿ������Ҫ�޸ĸ�HFElement����
typedef int HFElement;

#pragma region HuffmanTree
//�ַ���String
typedef char* String;

/*�޸�HuffmanTree��HFElement����(�������ⲿ������Ҫ�޸ĸ�����)*/
typedef struct  HuffmanNode {
	int Weight;			//�����Ȩ
	HFElement Data;
	struct  HuffmanNode *Left;
	struct  HuffmanNode *Right;
	String HuffmanCode;	//�շ�������
}HuffmanNode, *HuffmanTree;
#pragma endregion


#include "queue.h"		//�ڶ���HuffmanTree֮��Include
#include"linklist.h"	//�ڶ���HuffmanTree֮��Include


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

/*��ʼ��HuffmanTree*/
HuffmanTree InitHuffmanTree()
{
	return NULL;
}

/*(�ⲿ����)ͨ���ֶ����븳ֵHuffmanTree*/
/*�ڲ�������Build_HuffmanTree��Build_HuffmanCode*/
void CreateInitHuffmanTree_ByInputKeyCode(HuffmanTree * T)
{
	printf("WeightΪ-1��NULL,��������ӵ�Weightֵ :");
	int m_Weight;
	scanf_s("%d", &m_Weight);

	if (m_Weight != -1) {
		printf("������Ȩ[%d]Ԫ�ض�Ӧ��valueֵ��", m_Weight);
		HFElement m_value;
		scanf_s("%d", &m_value);

		LinkList* L =  LinkListInit();	//temp_List
		while (m_Weight != -1)
		{
			//�Ȱ���Nodeд��LinkList,LinkList������������weightȨֵ
			Element HF_Node = (Element)malloc(sizeof(HuffmanNode));
			HF_Node->Data = m_value;
			HF_Node->Weight = m_Weight;
			HF_Node->Left = NULL;
			HF_Node->Right = NULL;
			AppendLinkList(L, HF_Node);

			printf("WeightΪ-1��NULL,��������ӵ�Weightֵ :");
			scanf_s("%d", &m_Weight);
			if (m_Weight != -1) {
				printf("������Ȩ[%d]Ԫ�ض�Ӧ��valueֵ��", m_Weight);
				scanf_s("%d", &m_value);
			}
		}
		/*LinkList��С��������*/
		LinkList_InsertSort(L);

		/*�����ڲ�����������HuffmanTree*/
		Build_HuffmanTree(T,L);

		/*�����ڲ�����������HuffmanCode,Code��Ϊ�ֲ�����*/
		String Code = (String)calloc(L->Count, sizeof(char));
		Build_HuffmanCode(*T, Code,0, L->Count);
		
		//����LinkList���ַ���Code�ֲ�����
		DestroyLinkList(&L);
		free(Code);
	}
	return;
}

/*���ڲ�����������HuffmanTree*/
/*L:�Ѿ��ź���,T:��Root*/
void Build_HuffmanTree(HuffmanTree * T,LinkList * L)
{
	if (L == NULL && L->Count > 0) {
		printf("��LinkList,δ�ɹ������շ�����\n");
		return;
	}

	Node* p = L->Head->Next;
	if (L->Count == 1){
		*T = (HuffmanTree)malloc(sizeof(HuffmanNode));
		(*T)->Left = p->Data;
	}

	else {
		*T = p->Data;

		Node* pre = (Node*)malloc(sizeof(Node));//�ֲ�����(��Ҫָ��������ַ,ֻҪʹ��Data��
		pre->Data = *T;	//��¼��[0]��
		p = p->Next;	//��[1]����ʼ
		
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
				InsertLinkList(L, i+4, NewRoot);	//�����м�2�� + 1��ǰ������ +1����λ����
				LinkList_InsertSort(L);
				pre->Data = p->Next->Data;
				p = p->Next;
				L->Count--; //������ѭ��,û��Ҫ+������insert����Ϊ�˴��������㣬����ǻ�����
			}else {
				pre->Data = *T;//�����޸���L
			}
			p = p->Next;
		}
		free(pre);
		pre = NULL;
	}
	return;
}

/*(�ڲ�����)����HuffmanCode*/
/*T:�Ѵ����õ�Tree  
code :�����ʼ��calloc��NULL��String*
count :������0������Code�ĸ�ֵ��������������¼��ǰ�ݹ�Ĵ�����
size :LinkList��Ԫ������Count*/
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

/*������HuffmanNode��HuffmanTree*/
/*T : �Ѵ����ɹ���Tree
weight : ��Node��Ȩֵ
value �� ��Node��valueֵ*/
void InsertHuffmanNode(HuffmanTree * T, int weight, HFElement value)
{
	//������Ҷ��㶼�浽LinkList������Destroy����Build
	LinkList* L = LinkListInit();
	HuffmanTreeToLinkList(*T, L,-1);
	DestroyHuffmanTree(T);
	
	//�ⲿ����µ���Node
	Element HF_Node = (Element)malloc(sizeof(HuffmanNode));
	HF_Node->Data = value;
	HF_Node->Weight = weight;
	HF_Node->Left = NULL;
	HF_Node->Right = NULL;
	AppendLinkList(L, HF_Node);

	//����Build�շ�����
	LinkList_InsertSort(L);
	Build_HuffmanTree(T,L);
	String Code = (String)calloc(L->Count, sizeof(char));
	Build_HuffmanCode(*T, Code, 0, L->Count);

	//����LinkList���ַ���Code�ֲ�����
	DestroyLinkList(&L);
	free(Code);
	return;
}

/*(�ڲ�����)��HuffmanTree��Ҷ��㶼װ��LinkList[ ǰ�к���һ�� ]*/
/*weight:-1��ʾȫ����װ��ָ��weight�ͱ�ʾ��weight��װ*/
void HuffmanTreeToLinkList(HuffmanTree T,LinkList* L,int weight)
{
	if (T)
	{
		HuffmanTreeToLinkList(T->Left,L,weight);
		HuffmanTreeToLinkList(T->Right,L, weight);
		if (T->Left == NULL && T->Weight != weight) {
			//��ΪLinkListֻ�ǹ��ɣ�����Tree���ٶ����ʲ���Node��malloc
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

/*ɾ��HuffmanNode(����Ȩֵƥ��)*/
/*T : �Ѵ����ɹ���Tree
weight : ɾ��Nodeƥ���Ȩֵ*/
void DeleteHuffmanNode(HuffmanTree * T, int weight)
{
	//������Ҷ��㣨����ƥ���weight֮��)���浽LinkList������Destroy����Build
	LinkList* L = LinkListInit();
	HuffmanTreeToLinkList(*T, L, weight);
	DestroyHuffmanTree(T);

	//����Build�շ�����
	LinkList_InsertSort(L);
	Build_HuffmanTree(T,L);
	String Code = (String)calloc(L->Count, sizeof(char));
	Build_HuffmanCode(*T, Code, 0, L->Count);

	//����LinkList���ַ���Code�ֲ�����
	DestroyLinkList(&L);
	free(Code);
	return;
}

/*�޸�HuffmanNode(����Ȩֵƥ��[ ǰ�к���һ�� ])*/
/*T : �Ѵ����ɹ���Tree
weight : ��Ҫ�޸�Nodeƥ���Ȩֵ(���ظ�Ȩֵ��ȫ���滻)
value : �µ�valueֵ*/
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

/*����HuffmanTree ����NULL*/
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

/*�������*/
int GetDepth(HuffmanTree T)
{
	int i, j;
	if (T == NULL) return 0;
	i = GetDepth(T->Left);
	j = GetDepth(T->Right);
	return i > j ? i + 1 : j + 1;
}

#pragma region Traverse[ǰ�к���Ч����һ��]
/*ǰ�����*/
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

/*�������*/
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

/*�������*/
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

/*�������*/
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






