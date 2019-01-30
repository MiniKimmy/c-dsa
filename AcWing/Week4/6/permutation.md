## 51. 数字排列
[这里](https://www.acwing.com/problem/content/47/)
输入一组数字（可能包含重复数字），输出其所有的排列方式。

**Example 1:**
```
Input:[1,2,3]
Output:
      [
        [1,2,3],
        [1,3,2],
        [2,1,3],
        [2,3,1],
        [3,1,2],
        [3,2,1]
      ]
```
**Example 2:**
```
Input:[1,1,1]
Output:
      [
        [1,1,1],
      ]
```

## hints
```
    1.state二进制标记位置
        * 默认:二进制位置是0就未使用，1就已使用
        * ex:五位数00000，就可以用十进制0~31来标记
        * state >> i & 1 : 获取第[i]位，查看是否可用
        * state + (1 << i) : 将第[i]置1，更新state
    2.排序能将相同值的数字放在一起.
        * 保持相对位置就不会重复排列数
        * 保持源Source数组只读
    3.记录相对位置的方式
        * 使用一个下标指针start
        * 默认遇到相同的时候只在start后
```

## Solution
``` c
/**
 * Return an array of arrays of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

void swap(int* arr, int i, int j){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

/// 排序 -- 用于将相同val的元素站在一起
void qSort(int* arr, int l, int r){
    if(l >= r) return;

    int i = l+1;
    int j = r;
    int temp = arr[l];
    while(true){
        while(i<=r && arr[i] <= temp) ++i;
        while(j>=l && arr[j] > temp) --j;
        if(i>j) break;

        swap(arr,i,j);
        ++i;
        --j;
    }

    swap(arr,l,j);
    qSort(arr,l,j-1);
    qSort(arr,j+1,r);
}

/// 阶乘 --用于初始化返回值二维数组的最大值长度
int factorial(int n){
    int ret = 1;
    while(n>0){
        ret *= n;
        n--;
    }
    return ret;
}

void dfs(int* nums, int n, int u, int start, int state, int* buffer, int*** ret, int* index){
    if(u == n){
        int* item = (int*)malloc(sizeof(int) * n);
        for(int i = 0;i<n;++i){
            item[i] = buffer[i];
        }

        (*ret)[(*index)++] = item;
        return;
    }

    if (!u || nums[u] != nums[u - 1]) start = 0;
    for (int i = start; i < n; i ++ ){
        if (!(state >> i & 1)){
            buffer[i] = nums[u];
            dfs(nums, n, u + 1, i + 1, state + (1 << i), buffer,ret,index);
        }
    }
}

int** permutation(int* nums, int numsSize, int* returnSize) {
    if(nums==NULL || numsSize<=0){
        *returnSize = 0;
        return NULL;
    }
    qSort(nums,0,numsSize-1);

    int maxSize = factorial(numsSize);
    int** refRet = (int**)malloc(sizeof(int*) * maxSize);
    int* buffer = (int*)malloc(sizeof(int*) * numsSize);
    int index = 0;

    dfs(nums,numsSize, 0,0,0, buffer, &refRet,&index);

    free(buffer);
    *returnSize = index;
    return refRet;
}
```

## hints2
```
1.先实现(不考虑元素重复)的全排列LeetCode:46题permutation
2.这里的思路是交换数组元素的位置
    (1).ex: 1 2 3 4 5
        *代表5个坑，[] [] [] [] []
        *[x] [] [] [] []
    (2).第[0]位置：1~5都需要站一次
        *[1] [] [] [] []
        * 第[0]位置站好人之后，后面4个坑全排列[][][][]
    (3).简单来说就是,坑站了人之后,这个坑后面[p,q]段内的元素，递归[p,q]这段数继续全排列
    (4).在递归到最后剩下1个元素，全排列1个元素即自身,此时直接copy一下源数组[]的每个val值到返回值数组即可.
    (5).由于使用了swap交换元素位置，所以递归完回去之后要swap恢复现场
3.在这个基础上，再添加判断重复元素的功能
    (1).判断[p,q]这段元素是否有相同的val
    (2).如果存在相同val，则保持站在相对前面位置的不动
4.这种方式的好处是，不需要专门使用一个path[]数组去记录装进去哪些元素
```

## Solution2
``` c
/**
 * Return an array of arrays of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

void swap(int* arr, int i, int j){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

/// 排序
void qSort(int* arr, int l, int r){
    if(l >= r) return;

    int i = l+1;
    int j = r;
    int temp = arr[l];
    while(true){
        while(i<=r && arr[i] <= temp) ++i;
        while(j>=l && arr[j] > temp) --j;
        if(i>j) break;

        swap(arr,i,j);
        ++i;
        --j;
    }

    swap(arr,l,j);
    qSort(arr,l,j-1);
    qSort(arr,j+1,r);
}

/// 阶乘
int factorial(int n){
    int ret = 1;
    while(n>0){
        ret *= n;
        n--;
    }
    return ret;
}

/// 判断[p,q]这一段内是否有重复元素,保证p,q相对位置不变
bool isDuplicate(int* nums, int p, int q)
{
    //printf("[%d]=%d--[%d]=%d\n",p,nums[p],q,nums[q]);
    while(p < q) {
        if(nums[p] == nums[q]) return true;
        p ++;
    }
    return false;
}

void perm(int* nums, int n,int p, int q, int*** ret, int* index)
{
    if(p == q){
        int* item = (int*)malloc(sizeof(int) * n);
        for(int i = 0;i<n;++i){
            item[i] = nums[i];
        }
        (*ret)[(*index)++] = item;
        return;
    }else{
        for(int i = p; i <= q; ++i){
            if(isDuplicate(nums,p,i)){  //与当前[p]位置与后面某[x]位置有重复的话，则前面的保持不动
                continue;
            }

            swap(nums,p,i);
            perm(nums,n, p+1, q, ret, index);
            swap(nums,p,i);
        }
    }
}

int** permutation(int* nums, int numsSize, int* returnSize) {
    if(nums==NULL || numsSize<=0)
    {
        *returnSize = 0;
        return NULL;
    }

    qSort(nums,0,numsSize-1);
    int maxSize = factorial(numsSize);
    int** refRet = (int**)malloc(sizeof(int*) * maxSize);
    int index = 0;

    perm(nums,numsSize,0,numsSize-1,&refRet,&index);

    *returnSize = index;
    return refRet;
}
```