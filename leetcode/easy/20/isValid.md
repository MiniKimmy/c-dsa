## 20. Valid Parentheses

Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:
Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.

Note that an empty string is also considered valid.

**Example 1:**
```
Input: "()"
Output: true
```
**Example 2:**
```
Input: "()[]{}"
Output: true
```
**Example 3:**
```
Input: "(]"
Output: false
```
**Example 4:**
```
Input: "([)]"
Output: false
```
**Example 5:**
```
Input: "{[]}"
Output: true
```

## hints
```
    Stack-Probleam:
       push all the char'(' '{' '[' in Stack
       when got ')','}',']' ,check the top value whether is the corresponding char'(' '{' '['
       finally, check the stack is empty or not.
```

## Solution

``` c

typedef struct node{
    char val;
    struct node* next;
}Node;

typedef struct stack{
    Node* top;
    Node* buttom;
}Stack;

Stack* initStack(){
    Stack* ret = (Stack*)malloc(sizeof(Stack));
    Node* node = (Node*)malloc(sizeof(Node));
    node->next = NULL;
    node->val = 'a';   //rubbish value
    ret->top = node;
    ret->buttom = node;

    return ret;
}

int isEmpty(Stack* S){
    if(S == NULL || S->top==S->buttom) return 1;
    else return 0;
}

void push(Stack* S, char val){
    Node* node = (Node*)malloc(sizeof(Node));
    node->val = val;

    node->next = S->top;
    S->top = node;
    return;
}

void pop(Stack* S){
    if(isEmpty(S)) return;
    else{
        Node* p = S->top;
        S->top = S->top->next;
        free(p);
        p = NULL;
    }
}

char* peek(Stack* S){
    if(isEmpty(S)) return NULL;
    else{
        return &(S->top->val);
    }
}

void dispose(Stack* S){
    while(!isEmpty(S)){
        pop(S);
    }
    free(S->top);
    S->top = NULL;
    free(S);
    S=NULL;
    return;
}

//---------------------------------
bool isValid(char* s) {
    if(s == NULL) return true;
    if(*s == '}' || *s == ')' || *s == ']') return false;

    Stack* S = initStack();
    while(*s){
        char c = *s;
        char* top = peek(S);
        if(top == NULL || (c == '(') || (c =='{' ) || (c=='[')) push(S,c);
        else{
            switch(c){
                case ')':
                    if( (*top) =='(' ) pop(S);
                    else return false;
                    break;
                case '}':
                    if( (*top) =='{') pop(S);
                    else return false;
                    break;
                case ']':
                    if( (*top) =='[') pop(S);
                    else return false;
                    break;
                default: return false;
            }

        }

        s++;
    }

    bool ret = isEmpty(S) == 1?true:false;

    dispose(S);
    return ret;
}

```
