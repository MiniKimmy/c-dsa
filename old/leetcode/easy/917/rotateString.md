## 796.Rotate String
We are given two strings, A and B.

A shift on A consists of taking string A and moving the leftmost character to the rightmost position. For example, if A = 'abcde', then it will be 'bcdea' after one shift on A. Return True if and only if A can become B after some number of shifts on A.

**Example 1:**
```
Input: A = 'abcde', B = 'cdeab'
Output: true
```
**Example 2:**
```
Input: A = 'abcde', B = 'abced'
Output: false
```
**Note:**
    A and B will have length at most 100.

## hints
```
    1.each time to find A[0],then check the rotate.
    2.careful the Source input:
    "a","" -- false;
    "",""  -- true;
    3.each time refresh the flag and match once again.

```

## Analogous
|                         Nav               |                   Des            |
| :----------------------------------------:|:--------------------------------:|
| ![reverseOnlyLetters](../../easy/917/reverseOnlyLetters.md)|仅字母翻转       |
| ![compress](compress.md)|压缩字母                                            |

## Solution
``` c
bool rotateString(char* A, char* B) {
    if(A == NULL || B == NULL) return false;

    int flag = 0;
    char* p = A;
    char* q = B;
    if(*p && !(*q) || !(*p) && (*q)) return false;

    char* mark = q;
    while(*p && *q){
    //refresh.
        flag = 0;
        int real_flag = 0;
        q = mark;

    //find the B[flag] equals A[0]
        while(*q){
            if(*q == A[0]){
                break;
        }
            flag++;
            q++;
        }

        mark = q;
        mark++;
        if(!(*mark)) return false;

    //check the tail rotate array.
    //refresh p to check the rotate array agagin.
        p = A;
        while(*q && *p){
            if(*q != *p){
                real_flag = 1;
                break;
            }
            q++;
            p++;
        }

    //to check the head rotate array.
        if(real_flag == 1) continue;
        for(int i = 0;i<flag;++i){
            if(*p != B[i]){
                real_flag = 1;
                break;
            }
            p++;
        }

        if(real_flag == 0) break;
    }

    return true;
}
```
