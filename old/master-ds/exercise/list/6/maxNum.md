## Recusive maximun

Given a int[], find max element with recusion.

## CHINESE
设整数序列a1,a2,…,an，给出求解最大值的递归程序。

## Solution
``` c
int maxNumInner(int* arr, int size,int count, int max) {

    if (count == size) return max;
    max = arr[count] > max ? arr[count] : max;
    return maxNumInner(arr, size, count + 1, max);
}

int maxNum(int* arr, int size) {
    if (arr == NULL || size <= 0) return 0;
    return maxNumInner(arr, size, 0,arr[0]-1);
}
```