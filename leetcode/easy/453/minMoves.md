## 453. Minimum Moves to Equal Array Elements

Given a non-empty integer array of size n, find the minimum number of moves required to make all array elements equal, where a move is incrementing n - 1 elements by 1.

**Example:**
```
Input:
[1,2,3]

Output:
3

Explanation:
Only three moves are needed (remember each move increments two elements):

[1,2,3]  =>  [2,3,3]  =>  [3,4,3]  =>  [4,4,4]
```

## hints
```
    find the min of nums, and calc the distance between nums[i] - min.

    ex : [1,2,3,4]
    at first '1' is min, each other elements need to move 1 step, so we just need to assure the min add up to all the min level.

    [1,2,3,4] -> [2,2,4,5], then "2" is min now, which means step = 2-1
    [2,2,4,5] -> [3,3,4,6] -> [4,4,4,7] , then '4' is min now, which means step = 4-2 ...

    finally, [1,2,3,4] min steps = (2-1) + (4-2) + (7-4) = (2-1) + (3-1) + (4-1) = 6

```

## Solution
``` c
int minMoves(int* nums, int numsSize) {
    if(nums == NULL || numsSize == 0) return 0;

    int ret = 0;
    int min = nums[0];
    for(int i = 1;i<numsSize;++i){
        if(nums[i] < min){
            min = nums[i];
        }
    }

    for(int i = 0;i<numsSize;++i){
        ret = ret + nums[i] - min;
    }
    return ret;
}

```