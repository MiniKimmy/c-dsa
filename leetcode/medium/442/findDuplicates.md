## 442.Find All Duplicates in an Array

Given an array of integers, 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and others appear once.
<br />
Find all the elements that appear twice in this array.
<br />
Could you do it without extra space and in O(n) runtime?
<br />
**Example 1:**
```
Input:
[4,3,2,7,8,2,3,1]

Output:
[2,3]
```
**Example 2:**
```
Input:
[4,3,3,2,10,10,2,3,1]

Output:
[2,3,3,10]
```

## hints
```
    1.hash num(0~max)
    2.appears twice and more than twice, add to ret[]
```

## Solution
``` c
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

int* findDuplicates(int* nums, int numsSize, int* returnSize) {
    if(nums == NULL) {
        *returnSize = 0;
        return NULL;
    };

    int max = 0;
    for(int i = 0;i<numsSize;i++){
        if(nums[i]>max) max = nums[i];
    }

    int* hash = (int*)malloc(sizeof(int) * (max+1) );
    int* ret = (int*)malloc(sizeof(int) * numsSize);
    for(int i = 0;i<max+1;i++){
        hash[i] = 0;
    }

    int len = 0;
    for(int i = 0;i<numsSize;i++){
        if(hash[nums[i]] == 0){
            ++hash[nums[i]];
        }else{
            ret[len++] = nums[i];
        }
    }

    free(hash);
    *returnSize = len;
    return len==0?NULL:ret;
}
```