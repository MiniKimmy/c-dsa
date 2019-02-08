## 76. 和为S的连续正数序列
[这里](https://www.acwing.com/problem/content/description/72/)
输入一个正数s，打印出所有和为s的连续正数序列（至少含有两个数）。

**Example :**
```
Input:15
Output:[[1,2,3,4,5],[4,5,6],[7,8]]
Explanation:由于1+2+3+4+5=4+5+6=7+8=15，所以结果打印出3个连续序列1～5、4～6和7～8。
```

## hints
```
1.l和r同时在1开始，滑动窗口。
    * 根据不同情况移动左边界l或者右边界r
2.默认先移动右边界，同时累加
3.当累加的数比target大的时候移动左边界
4.在移动左边界的时候，同时累加的数减去左边界值
5.当累加的数等于target的时，同时实例化1维数组，Add到二维数组
    (1).[l,r]左右边界已确定，这个时候可轻松Add到二维数组里
    (2).同时，因为下一次累加肯定会超过target，所以手动在处理完添加到二维数组之后让左边界+1
        * 否则会一直出现sum=s的情况.
```

## Solution
``` c
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** findContinuousSequence(int sum, int** columnSizes, int* returnSize) {
    int** ret = (int**)malloc(sizeof(int*) * 1000);
    int index = 0;

    int start = 1; int end = 1;
    int s = 0;
    while(end*2-1 <= sum)   // example:"15 --> end = 8" : means 8*2-1=15
    {
        if(s<sum){
            s += end;
        }
        end++;

        while(s>sum){
            s -=start;
            start++;
        }

        if(s == sum){
            int len = end-start;
            (*columnSizes)[index] = len;
            int* item = (int*)malloc(sizeof(int) * len);

            for(int i = 0;i<len;++i){
                item[i] = i+start;
            }

            ret[index++] = item;

            // breake the balance
            s -=start;
            start++;
        }
    }

    *returnSize = index;
    return ret;
}
```