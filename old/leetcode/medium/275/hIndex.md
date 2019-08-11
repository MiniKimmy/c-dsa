## 275. H-Index II
[这里](https://leetcode.com/problems/h-index-ii/)
Given an array of citations sorted in ascending order (each citation is a non-negative integer) of a researcher, write a function to compute the researcher's h-index.

According to the definition of h-index on Wikipedia: "A scientist has index h if h of his/her N papers have at least h citations each, and the other N − h papers have no more than h citations each."

**Example:**
```
Input: citations = [0,1,3,5,6]
Output: 3
Explanation: [0,1,3,5,6] means the researcher has 5 papers in total and each of them had
             received 0, 1, 3, 5, 6 citations respectively.
             Since the researcher has 3 papers with at least 3 citations each and the remaining
             two with no more than 3 citations each, her h-index is 3.
```
**Note:**
* If there are several possible values for h, the maximum one is taken as the h-index.

**Follow up:**
* This is a follow up problem to H-Index, where citations is now guaranteed to be sorted in ascending order.
* Could you solve it in logarithmic time complexity?

## hints
```
    1.(二分)下标划分.因为边界是以这堆数里的数值作为划分
    2.l+r >> 1 等价于 (l+r)/2
    3.check的业务
        (1).题目要求是:选取边界的最大值
        (2).已经有序了.所以就直接判断
        (3).如果这个是无序的话（不是先排序，这里会耗时间(n²)），
            而是使用for一遍，根据l和mid的范围合法的，来累加数量
            然后累加完毕后，再处理(1)、(2)的业务
```

## Solution
``` c
// return 1表示数量比引用数量少（答案在左边r=mid）;0表示数量比引用数量多（答案在右边l=mid+1）
int check(int* citations,int citationsSize,int mid){
    if(citationsSize-mid<=citations[mid]) return 1;
    else return 0;
}

int hIndex(int* citations, int citationsSize) {
    if(citations== NULL || citationsSize<=0) return 0;

    int l = 0;
    int r = citationsSize-1;

    while(l<r){
        int mid = l+r>>1; //[l,mid],[mid+1,r]
        if(check(citations,citationsSize,mid)==1)
            r = mid;      //-->选择[l,mid]
        else
            l = mid+1;    //-->选择[mid+1,r]
    }

    if(citationsSize - l <= citations[l]) return citationsSize-l;
    return 0;
}
```