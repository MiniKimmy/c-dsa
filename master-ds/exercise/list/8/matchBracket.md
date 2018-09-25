## Match Bracket

Given a char[] with "()[]" elements, and check the char[] whether matches the '()','[]'.

## CHINESE
设表达式以字符形式已存入数组中，‘#’为表达式的结束符，试写出判断表达式中括号'()'和'[]'是否配对.


**Example 1:**
```
Input : ['(','(',')',')']
OutPut: true
```

**Example 2:**
```
Input : ['(',']']
OutPut: false
```

## hints
```
    stack
    1.( [ --> push
    2.) ] --> pop and judge match.
    3. check stack empty or not.
```

## Solution
``` c
int matchBracket(char* str) {
    if (str == NULL) return 1;

    char* stack = (char*)malloc(sizeof(char) * 1000);
    int top = -1;

    char* ch = str;
    while (*ch != '#') {
        char c = *ch;

        if (c == '(' || c == '[') {
            stack[++top] = c;
        }else if (c == ')') {
            if (top == -1 || stack[top] != '(') return 0;

            top--;
        }
        else if (c == ']') {
            if (top == -1 || stack[top] != '[') return 0;
            top--;
        }
        ch++;
    }

    free(stack);
    return top == -1 ? 1 : 0;
}
```