## 55. 连续子数组的最大和
[这里](https://www.acwing.com/problem/content/50/)
输入一个 非空 整型数组，数组里的数可能为正，也可能为负。
数组中一个或连续的多个整数组成一个子数组。
求所有子数组的和的最大值。

**Note:**
* 要求时间复杂度为O(n)

## hints
```
    1.前缀和思想
        (1).第[0]项默认=0
        (2).dp[i+1] = dp[i] + nums[i]
        (3).子段[a,b]的元素和:dp[b+1] - dp[a]
```

## Solution
``` c
int maxSubArray(int* nums, int numsSize) {

    int* dp = (int*)malloc(sizeof(int) * (numsSize+1));
    dp[0] = 0;
    int ret = nums[0];
    // 累加前缀和.默认dp[0]=0
    for(int i = 0;i<numsSize;++i){
        dp[i+1] = dp[i] + nums[i];
    }

    // 子数组的长度
    for(int i = 1;i<=numsSize;++i){

        // 当前长度下，查找该长度的子数组和的最大值
        for(int j = 0; j+i<=numsSize;++j)
        {
            int t = dp[i+j] - dp[j];
            if(ret < t) ret = t;
        }
    }

    free(dp);
    return ret;
}
```

## hints
```
    1.把一段数（在本题是一堆连续的数之和），看作一个数s
    2.s代表经历过在下标i之前得到的最大的sum
        (1).s : 表示这一堆"认为最大sum"总和的数是
            * 遍历的同时，每次记录最优的选择
        (2).s<0 s>0 s=0三种情况
            * s<0:加了一堆人，却是负数
                (1).如果全都是负数,那就s = x，而不是s += x
                (2).如果不全是负数,那么只把上一轮最优的保持即可
            * s>0:则 s+=x;
            * s==0:则可以合并为s<0的情况
        (3).ex:a b c d e] f g h
                       ↑
            (1).s=[abcde]的最佳选择
            (2).轮到f的时候，判断s目前的状况
                * if s<0，相当于选择max(s,f)
                * if s>0, 相当于选择max(s,s+f)
                * if s==0,相当于同化为第一种。
            (3).代码复杂度问题
                * 分析问题和写出来的时候会有点不同
                * 怎么好写就怎么方便，这个需要写过有习惯的，这个主要是能提高出错时候debug的速度
                * 按照思路模拟一遍代码也是可以的，这个主要是思路清晰
                * 想得出来、写的出来、不同的方式写出来、最优的方式写出来、规范地写出来
```

## Solution2
``` c
int max(int a, int b){
    return a>b?a:b;
}

int maxSubArray(int* nums, int numsSize) {
    int ret = nums[0]-1; // 随便定一个更小的数.最终结果起码会返回一个元素

    int s = 0;
    for(int i = 0;i<numsSize;++i)
    {
        if(s < 0) s = 0;
        s += nums[i];
        ret = max(ret,s);
    }

    return ret;
}
```