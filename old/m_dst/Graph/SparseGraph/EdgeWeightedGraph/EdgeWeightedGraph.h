#include"Edge.h"
#include"unionfind.h"

typedef struct GNode {
	Edge* edge;
	struct GNode* next;     
}GNode;

typedef struct LinkGNode {
	int count;
	GNode* head;  //List<Edge>
}LinkGNode;

typedef struct Graph {
	int v_Count;  //������
 	int e_Count;  //������
	int** pBase;  //���еĵ�  List<LinkGNode>  int**�� List<LinkGNode>. ר��"��retָ��"������
}Graph;

typedef struct MinTree { 
	int count;
	Edge** edges;
}MinTree;

#pragma region Functions
Graph* InitGraph(int V);
void CreateGraph_ByInputKeyCode(Graph* G);
void Traverse_Graph(Graph* G);
MinTree* GetMinTree(Graph* G);
void Traverse_Edges(Edge** list, int count);
	#pragma region PrivateFunctions
	GNode* NewGNode(Edge* e);
	LinkGNode* GetLinkGNode(Graph * G, int key);
	void AddGNode(LinkGNode* L, GNode* node);
	void AddEdges(Graph* G, Edge* E);
	void Traverse_ALLKEY(Graph* G);
	Edge** GetEdges(Graph* G);
	void InsertSortEdges(Edge** list, int count);
	MinTree* MinTreeInit(Graph* G);
	#pragma endregion
#pragma endregion

//��ʼ��ͼ
Graph* InitGraph(int V)
{
	Graph* ret = (Graph*)malloc(sizeof(Graph));
	if (ret == NULL) {
		PRINT_STRING("Graph��ʼ����̬�����ڴ�ʧ��");
		exit(-1);
	}
	ret->v_Count = V;
	ret->e_Count = 0;
	ret->pBase = (int**)malloc(sizeof(int*) * V);

	//����ͷ�ڱ�LinkGNode �� ret->pBase[i]
	for (int i = 0; i < ret->v_Count; i++) {
		ret->pBase[i] = (int*)malloc(sizeof(LinkGNode));
		if (ret->pBase[i] == NULL) {
			PRINT_STRING("pBase[i]��ʼ����̬�����ڴ�ʧ��");
			exit(-1);
		}
		LinkGNode* list = (LinkGNode*)malloc(sizeof(LinkGNode));
		list->count = 0;
		GNode* node = (GNode*)(malloc)(sizeof(GNode)); 
		node->edge = NULL;
		node->next = NULL;
		list->head = node;	
		ret->pBase[i] = (int*)list;
	}
	return ret;
}

//��Init��ʼ��������ͼ
void CreateGraph_ByInputKeyCode(Graph* G)
{
	Traverse_ALLKEY(G);
	printf("��������Ҫ���Edge�ĸ��� �� ");
	int m_Edge;
	scanf_s("%d", &m_Edge);

	//����Edge
	for (int i = 0; i < m_Edge; i++) 
	{
		PRINT_STRING("\n��������Ҫ���ӵ�2��Node��KEY");
		int v, w;
		float weight;
		scanf_s("%d", &v);
		scanf_s("%d", &w);
		scanf_s("%f", &weight);

		while (v >= G->v_Count || w >= G->v_Count || v == w || v <0 || w < 0) {
			printf("\n������������Ҫ���ӵ�2��Node��KEY,��������Ҳ��ܴ��� %d.\n", G->v_Count);
			scanf_s("%d", &v);
			scanf_s("%d", &w);
			scanf_s("%f", &weight);
		}

		Edge* edge = NewEdge(v, w, weight); //test weight = 1
		AddEdges(G, edge);

		if (G->e_Count > i) {
			printf("�������� %d ������\n", G->e_Count);
		}else {
			i = i == 0 ? 0 : --i;
			PRINT_STRING("δ���ӳɹ�,����������");
		}
	}
	return;
}

/*(�ڲ�����)*/ //���Edge����Ӧ��LinkGNode
void AddEdges(Graph* G, Edge* E)
{
	//�жϲ��ر�...��������

	//�õ�Key
	int v = GetNode(E);   
	int w = GetOtherNode(E, v); 

	//�õ�Key��List
	LinkGNode* v_list = GetLinkGNode(G, v);
	LinkGNode* w_list = GetLinkGNode(G, w);

	//���ɽ��node
	GNode* v_node = NewGNode(E);
	GNode* w_node = NewGNode(E);

	//��ӽ��
	AddGNode(v_list, v_node);
	AddGNode(w_list, w_node);
	
	G->e_Count ++ ;  //��ӱ�����

	return;
}

//��ȡ��С������Test
MinTree* GetMinTree(Graph* G)
{
	MinTree* ret = MinTreeInit(G);  
	Edge** data = GetEdges(G);
	UF* uf = InitUF(G->v_Count);

	for (int i = 0; i < G->e_Count; i++)
	{
		if (uf->count == 1) break;

		Edge* edge = data[i];
		int v = GetNode(edge);
		int w = GetOtherNode(edge,v);

		if (IsConnected(uf, v, w)) {
			continue;
		}else {
			WeightQuick_Union(uf, v, w);
			ret->edges[ret->count++] = edge;
		}
	}
	
	//Traverse_Edges(ret->edges, ret->count); //ֱ��������Ӻõ�Edge
	return ret;
}

/*�ڲ�����*/ //��ȡ���е�Edges
Edge** GetEdges(Graph* G)
{
	//��¼���е�Edge
	Edge** ret = (Edge**)malloc(sizeof(Edge*) * G->e_Count);
	if (ret == NULL) {
		PRINT_STRING("data[]��ʼ����̬�����ڴ�ʧ��");
		exit(-1);
	}

	//������е�Edge
	int k = 0;
	for (int i = 0; i < G->v_Count; i++)
	{
		LinkGNode* list = GetLinkGNode(G, i);
		GNode* node = list->head;
		for (int j = 0; j < list->count; j++)
		{
			node = node->next;
			if (GetOtherNode(node->edge, i) < i) {
				continue;
			}
			else {
				ret[k++] = node->edge;
			}
		}
	}

	//Traverse_Edges(ret, k); 	//Test

	InsertSortEdges(ret, k);    //����Edge
	return ret;
}

/*�ڲ�����*/ //��ʼ����С������
MinTree* MinTreeInit(Graph* G)
{
	//��ʼ����С������
	MinTree* ret = (MinTree*)malloc(sizeof(MinTree));
	if (ret == NULL) {
		PRINT_STRING("MinTree��ʼ����̬�����ڴ�ʧ��");
		exit(-1);
	}

	ret->count = 0;
	ret->edges = (Edge**)malloc(sizeof(Edge*)* G->v_Count);
	if (ret->edges == NULL) {
		PRINT_STRING("MinTree[]��ʼ����̬�����ڴ�ʧ��");
		exit(-1);
	}
	return ret;
}

/*�ڲ�����*/ //����Edge(��������)
void InsertSortEdges(Edge** list, int count)
{
	printf("\n");
	for (int i = 0; i < count; i++)
	{
		//printf("%d ", list[i]->weight);
		printf("%f ", list[i]->weight);
	}
	printf("\n");

	for (int i = 1; i < count; i++)
	{
		Edge* edge = list[i];
		int k = i;
		for (int j = i - 1; j >= 0 && CompareEdge(list[j], edge) == 1; j--)
		{
			list[j+1] = list[j];
			k = j;
		}
		if (k != i) {
			list[k] = edge;
		}
	}

	for (int i = 0; i < count; i++)
	{
		//printf("%d ", list[i]->weight);
		printf("%f ", list[i]->weight);
	}
	printf("\n");
}

/*(�ڲ�����)*/ //����GNode
GNode* NewGNode(Edge* e)
{
	GNode* ret = (GNode*)malloc(sizeof(GNode));
	if (ret == NULL) {
		PRINT_STRING("GNode��ʼ����̬�����ڴ�ʧ��");
		exit(-1);
	}
	ret->edge = e;
	ret->next = NULL;
	return ret;
}

/*(�ڲ�����)*/ //LinkGNode ���GNode
void AddGNode(LinkGNode* L, GNode* node)
{
	GNode* last = L->head; 
	for (int i = 0; i < L->count; i++)
	{
		last = last->next; //�õ����һ��GNode
	}
	
	last->next = node;
	L->count++;
}

/*(�ڲ�����)*/ //��ȡĳ�����LinkGNode
LinkGNode* GetLinkGNode(Graph * G, int key)
{
	if (key < G->v_Count) {
		return (LinkGNode*)G->pBase[key];
	}
	return NULL;
}

/*(�ڲ�����)*/ //����һ��Key
void Traverse_ALLKEY(Graph* G)
{
	for (int i = 0; i < G->v_Count; i++)
	{
		printf("%d ", i);
	}
	PRINT_STRING("\n----------------------");
}

/*(�ڲ�����)*/ //����һ��Graph
void Traverse_Graph(Graph* G)
{
	if (G == NULL) return;

	for (int i = 0; i < G->v_Count; i++)
	{
		LinkGNode* list = GetLinkGNode(G, i);
		printf("%d :", i);
		GNode* node = list->head;
		for (int j = 0; j < list->count; j++)
		{
			node = node->next;
			ToString_Edge(node->edge,i);
		}
		printf("\n");
	}
}

/*(�ڲ�����)*/ //����Edge[]
void Traverse_Edges(Edge** list,int count)
{
	printf("\n%d : e_count \n", count);
	for (int i = 0; i < count; i++)
	{
		//printf("%d : %d(%d)\n", list[i]->v, list[i]->w,list[i]->weight);
		printf("%d : %d(%f)\n", list[i]->v, list[i]->w, list[i]->weight);
	}
	PRINT_STRING("");
}