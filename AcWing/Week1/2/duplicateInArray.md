## 14.不修改数组找出重复的数字
[这里](https://www.acwing.com/problem/content/15/)
给定一个长度为 n+1 的数组nums，数组中所有的数均在 1~n 的范围内，其中 n≥1。请找出数组中任意一个重复的数，但不能修改输入的数组。

Example:**
```
Input:[2, 3, 5, 4, 3, 2, 6, 7]
Output:2 或 3。
```
**Follow up:**如果只能使用 O(1)的额外空间，该怎么做呢？

## hints
```
    如果不能创建额外的空间的话，冒泡查找？？
```

## Solution
``` c
/*O(n²) too slow */
int duplicateInArray(int* nums, int numsSize){
    for(int i = 0;i<numsSize;++i){
        for(int j = i+1;j<numsSize;++j){
            if(nums[i] == nums[j]) return nums[i];
        }
    }
    return -1;
}
```

