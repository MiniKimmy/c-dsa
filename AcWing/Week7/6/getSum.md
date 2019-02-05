## 84. 求1+2+…+n
[这里](https://www.acwing.com/problem/content/80/)
求1+2+…+n

**Note**
* 要求不能使用乘除法、
* for、while
* if、else
* switch、case等关键字
* 及条件判断语句（A?B:C）。

**Example :**
```
Input:10
Output:55
```
## hints
```
    1.与运算，阻断
```
## Solution
``` c
int getSum(int n) {
    int ret = n;
    (n>0) && (ret = ret + getSum(n-1));
    return ret;
}
```