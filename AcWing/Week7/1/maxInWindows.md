## 79. 滑动窗口的最大值
[这里](https://www.acwing.com/problem/content/75/)
给定一个数组和滑动窗口的大小，请找出所有滑动窗口里的最大值

**Example :**
```
Input:[2, 3, 4, 2, 6, 2, 5, 1] , k=3
Output:[4, 4, 6, 6, 6, 5]
```

## hints
```
1.首次先找做一轮，在第一个窗口内找出max.并且记录下标
2.滑动的时候
    (1).如果max还在窗口内则只需要比较nums[i]与max
    (2).如果max不在窗口内的话，则重新for一遍找max
```
## Solution
``` c
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

int* maxInWindows(int* nums, int numsSize, int k, int* returnSize) {
    int max = -1;
    int flag = -1;
    for(int i = 0;i<k;++i){
        if(max < nums[i]) {
            max = nums[i];
            flag = i;
        }
    }

    int* ret = (int*)malloc(sizeof(int)* (numsSize-k+1));
    int index = 0;
    ret[index++] = max;

    for(int i = k;i<numsSize;++i)
    {
        //printf("flag=%d,i-k=%d,max=%d\n",flag,i-k,max);
        if(flag == i-k){
            max = nums[i];
            flag = i;
            for(int j = i-k+1;j<i;++j){
                if(max < nums[j]) {
                    max = nums[j];
                    flag = j;
                }
            }

        }
        else if(max < nums[i]){
             max = nums[i];
             flag = i;
        }
        ret[index++] = max;
    }

    *returnSize = index;
    return ret;
}
```