## 209.Minimum Size Subarray Sum

Given an array of n positive integers and a positive integer s, find the minimal length of a contiguous subarray of which the sum ≥ s. If there isn't one, return 0 instead.

Example:
```
Input: s = 7, nums = [2,3,1,2,4,3]
Output: 2
Explanation: the subarray [4,3] has the minimal length under the problem constraint.
```

## hints
```
    slide-window. [dynamic-size]
    1.window size from 0 as beginning, and size=0 means that left and right start at "0".
    2.window has its left-side and its right-size, and size == right-left.
    3.so we need to use left-right pointer to describe.
    4.at first,right-pointer move, which means enlarge window size.
    5.then according to the condition, left-pointer move, which means shrinkage window size.
```

## Solution
``` c
int getMin(int a, int b){ return a>b?b:a; }

int minSubArrayLen(int s, int* nums, int numsSize) {
    int left = 0;
    int right = 0;
    int sum = 0;
    int min = INT_MAX;

    while(right<numsSize){
        sum += nums[right++]; //cause the last time "right++" so "current-right" hasn't handle.
        while(right<numsSize && sum < s)
            sum += nums[right++];

        while(left<right && sum - nums[left] >= s)
            sum -= nums[left++];

        if(sum >= s) min = getMin(min,right-left);
    }

    return min == INT_MAX?0:min;

}
```