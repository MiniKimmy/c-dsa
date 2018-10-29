## 345.Reverse Vowels of String

Write a function that takes a string as input and reverse only the vowels of a string.

**Example 1:**
```
Input: "hello"
Output: "holle"
```
**Example 2:**
```
Input: "leetcode"
Output: "leotcede"
```
**Note:**
The vowels does not include the letter "y".

## hints
```
    qSort mind
```

## Analogous
|                       Nav                 |                   Des            |
| :----------------------------------------:|:--------------------------------:|
| ![maxProfit](maxProfit.md)|买卖最大利润.                                     |


## Solution
``` c
char* reverseVowels(char* s) {
    if(s==NULL) return s;

    int len = 0;
    while(s[len]){
        len++;
    }
    if(len == 0) return s;

    int* hash = (int*)malloc(sizeof(int)*255);
    for(int i = 0;i<255;++i){
        hash[i] = 0;
    }
    hash['a'] = 1;
    hash['A'] = 1;
    hash['e'] = 1;
    hash['E'] = 1;
    hash['i'] = 1;
    hash['I'] = 1;
    hash['o'] = 1;
    hash['O'] = 1;
    hash['u'] = 1;
    hash['U'] = 1;

    int left = 0;
    int right = len-1;
    while(true){
        while(left<len && hash[s[left]] != 1) ++left;
        while(right>=0 && hash[s[right]] != 1) --right;
        if(left>right) break;
        char c = s[left];
        s[left] = s[right];
        s[right] = c;
        left++;
        right--;
    }

    free(hash);
    return s;
}
```