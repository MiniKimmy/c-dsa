## 90. 64位整数乘法
[这里](https://www.acwing.com/problem/content/92/)
求 a 乘 b 对 p 取模的值。
输入第一行输入整数a，第二行输入整数b，第三行输入整数p
输出一个整数，表示a*b mod p的值。

**Note**
* 数据范围:1≤a,b,p≤1018

**Example :**
```
Input:
3
4
5
Output:2
```
## hints
```
1.乘法转加法
    * ex:3 * 4 =3+3+3+3
2.快速幂思想
    * 3*1 = 3
      3*2 = 6
      3*4 = 12
    * 等价于二进制
        3 * (1)
        3 * (10)
        3 * (100)
    * ex:3*13
       = 3*(1101)
       = 3*(2^0 + 2^2 + 2^3)
       = 3*(1+4+8)
       = (1个3) + (4个3) + (8个3)
3.long类型
    (1).scanf("%ld",&n);
    (2).printf("%ln",n);
    (3).scanf("%lld",&n); long long类型
```
## Solution
``` c
#include<stdlib.h>
#include<stdio.h>

void mulInt64(long a,long b, long p)
{
    long res = 0;
    long t = a;
    while(b){
        if(b&1) res = (res*1l + t) % p;
        t = t * 2l % p;
        b >>= 1;
    }

    printf("%ld",res);
}

int main()
{
    long a,b,p;
    scanf("%ld\n%ld\n%ld",&a,&b,&p);

    mulInt64(a,b,p);
    return 0;
}
```