## 22. 旋转数组的最小数字
[这里](https://www.acwing.com/problem/content/20/)
把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
输入一个升序的数组的一个旋转，输出旋转数组的最小元素。

**Note:**
* 数组内所含元素非负，若数组大小为0，请返回-1。

**Example**
```
Input:[2,2,2,0,1]
Output:0
Explanation:0是最小值
```

## hints
```
    遍历一遍，找到第一个不是单增不减的数即可。
```

## Solution
``` c
/*o(n)*/
int findMin(int* nums, int numsSize) {
    if(nums ==NULL || numsSize == 0) return -1;
    int ret = nums[0];
    for(int i = 1;i<numsSize;++i){
        if(nums[i] >= ret){
            continue;
        }else{
            return nums[i];
        }
    }
    return ret;
}
```
## hints2
```
1.二分找分界点
    (1).去除最右边与开头的相同val再二分
2.由于左右单调，所以如果非单调则一定存在答案.
```
## Solution2
```
/*最坏o(n), 最快log(n)*/
int findMin(int* nums, int numsSize) {
    if(!nums || numsSize<=0 ) return -1;

    int k = numsSize-1;
    while(k && nums[0] == nums[k]) k--;

    int l = 0; int r = k;
    while(l<r)
    {
        int mid = l + r >> 1; // [l,mid] [mid+1,r]
        if(nums[mid] < nums[r]) r = mid;
        else l = mid + 1;
    }
    return nums[l];
}
```