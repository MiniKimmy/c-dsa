## Find Median

Given two ascending arrays, find the pos “[n/2 - 1]” of arr1+arr2.

## CHINESE
一个长度为L(L>1)的升序序列,处于L/2（取上限）位置的数称为中位数.
试设计一个时间和空间两方面都尽可能高效率的算法,找中位数.

**Example 1:**
```
Input:
[11,13,15,17,19]
[2,4,6,8,20]

Output: 11
```

## hints
```
    1.merge as an whole arr.
    2.return arr[size/2-1]
```

## Solution
``` c
int getMedian(int* nums1, int num1Size, int* nums2,int num2Size){

    int size = num1Size + num2Size;
    int* arr = (int*)malloc(sizeof(int) * size);

    int left = 0;
    int right = 0;
    int index = 0;
    for (int i = 0; left < num1Size && right< num2Size; ++i) {
        if (nums1[left] > nums2[right]) {
            arr[index++] = nums2[right++];
        }else {
            arr[index++] = nums1[left++];
        }
    }

    if (left >= num1Size) {
        for (int i = right; i < num2Size; ++i) {
            arr[index++] = nums2[i];
        }
    }else {
        for (int i = left; i < num1Size; ++i) {
            arr[index++] = nums1[i];
        }
    }

    int ret = arr[size / 2 - 1];
    free(arr);
    return ret;
}
```