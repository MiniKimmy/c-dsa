## 59. 把数字翻译成字符串
[这里](https://www.acwing.com/problem/content/55/)

给定一个数字，我们按照如下规则把它翻译为字符串：
0翻译成”a”，1翻译成”b”，……，11翻译成”l”，……，25翻译成”z”。
一个数字可能有多个翻译。

请编程实现一个函数用来计算一个数字有多少种不同的翻译方法。

**Example :**
```
Input:"12258"
Output:5
Explanation:12258有5种不同的翻译，它们分别是”bccfi”、”bwfi”、”bczi”、”mcfi”和”mzi”。
```
## hints
```
1.借用数字排列组合的思想。即按住位不动，而看看剩余部分有多少种组合
    (1)Ex:"12258"
        * 按住'1'不动，看有多少组合
        * 1 [] [] [] []
        * 有"1[2][2][5][8]、"1[22][5][8]"、"1[2][25][8]"
        * 按住'12'不动，看有多少组合
        * 12 [] [] [] 同理.
    (2).代码的思想就是[p,q]这段能有多少种组合？
    (3).剩下最后一个位时候即可以处理业务
2.string整数转int
    (1).for这个字符串
    (2).公式: res = res * 10 + str[i] - '0'; 【初始值res=0】
    (3).表示每次取一个数，然后留‘0’个位
```
## Solution
``` c
int getLen(char* str)
{
    int len = 0;
    while(str[len]){
        len++;
    }
    return len;
}

/// 查看[p,q]这段里有多少组合.
void dfs(char* s, int p, int q, int* ret)
{
    if(p == q){
        (*ret)++;
        return;
    }

    // 按住1位
    dfs(s,p+1,q,ret);

    // 按住2位
    if(p<q-1) {

        // string整数转int
        int res = 0;
        for(int i = p;i<p+2;++i){
            res = res * 10 + s[i+1] - '0';
        }

        if(res>=10 && res <= 25) dfs(s,p+2,q,ret);
    }
}

int getTranslationCount(char* s) {
    if(s == NULL) return 0;

    int len = getLen(s);
    int refRet = 0;

    dfs(s,0,len-1, &refRet);

    return refRet;
}

```