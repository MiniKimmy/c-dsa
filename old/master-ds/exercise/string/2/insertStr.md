## Insert string to string

Given two string s,t, inset t to s at pos index.You can assume that s has enough space to let t in.

## CHINESE
将字符串t插入到字符串s中的pos位置，假设分配给字符串s的空间足够让字符串t插入。

**Example 1:**
```
Input: "abcaaabc123","ppp",5
Output: "abcaapppabc123"
```
**Example 2:**
```
Input:"lad","abc", 4
Output:"ladabc"
Explaination: 4>size("lad")=3, just append the end of "lad"
```
**Example 3:**
```
Input:"lad","abc",-100
Output:"lad"
Explaination: -100 < 0, so nothing change.
```

## hints
```
    1.two situation: pos >= Length(s) append t and pos < Length(s) insert t.
    2.we don't know Length(s),

    |---------|------------|
    0         ↑         Length(s)
             pos
    |---------|************|------------|
    0         ↑ Length(t)  ↑        NewLength(s)
             pos         newpos

    3.so the first things is to judge s[pos]=='\0'?
    4.copy the s(right-size) to a buffer string
    5.insert t start from [pos] and mark the "newpos"
    6.then paste s(right-size) start from [newpos].
```

## Solution
``` c
void insertStr(char* s, char* t, int pos){
    if (pos < 0 || s == NULL) return;

    char* p = s;
    int len = 0;
    while (*p && len < pos) { //judge pos > s-Len ?
        ++len;
        ++p;
    }

    if (pos == len) {
        char* buffer = (char*)malloc(sizeof(char) * MAXSIZE);
        buffer[MAXSIZE - 1] = '\0';

        int i;
        for (i = pos; s[i] != '\0'; ++i) {
            buffer[i - pos] = s[i];
        }

        i = i - pos; //rightLen

        while (*t) {
            s[pos] = *t;
            ++t;
            ++pos;
            len++;
        }

        len = len + i; //new Size
        for (int j = 0; j < i; j++) {
            s[pos + j] = buffer[j];
        }

        free(buffer);
    }

    else {
        while (*t) {
            s[len] = *t;
            ++t;
            ++len;  //new Size
        }
    }

    s[len] = '\0'; //mark end-tag.
}
```