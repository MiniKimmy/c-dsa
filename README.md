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
| 14   | BST         | 二叉搜索树     | TODO                                                                                                  |
| 15   | AVL         | 平衡树         | TODO                                                                                                  |
| 16   | B+ Tree     | B+ 树          | TODO                                                                                                  |
| 17   | segmentTree | 线段树         | TODO                                                                                                  |



### 算法

| 序号 | 算法名       | 说明                          | C ++ 代码                                                                                          |
|------|--------------|-------------------------------|----------------------------------------------------------------------------------------------------|
| 0    | kmp          | KMP-O(n)                      | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/kmp/kmp.cpp)                  |
| 1    | bubbleSort   | 冒泡排序O(n²)                 | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/sort/bubbleSort.cpp)          |
| 2    | selectSort   | 选择排序O(n²)                 | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/sort/selectSort.cpp)          |
| 3    | insertSort   | 插入排序O(n²)                 | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/sort/insertSort.cpp)          |
| 4    | shellSort    | 希尔排序                      | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/sort/shellSort.cpp)           |
| 5    | mergeSort    | 归并排序O(nlogn)              | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/sort/mergeSort.cpp)           |
| 6    | quickSort    | 快速排序O(nlogn)              | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/sort/quickSort.cpp)           |
| 7    | heapSort     | 堆排序O(nlogn)                | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/sort/heapSort.cpp)            |
| 8    | unionfind    | 并查集-路径压缩O(1)           | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/unionfind/unionfind.cpp)      |
| 9    | unionfind    | 并查集-size优化O(1)           | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/unionfind/unionfind_size.cpp) |
| 10    | dijkstra     | 最短路-正权边朴素版O(n²)      | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/graph/dijkstra.cpp)           |
| 11    | dijkstra     | 最短路-正权边堆优化版O(mlogn) | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/graph/dijkstra_heap.cpp)      |
| 12    | bellman-ford | 最短路-负权边最短路O(nm)      | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/graph/bellman_ford.cpp)      |
| 13    | spfa         | 最短路-负权边最短路O(m)/O(nm) | [查看代码](https://github.com/MiniKimmy/c-dsa/blob/master/algorithms/graph/spfa.cpp)                                                                                               |
| 14    | floyd        | 最短路-多源汇最短路O(n³)      | TODO                                                                                               |
| 15    | prim         | 最小生成树-O(n²)              | TODO                                                                                               |
| 16    | kruskal      | 最小生成树                    | TODO                                                                                               |