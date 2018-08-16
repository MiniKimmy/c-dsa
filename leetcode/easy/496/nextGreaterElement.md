 ## 496 Next Greater Element I

You are given two arrays (without duplicates) nums1 and nums2 where nums1’s elements are subset of nums2. Find all the next greater numbers for nums1's elements in the corresponding places of nums2.

The Next Greater Number of a number x in nums1 is the first greater number to its right in nums2. If it does not exist, output -1 for this number.

**Example 1:**
```
Input: nums1 = [4,1,2], nums2 = [1,3,4,2].
Output: [-1,3,-1]
Explanation:
    For number 4 in the first array, you cannot find the next greater number for it in the second array, so output -1.
    For number 1 in the first array, the next greater number for it in the second array is 3.
    For number 2 in the first array, there is no next greater number for it in the second array, so output -1.
```
**Example 2:**
``
Input: nums1 = [2,4], nums2 = [1,2,3,4].
Output: [3,-1]
Explanation:
    For number 2 in the first array, the next greater number for it in the second array is 3.
    For number 4 in the first array, there is no next greater number for it in the second array, so output -1.
```

## hints
```
    find the target nums[i]'s right, means we need to find the nums[i] == nums[j] first,
    and then start to compare the right Element which is first greater than this nums[i].
    So set a flag when it can start to compare or not.
```

## Solution

``` c
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* nextGreaterElement(int* findNums, int findNumsSize, int* nums, int numsSize, int* returnSize) {
    int* ret = (int*)malloc(sizeof(int) * findNumsSize);
    *returnSize = findNumsSize;

    for(int i =0;i<findNumsSize;i++){
        ret[i] = -1;
        int flag = 0;
            for(int j =0;j<numsSize;j++){
                if(flag == 1){
                    if(findNums[i]<=nums[j]){
                        ret[i] = nums[j];
                        break;
                    }
                }
            if(findNums[i] == nums[j]){
                flag = 1;
            }
        }
    }
    return ret;
}
```