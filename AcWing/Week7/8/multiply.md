## 86. 构建乘积数组
[这里](https://www.acwing.com/problem/content/82/)
给定一个数组A[0, 1, …, n-1]，请构建一个数组B[0, 1, …, n-1]，其中B中的元素B[i]=A[0]×A[1]×… ×A[i-1]×A[i+1]×…×A[n-1]。

**Note**
* 能不能只使用常数空间？（除了输出的数组之外）

**Example :**
```
Input:[1, 2, 3, 4, 5]
Output:[120, 60, 40, 30, 24]
Explanation:120=1x2x3x4x5,60=1x3x4x5,40=1x2x4x5,30=1x2x3x5,24=1x2x3x4
```

## hints
```
1.全部非0元素相乘一遍，然后正常情况下相当于B[i] =总连乘值 / A[i]（这题不能用除法）
2.数有多少个0元素
    (1).处理1个0元素的情况
    (2).处理2个0元素以上的情况
    (3).处理0个0元素的情况
```
## Solution
``` c
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

int* multiply(int* A, int length, int* returnSize) {
    int* ret = (int*)malloc(sizeof(int) * length);
    int res = 1;

    int zeroCount = 0; // 0表示无0元素，否则表是有0元素
    for(int i = 0;i<length;++i){
        if(A[i]!=0) res *= A[i];
        else zeroCount++;
    }

    for(int i = 0;i<length;++i){
        if(zeroCount>=2) ret[i] = 0;
        if(!zeroCount) {
            //ret[i] = res / A[i]; 不使用除法
            int temp = 1;
            for(int j = 0;j<length;++j){
                if(i != j) temp *= A[j];
            }
            ret[i] = temp;
        }
        else if(zeroCount==1) ret[i] = A[i]!=0 ? 0 : res;
    }

    *returnSize = length;
    return ret;
}
```