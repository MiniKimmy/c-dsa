## 201. Bitwise AND of Numbers Range
[这里](https://leetcode.com/problems/bitwise-and-of-numbers-range/)
对[l,r]范围内所有数都&一遍

## hints
```
1.由于[m,n]范围的数据量很大，而&运算特点是只有全1才是1
2.因此先从m开始剔除一部分
    (1).把m作为起点，而n作为判断是否在范围内的标准
    (2).m只有它的二进制里有'1'的位才有可能结果&之后=1
    (3).然后进一步判断，在[m,n]范围内，该位是否可能存在‘0’的可能
3.判断[m,n]的范围的某一位上是否包含‘0’
    (1).因为每个数都比m大，按照一点点叠加++的思维，该位进位之后的最小的那个数要在[m,n]范围内，就会产生‘0’
    (2).简单点就，假如第k位
        (1).比k位高的位保持不动
        (2).比k位低的位全清0
        (3).然后第k位自身进位+1
        (4).得到的这个结果与n比较，比n大则表示不可能产生‘0’。

EX:
假如判断‘↓’的这位上是否可能产生‘0’，处于[m,n]范围。
                ↓
   m   = 101100110011
                ↓
target → 101101000000

  Step:* 000000010000
       * 000000001111
       * 111111110000
       * m & 111111110000
        = 101100110011
        & 111111110000
       *= 101100110000
```

## Solution
``` c
int rangeBitwiseAnd(int m, int n) {
    int res = 0;
    for(int i = 0; (1ll << i) <= m; i++ ){
        if(m >> i & 1){
            if((m & ~((1 << i) - 1ll)) + (1 << i) > n)
                res += 1 << i;
        }
    }
    return res;
}
```

## Solution
``` csharp
public class Solution {
    public int RangeBitwiseAnd(int m, int n) {
        int ret = 0;
        for(int i = 0; (1L << i) <= m; ++i){
            if((m >> i & 1) == 1){
                if(((m & (~((1L << i) - 1))) + (1 << i)) > n )
                    ret += 1 << i;
            }
        }
        return ret;
    }
}
```