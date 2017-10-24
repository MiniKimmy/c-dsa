#pragma once
#include<stdio.h>
#include<stdlib.h>

#pragma region Status
#define FALSE 0
#define TRUE 1
typedef int Status;
#pragma endregion

#pragma region LinkList
/*双哨兵+双向链表 --（查询路径缩短一半）*/
typedef int Element;
typedef struct Node {
	Element Data;
	struct Node * Next;
	struct Node * Front;
}Node;

typedef struct LinkList {
	struct Node * Head;	//头哨兵
	struct Node * Tail;	//尾哨兵
	int Count;	//链表长度
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



//LinkList追加
void Append(LinkList * list,Element value)
{
	if (list == NULL) {
		printf("空指针无效\n");
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

//LinkList插入
/*index：插入的位置，位置下标大于链表长度自动添加在链表最后*/
void Insert(LinkList * list, int index, Element value)
{
	if (list == NULL) {
		printf("空指针无效\n");
		return;
	}

	if (index < 0) {
		printf("index不可以为负数\n");
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

//手动输入初始化LinkList
LinkList* LinkListInit_KeyCodeInput()
{
	printf("请输入需要初始化元素的数量 :");
	int size;
	scanf_s("%d", &size);
	if (size < 0 ) {
		printf("输入数量出错\n");
		exit(-1);
	}

	Node* m_Head = (Node*)malloc(sizeof(Node));
	if (m_Head == NULL) {
		printf("头结点动态分配内存失败\n");
		exit(-1);
	}
	LinkList* ret = (LinkList*)malloc(sizeof(LinkList));
	if (ret == NULL) {
		printf("LinkList动态分配内存失败\n");
		exit(-1);
	}

	//初始化结构体成员
	m_Head->Next = NULL;
	m_Head->Front = NULL;
	ret->Head = m_Head;
	ret->Tail = m_Head;
	ret->Count = 0;

	//为链表添加数据
	for (int i = 0; i < size; i++)
	{
		printf("请输入第%d个元素的value :", i);
		int arg;
		scanf_s("%d", &arg);
		Append(ret, arg);
	}
	return ret;
}

//通过数组初始化LinkList
LinkList* LinkListInit_InputArr(int* arr,int size)
{
	if (arr == NULL) {
		printf("传入的int数组为空\n");
		exit(-1);
	}
	if (size < 0) {
		printf("Size不能为负数\n");
		exit(-1);
	}

	Node* m_Head = (Node*)malloc(sizeof(Node));
	if (m_Head == NULL) {
		printf("头结点动态分配内存失败\n");
		exit(-1);
	}
	LinkList* ret = (LinkList*)malloc(sizeof(LinkList));
	if (ret == NULL) {
		printf("LinkList动态分配内存失败\n");
		exit(-1);
	}

	//初始化结构体成员
	m_Head->Next = NULL;
	m_Head->Front = NULL;
	ret->Count = 0;
	ret->Head = m_Head;
	ret->Tail = m_Head;
	
	//写入具体数据
	for (int i = 0; i < size; i++){
		Append(ret, arr[i]);
		
	}
	return ret;
}

//判断是否为空
Status IsEmpty(LinkList * list)
{
	if (list == NULL) {
		printf("空指针无效\n");
		exit(-1);
	}

	if (list->Count == 0) return TRUE;
	else return FALSE;

	/*if (list->Head == list->Tail) return TRUE;
	else return FALSE;*/
}

//遍历LinkList
void ShowLinkList(LinkList * list)
{ 
	if (IsEmpty(list)) {
		printf("空LinkList,无元素\n");
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

//获取指定index的value
Element Get(LinkList * list, int index)
{
	if (IsEmpty(list)) {
		printf("空LinkList,无元素\n");
		return NULL;
	}
	if (index < 0 || index >= list->Count){
		printf("无法获取第[%d]个位置的元素\n", index);
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

//获取第一个元素的value
Element GetFirst(LinkList * list)
{
	if (IsEmpty(list)) {
		printf("空LinkList,无元素\n");
		return NULL;
	}

	return list->Head->Next->Data;
}

//修改指定index的value
void SetValue(LinkList * list, int index, Element value)
{
	if (IsEmpty(list)) {
		printf("空LinkList,无元素\n");
		return NULL;
	}
	if (index < 0 || index >= list->Count) {
		printf("无法修改第[%d]个位置的元素value\n", index);
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

//删除指定index的value
void Delete(LinkList * list, int index)
{
	if (IsEmpty(list)) {
		printf("空LinkList,无元素\n");
		return;
	}
	if (index < 0 || index >= list->Count) {
		printf("无法删除第[%d]个位置的元素\n", index);
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

//删除最后一个value
void Remove(LinkList * list)
{
	if (IsEmpty(list)) {
		printf("空LinkList,无元素\n");
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

//销毁LinkList
/*freeLinkList,返回NULL*/
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

//清除LinkList
/*返回一个空元素的LinkList*/
void Clear(LinkList * list)
{
	if (IsEmpty(list)) {
		printf("空序列无法排序\n");
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

//LinkList倒置
void Inversion(LinkList * list)
{
	if (IsEmpty(list)) {
		printf("空序列无法Inversion操作\n");
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

//LinkList冒泡排序
void LinkList_BubbleSort(LinkList * list)
{
	if (IsEmpty(list)) {
		printf("空序列无法排序\n");
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

//LinkList插入排序
void LinkList_InsertSort(LinkList * list)
{
	if (IsEmpty(list)) {
		printf("空序列无法排序\n");
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

//LinkList长度
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