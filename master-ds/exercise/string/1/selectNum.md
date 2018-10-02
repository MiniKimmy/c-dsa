## Select Number

Given a string, find the consecutive digit.

## CHINESE
输入一个字符串，内有数字和非数字字符,<br />
将其中连续的数字作为一个整体，依次存放到一数组a中,并输出这些数。<br />

**Example 1:**
```
Input: "ak123x456"
Output:["123","456"]
```
**Example 2:**
```
Input:"17960?302gef4563"
Output:["17960","302","4563"]
```

## hints
```
    easy..
```

## Analogous
|                Nav                    |                 Des                 |
|:-------------------------------------:|:-----------------------------------:|
|![isSubString](isSubString.md)         |查找第一个子串                       |
|![selectSubString](selectMaxDuplicateSubString.md) |挑选出最长重复字符的子串 |

## Solution
``` c
int isDigit(char c) {
    int temp = c - '0';
    if (temp >= 0 && temp <= 9) return 1;

    else return 0;
}

char** selectNum(char* str, int* returnSize) {
    if(str == NULL) {
        *returnSize = 0;
        return NULL;
    }

    char** ret = (char**)malloc(sizeof(char*) * MAXSIZE);
    int retSize = 0;

    char* buffer = (char*)malloc(sizeof(char*)*MAXSIZE);
    int bufferIndex = 0;

    int index = 0;
    while (str[index]) {
        if (isDigit(str[index]) == 1) {
            buffer[bufferIndex++] = str[index];

        }else if (bufferIndex != 0) {
            char* m_str = (char*)malloc(sizeof(char) * (bufferIndex + 1));
            m_str[bufferIndex] = '\0';

            for (int i = 0; i < bufferIndex; ++i) m_str[i] = buffer[i];
            ret[retSize++] = m_str;
            bufferIndex = 0;
        }

        index++;
    }

    if (bufferIndex != 0) {
        char* m_str = (char*)malloc(sizeof(char) * (bufferIndex + 1));
        m_str[bufferIndex] = '\0';
        for (int i = 0; i < bufferIndex; ++i) m_str[i] = buffer[i];
        ret[retSize++] = m_str;
        bufferIndex = 0;
    }

    free(buffer);
    *returnSize = retSize;
    return ret;
}
```