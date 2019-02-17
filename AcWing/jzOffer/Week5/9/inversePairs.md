## AcWing 65. 数组中的逆序对
[这里](https://www.acwing.com/problem/content/61/)
在数组中的两个数字如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。
输入一个数组，求出这个数组中的逆序对的总数。

**Example :**
```
Input:[1,2,3,4,5,6,0]
Output:6
```
## hints
```
    o(n²):冒泡。
```
## Solution
``` c
/*o(n²) */
int inversePairs(int* nums, int numsSize) {
    if(!nums || numsSize <= 0) return 0;

    int ret = 0;
    for(int i = 0;i<numsSize;++i){
        for(int j = i+1;j<numsSize;++j){
            if(nums[j] < nums[i]) ret++;
        }
    }
    return ret;
}
```