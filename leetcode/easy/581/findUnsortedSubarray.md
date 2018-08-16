## 581. Shortest Unsorted Continuous Subarray
Given an integer array, you need to find one continuous subarray that if you only sort this subarray in ascending order, then the whole array will be sorted in ascending order, too.

You need to find the shortest such subarray and output its length.

**Example 1:**
```
Input: [2, 6, 4, 8, 10, 9, 15]
Output: 5
Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the whole array sorted in ascending order.
```
**Note:**
Then length of the input array is in range [1, 10,000].
The input array may contain duplicates, so ascending order here means <= .

## hints
```
    [ContinuousArr1, ...DisContinuousArr ..., ContinuousArr2]
    1. ContinuousArr1 from [0] to [m] is ascending.
    2. DisContinuousArr from [m+1] to [m+n] is random order.
    3. ContinuousArr2 from [m+n+1] to [numsSize-1] is ascending.

    And we need to do is that
    1.mark the Arr1 the end pos --> posA
    2.mark the Arr2 the start pos --> posB
    3.find the maxValue && minValue from the DisContinuousArr --> max , min
    4.traverse the Arr1 to count the numbers of Arr1[i] < min. -->count_1
    5.traverse the Arr2 to count the numbers of Arr2[i] < max. -->count_2

    6. |_________________|_____________________|____________________|
       0                posA    ↑      ↑      posB               numsSize
                               max    min
        |_________________|_____________________|____________________|
     (0)↑--------↑                              ↑-------↑
          count_1                                 count_2

    7. So we need to change the length :【the solid line】

        |_________________|_____________________|____________________|
     (0)↑--------↑———————————————————————————————————————↑
          count_1                                 count_2
                 ↑-----------the--target-length----------↑

```

## Solution

``` c
int findUnsortedSubarray(int* nums, int numsSize) {
    if(nums==NULL || numsSize <=1) return 0;

    int pos = 0;
    for(int i = 1;i<numsSize;++i){
        if(nums[i-1]<=nums[i]){
            pos = i;
        }else{
            break;
        }
    }

    if(pos == numsSize-1) return 0;

    int postop = numsSize;
    int min = nums[numsSize-1];
    for(int i = numsSize-2;i>=pos;--i){
        if(nums[i] <= min && min>=nums[pos]){
            postop = nums[i] == min? postop:i;
            min = nums[i];
        }else{
            break;
        }
    }


    if(postop==numsSize){
        postop = numsSize-1;
    }

    int max = nums[postop];

    for(int i = pos+1; i<postop;++i){
        if(nums[i] < min){
            min = nums[i];
        }else if(nums[i] > max){
            max = nums[i];
        }
    }

    if(nums[0]>min && nums[numsSize-1] < max ) return numsSize ;

    int ret = 0;
    for(int i = 0;i<pos;++i){
        if(nums[i] <= min){
            ret++;
        }else{
            break;
        }
    }

    int result = pos+1-ret + postop-pos;
    ret = 0;
    int flag = 0;
    for(int i = postop;i<numsSize;++i){
        if(max > nums[i]){
            ret++;
            flag = 1;
        }else{
            break;
        }
    }

    return flag == 1?result + ret-1:result+ret;
}
```