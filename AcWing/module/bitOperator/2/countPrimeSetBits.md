
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
    (1).而且数据量是100W，即小于2^20
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