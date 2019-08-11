## Exchange the inner sequency.

Given an array with m+n elements with {am} and {bn} orderly by {a1,a2,...,am,b1,b2,...,bn},

and needed to exchange it from {am,bn} to {bn,am}.

So finally return {b1,b2,...,bn,a1,a2,...am}.

## CHINESE
已知A[m+n]存放2个序列am,bn,(a1,a2,...,am,b1,b2,...,bn),交换2个序列变成(b1,b2,...,bn,a1,a2,...am),要求空间复杂度O(1),时间复杂度O(n)

**Example 1:**
```
Input: [1,2,3,4,5,6],3,3
Output: [4,5,6,1,2,3]
```
**Example 2:**
```
Input:[-1,-2,-3,-3,-2,5,6],3,4
Output:[-2,-5,6,-1,-2,-3,-3]
```

**Note**: Space Complexity: O(1);Time Complexity: O(n).

## hints
```
    reverse array.
    ex:1234abcd
    1.dcba4321
    2.abcd|1234
```

## Solution
``` c
void exchangeArr(int* nums, int m, int n){
    if(nums == NULL) return;

    int arrSize = m + n;
    for (int i = 0; i < arrSize / 2; ++i) {
        int temp = nums[i];
        nums[i] = nums[arrSize - 1 - i];
        nums[arrSize - 1 - i] = temp;
    }

    for (int i = 0; i < n / 2; ++i) {
        int temp = nums[i];
        nums[i] = nums[n - 1 - i];
        nums[n - 1 - i] = temp;
    }

    for (int i = 0; i < m / 2; ++i) {
        int temp = nums[n+i];
        nums[n+i] = nums[arrSize - 1 - i];
        nums[arrSize - 1 - i] = temp;
    }
}
```