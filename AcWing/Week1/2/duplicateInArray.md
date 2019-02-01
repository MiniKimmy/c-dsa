## 14.不修改数组找出重复的数字
[这里](https://www.acwing.com/problem/content/15/)
给定一个长度为 n+1 的数组nums，数组中所有的数均在 1~n 的范围内，其中 n≥1。请找出数组中任意一个重复的数，但不能修改输入的数组。

**Note :**
* 只能使用 O(1)的额外空间.

**Example :**
```
Input:[2, 3, 5, 4, 3, 2, 6, 7]
Output:2 或 3
```

## hints
```
    如果不能创建额外的空间的话，冒泡查找..O(n²)
```

## Solution
``` c
/*O(n²) too slow */
int duplicateInArray(int* nums, int numsSize){
    for(int i = 0;i<numsSize;++i){
        for(int j = i+1;j<numsSize;++j){
            if(nums[i] == nums[j]) return nums[i];
        }
    }
    return -1;
}
```

## hints2
```
    1.抽屉原理
    2.二分法
        (1).数值划分。因为给的数是乱序，所以不能直接划分下标.
        (2).l + r >> 1 相当于(l+r)/2.
            移位运算的优先级小于加减运算的优先级
            l + r >> 1 相当于 (l + r) >> 1
        (3) 返回值是l或者r都可以，因为最后切分最后是 l==r
        (4) 这个是无序的，但是编号和值域已经确定，因此问题变成考虑的抽屉的个数重复问题，而利用数值的大小来划分边界。
    3. 哪一边个数越多的地方就越合法。合法表示满足题目要求。
```
## Solution
``` c
/*O(nlog(n)) bSearch*/
int duplicateInArray(int* nums, int numsSize){

    int l = 1;
    int r = numsSize-1;
    while(l < r){
        int mid = l + r >> 1;   // [l,mid] , [mid+1,r], mid是数值的界限，划分左右两边坑的数值.
        int count = 0;
        for(int i = 0;i<numsSize;++i){
            if(nums[i] >=l && nums[i] <= mid){
                count ++;
            }
        }

        if(count > mid) r = mid; // 选择-->[l,mid]。数量在左边的较多,答案在较多的那边。较多的那边会重复.
        else l = mid+1;          // 选择-->[mid+1,r]
    }

    return l;
}
```
