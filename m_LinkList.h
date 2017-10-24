#pragma once
#include<stdio.h>
#include<stdlib.h>

#pragma region Status
#define FALSE 0
#define TRUE 1
typedef int Status;
#pragma endregion

#pragma region LinkList
/*˫�ڱ�+˫������ --����ѯ·������һ�룩*/
typedef int Element;
typedef struct Node {
	Element Data;
	struct Node * Next;
	struct Node * Front;
}Node;

typedef struct LinkList {
	struct Node * Head;	//ͷ�ڱ�
	struct Node * Tail;	//β�ڱ�
	int Count;	//������
}LinkList;
#pragma endregion

#pragma region Functions;
LinkList* LinkListInit_InputArr(int* arr, int size);
Status IsEmpty(LinkList * list);
LinkList* LinkListInit_KeyCodeInput();
void ShowLinkList(LinkList * list);
void Insert(LinkList * list, int index, Element value);
void Append(LinkList* list, Element value);
void Delete(LinkList * list, int index);
void Remove(LinkList * list);
Element Get(LinkList * list, int index);
Element GetFirst(LinkList * list);
void SetValue(LinkList * list, int index, Element value);
void Destroy(LinkList** list);
void Clear(LinkList * list);
void Inversion(LinkList * list);
void LinkList_BubbleSort(LinkList * list);
void LinkList_InsertSort(LinkList * list);
int GetSize(LinkList * list);
#pragma endregion



//LinkList׷��
void Append(LinkList * list,Element value)
{
	if (list == NULL) {
		printf("��ָ����Ч\n");
		return;
	}
	Node* p = (Node*)malloc(sizeof(Node));
	p->Data = value;
	p->Next = NULL;
	p->Front = list->Tail;
	list->Tail->Next = p;
	list->Tail = p;
	list->Count++;
	return;
}

//LinkList����
/*index�������λ�ã�λ���±�����������Զ�������������*/
void Insert(LinkList * list, int index, Element value)
{
	if (list == NULL) {
		printf("��ָ����Ч\n");
		return;
	}

	if (index < 0) {
		printf("index������Ϊ����\n");
		return;
	}

	if (index >= list->Count){
		Append(list, value);
		return;
	}

	Node* p;
	if (index > list->Count / 2) {
		p = list->Tail;
		for (int i = list->Count - 1; i >= index; i--){
			p = p->Front;
		}
	}
	else {
		p = list->Head;
		for (int i = 0; i < index; i++) {
			p = p->Next;
		}
	}

	Node* item = (Node*)malloc(sizeof(Node));
	item->Data = value;
	item->Next = p->Next;
	item->Front = p;
	p->Next->Front = item;
	p->Next = item;
	list->Count++;
	return;
}

//�ֶ������ʼ��LinkList
LinkList* LinkListInit_KeyCodeInput()
{
	printf("��������Ҫ��ʼ��Ԫ�ص����� :");
	int size;
	scanf_s("%d", &size);
	if (size < 0 ) {
		printf("������������\n");
		exit(-1);
	}

	Node* m_Head = (Node*)malloc(sizeof(Node));
	if (m_Head == NULL) {
		printf("ͷ��㶯̬�����ڴ�ʧ��\n");
		exit(-1);
	}
	LinkList* ret = (LinkList*)malloc(sizeof(LinkList));
	if (ret == NULL) {
		printf("LinkList��̬�����ڴ�ʧ��\n");
		exit(-1);
	}

	//��ʼ���ṹ���Ա
	m_Head->Next = NULL;
	m_Head->Front = NULL;
	ret->Head = m_Head;
	ret->Tail = m_Head;
	ret->Count = 0;

	//Ϊ�����������
	for (int i = 0; i < size; i++)
	{
		printf("�������%d��Ԫ�ص�value :", i);
		int arg;
		scanf_s("%d", &arg);
		Append(ret, arg);
	}
	return ret;
}

//ͨ�������ʼ��LinkList
LinkList* LinkListInit_InputArr(int* arr,int size)
{
	if (arr == NULL) {
		printf("�����int����Ϊ��\n");
		exit(-1);
	}
	if (size < 0) {
		printf("Size����Ϊ����\n");
		exit(-1);
	}

	Node* m_Head = (Node*)malloc(sizeof(Node));
	if (m_Head == NULL) {
		printf("ͷ��㶯̬�����ڴ�ʧ��\n");
		exit(-1);
	}
	LinkList* ret = (LinkList*)malloc(sizeof(LinkList));
	if (ret == NULL) {
		printf("LinkList��̬�����ڴ�ʧ��\n");
		exit(-1);
	}

	//��ʼ���ṹ���Ա
	m_Head->Next = NULL;
	m_Head->Front = NULL;
	ret->Count = 0;
	ret->Head = m_Head;
	ret->Tail = m_Head;
	
	//д���������
	for (int i = 0; i < size; i++){
		Append(ret, arr[i]);
		
	}
	return ret;
}

//�ж��Ƿ�Ϊ��
Status IsEmpty(LinkList * list)
{
	if (list == NULL) {
		printf("��ָ����Ч\n");
		exit(-1);
	}

	if (list->Count == 0) return TRUE;
	else return FALSE;

	/*if (list->Head == list->Tail) return TRUE;
	else return FALSE;*/
}

//����LinkList
void ShowLinkList(LinkList * list)
{ 
	if (IsEmpty(list)) {
		printf("��LinkList,��Ԫ��\n");
		return;
	}

	Node* p = list->Head->Next;
	while (p){
		printf("%d ", p->Data);
		p = p->Next;
	}
	printf("\n");
	return;
}

//��ȡָ��index��value
Element Get(LinkList * list, int index)
{
	if (IsEmpty(list)) {
		printf("��LinkList,��Ԫ��\n");
		return NULL;
	}
	if (index < 0 || index >= list->Count){
		printf("�޷���ȡ��[%d]��λ�õ�Ԫ��\n", index);
		return NULL;
	}

	Node* p ;
	if (index > list->Count / 2) {
		p = list->Tail;
		for (int i = list->Count - 1; i > index; i--){
			p = p->Front;
		}
	}
	else{
		p = list->Head;
		for (int i = 0; i <= index; i++) {
			p = p->Next;
		}
	}
	return p->Data;
}

//��ȡ��һ��Ԫ�ص�value
Element GetFirst(LinkList * list)
{
	if (IsEmpty(list)) {
		printf("��LinkList,��Ԫ��\n");
		return NULL;
	}

	return list->Head->Next->Data;
}

//�޸�ָ��index��value
void SetValue(LinkList * list, int index, Element value)
{
	if (IsEmpty(list)) {
		printf("��LinkList,��Ԫ��\n");
		return NULL;
	}
	if (index < 0 || index >= list->Count) {
		printf("�޷��޸ĵ�[%d]��λ�õ�Ԫ��value\n", index);
		return NULL;
	}

	Node* p;
	if (index > list->Count / 2) {
		p = list->Tail;
		for (int i = list->Count - 1; i > index; i--) {
			p = p->Front;
		}
	}
	else {
		p = list->Head;
		for (int i = 0; i <= index; i++) {
			p = p->Next;
		}
	}
	p->Data = value;
}

//ɾ��ָ��index��value
void Delete(LinkList * list, int index)
{
	if (IsEmpty(list)) {
		printf("��LinkList,��Ԫ��\n");
		return;
	}
	if (index < 0 || index >= list->Count) {
		printf("�޷�ɾ����[%d]��λ�õ�Ԫ��\n", index);
		return;
	}

	Node* p;
	if (index > list->Count / 2) {
		p = list->Tail;
		for (int i = list->Count - 1; i >= index; i--) {
			p = p->Front;
		}
	}
	else {
		p = list->Head;
		for (int i = 0; i < index; i++) {
			p = p->Next;
		}
	}

	Node* temp = p->Next;  
	temp->Next->Front = p;
	p->Next = temp->Next;
	free(temp);
	temp->Next = NULL;
	temp->Front = NULL;
	list->Count--;
	return;
}

//ɾ�����һ��value
void Remove(LinkList * list)
{
	if (IsEmpty(list)) {
		printf("��LinkList,��Ԫ��\n");
		return;
	}

	Node * p = list->Tail;
	list->Tail = p->Front;
	free(p);
	p->Front = NULL;
	list->Tail->Next = NULL;
	list->Count--;
	return;
}

//����LinkList
/*freeLinkList,����NULL*/
void Destroy(LinkList** list)
{
	Node* p = (*list)->Head;
	while (p) {
		Node* q = p->Next;
		free(p);
		p->Front = NULL;
		p->Next = NULL;
		p = q;
	}
	
	free(*list);
	(*list)->Tail = NULL;
	(*list)->Head = NULL;
	*list = NULL;
	return;
}

//���LinkList
/*����һ����Ԫ�ص�LinkList*/
void Clear(LinkList * list)
{
	if (IsEmpty(list)) {
		printf("�������޷�����\n");
		return;
	}

	Node* p = list->Head->Next;
	while (p) {
		Node* q = p->Next;
		free(p);
		p->Front = NULL;
		p->Next = NULL;
		p = q;
	}
	list->Tail = list->Head;
	list->Head->Next = NULL;
	list->Head->Front = NULL;
	list->Count = 0;
	return;
}

//LinkList����
void Inversion(LinkList * list)
{
	if (IsEmpty(list)) {
		printf("�������޷�Inversion����\n");
		return;
	}

	Node* p = list->Head->Next;
	Node* q = list->Tail;
	for (int i = 0; i < list->Count / 2; i++)
	{
		int temp = p->Data;
		p->Data = q->Data;
		q->Data = temp;
		p = p->Next;
		q = q->Front;
	}
	return;
}

//LinkListð������
void LinkList_BubbleSort(LinkList * list)
{
	if (IsEmpty(list)) {
		printf("�������޷�����\n");
		return;
	}

	int i, j;
	Node* p;
	Node* q;
	for (i = 0, p = list->Head->Next; i < list->Count - 1; i++,p = p->Next){
		for (j = i+1,q = p->Next; j < list->Count;j++,q = q->Next){
			if (p->Data > q->Data) {
				int temp = p->Data;
				p->Data = q->Data;
				q->Data = temp;
			}
		}
	}
	return;
}

//LinkList��������
void LinkList_InsertSort(LinkList * list)
{
	if (IsEmpty(list)) {
		printf("�������޷�����\n");
		return;
	}

	int i;
	Node* p;

	for (i = 0,p = list->Head->Next; i < list->Count - 1; i++,p = p->Next)
	{
		Node* q = p->Next;
		Node* t = p;
		while (q)	 
		{
			if (t->Data > q->Data){
				t = q;   
				q = q->Next;
			}
			else {
				q = q->Next;
			}
		}
		Element temp = p->Data;
		p->Data = t->Data;
		t->Data = temp;
	}
	return;
}

//LinkList����
int GetSize(LinkList * list)
{
	if (IsEmpty(list)) {
		return 0;
	}
	return list->Count;

	/*int ret = 0;
	Node* p = list->Head->Next;
	while (p)
	{
		ret++;
		p = p->Next;
	}
	return ret;*/
}