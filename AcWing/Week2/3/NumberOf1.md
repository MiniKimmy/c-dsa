## 26. 二进制中1的个数
[这里](https://www.acwing.com/problem/content/25/)
输入一个32位整数，输出该数二进制表示中1的个数。

**Note:**
* 负数在计算机中用其绝对值的补码来表示。

**Example 1:**
```
Input:9
Output:2
Explanation: 9->1001, 有2个1
```
**Example 2:**
```
Input:-2
Output:31
Explanation: -2->11111111111111111111111111111110, 有31个1
```

## hints
```
    1.计算正整数里含有多少个1。像手写的“能相加就取1”
    2.负整数转化为正整数处理。返回时，当负整数的最低位为1的时候要+1。
```

## Solution
``` c
int getBit(int n){                   // 计算正整数里含有多少个1。像手写的“能相加就取1”
    int ret = 0;
    for(int i=31;i>=0;--i){
        long a = pow(2,i);
        if(a<=n){
            ret++;
            n -= a;
        }
    }
    return ret;
}

int NumberOf1(int n){
    if(n == -2147483648) return 1; // 特殊溢出情况处理

    if(n==0){                      // 0处理
        return 0;
    }else if(n>0){                 // 正整数处理
        return getBit(n);
    }else{
        int last = n & 0x01;       // 负整数转为正整数.返回时,当负整数的最低位为1的时候要+1。
        return last!=0? 32 - getBit(-n)+1: 32-getBit(-n);
    }
}
```