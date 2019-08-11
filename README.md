### 用 c/cpp 语言实现常见数据结构与算法



## 数据结构

### 线性表

| 结构名     | 说明     | 代码                                                         |
| ---------- | -------- | ------------------------------------------------------------ |
| singlelist | 单向链表 | TODO |
| sqlist     | 顺序表   | TODO|
| doublelist | 双向链表 | TODO                                                         |
| looplist   | 循环链表 | TODO                                                         |



### 栈和队列

| 结构名        | 说明  | 代码                                                         |
| ------------- | ---------------------------- | ------------------------------------------------------------ |
| linkedstack   | 基于singlelist实现的链式栈   | TODO |
| slicestack    | 基于slice实现的链式栈        | TODO |
| sqstack       | 基于sqlist实现的链式栈       | TODO |
| linkedqueue   | 基于linkedlist实现的链式队列 | TODO |
| sqlistqueue   | 基于sqlist实现的链式队列     | TODO |
| priorityqueue | 优先队列                     | TODO |



### 树结构

| 结构名      | 说明                    | 代码                                                         |
| ----------- | ----------------------- | ------------------------------------------------------------ |
| BST         | 二叉搜索树              | TODO |
| AVL         | 二叉搜索平衡树 - AVL树  | TODO |
| RBTree      | 二叉搜索平衡树 - 红黑树 | TODO                                                         |
| Trie        | 前缀树                  | TODO                                                         |
| B+Tree      | B+ 树                   | TODO                                                         |
| kd 树       | kd 树                   | TODO                                                         |
| SegmentTree | 线段树                  | TODO                                                         |



### 堆结构

| 结构名    | 说明                 | 代码                                                         |
| --------- | -------------------- | ------------------------------------------------------------ |
| maxheap   | 基于数组实现的最大堆 | TODO |
| minheap   | 基于数组实现的最小堆 | TODO |
| indexheap | 索引堆               | TODO |
| leftheap  | 左偏堆               | TODO |
| fiboheap  | 斐波那契堆           | TODO |



### 集合

| 结构名    | 说明                    | 代码                                                         |
| --------- | ----------------------- | ------------------------------------------------------------ |
| mapset    | 基于 map 实现的集合     | TODO |
| hashtable | 哈希表                  | TODO                                                         |
| hashset   | 基于hashtable实现的集合 | TODO                                                         |



### 图结构

| 结构名                 | 说明                  | 代码                                                         |
| ---------------------- | --------------------- | ------------------------------------------------------------ |
| unionfind - quickfind  | 并查集 - 快速查找版本 | TODO |
| unionfind - quickunion | 并查集 - 快速联合版本 | TODO |
| sparsegraph            | 稀疏图 - 邻接表       | TODO |
| densegraph             | 稠密图 - 邻接矩阵     | TODO |



## 算法

### 排序算法

| 算法名        | 说明                       | 代码                                                         |
| ------------- | -------------------------- | ------------------------------------------------------------ |
| BubbleSort    | 冒泡排序；O(n²)；稳定      | [查看代码](https://github.com/gothicrush/go-dsa/tree/master/algorithms/sort) |
| SelectionSort | 选择排序；O(n²)；不稳定    | TODO |
| InsertionSort | 插入排序；O(n²)；稳定      | TODO |
| ShellSort     | 希尔排序；稳定             | TODO |
| MergeSort     | 归并排序；O(nlogn)；稳定   | TODO |
| QuickSort     | 快速排序；O(nlogn)；不稳定 | TODO |
| CountSort     | 计数排序                   | TODO                                                         |
| RadixSort     | 基数排序                   | TODO                                                         |



### 图算法

| 算法名       | 说明                              | 代码                                                         |
| ------------ | --------------------------------- | ------------------------------------------------------------ |
| components   | 联通分量算法                      | TODO |
| shorestpath  | 无权图最短路径算法                | TODO |
| prim         | 最小生成树 - prim算法             | TODO       |
| krusk        | 最小生成树 - krusk算法            | TODO               |
| dijkstra     | 有权图最短路径 - dijkstra算法     | TODO           |
| bellman-ford | 有权图最短路径 - bellman-ford算法 | TODO                |

