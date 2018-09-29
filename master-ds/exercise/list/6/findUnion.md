## Find all 2-group in array

## CHINESE
设计算法以求解从集合{1..n}中选取k（k<=n）个元素的所有组合。

**Example 1:**
```
Input: 4
Output:[{1,2},{1,3},{1,4},{2,3},{2,4},{3,4}]
Explanation:from int[1,2,3,4], selete each 2 elements collection.
```
**Example 2:**
```
Input:3
Output:[{1,2},{1,3},{2,3}]
```

## hints
```
    easy.
```

## Solution
``` c
int** findUnion(int n, int* returnColumn) {
    if(n <= 0 ) {
        *returnColumn = 0;
        return NULL;
    }

    int** ret = (int**)malloc(sizeof(int*) * 1000);
    int i = 1;
    int size = 0;
    while (i < n) {
        int j = i+1;
        while (j <= n) {
            int* group = (int*)malloc(sizeof(int) * 2);
            group[0] = i;
            group[1] = j;
            ret[size] = group;
            size++;
            j++;
        }
        i++;
    }

    *returnColumn = size;
    return ret;
}
```