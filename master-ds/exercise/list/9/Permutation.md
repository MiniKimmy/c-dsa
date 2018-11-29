## Permutation

Given a int[], permutation it.

## CHINESE
对一个n个元素的数组全排列输出

**Example 1:**
```
Input :[1,2,3]
Output:
[1,2,3]
[1,3,2]
[2,1,3]
[2,3,1]
[3,1,2]
[3,2,1]
```

## hints
```
ex:1,2,3
    [1,    2,3]
    [1,    3,2]
     ↑
    [2,    1,3]
    [2,    3,1]
     ↑
    [3,    1,2]
    [3,    2,1]
     ↑
    split a little step:
    1.each time, exchange pos[0] and pos[i]
    2.and the rest elements "perm(arr,1,2)"

    3.then exchange const "0" as "p"
    4.exchange const "1" as "p+1"
    5.exchange const "2" as arrSize-1

    6.Be careful: when exchange pos[0] and pos[1],
    the next time, we need to exchange pos[0] and pos[2]
    it would meet chaos!!!
    Because we use the stable order "1,2,3" but not "2 3 1"!!
    so the next time,we change [0],[2] will become "1 3 2" but not "3 1 2"
    so we need to refresh it as "1,2,3" and then change pos[0],[2]--> "3,1,2"
```

## Solution
``` c
void swap(int* arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void traverseArray(int* arr, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void permutationInner(int* arr, int left, int right){

    if (left >= right) {
        traverseArray(arr, right + 1);
        return;
    }else{
        for (int i = left; i <= right; ++i) {
            swap(arr, left, i);
            permutationInner(arr, left + 1, right);
            swap(arr, left, i);
        }
    }
}

void permutation(int* arr, int n){
    if (arr == NULL || n <= 0) return;
    permutationInner(arr, 0, n - 1);
}
```

## Solution2
```
/*Store int** as return */

void swap(int* arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void permutationInner(int* arr, int left, int right, int** ret, int* count){
    if (left >= right) {
        int* item = (int*)malloc(sizeof(int) * (right + 1));
        for (int j = 0; j < right+1; ++j) {
            item[j] = arr[j];
        }
        (*ret)[(*count)] = item;   // must use "(*ret)[(*count)]" but not use “*ret[(*count)]”
        *count = *count + 1;
    }else{
        for (int i = left; i <= right; ++i) {
            swap(arr, left, i);
            permutationInner(arr, left + 1, right, ret, count);
            swap(arr, left, i);
        }
    }
}

int** permutation(int* arr, int n,int* returnSize){
    if (arr == NULL || n <= 0) return;
    int** ret = (int**)malloc(sizeof(int*) * 500);  // "500" is const.
    int count = 0;
    permutationInner(arr, 0, n - 1, &ret, &count);
    *returnSize = count;
    return ret;
}
```