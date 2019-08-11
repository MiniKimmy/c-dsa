## 231. Power of Two
[这里](https://leetcode.com/problems/power-of-two/submissions/)
判断1个数是否为2的x次方.

**Example 1:**
```
Input: 0
Output: false
```
**Example 2:**
```
Input: 16
Output: true
Explanation: 24 = 16
```
**Example 3:**
```
Input: 218
Output: false
```
## hints
```
    位运算
1.n >> 1 即 n / 2^1，即可去掉最低位
2.判断是否2的x次方，即最高位是1，其余位都是0
```
## Solution
``` c
bool isPowerOfTwo(int n) {
    if(!n) return false;

    while(n >> 1)
    {
        if(n&1) return false;
        n = n >> 1;
    }
    return true;
}
```