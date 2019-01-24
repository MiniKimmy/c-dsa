## 13.找出数组中重复的数字
[这里](https://www.acwing.com/problem/content/14/)
给定一个长度为 n 的整数数组 nums，数组中所有的数字都在 0~n−1
的范围内。数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。

**Notice:**
1.如果某些数字不在 0~n−1的范围内，
2.或数组中不包含重复数字，则返回 -1

## hints
```
    1.出现的次数映射到hash记录
    2.返回结果只需要任意一个，所以出现次数>=2就立刻返回
    3.注意判断大小0~n-1的范围才记录
```

## Solution
``` c
int duplicateInArray(int* nums, int numsSize){
    int* hash = (int*)malloc(sizeof(int) * numsSize);
    for(int i = 0;i<numsSize;++i) hash[i] = 0;

    for(int i = 0;i<numsSize;++i){
        if(nums[i]>= numsSize || nums[i] < 0) return -1;
        hash[nums[i]]++;
    }

    for(int i = 0;i<numsSize;++i){
        if(hash[i] >= 2) return i;
    }

    return -1;
}
```