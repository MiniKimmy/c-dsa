## Check from vi to vj

Given a directed graph, determine whether vi can reach vj.

给定一个有向图，判断vi是否能到达vj

**Example 1:**
```
ex:Graph "01,02,23,31,12"
Input:0,3
Output:true
Explanation:[0->2->3 or 0->1->2->3]
```
**Example 2:**
```
ex:Graph "01,02,23,31,12"
Input:1,0
Output:false
```
**Example 3:**
```
ex:Graph "01,02,23,31,12"
Input:3,0
Output:false
```

## hints
```
    dfs Traverse Graph.
```

## Solution
``` c
/**
* Definition for a adjacency graph.
* struct AdjacencyGraph {
*     int vertices;
*     int edges;
*     VNode* nodes[MAXSIZE];
*     int* columnSize;
* };
* Node* findVNode(struct AdjacencyGraph* G, int v) { return v < 0 || CastGraph(G)->vertices <= v ? NULL : CastGraph(G)->vNodes[v]; }
*/

int checkPathInner(struct AdjacencyGraph* G, int start, int end, int* marked) {
    marked[start] = 1;
    Node* p = findVNode(G, start);

    while (p->next) {
        p = p->next;
        if (p->val == end) return 1;

        if (marked[p->val] == 0) {
            return checkPathInner(G, p->val, end, marked);
        }
    }

    return 0;
}

/*true return 1,false return 0*/
int checkPath(struct AdjacencyGraph* G, int start, int end) {

    int* marked = (int*)malloc(sizeof(int) * G->vertices);
    for (int i = 0; i < G->vertices; ++i) {
        marked[i] = 0;
    }

    return checkPathInner(G, start, end, marked);
}
```