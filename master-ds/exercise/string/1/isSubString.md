## Is SubString

Given two String s,t, check t is subString of s. <br />
if yes, return the first index of s, else return 0. <br />

## CHINESE
设s、t为两个字符串，分别放在两个一维数组中，m、n分别为其长度，判断t是否为s的子串。如果是，输出子串所在位置(子串t的第一个字符),否则输出0.

**Example 1:**
```
Input: "abcde",5,"cd",2
Output:2
```

**Example 2:**
```
Input:"abcde",5,"z",1
Output:0
```

## hints
```
    easy..
```

## Analogous
|                Nav                    |                 Des                 |
|:-------------------------------------:|:-----------------------------------:|
|![selectNum](selectNum.md)             |挑选出每组连续数字字符               |

## Solution
``` c
int isSubString(char* s, int m, char* t, int n) {
    if (s == NULL || t == NULL || n > m ) return 0;

    int len = 0;
    for (int i = 0; i < m; i++) {
        if (t[len] == s[i]) {
            len++;
        }else {
            len = 0;
        }

        if (len == n) return i-len+1;
    }

    return 0;
}
```