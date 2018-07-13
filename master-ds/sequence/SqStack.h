#include<stdlib.h>
#include<stdio.h>

#define SqStackInitSIZE 20

typedef struct {
    int* data;
    int top;
    int capacity;
}SqStack;

#pragma region SqStackFunctions
SqStack* initSqStack();
SqStack* createSqStack(int size);
int isEmptySqStack(SqStack* S);
int isFullSqStack(SqStack* S);
int push(SqStack* S, int value);
int pop(SqStack* S, int* get);
int* peek(SqStack* S);
int clearSqStack(SqStack* S);
int destroySqStack(SqStack** S);
#pragma endregion

SqStack* initSqStack()
{
    SqStack* stack = (SqStack*)malloc(sizeof(SqStack));
    stack->data = (int*)malloc(sizeof(int) * SqStackInitSIZE);
    stack->capacity = SqStackInitSIZE;
    stack->top = -1;
    return stack;
}


SqStack* createSqStack(int size)
{
    SqStack* stack = (SqStack*)malloc(sizeof(SqStack));
    stack->data = (int*)malloc(sizeof(int)* size);
    stack->capacity = size;
    stack->top = -1;
    return stack;
}

int isEmptySqStack(SqStack* S)
{
    if (S == NULL || S->top == -1) return 1;
    else return 0;
}

int isFullSqStack(SqStack* S)
{
    if (S == NULL) return 0;
    else if (S->top + 1 >= S->capacity) return 1;
    else return 0;
}

int push(SqStack* S, int value)
{
    if (isFullSqStack(S)) return 0;
    S->data[++S->top] = value;

    return 1;
}

int pop(SqStack* S, int* get)
{
    if(isEmptySqStack(S)) return 0;
    *get = S->data[S->top--];
    return 1;
}

int* peek(SqStack* S)
{
    if (isEmptySqStack(S)) return NULL;
    return &(S->data[S->top]);
}

int clearSqStack(SqStack* S)
{
    if (isEmptySqStack(S)) return 0;

    S->top = -1;
    return 1;
}

int destroySqStack(SqStack** S)
{
    if (!clearSqStack(*S)) return 0;

    free((*S)->data);
    (*S)->data = NULL;
    free(*S);
    *S = NULL;
    return 1;
}
