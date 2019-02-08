## 22. 旋转数组的最小数字
[这里](https://www.acwing.com/problem/content/20/)
把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
输入一个升序的数组的一个旋转，输出旋转数组的最小元素。

例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。
数组可能包含重复项。

**Note:**数组内所含元素非负，若数组大小为0，请返回-1。

**Example**
```
Input:[2,2,2,0,1]
Output:0
```

## hints
```
    遍历一遍，找到第一个不是单增不减的数即可。
```

## Solution
``` c
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