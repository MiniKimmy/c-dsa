## 477. Total Hamming Distance
[这里](https://leetcode.com/problems/total-hamming-distance/)
汉明距是2个整数的二进制表示有不同的位的数量。

## hints
```
1.每个数的每个位都逐个看（总共[0,31]位，共32位）
    (1).假如第k位上，这个数组每个数该位是 ex:1 1 0 0 1
    (2).然后由于只是看‘1’与‘0’有多少组不同
    (3).因此第k位上的总距离= ‘1’的数量 * ‘0’的数量
2.即外层for一遍每一位[0,31]，内层for一遍数据源每个数。
```
## Solution
``` c
int totalHammingDistance(int* nums, int numsSize) {
    int res = 0;
    for(int i = 0 ; i < 31; ++i){
        int ones = 0;
        for(int j = 0; j < numsSize; ++j){
            if(nums[j] >> i & 1){
                ones++;
            }
        }
        res += (numsSize-ones) * ones;
    }

    return res;
}
```

## Solution
``` csharp
public class Solution {
    public int TotalHammingDistance(int[] nums) {

        int ret = 0;
        int n = nums.Length;

        for(int i = 30; i>=0;--i){
            int ones = 0;
            for(int j = 0; j< n;++j){
                if( (nums[j] >> i & 1) == 1){
                    ones++;
                }
            }
            ret += (n - ones) * ones;
        }

        return ret ;
    }
}
```