## Remove range of array

Delete array's elements whose value is in range[s,t].

## CHINESE
删除顺序表中定值在s与t之间的所有元素,要求空间复杂度O(1),时间复杂度O(n)

**Example 1:**
```
Input: [1,2,3,4,5,6],2,5
Output: [1,6]
```
**Example 2:**
```
Input:[-1,2,3,-4,5,-3], -3,0
Output:[2,3,-4,5]
```

**Note**: Space Complexity: O(1);Time Complexity: O(n)

## hints
```
    1.traverse the array.
    2.use temp-index, let the target element put forward.
```

## Solution
``` c
void removeArrRange(int* arr, int* arrSize, int s, int t){
    int j = 0;
    for (int i = 0; i < *arrSize; ++i) {
        if (!(arr[i]>=s && arr[i] <= t) ) {
            arr[j] = arr[i];
            j++;
        }
    }

    *arrSize = j;
}
```