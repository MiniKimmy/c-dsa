## 52. 数组中出现次数超过一半的数字
[这里](https://www.acwing.com/problem/content/description/48/)

数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。
假设数组非空，并且一定存在满足条件的数字。

**Note**
* 要求只能使用 O(n) 的时间和额外 O(1) 的空间

**Example :**
```
Input:[1,2,1,1,3]
Output:1
```
## hints
```
    1.qsort
    2.遍历一遍,查找数量最多的项
    3.因为排序好了之后，不同的两段数字只会出现一次分界
```

## Solution
``` c
void swap(int* arr,int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void quickSort(int* arr, int l, int r)
{
    if(l > r) return;
    int i = l+1; int j = r;
    int temp = arr[l];

    while(true){
        while(i<=r && arr[i] >= temp) ++i;
        while(j>=l && arr[j] < temp) --j;
        if(i>j) break;
        swap(arr,i,j);
        ++i;
        --j;
    }
    swap(arr,l,j);
    quickSort(arr,l,j-1);
    quickSort(arr,j+1,r);
}

int moreThanHalfNum_Solution(int* nums, int numsSize) {

    int n = numsSize;
    quickSort(nums,0,n-1);

    int index = 0;
    int count = 0;

    for(int i = 0;i<n;++i){
        if(nums[i] == nums[index]){
            count++;
        }else{
            index = i;
            count = 1;
        }
        if(count > n/2) {
            return nums[i];
        }
    }

    /* “出现次数超过半数”也等价于出现次数最多的数字
    int index = 0;
    int count = 0;
    int max = -1;
    int maxIndex = -1;
    for(int i = 0;i<n;++i){
        if(nums[i] == nums[index]){
            count++;
        }else{
            index = i;
            count = 1;
            index = i;
        }
        if(count > max) {
            max = count;
            maxIndex = index;
        }
    }

    return nums[maxIndex];
    */
}
```

## hints
```
    * 非黑即白
    * 因为超过半数，所以答案的数量一定能掩盖“非答案”的数量
    * 在count数量为0的时候去转化val对象即可.
```
## Solution
``` c
int moreThanHalfNum_Solution(int* nums, int numsSize) {
    int count = 0;
    int val = -1;

    for(int i = 0;i<numsSize;++i){
        if(val == nums[i]){
            count++;
        }else{
            if(count) count--; //非零就--
            else{
                count = 1;
                val = nums[i];
            }
        }
    }

    return val;
}
```