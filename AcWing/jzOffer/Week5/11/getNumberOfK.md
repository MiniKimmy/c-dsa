## 67. 数字在排序数组中出现的次数
[这里](https://www.acwing.com/problem/content/63/)
统计一个数字在排序数组中出现的次数。

**Example :**
```
Input:[1, 2, 3, 3, 3, 3, 4, 5] ,  3
Output:4
Explanation:由于3在这个数组中出现了4次，因此输出4。
```
## hints
```
    no hints
```
## Solution
``` c
int getNumberOfK(int* nums, int numsSize, int k) {
    if(!nums || numsSize <=0 ) return 0;

    int ret = 0;
    for(int i = 0;i<numsSize;++i)
    {
        if(nums[i] == k){
            ret++;
        }
    }
    return ret;

}
```