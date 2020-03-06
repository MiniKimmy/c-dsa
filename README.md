### 用 C ++ 语言实现常见数据结构与算法


### 数据结构

| 序号 | 结构名      | 说明           | C ++ 代码                                                                                             |
|------|-------------|----------------|-------------------------------------------------------------------------------------------------------|
| 0    | singlelist  | 单链表         | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/list/singlelist/staticlist.cpp)  |
| 1    | doublelist  | 双链表         | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/list/doublelist/doublelist.cpp)  |
| 2    | sqstack     | 栈             | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/stack/sqstack.cpp)               |
| 3    | sqqueue     | 队列           | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/queue/sqqueue.cpp)               |
| 4    | dullstack   | 单调栈         | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/stack/dullstack.cpp)             |
| 5    | dullqueue   | 单调队列       | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/queue/dullqueue.cpp)             |
| 6    | loopqueue   | 循环队列       | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/queue/loopqueue.cpp)             |
| 7    | trie        | 前缀树         | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/tree/trie/trie.cpp)              |
| 8    | heap        | 二叉堆         | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/heap/heap.cpp)                   |
| 9    | hashtable   | 拉链法         | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/hashtable/hashtable_chain.cpp)   |
| 10   | hashtable   | 开发寻址法     | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/hashtable/hashtable_address.cpp) |
| 11   | hashtable   | 字符串前缀哈希 | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/hashtable/hashtable_prefix.cpp)  |
| 12   | densegraph  | 邻接矩阵       | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/graph/densegraph.cpp)            |
| 13   | sparsegraph | 邻接表         | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/graph/sparsegraph.cpp)           |
| *    | BST         | 二叉搜索树     | TODO                                                                                                  |
| *    | AVL         | 平衡树         | TODO                                                                                                  |
| *    | B+ Tree     | B+ 树          | TODO                                                                                                  |
| *    | segmentTree | 线段树         | TODO                                                                                                  |



### 算法

| 序号 | 算法名       | 说明                           | C ++ 代码                                                                                          |
|------|--------------|--------------------------------|----------------------------------------------------------------------------------------------------|
| 0    | kmp          | kmp算法O(n)                    | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/kmp/kmp.cpp)                  |
| 1    | bubbleSort   | 冒泡排序O(n²)                  | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/sort/bubbleSort.cpp)          |
| 2    | selectSort   | 选择排序O(n²)                  | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/sort/selectSort.cpp)          |
| 3    | insertSort   | 插入排序O(n²)                  | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/sort/insertSort.cpp)          |
| 4    | shellSort    | 希尔排序                       | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/sort/shellSort.cpp)           |
| 5    | mergeSort    | 归并排序O(nlogn)               | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/sort/mergeSort.cpp)           |
| 6    | quickSort    | 快速排序O(nlogn)               | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/sort/quickSort.cpp)           |
| 7    | heapSort     | 堆排序O(nlogn)                 | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/sort/heapSort.cpp)            |
| 8    | topoSort     | 拓扑排序O(n + m)               | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/graph/topoSort.cpp)            |
| 9    | unionfind    | 并查集-路径压缩O(1)            | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/unionfind/unionfind.cpp)      |
| 10   | unionfind    | 并查集-size优化O(1)            | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/unionfind/unionfind_size.cpp) |
| 11   | dijkstra     | 最短路-正权边朴素版O(n²)       | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/graph/dijkstra.cpp)           |
| 12   | dijkstra     | 最短路-正权边堆优化版O(mlogn)  | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/graph/dijkstra_heap.cpp)      |
| 13   | bellman-ford | 最短路-负权边最短路O(nm)       | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/graph/bellman_ford.cpp)       |
| 14   | spfa         | 最短路-负权边最短路O(m)/O(nm)  | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/graph/spfa.cpp)               |
| 15   | floyd        | 最短路-多源汇最短路O(n³)       | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/graph/floyd.cpp)              |
| 16   | prim         | 最小生成树-prim算法O(n²)       | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/graph/prim.cpp)               |
| 17   | kruskal      | 最小生成树-kruskal算法O(mlogm) | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/graph/kruskal.cpp)            |