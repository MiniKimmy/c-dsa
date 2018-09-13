## Find target in ascending Array

Given a ascending array, find "x" <br />
1.if "x" find ok, swap the next index with "x" unless "x" is the end of the array. <br />
2.if "x" can't find, insert "x" to the array and keep ascending order. <br />

## CHINESE
给定一个升序线性表(a1,a2,a3,…,an),用最少时间在表中查找数值为x的元素。<br />
(1)若找到将其与后继元素位置相交换,若是最后一个位置则不需要交换。<br />
(2)若找不到将其插入表中并使表中元素仍递增有序。<br />

**Example 1:**
```
Input:[1,2,3,4,5],x=2
OutPut:[1,3,2,4,5]
```
**Example 2:**
```
Input:[1,2,3,4,5],x=5
OutPut:[1,2,3,4,5]
```
**Example 3:**
```
Input:[1,2,3,4,5],x=6
OutPut:[1,2,3,4,5,6]
```
**Example 4:**
```
Input:[1,2,3,4,5],x=0
OutPut:[0,1,2,3,4,5]
```

## hints
```
    binarySearch + mark position.
    1.normal binarySearch and mark the final index.
    2.if it can't find, malloc new Array
    and for(0 to pos) && pos && for(pos+1 to arrsize+1) as 3 situation to copy old array.
```

## Analogous
|                         Nav            |                   Des                 |
| :-------------------------------------:|:-------------------------------------:|
| ![putMinusForward](putMinusForward.md) |把负数放在正数前面                     |
| ![putOddForward](putOddForward.md)     |把偶数放在奇数前面                     |

## Solution
``` c
void swap(int* arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int binarySearchHelper(int* arr, int left, int right, int x, int* resultIndex) {
    if (left > right) return left;
    int mid = left + (right - left) / 2;

    if (arr[mid] == x)  *resultIndex = mid;
    else if (arr[mid] > x) binarySearchHelper(arr, left, mid - 1, x, resultIndex);
    else binarySearchHelper(arr, mid + 1, right, x, resultIndex);
}

int* binarySearch(int* arr, int arrsize, int x,int* returnSize) {
    int resultIndex = -1;
    int pos = binarySearchHelper(arr, 0, arrsize - 1, x, &resultIndex);

    if (resultIndex != -1) {
        if (resultIndex != arrsize - 1) {
            swap(arr, resultIndex, resultIndex + 1);
        }
    }else {
        int* ret = (int*)malloc(sizeof(int) * (arrsize + 1));

        for (int i = 0; i < pos; ++i) {
            ret[i] = arr[i];
        }
        ret[pos] = x;
        for (int i = pos+1; i < arrsize + 1; ++i) {
            ret[i] = arr[i-1];
        }

        *returnSize = arrsize + 1;
        return ret;
    }

    *returnSize = arrsize;
    return arr;
}

```