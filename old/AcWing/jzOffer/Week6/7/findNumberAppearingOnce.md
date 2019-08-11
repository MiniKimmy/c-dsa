## 74. 数组中唯一只出现一次的数字
[这里](https://www.acwing.com/problem/content/70/)

在一个数组中除了一个数字只出现一次之外，其他数字都出现了三次。
请找出那个只出现一次的数字。
你可以假设满足条件的数字一定存在。

**Note :**
* 要求只使用 O(n) 的时间和额外 O(1) 的空间

**Example :**
```
Input:[1,1,1,2,2,2,3,4,4,4]
Output:3
```

## hints
```
    1.qSort把相同的数堆在一起
    2.因为其余数字一定有3个，那么如果已经有2个的数字相等，那么这个数字比如是3个。
```
## Solution
``` c
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

int findNumberAppearingOnce(int* nums, int numsSize) {
    qSort(nums,0,numsSize-1);

    for(int i = 0;i<numsSize;++i){
        if(i < numsSize -1 && nums[i] == nums[i+1]){
            i +=2;
            continue;
        }
        int a = nums[i];
        int b = nums[i+1];
        int c = nums[i+2];
        return a == b?c:a==c?b:a;
    }
}

```