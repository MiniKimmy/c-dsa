## 41. 包含min函数的栈
[这里](https://www.acwing.com/problem/content/90/)
设计一个支持push，pop，top等操作并且可以在O(1)时间内检索出最小元素的堆栈。
* push(x)–将元素x插入栈中
* pop()–移除栈顶元素
* top()–得到栈顶元素
* getMin()–得到栈中最小元素

**Example  :**
```
MinStack minStack = new MinStack();
minStack.push(-1);
minStack.push(3);
minStack.push(-4);
minStack.getMin();   --> Returns -4.
minStack.pop();
minStack.top();      --> Returns 3.
minStack.getMin();   --> Returns -1.
```
## hints
```
    1.gitMin只是获取元素val，并没有把min的指针弹出
    2.Top只是获取之stack顶的val值，并没有把栈顶元素弹出
    3.每次pop的时候要判断是否把min弹出，若弹出则要O(n)一下找另外的min记录下来
    4.给的初始化方法里有maxSize,所以使用数组栈而不使用链栈。
```

## Solution
``` c
typedef struct {
    int minValIndex;
    int top;
    int* stack;
} MinStack;

/** initialize your data structure here. */
MinStack* minStackCreate(int maxSize) {
    MinStack* ret = (MinStack*)malloc(sizeof(MinStack));
    ret->top = -1;
    ret->stack = (int*)malloc(sizeof(int)*maxSize);
    ret->minValIndex = -1;
    return ret;
}

void minStackPush(MinStack* obj, int x) {
    if(obj == NULL) return;

    obj->stack[++(obj->top)] = x;
    if(obj->minValIndex == -1) obj->minValIndex = obj->top;
    else if(obj->stack[obj->minValIndex] > x) obj->minValIndex = obj->top;
    return;
}

void minStackPop(MinStack* obj) {
    if(obj == NULL) return;
    if(obj->top == obj->minValIndex){
        int min = obj->stack[0];
        int index = 0;
        for(int i = 1;i<obj->top;++i){
            if(min > obj->stack[i]){
                min = obj->stack[i];
                index = i;
            }
        }
        obj->minValIndex = index;
    }
    return (obj->top)--;
}

int minStackTop(MinStack* obj) {
    if(obj == NULL) return;
    return obj->stack[(obj->top)];
}

int minStackGetMin(MinStack* obj) {
    return obj->stack[obj->minValIndex];
}

void minStackFree(MinStack* obj) {
    free(obj->stack);
    free(obj);
    return;
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * struct MinStack* obj = minStackCreate(maxSize);
 * minStackPush(obj, x);
 * minStackPop(obj);
 * int param_3 = minStackTop(obj);
 * int param_4 = minStackGetMin(obj);
 * minStackFree(obj);
 */
```