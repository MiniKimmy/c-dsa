## 260. Single Number III
[这里](https://leetcode.com/problems/single-number-iii/)
只有2个数字是出现1次，找出这2个数字

## hints
```
1.因为答案只有2个数a和b，所以全部异或一遍得到 a ^ b
    (1).因为a != b，所以会a ^ b 肯定有不同的位
    (2).找出某个位不同，异或运算（不同=1，相同=0），所以找出“某个位上=1”的那个位
2.重新for一遍全部数，根据这个“位”来作区分“a”和“b”
3.最后的结果会得到a 或者 b
4.然后基于 s1=a^b; s2 = a; 求b，即再一遍异或，异或会把相同的数消掉：a ^ b ^ a = b
```
## Solution
``` c
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

int* singleNumber(int* nums, int numsSize, int* returnSize) {
    int s = 0;
    for(int i = 0;i<numsSize;++i) s ^=nums[i];

    int k = 0;
    while(!(s >> k & 1) ) ++k;

    int s2 = 0;
    for(int i = 0;i<numsSize;++i)
        if( nums[i]>>k & 1 ) s2 ^= nums[i];

    /*
        s = a ^ b;
        ret[0] = s2 = a;
        ret[1] = s ^ s2 = a ^ b ^ a = b;
    */

    *returnSize = 2;
    int* ret = (int*)malloc(sizeof(int) * 2);
    ret[0] = s2;
    ret[1] = s ^ s2;
    return ret;
}
```

## Solution
``` csharp
public class Solution {
    public int[] SingleNumber(int[] nums) {
        int s = 0;
        for(int i = 0;i<nums.Length;++i) s ^= nums[i];

        int k = 0;
        while(( s >> k & 1) == 0) ++k;

        int s2 = 0;
        for(int i = 0; i<nums.Length; ++i){
            if((nums[i] >> k & 1) == 1){
                s2 ^= nums[i];
            }
        }

        return new int[2]{s^s2,s2};
    }
}
```