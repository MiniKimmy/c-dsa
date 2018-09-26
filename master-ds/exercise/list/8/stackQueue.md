## Simulation Queue as Stack

Use stack S1 S2 , desigin a queue.

## CHINESE
请利用两个栈S1和S2来模拟一个队列。已知栈的三个运算定义如下：<br />
PUSH(ST,x):元素x入ST栈； <br />
POP(ST,x)：ST栈顶元素出栈，赋给变量x； <br />
Sempty(ST)：判ST栈是否为空。 <br />
那么如何利用栈的运算来实现该队列的三个运算： <br />
enqueue:插入一个元素入队列；  <br />
dequeue:删除一个元素出队列； <br />
queue_empty：判队列为空。 <br />

## Solution
``` c
typedef struct sqStack {
    int* st;
    int top;
};

struct sqStack* initSqStack(int size) {
    struct sqStack* ret = (struct sqStack*)malloc(sizeof(struct sqStack));
    ret->st = (int*)malloc(sizeof(int) * size);
    ret->top = -1;
    return ret;
}

void PUSH(struct sqStack* S, int val) {
    if (S == NULL) return;
    S->st[++S->top] = val;
}

void POP(struct sqStack* S, int* returnVal) {
    if (EMPTY(S)) {
        returnVal = NULL;
        return;
    }

    *returnVal = S->st[S->top--];
}

int EMPTY(struct sqStack* S) {
    if (S->top == -1) return 1;
    else return 0;
}

void enqueue(struct sqStack* S, int val) {
    PUSH(S, val);
}

void dequeue(struct sqStack* S, int* returnVal) {
    if (queue_empty(S) == 1) {
        *returnVal = NULL;
        return;
    }

    int temp;
    struct sqStack* st = initSqStack(S->top);
    while (S->top != -1) {
        POP(S, &temp);
        PUSH(st, temp);
    }

    *returnVal = temp;
    POP(st, &temp);

    while (st->top != -1) {
        POP(st, &temp);
        PUSH(S, temp);
    }

    free(st);
    return;
}

int queue_empty(struct sqStack* S) {
    return EMPTY(S);
}

```