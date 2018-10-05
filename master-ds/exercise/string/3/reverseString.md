## Reverse String

Given a string, use recursion to reverse this string.

写一个递归算法来实现字符串逆序存储.

**Example 1:**
```
Input: "123"
Output: "321"
```
**Example 2:**
```
Input:"a"
Output:"a"
```

**Note:**<br />
```
    Space Complexity is O(1).
```

## hints
```
    1.calc length(str)
    2.like for(i=0;i<len/2;++i)
```

## Solution
``` c
void reverseStrInner(char* c, int left, int right) {

    if (left >= right) return;
    char ch = c[left];
    ch = c[left] ;
    c[left] = c[right];
    c[right] = ch;
    reverseStrInner(c, left + 1, right - 1);
}

void reverseString(char* c) {
    if (c == NULL) return;

    char* p = c;
    int len = 0;
    while (*p) {
        len++;
        ++p;
    }

    reverseStrInner(c, 0, len-1);
}
```