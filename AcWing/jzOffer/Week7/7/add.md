## 85. 不用加减乘除做加法
[这里](https://www.acwing.com/problem/content/81/)
写一个函数，求两个整数之和，要求在函数体内不得使用＋、－、×、÷ 四则运算符号。
[leetcode371](https://leetcode.com/problems/sum-of-two-integers/)

**Example :**
```
Input:num1 = 1 , num2 = 2
Output:3
```
## hints
```
1.异或:相当于不进位的加法.【00=0,01=1,11=0】
2.(a & b) << 1
    (1).先&再<< 左移1位
    (2).&的优先级比移位运算符(>> <<)低
    (3).得到每一位的进位标识符.左移1位是给高位进位
3.结合1和2，就相当于加法两步走。先无进位加法，再把进位加上
4.c语言的话在leetcode需要强转为unsigned才能左移，否则输入2个负数的例子会报溢出的RE错误。
```
## Solution
``` c
/* 1 + 2 =3

    0001
  + 0010
  ------
s ^ 0011  （sum）
c & 0000  （carry）
--------
=   0011

*/

int add(int num1, int num2){
    while(num2){
        int sum = num1 ^ num2;           // 异或，相加不进位
        //int carry = (num1 & num2) << 1;
        int carry = (unsigned)(num1 & num2) << 1;  // 与+左移，获取每个位的进位标志【注:先&再左移，&优先级比<<低，要加括号】
        num1 = sum;
        num2 = carry;
    }

    return num1;
}
```