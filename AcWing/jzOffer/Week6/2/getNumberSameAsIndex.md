## 69. 数组中数值和下标相等的元素
[这里](https://www.acwing.com/problem/content/description/65/)
假设一个单调递增的数组里的每个元素都是整数并且是唯一的。
请编程实现一个函数找出数组中任意一个数值等于其下标的元素。

**Example :**
```
Input:[-3, -1, 1, 3, 5]
Output:3
Explanation:[-3, -1, 1, 3, 5]中，数字3和它的下标相等。
```
## hints
```
    no hints
```
## Solution
``` c
int getNumberSameAsIndex(int* nums, int numsSize) {
    for(int i = 0;i<numsSize;++i){
        if(i == nums[i]) return i;
    }
    return -1;
}
```