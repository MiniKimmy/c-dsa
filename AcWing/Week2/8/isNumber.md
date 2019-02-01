## 31. 表示数值的字符串
[这里](https://www.acwing.com/problem/content/29/)
请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。

**Note :**
* 小数可以没有整数部分，例如.123等于0.123；
* 小数点后面可以没有数字，例如233.等于233.0；
* 小数点前面和后面可以有数字，例如233.666;
* 当e或E前面没有数字时，整个字符串不能表示数字，例如.e1、e1；
* 当e或E后面没有整数时，整个字符串不能表示数字，例如12e、12e+5.4;

**Example 1:**
```
Input :"+100","5e2","-123","3.1416","-1E-16"
Output:true
```
**Example 2:**
```
Input :"12e","1a3.14","1.2.3","+-5","12e+4.3"
Output:false
```
## hints
```
    1.分情况讨论
    2.先考虑边界情况
    3.再细分具体的枚举
        (1)数字
        (2)字符'.'、'e、E'
    4.记录个数的形式，出现次数
        (1)在更新个数的时候，顺便判断当前周围情况
    5.通过提交来把没考虑到的情况补充完.
    6.修改题目给的方法参数里的变量名，为了方便处理实际有意义有效的参数来处理。
```
## Solution
``` c
/// 获取字符串长度
int getLen(char* str){
    int len = 0;
    while(str[len]){
        len++;
    }
    return len;
}

/// 截取[l,r]的字符串
int subStr(char* str, int l, int r)
{
    int len = r-l + 1;
    char* ret = (int*)malloc(sizeof(int) * (len+1));

    for(int i = l;i<=r;++i){
        ret[i-l] = str[i];
    }

    ret[len] = '\0';
    return ret;
}

bool isNumber(char* _s) {
    if(_s == NULL) return false;
    int _size = getLen(_s);

    if(_size == 0) return false;        //空str,

    /// trim
    int i = 0; int j = _size-1;
    while(i<=j && _s[i] == ' ') ++i;
    while(i<=j && _s[j] == ' ') --j;
    if(i > j) return false;            // 空格

    char* s = subStr(_s,i,j);          //获取实际有意义的字符串
    int size = j-i+1;

    if(s[0] == '+' || s[0] =='-') {
        s=subStr(s,1,size-1);
        size--;
        if(size == 0) return false;   // '+','-'
    }

    int doc = 0; int e = 0;
    for(int i = 0;i<size;++i){
        char c = s[i];
        if(c >= '0' && c<= '9') continue; // 普通数字

        // 非数字
        else {
            if(c == '.'){
                doc++;
                if(doc>=2 || e || (i==size-1 && size==1) ) return false;       //1..; ..1; 1.1.; .;
            }

            else if(c == 'e' || c == 'E'){
                e++;
                if(e>=2 || !i || (i == size-1) || s[i-1] == '.' ) return false;// e,ee, 11e,
                if(s[i+1] == '+' || s[i+1] == '-') i++;                        // e后带有±
                if(s[i+1] < '0' || s[i+1] >'9') return false;                  // e前后
            }
            else {
                return false;
            }
        }

    }
    return true;
}
```