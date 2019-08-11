## 344.Reverse String

Write a function that takes a string as input and returns the string reversed.

**Example 1:**
```
Input: "hello"
Output: "olleh"
```
**Example 2:**
```
Input: "A man, a plan, a canal: Panama"
Output: "amanaP :lanac a ,nalp a ,nam A"
```

## hints
```
    reverse list
```

## Solution
``` c
char* reverseString(char* s) {
    if(s == NULL) return s;

    int len = 0;
    while(s[len]){
        ++len;
    }

    for(int i = 0;i<len/2;++i){
        char c = s[i];
        s[i] = s[len-1-i];
        s[len-1-i] = c;
    }

    return s;
}
```
