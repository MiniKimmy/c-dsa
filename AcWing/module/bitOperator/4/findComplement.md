## 476. Number Complement
[这里](https://leetcode.com/problems/number-complement/)

给一个正整数，对其二进制表示形式每位取反。（该整数最高位是1,，省略高位多余的0）

## hints
```
for一遍每位，然后取反，塞回到对应的位上面。
1.取非（c/c++）
    * !0 = 1;
    * !100 = 0;  --->!(非0数) = 0;
2.不能用'~'取反符号
    (1).因为虽然 5 = 101；但是int里表示的5是：000000..101
    (2).取反~是把所有的位都取反。
```
## Solution
``` c
int findComplement(int num) {
    int res = 0;
    int k = 0;
    for(int i = num; i ; i >>= 1, ++k){
        //res += i & 1? (0 << k): (1 << k);
        res += !(i&1) << k;
    }
    return res;
}
```
## hints2
```
1.!a 在c#取非并不能像c/c++ 使用。
```
## Solution
``` csharp
public class Solution {
    public int FindComplement(int num) {
        int res = 0;
        int t = 0;
        while(num > 0){
            res += ((num & 1) == 1? 0 : 1) << t ;
            t++;
            num >>= 1;
        }

        return res;
    }
}
```