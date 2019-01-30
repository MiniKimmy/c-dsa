## 54. 数据流中的中位数
[这里](https://www.acwing.com/problem/content/88/)
如何得到一个数据流中的中位数？
如果从数据流中读出奇数个数值，那么中位数就是所有数值排序之后位于中间的数值。
如果从数据流中读出偶数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。

**Example :**
```
Input:1,2,3,4
Output:1,1.5,2,2.5
Explanation:1 2 3 4是一个个传进来的，1 1.5 2 2.5是每次的中位数
即insert(int num) 和 “getMedian()” 交替调用
```

## hints
```
1.写一个二叉堆
    (1).实现上浮、下浮方法；
    (2).构造heap数据类型，获取top堆顶，添加、删除
    (3).动态扩充数组是预防数据量太大.

2.默认先把元素存在大顶堆max_heap
    (1)逆序情况:即max_heap.top > min_heap.top , 交换两个堆的堆顶元素
    (2)大小堆的元素数量情况:max_heap数量是比min_heap至多多1个元素。数量过多时候，max_heap把堆顶元素转移给min_heap
3.中位数处理
    (1).奇数个元素:直接获取max_heap.top
    (2).偶数个元素:(max_heap.top + min_heap.top) / 2.0
```

## Solution
``` c
//-----------------------------------内部调用------------------------------------------
typedef enum PriorityHeapType {
    MAXHEAP, // 大根堆
    MINHEAP  // 小根堆
}PriorityHeapType;

typedef struct PriorityHeap {
    int* data;
    int capicity;
    int count;
    PriorityHeapType type;  // 堆类型
}PriorityHeap;

/// 动态扩充数组
void allocateHeap(PriorityHeap* heap){
    heap->capicity *= 2;
    int* copy = (int*)malloc(sizeof(int) * heap->capicity);
    for (int i = 1; i <= heap->count; ++i) {
        copy[i] = heap->data[i];
    }

    int* temp = heap->data;
    heap->data = copy;

    free(temp);
    return;
}

/// 是否需要动态扩充
int isAllocate(PriorityHeap* heap) {
    if (!heap) return 0;
    return heap->count + 5 == heap->capicity ? 1 : 0;
}

/// 堆内元素判断大小
int compareHeap(PriorityHeap* heap, int i, int j)
{
    if (!heap) return 0;
    if (heap->type == MINHEAP) {
        return heap->data[i] < heap->data[j] ? 1 : 0;
    }else {
        return heap->data[i] > heap->data[j] ? 1 : 0;
    }
}

/// 上浮
void swim(PriorityHeap* heap)
{
    if (!heap) return;

    int k = heap->count;
    while (k > 1 && compareHeap(heap,k,k/2)) {
        int temp = heap->data[k];
        heap->data[k] = heap->data[k/2];
        heap->data[k / 2] = temp;
        k = k / 2;
    }
}

/// 下沉
void sink(PriorityHeap* heap)
{
    if (!heap) return;

    int k = 1;
    while (2 * k <= heap->count) {
        int index = 2 * k;
        if (index<heap->count && !compareHeap(heap, index, index + 1)){
            index++;
        }

        if (!compareHeap(heap, k, index)) {
            int temp = heap->data[k];
            heap->data[k] = heap->data[index];
            heap->data[index] = temp;
            k = index;
        }else {
            break;
        }
    }
}

//---------------------外部调用----------------------------------------------------
/// 获取堆顶元素
void getTop(PriorityHeap* heap, int* out_top)
{
    if (!heap || !heap->count) return;
    *out_top = heap->data[1];
}

/// 添加新元素
void push_priorityHeap(PriorityHeap* heap, int val)
{
    if (!heap) return;

    if (isAllocate(heap)) {
        allocateHeap(heap);
    }

    heap->data[++(heap->count)] = val;
    swim(heap);
    return;
}

/// 删除堆顶元素
void pop_priorityHeap(PriorityHeap* heap)
{
    if (!heap) return;

    heap->data[1] = heap->data[heap->count];
    heap->count--;
    sink(heap);
    return;
}

/// 实例化heap
PriorityHeap* createPriorityHeap(int size, PriorityHeapType type){
    if (size <= 0) return NULL;

    PriorityHeap* priority_heap = (PriorityHeap*)malloc(sizeof(PriorityHeap));
    priority_heap->type = type;
    priority_heap->capicity = size;
    priority_heap->count = 0;
    priority_heap->data = (int*)malloc(sizeof(int) * (size + 1));
    return priority_heap;
}



//--------------------题目--------------------------------------

// 由于不能直接在在方法体外直接实例化heap。
// 经过调试发现，后台会首先调用“insert再getMedian...不断交替调用”
// 所以把实例化heap写在“insert”开头.

PriorityHeap* min_heap = NULL;
PriorityHeap* max_heap = NULL;

void insert(int num){
    // 实例化heap
    if(min_heap == NULL || max_heap == NULL){
        min_heap = createPriorityHeap(100, MINHEAP);
        max_heap = createPriorityHeap(100, MAXHEAP);
    }

    // 默认都塞进大根堆
    push_priorityHeap(max_heap,num);

    int min_top = 0;
    int max_top = 0;
    getTop(min_heap,&min_top);
    getTop(max_heap,&max_top);

    // 两个堆逆序，交换元素
    if(min_heap->count && max_top > min_top){
        pop_priorityHeap(min_heap);
        pop_priorityHeap(max_heap);
        push_priorityHeap(max_heap,min_top);
        push_priorityHeap(min_heap,max_top);
    }

    // 如果大根堆数量比小根堆多.大根堆给小根堆一个元素
    if(max_heap->count > min_heap->count + 1 ){
        int res = 0;
        getTop(max_heap,&res);
        pop_priorityHeap(max_heap);
        push_priorityHeap(min_heap,res);
    }

    return;
}

double getMedian(){
    double ret = 0;

    // 奇数个的时候，在大根堆堆顶；偶数个的时候 中位数=大根堆与小根堆堆顶元素的平均数.
    if(max_heap->count + min_heap->count & 1){
        int res = 0;
        getTop(max_heap,&res);
        ret = (double)res;
    }else{
        int res1 = 0;
        int res2 = 0;
        getTop(min_heap,&res1);
        getTop(max_heap,&res2);
        ret = (res1+res2) / 2.0;
    }

    return ret;
}
```

## hints2
```
    1.每次接收到就排序依次
    2.根据数组元素个数来获取中位数
```
## Solution2
``` c++
class Solution
{

    public: vector<double>res;
    void insert(int num){
        res.push_back(num);
        sort(res.begin(),res.end());
    }

    double getMedian()
    {
        int n = res.size();
        if (n & 1)  return res[n/2];
        else return (res[n/2]+res[n/2-1])/2;
    }
};
```