## 30. 正则表达式匹配
[这里](https://www.acwing.com/problem/content/description/28/)
请实现一个函数用来匹配包括'.'和'*'的正则表达式。
模式中的字符'.'表示任意一个字符，而'*'表示它前面的字符可以出现任意次（含0次）。
在本题中，匹配是指字符串的所有字符匹配整个模式。

例如，字符串"aaa"与模式"a.a"和"ab*ac*a"匹配，但是与"aa.a"和"ab*a"均不匹配。

**Example 1:**
```
Input：s="aa",p="a*"
Output:true
```
**Example 2:**
```
Input：s="aaa"; p="a*",p="a.a",p="ab*ac*a"
Output:true
```
**Example 3:**
```
Input：s="aaa"; p="aa.a",p="ab*a"
Output:false
```
## hitns
```
**关于dp,二维数组记录状态
1.初始化时候需要开辟[n+1][m+1]的空间，n和m分别表示s、p的字符串长度
    (1).为了使用f[n][m]:处于字符串s和字符串p都不选，这种也表示一种情况。
2.状态表示
    (1).哪两个是影响状态的元素
    (2).主动权在谁手上
3.状态切换
    (1).核心是分情况,即思考 f[x][y] = ? 的问题
    (2).一上来先对边界判断
        * 边界即已经到了最后一步，判断完是符合边界条件就可以在if的方法体内return
        * 边界1：当前已经被访问过
        * 边界2：发生数组越界的情况(或者说到达最后一步的情况)
    (3).把所有情况列一遍
        * 独立思考每一种情况，写对应的处理方式
    (4).func dp()的思路
        * 当前状态 和 相邻状态
        * 当前状态就可以直接访问方法的参数"状态表示",
        * 相邻状态就需要递归func dp(),把状态切换的参数传入递归方法
        * 使用全局f，最好用int[][],设置一个默认特殊值值表示未访问过未修改过当前f
            *## 然后bool变量接收if语句段
            * 把bool值赋值给f
            * 因为bool只有0、1,所以特殊值可以取-1,表示当前未知√、×。
    (4). 最后把相同处理的情况可以写在一起
        * 虽然if语句不同，但是可以通过&& || 来拼接2种情况
        * 注:一个情况一个if写也可以，按容易的情况先写的原则
**关于本题** --func dp思想
    (1).dp需要上一个状态来确定下一个状态
        * 它这个状态要根据后面的提供信息（递归获取下一级的信息，一直问下一个人拿）
        * 而我们目前处于最开始的状态，完全不知道下一个人，所以需要递归下一个人，递归的同时把参数告诉下一位.
    (2).状态表示f[i][j]
        * i表示字符串s的下标
        * j表示字符串p的下标
    (3).状态切换
        (1).p[j]是普通字母: f[i][j] = s[i] == p[j] && f[i+1][j+1]
            * 需要匹配当前成功之后，才去匹配下一个[i+1][j+1]
        (2).p[j]是".":f[i][j] = f[i+1][j+1]
        (3).p[j+1]是"*":
            (1).b*表示0个的情况:f[i][j] = f[i][j+2]
                * 匹配p[j]成功或者不成功都没影响，即ex:aa* 和a*是同一个东西
            (2).b*大于0个的情况:f[i][j] = f[i+1][j]
                * 先要匹配p[j]成功
    (4).写if的情况的时候，因为1、2的处理方式类似，可以合并为同一个if里
    (5).需要使用到相邻状态的时候就进行dp递归.
```

## Solution
``` c
int getLen(char* str){
    int len = 0;
    while(str[len]){
        len++;
    }
    return len;
}

bool dp(char* s, char* p, int sLen, int pLen, int x, int y, int*** f)
{
    if( (*f)[x][y] != -1 ) return (*f)[x][y];
    if(y == pLen){
        (*f)[x][y] = x == sLen;
        return (*f)[x][y];
    }

    // 匹配当前状态
    bool first_match = x < sLen && (p[y] == '.' || p[y] == s[x]);

    if(y + 1 < pLen && p[y+1] == '*'){
        // '*'的情况
        (*f)[x][y] = first_match && dp(s,p,sLen,pLen,x+1,y,f) || dp(s,p,sLen,pLen,x,y+2, f);
    }else{
        // '.' 和 '普通字母'的情况
        (*f)[x][y] = first_match && dp(s,p,sLen,pLen,x+1,y+1,f);
    }

    return (*f)[x][y];
}

bool isMatch(char* s, char* p) {
    if(s == NULL || p == NULL) return false;

    int n = getLen(s); int m = getLen(p);

    // init-int[][],初始化赋值-1
    int** f = (int**)malloc(sizeof(int*) * (n+1));
    for(int i = 0;i<n+1;++i){
        f[i] = (int*)malloc(sizeof(int) * (m+1));
    }
    for(int i = 0;i<n+1;++i){
        for(int j = 0;j<m+1;++j){
            f[i][j] = -1;
        }
    }

    return dp(s,p,n,m,0,0,&f);
}
```

