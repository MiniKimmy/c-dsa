## 63. 字符串中第一个只出现一次的字符
[这里](https://www.acwing.com/problem/content/59/)
在字符串中找出第一个只出现一次的字符。
如果字符串中不存在只出现一次的字符，返回#字符。

**Example :**
```
Input:"abaccdeff"
Output:'b'
```
## hints
```
    1.hash记录字母出现字数
    2.for遍历源字符串，再hash[i]查看次数是否为1
```
## Solution
``` c
char firstNotRepeatingChar(char* s) {
    int* hash = (int*)malloc(sizeof(int) * 255);

    for(int i = 0;i<255;++i){
        hash[i] = 0;
    }

    char* p = s;
    while(*p){
        hash[(int)(*p)]++;
        p++;
    }

    p = s;
    while(*p)
    {
        if(hash[(int)(*p)] == 1){
            free(hash);
            return *p;
        }
        ++p;
    }

    free(hash);
    return '#';
}
```