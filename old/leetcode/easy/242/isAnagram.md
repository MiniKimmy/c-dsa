## 242. Valid Anagram

Given two strings s and t , write a function to determine if t is an anagram of s.

**Example 1:**
```
Input: s = "anagram", t = "nagaram"
Output: true
```
**Example 2:**
```
Input: s = "rat", t = "car"
Output: false
```
**Note:**
You may assume the string contains only lowercase alphabets.

**Follow up:**
What if the inputs contain unicode characters? How would you adapt your solution to such case?<br/>

## hints:
```
    hashtable

    1.count the number of each word appear in char* s and char* t
    2.compare the numbers of corresponding word in m1[] and m2[]
```

## Solution

``` c
bool isAnagram(char* s, char* t) {

    int* m1 = malloc(sizeof(int)*255);
    int* m2 = malloc(sizeof(int)*255);
    for(int i = 0;i<255;++i){
        m1[i] = 0;
        m2[i] = 0;
    }

    int len = 0;
    while(s[len]){
        m1[s[len]]++;
        ++len;
    }

    int len_t = 0;
    while(t[len_t]){
        m2[t[len_t]]++;
        ++len_t;
    }

    if(len_t > len) return false;

    for(int i = 97;i<=122;++i){
        if(m1[i] != m2[i]){
            return false;
        }
    }

    free(m1);
    free(m2);
    return true;
}

```