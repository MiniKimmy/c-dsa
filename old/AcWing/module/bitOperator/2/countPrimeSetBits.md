## 762. Prime Number of Set Bits in Binary
[这里](https://leetcode.com/problems/prime-number-of-set-bits-in-binary-representation/)

**Example 1:**
```
Input: L = 6, R = 10
Output: 4
Explanation:
6 -> 110 (2 set bits, 2 is prime)
7 -> 111 (3 set bits, 3 is prime)
9 -> 1001 (2 set bits , 2 is prime)
10->1010 (2 set bits , 2 is prime)
Explanation:6的二进制是110,有2个‘1’，而2不是素数。即找出[L,R]出现的数，这些数字的二进制形式里有‘1’的数量，若这个数量是素数则符合，累加这个区间二进制形式时素数的个数。
```
## hints
```
1.for一遍每一个数，统计它的二进制表示有多少个‘1’
2.判断素数，符合则累加+1
```
## Solution
``` c
#include<math.h>

bool isPrime(int n) {
    if(n <= 1) return false;
    int len = sqrt(n);

    for(int i = 2;i<=len;++i){
        if(!(n % i)) return false;
    }

    return true;
}

int countPrimeSetBits(int L, int R) {
    int ret = 0;
    for(int i = L;i<=R;++i){

        int s = 0;
        for(int k = i;k; k >>= 1) s += k & 1;
        if(isPrime(s)) ret++;
    }
    return ret;
}
```
## hints2
```
1.由于本题的素数不是[L,R]，而是它们二进制有多少个1，再判断是否为素数
    (1).而且数据量是10^6 = 100W，即100W < 2^20
    (2).所以最多只会有20个1
    (3).因此可以用HashSet<int>来先保存好20以内的素数，O(1)判断是否为素数
2.当然，可以直接写一个方法代替HashSet<int>
即 return x == 2 | x==3 | x==5 .. | x==19;
```
## Solution2
``` csharp
public class Solution {
    public int CountPrimeSetBits(int L, int R) {
        HashSet<int> prime = new HashSet<int>(){
          2,3,5,7,11,13,17,19
        };

        int ret = 0;
        for(int i = L;i<=R;++i)
        {
            int s = 0;
            for(int k = i; k > 0; k >>= 1) s += k & 1;
            if(prime.Contains(s) == true) ret++;
        }
        return ret;
    }
}
```