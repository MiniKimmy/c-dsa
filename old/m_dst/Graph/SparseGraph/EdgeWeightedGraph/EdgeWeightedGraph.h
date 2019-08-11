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
	int v_Count;  //点总数
 	int e_Count;  //边总数
	int** pBase;  //所有的点  List<LinkGNode>  int**是 List<LinkGNode>. 专门"存ret指针"的数组
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

//初始化图
Graph* InitGraph(int V)
{
	Graph* ret = (Graph*)malloc(sizeof(Graph));
	if (ret == NULL) {
		PRINT_STRING("Graph初始化动态分配内存失败");
		exit(-1);
	}
	ret->v_Count = V;
	ret->e_Count = 0;
	ret->pBase = (int**)malloc(sizeof(int*) * V);

	//创建头哨兵LinkGNode 即 ret->pBase[i]
	for (int i = 0; i < ret->v_Count; i++) {
		ret->pBase[i] = (int*)malloc(sizeof(LinkGNode));
		if (ret->pBase[i] == NULL) {
			PRINT_STRING("pBase[i]初始化动态分配内存失败");
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

//先Init初始化再生成图
void CreateGraph_ByInputKeyCode(Graph* G)
{
	Traverse_ALLKEY(G);
	printf("请输入需要添加Edge的个数 ： ");
	int m_Edge;
	scanf_s("%d", &m_Edge);

	//连接Edge
	for (int i = 0; i < m_Edge; i++) 
	{
		PRINT_STRING("\n请输入需要连接的2个Node的KEY");
		int v, w;
		float weight;
		scanf_s("%d", &v);
		scanf_s("%d", &w);
		scanf_s("%f", &weight);

		while (v >= G->v_Count || w >= G->v_Count || v == w || v <0 || w < 0) {
			printf("\n请重新输入需要连接的2个Node的KEY,不能相等且不能大于 %d.\n", G->v_Count);
			scanf_s("%d", &v);
			scanf_s("%d", &w);
			scanf_s("%f", &weight);
		}

		Edge* edge = NewEdge(v, w, weight); //test weight = 1
		AddEdges(G, edge);

		if (G->e_Count > i) {
			printf("已连接了 %d 个链接\n", G->e_Count);
		}else {
			i = i == 0 ? 0 : --i;
			PRINT_STRING("未链接成功,请重新输入");
		}
	}
	return;
}

/*(内部方法)*/ //添加Edge到对应的LinkGNode
void AddEdges(Graph* G, Edge* E)
{
	//判断不重边...【待整理】

	//拿到Key
	int v = GetNode(E);   
	int w = GetOtherNode(E, v); 

	//拿到Key的List
	LinkGNode* v_list = GetLinkGNode(G, v);
	LinkGNode* w_list = GetLinkGNode(G, w);

	//生成结点node
	GNode* v_node = NewGNode(E);
	GNode* w_node = NewGNode(E);

	//添加结点
	AddGNode(v_list, v_node);
	AddGNode(w_list, w_node);
	
	G->e_Count ++ ;  //添加边数量

	return;
}

//获取最小生成树Test
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
	
	//Traverse_Edges(ret->edges, ret->count); //直接输出连接好的Edge
	return ret;
}

/*内部方法*/ //获取所有的Edges
Edge** GetEdges(Graph* G)
{
	//记录所有的Edge
	Edge** ret = (Edge**)malloc(sizeof(Edge*) * G->e_Count);
	if (ret == NULL) {
		PRINT_STRING("data[]初始化动态分配内存失败");
		exit(-1);
	}

	//添加所有的Edge
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

	InsertSortEdges(ret, k);    //排序Edge
	return ret;
}

/*内部方法*/ //初始化最小生成树
MinTree* MinTreeInit(Graph* G)
{
	//初始化最小生成树
	MinTree* ret = (MinTree*)malloc(sizeof(MinTree));
	if (ret == NULL) {
		PRINT_STRING("MinTree初始化动态分配内存失败");
		exit(-1);
	}

	ret->count = 0;
	ret->edges = (Edge**)malloc(sizeof(Edge*)* G->v_Count);
	if (ret->edges == NULL) {
		PRINT_STRING("MinTree[]初始化动态分配内存失败");
		exit(-1);
	}
	return ret;
}

/*内部方法*/ //排序Edge(插入排序)
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

/*(内部方法)*/ //生成GNode
GNode* NewGNode(Edge* e)
{
	GNode* ret = (GNode*)malloc(sizeof(GNode));
	if (ret == NULL) {
		PRINT_STRING("GNode初始化动态分配内存失败");
		exit(-1);
	}
	ret->edge = e;
	ret->next = NULL;
	return ret;
}

/*(内部方法)*/ //LinkGNode 添加GNode
void AddGNode(LinkGNode* L, GNode* node)
{
	GNode* last = L->head; 
	for (int i = 0; i < L->count; i++)
	{
		last = last->next; //拿到最后一个GNode
	}
	
	last->next = node;
	L->count++;
}

/*(内部方法)*/ //获取某个点的LinkGNode
LinkGNode* GetLinkGNode(Graph * G, int key)
{
	if (key < G->v_Count) {
		return (LinkGNode*)G->pBase[key];
	}
	return NULL;
}

/*(内部方法)*/ //遍历一次Key
void Traverse_ALLKEY(Graph* G)
{
	for (int i = 0; i < G->v_Count; i++)
	{
		printf("%d ", i);
	}
	PRINT_STRING("\n----------------------");
}

/*(内部方法)*/ //遍历一次Graph
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

/*(内部方法)*/ //遍历Edge[]
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