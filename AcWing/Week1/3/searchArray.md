## 15. 二维数组中的查找
[这里](https://www.acwing.com/problem/content/16/)
在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。

**Example 1:**
```
Input:
[
  [1,2,8,9]，
  [2,4,9,12]，
  [4,7,10,13]，
  [6,8,11,15]
]
target=7
Output:true
```
**Example 2:**
```
Input:
[
  [1,2,8,9]，
  [2,4,9,12]，
  [4,7,10,13]，
  [6,8,11,15]
]
target=5
Output:false
```

## hitns
```
    1.先行后列遍历，遇到比自己大的就break，跳到下一行重新开始
```

## Solution
``` c
/*o(n²)*/
bool searchArray(int** array, int arrayRowSize, int arrayColSize, int target) {
    for(int i = 0;i<arrayRowSize;++i){
        for(int j = 0;j<arrayColSize;++j){
            if(array[i][j]==target) return true;
            else if(array[i][j]>target) break;
        }
    }
    return false;
}
```