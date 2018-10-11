## 791. Custom Sort String

S and T are strings composed of lowercase letters. In S, no letter occurs more than once.
<br />
S was sorted in some custom order previously. We want to permute the characters of T so that they match the order that S was sorted. More specifically, if x occurs before y in S, then x should occur before y in the returned string.
<br />
Return any permutation of T (as a string) that satisfies this property.
<br />
**Example :**
```
Input:
S = "cba"
T = "abcd"
Output: "cbad"
```
**Explanation:**
```
"a", "b", "c" appear in S, so the order of "a", "b", "c" should be "c", "b", and "a".

Since "d" does not appear in S, it can be at any position in T. "dcba", "cdba", "cbda" are also valid outputs.
```

**Note:**
```
    S has length at most 26, and no character is repeated in S.
    T has length at most 200.
    S and T consist of lowercase letters only.
```

## Analogous
|                         Nav               |                   Des            |
| :----------------------------------------:|:--------------------------------:|
| ![reverseOnlyLetters](../../easy/917/reverseOnlyLetters.md)|仅字母翻转       |

## hints
```
    1.hash all the exist char of ("S")
    2.traverse "T" each time, to find all the current top char.
```
## Solution
``` c
char* customSortString(char* S, char* T) {
    if(S == NULL) return T;

    int* hash = (int*)malloc(sizeof(int)*255);
    for(int i =0;i<255;i++){
        hash[i] = 0;
    }

    char* p = S;
    int len = 0;

    while(*p){
        hash[(*p)] = len;
        len++;
        p++;
    }

     char* q = T;
     for(int i = 0;i<len;++i){
        p = T;
        while(*p){
            if(hash[(*p)] == i){
                char temp = *T;
                *T = *p;
                *p = temp;
                T++;
            }
            p++;
        }
    }

    free(hash);
    return q;
}
```