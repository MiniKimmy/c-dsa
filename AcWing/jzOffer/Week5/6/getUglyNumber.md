## 62. 丑数
[这里](https://www.acwing.com/problem/content/58/)
我们把只包含因子2、3和5的数称作丑数（Ugly Number）。
求第n个丑数的值。

**Example :**
```
Input:5
Output:5
Explanation:6、8都是丑数，但14不是，因为它包含因子7。
1,2,3,4,5刚好第5个丑数是5
```
## hints
```
1.比较三个数，返回最小值
    * 先比较2个数得到最小值，再比较第3个数比较
    * 1个数直接一次性&&比较完
2.因子的问题
    (1).一个个数字检查是可，但这里会TLE
    (2).直接使用数组记录找出因子
        * 直接（个数*因子底数）必符合丑数条件
        * 像10这种的数，重复计数。
    (3).不必每个数检测，而是一种直接找的思路
    (4).题目要求是第n个，那么就要根据大小来排队。
```
## Solution
``` c
/*o(n)*/
int min(int a,int b,int c)
{
    return a <= b && a <= c? a : b<=a&&b<=c?b : c;

    /*
        int temp = a < b ? a : b;
        return temp > c?c:temp;
    */

    // return (a < b ? a : b) < c ? (a < b ? a : b) : c;
}

int getUglyNumber(int n)
{
    if(n == 1) return 1;

    // 记录因子是2,3,5的数
    int* buffer = (int*)malloc(sizeof(int) * 3);
    for(int i = 0;i<3;++i){
        buffer[i] = 0;
    }

    int* arr = (int*)malloc(sizeof(int) * n);
    arr[0] = 1;

    for(int i = 1;i<n;++i)
    {
        arr[i] = min(arr[buffer[0]]*2,arr[buffer[1]]*3,arr[buffer[2]]*5);
        if(arr[i] == arr[buffer[0]]*2) buffer[0]++;
        if(arr[i] == arr[buffer[1]]*3) buffer[1]++;
        if(arr[i] == arr[buffer[2]]*5) buffer[2]++;
    }


    int ret = arr[n-1];
    free(arr);
    free(buffer);
    return ret;
}


/* TLE
int getUglyNumber(int n) {
    if(n == 1) return 1;
    n--;
    int num = 2;

    while(n)
    {
        int _num = num;
        while(_num != 1){
            int flag = 0;
            if( !(_num % 2) ){
                _num /= 2;
                flag = 1;
            }

            if( !(_num % 3) ){
                _num /= 3;
                flag = 1;
            }

            if( !(_num % 5) ){
                _num /= 5;
                flag = 1;
            }

            if(!flag) break;
        }

        if(_num == 1){
            n--;
        }

        num++;
    }

    return num - 1;
}
*/
```