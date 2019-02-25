## 137. Single Number II
[这里](https://leetcode.com/problems/single-number-ii/)
相同的都是3个数字，唯一一个数字不是3个数字，找出这个唯一一个数字。

**Example 1:**
```
Input: [2,2,2,3]
Output: 3
```
**Example 2:**
```
Input: [-2,-2,1,1,-3,1,-3,-3,-4,-2]
Output: -4
```
## hints
```
累加每一个数的每一位,得到的结果是:(3*对应bit + 1)
ex: 2 2 2 3
  10
  10
  10
  11
+---
  41

因此 “s % 3” 得出‘3’对应位上多余的数，这个多余的数即是唯一那个不同的那个数字提供的。

1.考虑0~31位 (int 范围是[-2^31,2^31-1])
2.由于example 2 是负数输入源，因此移位可能会溢出
    (1).为了避免溢出,使用unsigned int 范围是[0,2^31]
    (2).这是针对负数输入源的问题，所以不能用 int
```

## Solution
``` c
int singleNumber(int* nums, int numsSize) {
    int n = numsSize;
    int ret = 0;
    for(int i = 0;i<32; ++i){
        // int s = 0; 不可以用int，
        unsigned int s = 0;
        for(int j = 0;j<n;++j){
            s += (nums[j] >> i) & 1;
        }

        ret += (s % 3) << i;
    }

    return ret;
}
```

## hints2
```
c#语言可以直接用int 而无需使用 “UInt32”
```
## Solution
``` csharp
public class Solution {
    public int SingleNumber(int[] nums) {
        int n = nums.Length;
        int ret = 0;

        for(int i = 0;i<32;++i){
            int s = 0;
            for(int j = 0; j < n; ++j){
                s += (nums[j] >> i) & 1;
            }

            ret += (s % 3) << i;
        }

        return ret;
    }
}
```