## Get min num of Array

## CHINESE
给定一个n(n≥1)的整数数组,求出数组中未出现的最小正整数.

**Example 1:**
```
Input :[-5,3,2,3]
Output:1
```
**Example 2:**
```
Input :[1,2,3]
Output:4
```

## hints
```
    1.buffer[]-->mark val∈[1,n]
    2.Traverse buffer[] once again, and check the marks.
```

## Solution
``` c
int getMinPositityNum(int* arr, int n){
    if (arr == NULL || n <= 0) return -1;

    int* buffer = (int*)malloc(sizeof(int) * n); //返回值一定在[1,n]之内
    for (int i = 0; i < n; ++i) {
        buffer[i] = 0;
    }

    for (int i = 0; i < n; ++i) {
        if (arr[i] > 0 && arr[i] <= n) {
            buffer[arr[i] - 1] = 1;  //记录出现在[1,n]范围之内的数
        }
    }

    for (int i = 0; i < n; ++i) {
        if (buffer[i] == 0) {   //一旦遇到未标记的数,就返回它
            free(buffer);
            return i+1;
        }
    }

    return n+1;
}
```