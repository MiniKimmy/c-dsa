## 87. 把字符串转换成整数
[这里](https://www.acwing.com/problem/content/description/83/)
请你写一个函数StrToInt，实现把字符串转换成整数这个功能。

**Note**
* 不能使用atoi或者其他类似的库函数。
* 你的函数应满足下列条件：
    * 忽略所有行首空格，找到第一个非空格字符，可以是 ‘+/−+/−’ 表示是正数或者负数，紧随其后找到最长的一串连续数字，将其解析成一个整数；
    * 整数后可能有任意非数字字符，请将其忽略；
    * 从前往后遍历时，如果第一段连续非空格字符串不是一个有效的整数表示，则返回0；
    * 如果整数大于INT_MAX(2^31 − 1)，请返回INT_MAX；如果整数小于INT_MIN(−2^31) ，请返回INT_MIN；
* 2^31 − 1 = 2147483647
* -2^31 = 2147483648

**Example :**
```
Input:"123"
Output:123
```
## hints
```
    1.先使用long接收完整，再int返回
    2.有效数字，需要遍历每一个位都是数字。
```
## Solution
``` c
#define INT_MAX 2147483647
#define INT_MIN -2147483648

int getLen(char* str){
    int len = 0;
    while(str[len]){
        len++;
    }
    return len;
}

int isDigit(char c){
    if(c >= '0' && c <='9') return 1;
    else return 0;
}

// 1表示有效数字,0表示无效数字
int checkDigit(char* str, int start, int end)
{
    if(str[start] == '+' || str[start] == '-') start++;
    for(int i = start; i<=end;++i){
        if(!isDigit(str[i])) return 0;
    }
    return 1;
}

int strToInt(char* str) {
    int len = getLen(str);
    int i = 0;
    int j = len-1;
    while(i<len && str[i] == ' ') ++i;
    while(j>=0 && !isDigit(str[j])) --j;
    if(i>j || (!checkDigit(str,i,j)) ) return 0;

    int symbol = 1; //符号位 1是正数，-1是负数
    if(str[i] == '+'){
        i++;
    }
    else if(str[i] == '-'){
        symbol = -1;
        i++;
    }

    long res = 0;
    int bit = 1;
    for(int k = j;k>=i;--k,bit*=10)
    {
        res += (str[k] - '0')*bit;
    }

    res *= symbol;
    if(res >=INT_MAX) return INT_MAX;
    if(res <=INT_MIN) return INT_MIN;

    return res;
}
```