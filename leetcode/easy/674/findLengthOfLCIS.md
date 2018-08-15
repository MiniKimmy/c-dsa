## 674.Longest Continuous Increasing Subsequence

Given an unsorted array of integers, find the length of longest continuous increasing subsequence (subarray).

**Example 1:**
```
Input: [1,3,5,4,7]
Output: 3
Explanation: The longest continuous increasing subsequence is [1,3,5], its length is 3.
Even though [1,3,5,7] is also an increasing subsequence, it's not a continuous one where 5 and 7 are separated by 4.
```
**Example 2:**
```
Input: [2,2,2,2,2]
Output: 1
Explanation: The longest continuous increasing subsequence is [2], its length is 1.
```
**Note:** Length of the array will not exceed 10,000.

## hints
```
    countNum and get the maxCount.

    when it occurs discontinuous, clear the COUNT and predicate it is max or not.
    Caution: when come the last num, we need to judge if it is really put in the COUNT.
```

## Solution

``` c

int findLengthOfLCIS(int* nums, int numsSize) {
    if(nums == NULL || numsSize == 0) return 0;

    int window = 1;
    int ret = 1;
    for(int i = 1;i<numsSize;++i){
        if(nums[i-1]<nums[i]){
            window++;
        }else{
            if(ret<window){
                ret = window;
            }
            window = 1;
        }
    }

    return window>ret?window:ret;
}

```