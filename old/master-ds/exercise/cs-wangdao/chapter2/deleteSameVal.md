## Delete Same Value Elements in Orderly array.

Given an orderly array,delete the same value elements.

## CHINESE
删除有序顺序表中所有值重复的元素,要求空间复杂度O(1),时间复杂度O(n)

**Example 1:**
```
Input: [1,2,2,2,2,2,2,2,3,4,5,6]
Output: [1,2,3,4,5,6]
```
**Example 2:**
```
Input:[-1,-2,-3,-3]
Output:[-1,-2,-3]
```

**Note**: Space Complexity: O(1);Time Complexity: O(n).

## hints
```
    ex:1,2,2,2,2,2,2,2,3,4,5,6
    1.j mark the different,
    2.when meet different, exchange as "1,3,2,2,2,2,2,2,4,5,6"
    3.finally:"1,3,4,5,6,2,2,2,2,2,2"
```

## Solution
``` c
void deleteSameVal(int* arr, int* arrSize){
    if (arr == NULL || arrSize == NULL) return;

    int j = 0;
    for (int i = 1; i < *arrSize; ++i) {
        if (arr[i] != arr[j]) {
            ++j;   //mark the different.
            arr[j] = arr[i];
        }
    }

    *arrSize = j;
}
```