## Select Max Duplicate SubString

Given a string with '0-9'、'a-z','A-Z',find the max duplicate substring.

## CHINESE
如果字符串的一个子串（其长度大于1）的各个字符均相同，则称之为等值子串。<br />
输入字符串S,若串S中不存在等值子串,则返回NULL，否则返回第一个长度最大的等值子串。<br />

**Example 1:**
```
Input: "abc123abc123"
Output: NULL
Explaintion: 要求重复子串长度>1
```
**Example 2:**
```
Input:"abceebccadddddaaadd"
Output:"ddddd"
```

## Analogous
|                Nav                    |                 Des                 |
|:-------------------------------------:|:-----------------------------------:|
|![selectNum](selectNum.md)             |挑选出每组连续数字字符               |
|![isSubString](isSubString.md)         |查找第一个子串                       |
|![int16Parse](int16Parse.md)           |将数字字符串转化为整数               |

## Solution
``` c
char* selectMaxDuplicateSubString(char* str) {
    if (str == NULL) return NULL;

    int max = 0;
    int buffer = 1;
    int flagIndex = 0;

    int i = 1;
    char c = str[0];
    while (str[i]) {
        if (c == str[i]) {
            buffer++;
        }else {
            c = str[i];
            if (buffer > max) {
                max = buffer;
                flagIndex = i;
            }
            buffer = 1;
        }

        i++;
    }

    if (buffer > max) max = buffer;
    if (max > 1) {
        char* ret = (char*)malloc(sizeof(char) * (max + 1));
        ret[max] = '\0';

        for (int i = 0; i < max; ++i) {
            ret[i] = c;
        }
        return ret;
    }

    return NULL;
}
```
