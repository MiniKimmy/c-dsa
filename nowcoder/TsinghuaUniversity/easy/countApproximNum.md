## 约数的个数

输入n个整数,依次输出每个数的约数的个数

**Input:**
```
输入的第一行为N，即数组的个数(N<=1000)
接下来的1行包括N个整数，其中每个数的范围为(1<=Num<=1000000000)
当N=0时输入结束。
```

**Output:**
```
可能有多组输入数据，对于每组输入数据，
输出N行，其中每一行对应上面的一个数的约数的个数。
```

**Example 1:**
```
input:
5
1 3 4 6 12

output:
1
2
3
4
6
```

## hints
```
    Ending Tag is the when a==b --> min*min == n.

    a*a = n is count+1
    n%i = 0 is count+2
```

## Solution

``` c
#include<stdio.h>
#include<stdlib.h>

int countApproximNum(long n){
    if(n == 1) return 1;

    int ret = 0;
    long i ;
    for(i = 1;i*i<n;++i){
        if(n%i == 0){
            ret+=2;
        }
    }

    return i*i==n? ret+1:ret;
}

int main(void){

    int N ;
    while(scanf("%d",&N) != EOF){
        long test[N];

        for(int i = 0;i<N;++i){
            long a;
            scanf("%d",&a);
            test[i]= countApproximNum(a);
        }

        for(int i = 0;i<N;i++){
            printf("%d\n",test[i]);
        }
    }

    return 0;
}
```