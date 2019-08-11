## String to Int16

Given a digital string, exchange it to a real data int16 with +,- digit.

## CHINESE
给定一串由0~9字符和的‘-’组成字符串,返回值为整型数值 。

**Example 1:**
```
Input: "123"
Output: 123
```
**Example 2:**
```
Input:"-123"
Output:-123
```

## hints
```
   easy.
```

## Analogous
|                Nav                    |                 Des                 |
|:-------------------------------------:|:-----------------------------------:|
|![isSubString](isSubString.md)         |查找第一个子串                       |
|![selectSubString](selectMaxDuplicateSubString.md) |挑选出最长重复字符的子串 |
|![selectNum](selectNum.md)             |挑选出每组连续数字字符               |

## Solution
``` c
#include<math.h>

int int16Parse(char* c) {
    if (c == NULL) return 0;
    int* m = (int*) malloc(sizeof(int) * 11);
    int top = -1;

    int len = c[0] == '-'? 1: 0;
    while (c[len]) {
        m[++top] = c[len] - '0';
        len++;
    }

    if (top + 1 == 10) {
        //printf("stack overflow");
        free(m);
        return len > top + 1 ? INT_MIN : INT_MAX;
    }

    int ret = 0;
    int realLength = top;
    for (int i = 0; i <= realLength; ++i) {
        int p = pow(10, i);
        ret += m[top--] * p;
    }

    free(m);
    return len > realLength+1? -ret:ret;
}
```