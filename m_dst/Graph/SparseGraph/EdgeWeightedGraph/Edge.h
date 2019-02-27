#include<stdio.h>
#include<stdlib.h>
#define PRINT_STRING(x) printf("%s\n",x)

typedef struct Edge {
	int v;
	int w;
	float weight;
}Edge;

#pragma region Functions
int GetNode(Edge* E);
int GetOtherNode(Edge* E, int v);
Edge* NewEdge(int v, int w, float weight);
//Edge* NewEdge(int v, int w, int weight);
int CompareEdge(Edge* e1, Edge* e2);
#pragma endregion

//��ȡһ�����Key
int GetNode(Edge* E) {
	return E->v;
}

//��ȡ��һ�����Key
int GetOtherNode(Edge* E, int v)
{
	if (v == E->v) return E->w;
	if (v == E->w) return E->v;
	else return -1;
}

//����Edge
Edge* NewEdge(int v, int w, float weight)
{
	Edge* ret = (Edge*)malloc(sizeof(Edge));
	if (ret == NULL) {
		PRINT_STRING("newEdge�ڳ�ʼ����̬�����ڴ�ʧ��");
		exit(-1);
	}
	ret->v = v;
	ret->w = w;
	ret->weight = weight;

	return ret;
}

//�Ƚ�Weight . e1.weight > e2.weight --> return 1
int CompareEdge(Edge* e1, Edge* e2)
{
	if (e1->weight > e2->weight) return 1;
	else if (e1->weight < e2->weight) return -1;
	else return 0;
}

//Test
void ToString_Edge(Edge* e,int key)
{
	if (e->v == key) {
		printf("%d ", e->w);
	}else {
		printf("%d ", e->v);
	}
	return;
}