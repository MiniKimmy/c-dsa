## 53. 最小的k个数
[这里](https://www.acwing.com/problem/content/49/)
输入n个整数，找出其中最小的k个数。

**Example :**
```
Input:[1,2,3,4,5,6,7,8] , k=4
Output:[1,2,3,4]
```

## hints
```
    直接快排.
```

## Solution
``` c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
void swap(int* arr, int i,int j){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void quickSort(int* arr, int l, int r)
{
    if(l >= r) return ;

    int i = l+1;
    int j = r;
    int temp = arr[l];

    while(true) {
        while(i <= r && arr[i] < temp) ++i;
        while(j >= l+1 && arr[j] >= temp) --j;
        if(i > j) break;
        swap(arr,i,j);
        ++i;
        --j;
    }

    swap(arr, l, j);   // 出来之后再和left交换一次
    quickSort(arr,l,j-1);
    quickSort(arr,j+1,r);
}

int* getLeastNumbers_Solution(int* input,int lengthofinput, int k) {
    int n = lengthofinput;
    if(n == 0 || input == NULL) return NULL;

    quickSort(input, 0, n-1);
    int* ret = (int*)malloc(sizeof(int) * k);
    for(int i = 0;i<k;++i){
        ret[i] = input[i];
    }

    return ret;
}
```