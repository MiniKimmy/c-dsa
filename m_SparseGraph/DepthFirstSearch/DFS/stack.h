#pragma once
#define PRINT_STRING(x) printf("%s\n",x)
 
typedef int Element; //Include�������ļ�ʱ��Ҫ�޸�Element������

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

/*��ʼ��Stack*/
Stack* InitStack()
{
    Stack* ret = (Stack*)malloc(sizeof(Stack));
    if (ret == NULL) {
        PRINT_STRING("Stack��ʼ����̬�����ڴ�ʧ��\n");
        exit(-1);
    }
    ret->Count = 0;
    ret->Top = NULL;
    ret->Bottom = NULL;
    return ret;
}

/*�ж�Stack�Ƿ�Ϊ��ջ*/
Boolean IsEmptyStack(Stack * S)
{
    if (S == NULL) {
        PRINT_STRING("StackΪNULL");
        exit(-1);
    }

    if (S->Bottom == NULL) return TRUE;
    else return FALSE;
}

/*��ջ*/
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

/*��ȡTopԪ�ص�value*/
Element* GetValue_Stack(Stack * S)
{
    if (IsEmptyStack(S)) return NULL;
    return &(S->Top->Data);
}

/*��ջ*/
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

/*������е�Ԫ�أ�Stack*����ɾ��*/
void ClearStack(Stack * S)
{
    if (IsEmptyStack(S)) return;
    while (S->Bottom) {
        Pop_Stack(S);
    }
    return;
}

/*ɾ��Stack�����ڴ棬����NULL*/
void DestroyStack(Stack** S)
{
    if (*S == NULL) {
        PRINT_STRING("StackΪNULL");
        return;
    }
    ClearStack(*S);
    *S = NULL;
    return;
}
