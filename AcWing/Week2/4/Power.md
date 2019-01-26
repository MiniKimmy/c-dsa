## 27. 数值的整数次方
[这里](https://www.acwing.com/problem/content/26/)
实现函数double Power(double base, int exponent)，求base的 exponent次方。
不得使用库函数，同时不需要考虑大数问题。

**Note:**不会出现底数和指数同为0的情况

**Example 1:**
```
Input:10,2
Output:100
```
**Example 2:**
```
Input:-4,-2
Output:0.0625
```
**Example 3:**
```
Input:2,0
Output:1
```
## hints
```
    1.分情况
        (1).0次幂返回1
        (2).正数幂or负数幂，先统计次数。（1次方跳过）
            记录底数:
                * 10^2,底数是10，次数是1
                * -2^-4,底数是-2,次数是3
        (3).全部使用乘法(除法只是乘法的倒数而已)
        (4).返回时候根据幂的±，幂是正数的话就是x>=1的数;否则是0<x<1的数，最后才使用倒数.
```
## Solution
``` c
double Power(double base, int exponent){
    if(exponent == 0) return 1;

    double temp = base;
    int times = exponent>0?exponent:-exponent;
    for(int i = 1;i<times;++i){
        base *= temp;
    }

    return exponent>=0 ?base: 1/ (base);
}
```