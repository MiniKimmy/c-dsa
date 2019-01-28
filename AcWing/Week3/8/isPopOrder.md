## 42. 栈的压入、弹出序列
[这里](https://www.acwing.com/problem/content/40/)
输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否可能为该栈的弹出顺序。

假设压入栈的所有数字均不相等。

例如序列1,2,3,4,5是某栈的压入顺序，序列4,5,3,2,1是该压栈序列对应的一个弹出序列，但4,3,5,1,2就不可能是该压栈序列的弹出序列。

**Example :**
```
Input:[1,2,3,4,5]
      [4,5,3,2,1]
Output:true
```
## hints
```
    1.往下走一步和往上走一步的问题
        (1).不管三七二十一，先走一步
        (2).然后while判断这步是不是有标记过，有标记就继续走
    2.使用一维数组记录标记
        * st表示subject.to.
```

## Solution
``` c
bool isPopOrder(int* pushV, int* popV, int pushVLength, int popVLength){
    if(pushV == NULL || popV== NULL || pushVLength<=0 || popVLength<=0) return false;
    int n = pushVLength;
    //标记数组，0表示未弹出，1表示已弹出
    int* st = (int*)malloc(sizeof(int) * n);

    int count = 0;
    int index = -1;
    while(count < n){
        int pop = popV[count];
        if(pushV[index] != pop){
            index++;
            while(index< 0 || st[index] == 1){
                index++;
            }
            if(index == n) {
                free(st);
                return false;
            }
        }

        else{
            st[index] = 1;
            index--;
            count++;
            while(index>= 0 && st[index] == 1){
                index--;
            }
        }
    }

    free(st);
    return true;
}
```