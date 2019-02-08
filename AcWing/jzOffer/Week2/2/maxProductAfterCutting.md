## 25. 剪绳子
[这里](https://www.acwing.com/problem/content/24/)
给你一根长度为n绳子，请把绳子剪成 m 段（m、n 都是整数，2≤n≤58 并且 m≥2）。
每段的绳子的长度记为k[0]、k[1]、……、k[m]。k[0]k[1] … k[m] 可能的最大乘积是多少？

**Example :**
```
Input:8
Output:18
Explanation:剪成长度分别为2、3、3的三段
```

## hints
```
    1.整数拆分尽量多的3,然后其次是2
        (1).整数乘积
            ex 1: ni>=5 时 3*(ni-3)=3ni-9 >= ni ?--> 2ni-9 >=1 √
                拆多个3出来时候乘积会更大.
            ex 2: ni==4 时 ni=2*2就能拆成两个2
        (2).拆成尽量多的3，而2最多是两个。因为2*2*2=8>=5了，
    2.注意，题目要求至少要拆2段
```

## Solution
``` c
int maxProductAfterCutting(int length){
    if(length <= 3){
        return length-1;
    }

    int a = length % 3;
    int b = length / 3;

    if(a == 0){
        return pow(3,b); //pow(a,b) 表示a的b次幂
    }

    if(a == 1){
        b--;
        return pow(3,b) * 4;
    }

    if(a == 2){
        return pow(3,b) * 2;
    }

    return 0;

}
```