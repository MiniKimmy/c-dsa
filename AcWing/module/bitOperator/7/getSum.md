## 371. Sum of Two Integers
[这里](https://leetcode.com/problems/sum-of-two-integers/)
不使用±运算符号实现加法

## hints
```
a=1,b=2
  0001
  0010
------
^ 0011 (sum)   --作为下一个a
& 0000 (carry) --作为下一个b
---------
  0011

ps（c语言）:左移1位去掉最高位的情况注意“负数去掉最高位”需要移位之前强转为(unsigned)
```
## Solution
``` c
int getSum(int a, int b) {
    while(b){
        int sum = a ^ b;
        int carry = (unsigned)(a & b) << 1; //c语言必须强转
        a = sum;
        b = carry;
    }
    return a;
}
```
## hints2
```
1.c#语言不需要强转为unsigned,直接左移即可。
2.可以递归也可以像上面用迭代while
```
## Solution
``` csharp
public class Solution {
    public int GetSum(int a, int b) {
        if(b == 0) return a;
        int sum = a ^ b;
        int carry = (a & b) << 1;
        return GetSum(sum,carry);
    }
}
```