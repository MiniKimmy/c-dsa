## 32. 调整数组顺序使奇数位于偶数前面
[这里](https://www.acwing.com/problem/content/description/30/)
输入一个整数数组，实现一个函数来调整该数组中数字的顺序。
使得所有的奇数位于数组的前半部分，所有的偶数位于数组的后半部分。

**Example :**
```
Input:[1,2,3,4,5]
Output:[1,3,5,2,4]
```
## hints
```
    1.qSort mind
```
## Solution
``` c
void reOrderArray(int *array, int length) {
    if(array == NULL || length <= 0) return ;

    int l = 0; int r = length-1;
    while(l<r){
         // 左边找到偶数
         while(l<=r && array[l] % 2 != 0) l++;
         // 右边找到技术
         while(l<=r && array[r] % 2 == 0) r--;
         if(l>r) return;
         int temp = array[l];
         array[l] = array[r];
         array[r] = temp;
         ++l;
         --r;
    }
    return;
}
```