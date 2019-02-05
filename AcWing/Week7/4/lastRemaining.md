## 82. 圆圈中最后剩下的数字
[这里](https://www.acwing.com/problem/content/78/)
0, 1, …, n-1这n个数字(n>0)排成一个圆圈，从数字0开始每次从这个圆圈里删除第m个数字。
求出这个圆圈里剩下的最后一个数字。

**Example :**
```
Input: n=5,m=3
Output:3
```
## hints
```
    1.使用特殊标记值标记已经轮过的数
    2.使用数组存储圈里每一个数
```

## Solution
``` c
/* 使用特殊标记值标记已经轮过的数*/
int lastRemaining(int n, int m){
    int* arr = (int*)malloc(sizeof(int) * n);
    for(int i = 0;i<n;++i){
         arr[i] = i;
    }

    int index = -1;
    int ret = 0;

    int _n = n;
    while(_n)
    {
        int count = 0;
        while(count < m){
            index = (index+1) % n;
            if(arr[index] == n) continue;  // 这里使用了 arr[i]= n  这个数值标记已轮过.
            count++;
        }

        arr[index] = n;
        ret = index;
        _n--;
    }

    free(arr);
    return ret;
}
```