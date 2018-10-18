## 171.Excel Sheet Column Number

Given a column title as appear in an Excel sheet, return its corresponding column number.

**For example:**
```
    A -> 1
    B -> 2
    C -> 3
    ...
    Z -> 26
    AA -> 27
    AB -> 28
    ...
```
**Example 1:**
```
Input: "A"
Output: 1
```
**Example 2:**
```
Input: "AB"
Output: 28
```
**Example 3:**
```
Input: "ZY"
Output: 701
```

## hints
```
current: s[0]='A'
1  ->dp[0] = 1

AA
dp[1] = 26 * (dp[0]) + (currenChar -'A' +1)

AAA
dp[2] = 26*(dp[1]) + 1

AAA
dp[3] = 26*(dp[2])+1
```

## Solution
``` c
int titleToNumber(char* s) {
    if(s == NULL) return 0;

    int len = 0;
    while(s[len]){
        len++;
    }

    int* dp = (int*)malloc(sizeof(int) * len);
    dp[0] = s[0]-'A'+1;
    for(int i = 1;i<len;++i){
        int c = s[i] - 'A' +1;
        dp[i] = 26*dp[i-1] + c;
    }

    return dp[len-1];
}
```