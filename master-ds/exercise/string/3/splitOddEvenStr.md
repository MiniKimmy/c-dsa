## Split Odd And Even String

Given a string, put the odd index char ascending to the front of the string, and put the even index char descending to the back of the string.

## CHINESE
给一个字符串S,将S的所有第偶数个字符按照其原来的下标从大到小的次序放在S的后半部分;<br />
将S的所有第奇数个字符按照其原来的下标从小到大的次序放在S的前半部分. <br />

**Example 1:**
```
Input: "ABCDEFGHIJKL"
Output: "ACEGIKLJHFDB"
```
**Explaination:**
```
odd-list:"ACEGIK" as left-size
even-list:"BDFHJL"(reverse)->"LJHFDB" as right-size
```
**Example 2:**
```
Input:"abcd"
Output:"acdb"
```
**Explaination:**
```
odd-list:"ac" as left
even-list:"bd"(reverse)->"db" as right
```

## hints
```
    1.getLength(S)
    2.judge (i%2==0) or (i%2!=0) to put it the right pos.
```

## Analogous
|                Nav                    |                 Des                 |
|:-------------------------------------:|:-----------------------------------:|
|![reverseString](reverseString.md)     |递归翻转字符串                       |


## Solution
``` c
char* splitOddEvenStr(char* str) {
    int len = 0;
    while (str[len])
        len++;

    if (0 == len || str == NULL) return NULL;
    char* ret = (char*)malloc(sizeof(char) * (len+1));
    ret[len] = '\0';

    for (int i = 0; i < len; ++i) {
        int offset = i + 1;
        if (offset % 2 != 0) {
            ret[i / 2] = str[i];
        }else {
            ret[len - (i / 2) -1] = str[i];
        }
    }

    return ret;
}
```