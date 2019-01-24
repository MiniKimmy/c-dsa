## 20. 用两个栈实现队列
[这里](https://www.acwing.com/problem/content/36/)
请用栈实现一个队列，支持如下四种操作：
* push(x) – 将元素x插到队尾；
* pop() – 将队首的元素弹出，并返回该元素；
* peek() – 返回队首元素；
* empty() – 返回队列是否为空；

## hints
```
    1.按栈的方式push。单纯用1个栈即可
    2.pop的时候使用2个栈
        * stack1转移到stack2
        * 当stack1剩下1个的时候不转移，作为返回值pop
        * 在返回之前，把stack2重新push回去stack1
```
## Solution
``` c
typedef struct {
    int* stack1;
    int top1;
    int* stack2;
} MyQueue;

/** Initialize your data structure here. */
MyQueue* myQueueCreate(int maxSize) {
    MyQueue* ret = (MyQueue*)malloc(sizeof(MyQueue));
    ret->stack1 = (int*)malloc(sizeof(int) * 1000);
    ret->stack2 = (int*)malloc(sizeof(int) * 1000);
    ret->top1 = -1;
    return ret;
}

/** Push element x to the back of queue. */
void myQueuePush(MyQueue* obj, int x) {
    ++(obj->top1);
    obj->stack1[obj->top1] = x;
    return;
}

/** Removes the element from in front of queue and returns that element. */
int myQueuePop(MyQueue* obj) {
    int top = -1;
    while(obj->top1>0){
        obj->stack2[++top] = obj->stack1[obj->top1];
        --(obj->top1);
    }

    int ret = obj->stack1[obj->top1];
    --(obj->top1);

    while(top>=0){
        ++(obj->top1);
        obj->stack1[obj->top1] = obj->stack2[top--];
    }

    return ret;
}

/** Get the front element. */
int myQueuePeek(MyQueue* obj) {
    return obj->stack1[0];
}

/** Returns whether the queue is empty. */
bool myQueueEmpty(MyQueue* obj) {
    if(obj->top1 == -1) return true;
    else return false;
}

void myQueueFree(MyQueue* obj) {
    free(obj->stack1);
    free(obj->stack2);
    free(obj);
    return;
}

/**
 * Your MyQueue struct will be instantiated and called as such:
 * struct MyQueue* obj = myQueueCreate(maxSize);
 * myQueuePush(obj, x);
 * int param_2 = myQueuePop(obj);
 * int param_3 = myQueuePeek(obj);
 * bool param_4 = myQueueEmpty(obj);
 * myQueueFree(obj);
 */
```