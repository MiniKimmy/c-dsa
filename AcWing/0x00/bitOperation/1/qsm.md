## 89.a^b
[这里](https://www.acwing.com/problem/content/91/)
求 a 的 b 次方对 p取模的值。
输入三个整数a,b,p,在同一行用空格隔开。
输出一个整数，表示a^b mod p的值。

**Note**
* 数据范围:1≤a,b,p≤109

**Example :**
```
Input:3 2 7
Output:2
```
## hints
```
1.“AcWing分享”里有[快速幂模板](https://www.acwing.com/blog/content/24/)
2.思想是将a^b --转化为--> a^(2^k)
3.需要的基本位运算知识
    (1).1 << n 即表示1左移n为，即2^n
    (2).n >> x 即表示n右移x位，即n / 2^x
        * n >>= 1 即表示n左移1位，n去掉最低位
    (3).n & 1 即表示查看n的最低位
4.mod取模的知识
    (1).n mod 10 等价于 n mod 10 mod 10（重复mod是不会影响结果的）
    (2).(n1 + n2) mod 100 等价于 n1 mod 100 + n2 mod 100 （分配律）
    (3).控制范围，n mod p 相当于把n控制在p的范围内，取模之后的结果≤p
5.二进制转十进制的计算
    * ex: 1101 表示 2^0 + 2^2 + 2^3 = 13
6.快速幂的思想
    (1).ex: 3^13 = 3^(1101)
                 = 3^(2^0 + 2^2 + 2^3)
                 = [3^(2^0)] * [3^(2^2)] * [3^(2^3)]
    (2).基于位运算 “n & 1” 可以每次查看最低位
    (3).基于 “n >>= 1” 可以每次去掉最低位
    (4).简单来说就是，每次查看最低位（1就累计到res，0就不变），然后把最低位去掉；同时，每次倍增(2^1)准备好
7. 1l 和 1ll 是整数1的long类型或long long类型，避免计算时发生溢出。
    * 读取long类型是"%ld"而不是"%d"; scanf("%ld",&n); printf("%ld",n);
```
## Solution
``` c
#include<stdlib.h>
#include<stdio.h>

void qsm(int a, int b, int p)
{
    int res = 1 % p;
    int t = a;
    while(b){
        if(b&1) res = res * 1ll * t % p;
        t = t * 1ll * t % p;
        b >>= 1;
    }

    printf("%d", res);
}

int main()
{
    int a,b,p;
    scanf("%d %d %d",&a,&b,&p);

    qsm(a,b,p);
    return 0;
}
```