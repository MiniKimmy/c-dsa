#include<stdio.h>
#include<stdlib.h>
#define PRINT_STRING(x) printf("%s\n",x)


typedef int TElement;  //import到其他文件时候需要修改该类型

/*Bool枚举*/
typedef enum Status {
    FALSE,
    TRUE,
}Status;

/*结点Node数据类型*/
typedef struct Node {
    TElement data;
    struct Node* next;
}Node;

typedef struct Stack {
    Node* top;
    Node* bottom;
    int count;
}Stack;

#pragma region Functions
Stack* InitStack();
Status IsEmpty_Stack(Stack * S);
TElement* GetValue_Stack(Stack * S);
void Push_Stack(Stack * S, TElement value);
void Pop_Stack(Stack * S);
void Clear_Stack(Stack * S);
void Destroy_Stack(Stack** S);
#pragma endregion

/*初始化Stack*/
Stack* InitStack()
{
    Stack* ret = (Stack*)malloc(sizeof(Stack));
    if (ret == NULL) {
        PRINT_STRING("Stack初始化动态分配内存失败");
        exit(-1);
    }

    ret->count = 0;
    ret->top = NULL;
    ret->bottom = NULL;
    return ret;
}
/*判断Stack是否为空*/
Status IsEmpty_Stack(Stack* S)
{
    if (S == NULL) {
        printf("Stack为NULL");
        return TRUE;
    }

    if (S->bottom == NULL) return TRUE;
    else return FALSE;
}

/*堆栈*/
void Push_Stack(Stack* S, TElement value)
{
    if (S == NULL) return;
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        PRINT_STRING("堆栈node初始化动态分配内存失败");
        exit(-1);
    }

    node->data = value;
    //添加第[0]个元素
    if (S->count == 0){
        S->bottom = node;
    }
    node->next = S->top;
    S->top = node;
    S->count++;
    return;
}

/*出栈*/
void Pop_Stack(Stack* S)
{
    if (IsEmpty_Stack(S)) return;
    
    //删除最后第[0]个元素时
    if (S->top == S->bottom) {
        S->bottom = NULL;
    }

    Node* node = S->top;
    S->top = S->top->next;
    free(node);
    node = NULL;
    S->count--;
    return;
}

/*返回栈顶的元素的指针*/
TElement* GetValue_Stack(Stack* S)
{
    if (IsEmpty_Stack(S)) return NULL;
    return &(S->top->data);
}

/*全部出栈*/
void Clear_Stack(Stack* S)
{
    while (S->bottom != NULL)
    {
        Pop_Stack(S);
    }
    return;
}

/*销毁Stack*/
void Destroy_Stack(Stack** S)
{
    if (*S == NULL) return;
    Clear_Stack(*S);
    free(*S);
    *S = NULL;
    return;
}
