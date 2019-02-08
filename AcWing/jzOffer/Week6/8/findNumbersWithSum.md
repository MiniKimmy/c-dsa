## 75. 和为S的两个数字
[这里](https://www.acwing.com/problem/content/71/)

输入一个数组和一个数字s，在数组中查找两个数，使得它们的和正好是s。
如果有多对数字的和等于s，输出任意一对即可。
你可以认为每组输入中都至少含有一组满足条件的输出。

**Example :**
```
Input:[1,2,3,4] , sum=7
Output:[3,4]
```

## hints
```
    1.qSort将数组有小到大
    2.然后用指针，两边夹出sum
```

## Solution
``` c
/**
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

int* findNumbersWithSum(int* nums, int numsSize, int target) {
    qSort(nums,0,numsSize-1);
    int i = 1; int j = numsSize-1;
    while(nums[j]>=target) j--;

    while(i<j){
        int res = nums[j] + nums[i];
        if(res == target){
            int* ret = (int*)malloc(sizeof(int) * 2);
            ret[0] = nums[i];
            ret[1] = nums[j];
            return ret;
        }

        if(res < target) ++i;
        else --j;
    }

}
```