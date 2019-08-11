#include<stdio.h>
#include<stdlib.h>
#define PRINT_STRING(x) printf("%s\n",x)


typedef int TElement;  //import�������ļ�ʱ����Ҫ�޸ĸ�����

/*Boolö��*/
typedef enum Status {
    FALSE,
    TRUE,
}Status;

/*���Node��������*/
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

/*��ʼ��Stack*/
Stack* InitStack()
{
    Stack* ret = (Stack*)malloc(sizeof(Stack));
    if (ret == NULL) {
        PRINT_STRING("Stack��ʼ����̬�����ڴ�ʧ��");
        exit(-1);
    }

    ret->count = 0;
    ret->top = NULL;
    ret->bottom = NULL;
    return ret;
}
/*�ж�Stack�Ƿ�Ϊ��*/
Status IsEmpty_Stack(Stack* S)
{
    if (S == NULL) {
        printf("StackΪNULL");
        return TRUE;
    }

    if (S->bottom == NULL) return TRUE;
    else return FALSE;
}

/*��ջ*/
void Push_Stack(Stack* S, TElement value)
{
    if (S == NULL) return;
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        PRINT_STRING("��ջnode��ʼ����̬�����ڴ�ʧ��");
        exit(-1);
    }

    node->data = value;
    //��ӵ�[0]��Ԫ��
    if (S->count == 0){
        S->bottom = node;
    }
    node->next = S->top;
    S->top = node;
    S->count++;
    return;
}

/*��ջ*/
void Pop_Stack(Stack* S)
{
    if (IsEmpty_Stack(S)) return;
    
    //ɾ������[0]��Ԫ��ʱ
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

/*����ջ����Ԫ�ص�ָ��*/
TElement* GetValue_Stack(Stack* S)
{
    if (IsEmpty_Stack(S)) return NULL;
    return &(S->top->data);
}

/*ȫ����ջ*/
void Clear_Stack(Stack* S)
{
    while (S->bottom != NULL)
    {
        Pop_Stack(S);
    }
    return;
}

/*����Stack*/
void Destroy_Stack(Stack** S)
{
    if (*S == NULL) return;
    Clear_Stack(*S);
    free(*S);
    *S = NULL;
    return;
}
