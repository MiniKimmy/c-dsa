## Max Profit

## CHINESE
在数组中,某个数字减去它的右边的数字得到一个数对之差。求所有数对之差的最大值.

**Example 1:**
```
Input: [2,4,1,16,7,5,11,9],
Output: 11
Explaination:16-5=11
```

## hints
```
    1.While traversing the array, find the left-max
    2.and meanwhile sale it each time if it can get better profit.
```

## Analogous
|                         Nav               |                Des              |
|:----------------------------------------:|:--------------------------------:|
|![maxProfit](../../../../leetcode/easy/122/maxProfit.md)|122.leetcode        |


## Solution
``` c
int getMaxProfit(int* nums, int numsSize)
{
    if (nums == NULL || numsSize <= 1) return 0;

    int max = nums[0] - nums[1] - 1;
    int buy = nums[0];
    for (int i = 1; i < numsSize; ++i) {
        if (buy - nums[i] > max) {
            max = buy - nums[i];
        }

        if (buy < nums[i]) {
            buy = nums[i];
        }
    }
    return max;
}
```