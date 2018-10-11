## 917.Reverse Only Letters

Given a string S, return the "reversed" string where all characters that are not a letter stay in the same place, and all letters reverse their positions.

**Example 1:**
```
Input: "ab-cd"
Output: "dc-ba"
```
**Example 2:**
```
Input: "a-bC-dEf-ghIj"
Output: "j-Ih-gfE-dCba"
```
**Example 3:**
```
Input: "Test1ng-Leet=code-Q!"
Output: "Qedo1ct-eeLg=ntse-T!"
```

**Note:**
```
    S.length <= 100
    33 <= S[i].ASCIIcode <= 122
    S doesn't contain \ or "
```

## hints
```
    1.mark the symbol in the same pos.
    2.judge sorceStr is an alpha and retStr is an alpha,
    otherwise, either sorceStr move next, or retStr move next within the other pointer doesn't move.
```

## Analogous
|                         Nav               |                   Des            |
| :----------------------------------------:|:--------------------------------:|
| ![customSortString](../../medium/791/customSortString.md)|自定义模板排序字母 |

## Solution
``` c
int isAlpha(char c){
    if((c>=65 && c<= 90) || (c>=97 && c<=122)) return 1;
    else return 0;
}

char* reverseOnlyLetters(char* S) {
    if(S == NULL) return NULL;

    char* p = S;
    int len = 0;
    while(*p){
        ++len;
        p++;
    }

    char* ret = (char*)malloc(sizeof(char) * (len+1) );
    ret[len] = '\0';   // must need "\0" at the end of char*

    for(int i = 0;i<len;++i){
        if(isAlpha(S[i]) == 0 ){
            ret[i] = S[i];
        }else{
            ret[i] = 'a'; //emphasize the symbol. and other is a letter.
        }
    }

    p = S;
    int j = len-1;
    while(*p && j>=0){
        char c = *p;
        if(isAlpha(c) == 0) {
            p++;
            continue;
        }

        if(isAlpha(ret[j]) == 0){
            j--;
        }else{
            ret[j--] = c;
            p++;
        }
    }

    return ret;
}
```



