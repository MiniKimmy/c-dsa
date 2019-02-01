## 73. 数组中只出现一次的两个数字
[这里](https://www.acwing.com/problem/content/69/)

一个整型数组里除了两个数字之外，其他的数字都出现了两次。
请写程序找出这两个只出现一次的数字。
你可以假设这两个数字一定存在。

**Example :**
```
Input:[1,2,3,3,4,4]
Output:[1,2]
```
## hints
```
    1.qSort把相同的数放在一堆
    2.for一遍来找
```

## Solution
``` c
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

void swap(int* arr,int i,int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void qSort(int* arr, int l, int r)
{
    if(l > r) return ;
    int i = l + 1; int j = r; int temp = arr[l];
    while(true){
        while(i<=r && arr[i] <= temp) ++i;
        while(j>=l+1 && arr[j] > temp) --j;
        if(i>j) break;
        swap(arr,i,j);
        ++i;
        --j;
    }

    swap(arr,l,j);
    qSort(arr,l,j-1);
    qSort(arr,j+1,r);
}

int* findNumsAppearOnce(int* nums, int numsSize, int* returnSize) {
    qSort(nums,0,numsSize-1);
    *returnSize = 2;
    int* ret = (int*)malloc(sizeof(int) * 2);
    int index = 0 ;
    for(int i = 0;i<numsSize;++i){
        if(i < numsSize-1 &&  nums[i] == nums[i+1]) {
            i++;
            continue;
        }
        ret[index++] = nums[i];
        if(index == 2) break;
    }

    return ret;
}
```