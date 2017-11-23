#pragma once
#define PRINT_STRING(x) printf("%s\n",x)
 
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
Boolean IsEmptyStack(Stack * S);
void Push_Stack(Stack * S, Element value);
Element* GetValue_Stack(Stack * S);
void Pop_Stack(Stack * S);
void ClearStack(Stack * S);
void DestroyStack(Stack** S);
#pragma endregion

/*初始化Stack*/
Stack* InitStack()
{
    Stack* ret = (Stack*)malloc(sizeof(Stack));
    if (ret == NULL) {
        PRINT_STRING("Stack初始化动态分配内存失败\n");
        exit(-1);
    }
    ret->Count = 0;
    ret->Top = NULL;
    ret->Bottom = NULL;
    return ret;
}

/*判断Stack是否为空栈*/
Boolean IsEmptyStack(Stack * S)
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

/*出栈*/
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
