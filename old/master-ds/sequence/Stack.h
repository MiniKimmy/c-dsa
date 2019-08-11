#include<stdlib.h>
#include<stdio.h>

typedef struct SNode {
    int data;
    struct SNode* next;
}SNode;

typedef struct {
    SNode* top;
    SNode* bottom;
    int count;
}Stack;


#pragma region StackFunctions
Stack* initStack();
int push(Stack* S, int value);
int pop(Stack* S,int* topValue);
int clearStack(Stack* S);
int destroyStack(Stack** S);
int isEmptyStack(Stack* S);
#pragma endregion

Stack* initStack()
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    SNode* top = (SNode*)malloc(sizeof(SNode));
    top->next = NULL;
    stack->count = 0;
    stack->top = top;
    stack->bottom = top;
    return stack;
}

int isEmptyStack(Stack* S)
{
    if (S == NULL) return -1;
    else if (S->count == 0) return 1;
    else return 0;
}

int push(Stack* S, int value)
{
    if (S == NULL) return 0;

    SNode* p = (SNode*)malloc(sizeof(SNode));
    p->data = value;
    p->next = S->top;
    S->top = p;
    S->count++;
    return 1;
}

int pop(Stack* S, int* topValue)
{
    if (S == NULL || S->count == 0) return 0;

    *topValue = S->top->data;
    SNode* p = S->top;
    S->top = S->top->next;
    free(p);
    S->count--;
    return 1;
}

int clearStack(Stack* S)
{
    if (S == NULL || S->count == 0) return 0;

    SNode* p = S->top;
    while (S->top != S->bottom) {
        S->top = S->top->next;
        free(p);
        p = S->top;
    }
    S->count = 0;
    return 1;
}

int destroyStack(Stack** S)
{
    if (S == NULL) return 0;

    clearStack(*S);
    free((*S)->top);
    (*S)->top = NULL;
    free(*S);
    *S = NULL;
    return 1;
}
