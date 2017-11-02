#pragma once
/*brief An implementation of LinkList,  including insert,append,destroy,insertSort (Only for HuffmanTree)*/

//[ 即根据外部导入需要修改该Element类型 ]
typedef HuffmanTree Element; 

#pragma region LinkList
typedef struct Node {
	Element Data;
	struct Node * Next;
	struct Node * Front;
}Node;

/*修改链表内Node的Data类型(即根据外部导入需要修改该类型)*/
typedef struct LinkList {
	struct Node * Head;	 
	struct Node * Tail;	 
	int Count;	 
}LinkList;
#pragma endregion

#pragma region Functions;
LinkList* LinkListInit();
Status IsEmptyLinkList(LinkList * L);
void InsertLinkList(LinkList * L, int index, Element value);
void AppendLinkList(LinkList* L, Element value);
void DestroyLinkList(LinkList** L);
void LinkList_InsertSort(LinkList * L);
#pragma endregion


/*初始化LinkList*/
LinkList* LinkListInit()
{
	Node* head = (Node*)malloc(sizeof(Node));
	if (head == NULL) {
		printf("头哨兵初始化动态分配内存失败\n");
		exit(-1);
	}

	LinkList* ret = (LinkList*)malloc(sizeof(LinkList));
	if (ret == NULL) {
		printf("LinkList初始化动态分配内存失败\n");
		exit(-1);
	}
	ret->Count = 0;
	ret->Head = head;
	ret->Tail = head;
	return ret;
}

//LinkList追加
void AppendLinkList(LinkList * L, Element value)
{
	if (L == NULL) {
		printf("空指针无效\n");
		return;
	}
	Node* p = (Node*)malloc(sizeof(Node));
	p->Data = value;
	p->Next = NULL;
	p->Front = L->Tail;
	L->Tail->Next = p;
	L->Tail = p;
	L->Count++;
	return;
}

//LinkList插入
/*index：插入的位置，位置下标大于链表长度自动添加在链表最后*/
void InsertLinkList(LinkList * L, int index, Element value)
{
	if (L == NULL) {
		printf("空指针无效\n");
		return;
	}

	if (index < 0) {
		printf("index不可以为负数\n");
		return;
	}

	if (index >= L->Count) {
		AppendLinkList(L, value);
		return;
	}

	Node* p;
	if (index > L->Count / 2) {
		p = L->Tail;
		for (int i = L->Count - 1; i >= index; i--) {
			p = p->Front;
		}
	}
	else {
		p = L->Head;
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
	L->Count++;
	return;
}

//判断是否为空LinkList
Status IsEmptyLinkList(LinkList * L)
{
	if (L == NULL) {
		printf("空指针无效\n");
		return FALSE;
	}

	if (L->Head == L->Tail) return TRUE;
	else return FALSE;
}

//销毁LinkList,返回NULL
void DestroyLinkList(LinkList** L)
{
	if (*L == NULL) {
		printf("无法操作空Link\n");
		return;
	}

	Node* p = (*L)->Head;
	while (p) {
		Node* q = p;
		p = p->Next;
		free(q);
	}

	free(*L);
	(*L)->Tail = NULL;
	(*L)->Head = NULL;
	*L = NULL;
	return;
}

//LinkList插入排序
//（根据具体类型修改比较大小条件)
void LinkList_InsertSort(LinkList * L)
{
	if (IsEmptyLinkList(L)) {
		printf("空LinkList无法排序\n");
		return;
	}

	Node* p = L->Head->Next;
	while (p->Next)	
	{
		Node* q = p->Next;
		Node* t = p;
		while (q)
		{
			if (t->Data->Weight > q->Data->Weight) {
				t = q;
				q = q->Next;
			}else {
				q = q->Next;
			}
		}
		if (t != p){
			Element temp = p->Data;
			p->Data = t->Data;
			t->Data = temp;
		}
		p = p->Next;
	}
	return;
}