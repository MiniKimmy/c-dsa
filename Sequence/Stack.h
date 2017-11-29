#pragma once
#include<stdio.h>
#include<stdlib.h>
#define PRINT_STRING(x) printf("%s\n",x)

typedef enum Status
{ 
    FALSE, 
    TRUE,
}Status; //标志位

typedef int Element; //Include到其他文件时候要修改Element的类型

#pragma region Stack
typedef struct SNode {
    Element Data;
    struct SNode *Next;
}SNode;
typedef struct LinkStack {
    SNode *Top;
    SNode *Bottom;
    int Count;
}Stack;
#pragma endregion

#pragma region Functions
Stack* InitStack();
void CreateStack_ByInputArray(Stack * S, int *arr, int stacksize);
void CreateStack_ByInputKeyCode(Stack * S);
Status IsEmptyStack(Stack * S);
void Push_Stack(Stack * S, Element value);
Element* GetValue_Stack(Stack * S);
void Pop_Stack(Stack * S);
void ClearStack(Stack * S);
void DestroyStack(Stack** S);
void Traverse_Stack(Stack * S);
#pragma endregion

/*初始化Stack*/
Stack* InitStack()
{
    Stack* ret = (Stack*)malloc(sizeof(Stack));
    if (ret == NULL){
        PRINT_STRING("Stack初始化动态分配内存失败\n");
        exit(-1);
    }
    ret->Count = 0;
    ret->Top = NULL;
    ret->Bottom = NULL;
    return ret;
}

/*通过传入int数组的数据创建Stack*/
/*S：Stack*栈对象,arr：int数组，arrsize：数组长度 */
void CreateStack_ByInputArray(Stack * S, int *arr, int arrsize)
{
    if (S == NULL || arr == NULL) {
        PRINT_STRING("传入的参数为NULL");
        return;
    }

    if (arrsize < 0) {
        PRINT_STRING("赋值个数不能为负数");
        return;
    }

    for (int i = 0; i < arrsize; i++) {
        Push_Stack(S, arr[i]);
    }
    return;
}

/*通过手动赋值创建Stack*/
void CreateStack_ByInputKeyCode(Stack * S)
{
    if (S == NULL) {
        PRINT_STRING("Stack为NULL");
        return;
    }

    PRINT_STRING("需要堆栈的元素个数是 : ");
    int size;
    scanf_s("%d", &size);
    while (size < 0){
        printf("无法产生%d个元素,请输入非负值的size\n", size);
        scanf_s("%d", &size);
    }

    for (int i = 0; i < size; i++){
        printf("请输入第[%d]个元素的Value : ", i);
        Element arg;
        scanf_s("%d", &arg);
        Push_Stack(S, arg);
    }
    return;
}

/*判断Stack是否为空栈*/
Status IsEmptyStack(Stack * S)
{
    if (S == NULL) {
        PRINT_STRING("Stack为NULL");
        exit(-1);
    }

    if (S->Bottom == NULL) return TRUE;
    else return FALSE;
}

/*堆栈*/
void Push_Stack(Stack * S, Element value)
{
    SNode* p = (SNode*)malloc(sizeof(SNode));
    p->Data = value;
    p->Next = S->Top;
    if (S->Bottom == NULL) {
        S->Bottom = p;
    }
    S->Top = p;
    S->Count++;
    return;
}

/*获取Top元素的value*/
Element* GetValue_Stack(Stack * S)
{
    if (IsEmptyStack(S)) return NULL;
    return &(S->Top->Data);
}

//出栈
void Pop_Stack(Stack * S)
{
    if (IsEmptyStack(S)) return;
    
    SNode* p = S->Top;
    if (p == S->Bottom) {
        S->Bottom = NULL;
    }
    S->Top = S->Top->Next;
    free(p);
    p->Next = NULL;
    S->Count--;
    return;
}

/*清除所有的元素，Stack*对象不删除*/
void ClearStack(Stack * S)
{
    if (IsEmptyStack(S)) return;
    while (S->Bottom) {
        Pop_Stack(S);
    }
    return;
}

/*删除Stack所有内存，返回NULL*/
void DestroyStack(Stack** S)
{
    if (*S == NULL) {
        PRINT_STRING("Stack为NULL");
        return;
    }
    ClearStack(*S);
    *S = NULL;
    return;
}

/*遍历Stack*/
void Traverse_Stack(Stack * S)
{
    if (IsEmptyStack(S)) return;

    SNode* p = S->Top;
    for (int i = 0; i < S->Count; i++)
    {
        printf("%d\n", p->Data);
        p = p->Next;
    }
    return;
}
