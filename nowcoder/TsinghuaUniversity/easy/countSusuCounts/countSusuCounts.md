## 质因数的个数
求正整数N(N>1)的质因数的个数。
相同的质因数需要重复计算。如120=2*2*2*3*5，共有5个质因数。

## Input:
可能有多组测试数据，每组测试数据的输入是一个正整数N，(1<N<10^9)。

## Output:
对于每组数据，输出N的质因数的个数。

**Example 1:**
```
input
120

output
5
```

## hints
```
    Like "Susu" use <=Sqrt(N)

    And we can conclude that i start from 2 ~ Sqrt(N),
    when i=2, i=3 , we count all the element from N,
       so when i=4 it wont't find one, and when i=6 as the same casuse "2*3==6" so i=6 will success.
    Finally, we output count+1 owing that the last time N%i !=0 so the last step N must be a Susu.
```

## Solution

``` c
#include<stdio.h>
#include<stdlib.h>
#include<math.h> //double sqrt(double n)

int main(void){
    int N;
    while(scanf("%d",&N) != EOF){
        if(N==1){
            printf("%d",0);
        }else{
            int ret = 0;
            for(int i = 2;i<=sqrt(N);++i){
                while(N != i){
                    if(N%i == 0){
                        ret++;
                        N=N/i;
                    }else break;
                }
            }
            printf("%d",ret+1);
        }
    }
    return 0;
}

```