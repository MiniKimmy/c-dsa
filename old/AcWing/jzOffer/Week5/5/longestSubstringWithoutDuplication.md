## 61. 最长不含重复字符的子字符串
[这里](https://www.acwing.com/problem/content/57/)
请从字符串中找出一个最长的不包含重复字符的子字符串，计算该最长子字符串的长度。

**Note**
* 假设字符串中只包含从’a’到’z’的字符。

**Example :**
```
Input:"abcabc"
Output:3
Explanation: "abc"是无重复的连续字符串最大长度为3
```
## hints
```
    1.hash[]记录出现过的字母的下标位置
    2.若出现相同字母，则计算区间长度，清空hash
    3.在hash找出那个字母的下一个坐标，重新开始数
```

## Solution
``` c
void longestSubstringWithoutDuplicationInner(char* s, int start, int* ret){
    if(!s[start]) return;

    int* hash = (int*)malloc(sizeof(int) * 255);
    for(int i = 0;i<255;++i){
        hash[i] = -1;
    }

    int index = start;
    while(s[index]){
        int c = s[index];
        if(hash[c] != -1) break;

        hash[c] = index;
        index++;
    }

    if(*ret < index-start){
        *ret = index-start;
    }

    int nextStart = s[index]? hash[(int)(s[index])] + 1 : index;

    free(hash);
    longestSubstringWithoutDuplicationInner(s, nextStart, ret);
}

int longestSubstringWithoutDuplication(char* s) {
    int refRet = 0;

    longestSubstringWithoutDuplicationInner(s,0,&refRet);
    return refRet;
}
```