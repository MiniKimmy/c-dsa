## 81. 扑克牌的顺子
[这里](https://www.acwing.com/problem/content/description/77/)
从扑克牌中随机抽5张牌，判断是不是一个顺子，即这5张牌是不是连续的。
2～10为数字本身，A为1，J为11，Q为12，K为13，大小王可以看做任意数字。

**Note**
* 为了方便，大小王均以0来表示，并且假设这副牌中大小王均有两张。

**Example 1:**
```
Input:[8,9,10,11,12]
Output:true
```
**Example 2:**
```
Input:[0,8,9,11,12]
Output:true
```
## hints
```
1.总共13种牌，定义一个数组arr，记录源数组[]是哪几张牌
    * 记录的时候顺便排除相同元素值的卡牌
2.利用quickSort是思路，两边夹
    (1).找到13张牌里含有牌的的左右边界[l,r]
    (2).如果[l,r]区间长度>5，就不是顺子；否则就是顺子
```
## Solution
``` c
bool isContinuous(int* numbers, int length) {
    if(!numbers || length !=5 ) return false;

    int size = 13;
    int* arr = (int*)malloc(sizeof(int) * size);
    for(int i = 0;i<size;++i){
        arr[i] = 0;
    }

    for(int i = 0;i<length;++i){
        arr[numbers[i]]++;
        if(numbers[i] != 0 && arr[numbers[i]] >=2 ) return false; //排除相同的元素的卡牌
    }

    int i = 1;
    int j = size -1;

    while(i<size && arr[i] == 0) ++i;
    while(j>=1 && arr[j] == 0) --j;

    free(arr);
    return j-i+1 > length ? false : true;
}
```