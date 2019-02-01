## 68. 0到n-1中缺失的数字
[这里](https://www.acwing.com/problem/content/64/)
一个长度为n-1的递增排序数组中的所有数字都是唯一的，并且每个数字都在范围0到n-1之内。
在范围0到n-1的n个数字中有且只有一个数字不在该数组中，请找出这个数字。

**Example :**
```
Input:[0,1,2,4]
Output:3
```
## hints
```
    no hints.
```
## Solution
``` c
int getMissingNumber(int* nums, int numsSize) {
    if(nums== NULL || numsSize<=0) return 0;
    for(int i = 0;i<numsSize;++i){
        if(nums[i] != i){
            return i;
        }
    }
    return numsSize;
}
```