## Seperate two side.

Given a int[] called "A[]", base on numbers[maxsize-1] "A[n-1]" to seperate tow side,
put elements > A[n-1] on the left of A[n-1], and put elements < A[n-1] on the right of A[n-1].

## CHINESE
设有一元素为整数的线性表L=(a1,a2,a3,…,an),存放在一维数组A[N]中,
设计一个算法,以表中an作为参考元素,将该表分为左、右两部分,
其中左半部分每个元素小于等于an,右半部分每个元素都大于an, an位于分界位置上(要求结果仍存放在A[N]中)。


**Example 1:**
```
Input: [1,3,4,5,6,7,4]
One of Output: [1,3,4,4,5,6,7]
```

**Example 2:**
```
Input: [1,3,9,2,6,7,4]
One of Output: [1,3,2,4,7,6,9]
```

## hints
```
    use 2 containers to save the both sides elements.
    then cover the sourceArray.
```

## Analogous
|                         Nav            |                   Des                    |
| :-------------------------------------:|:----------------------------------------:|
| ![moveNegativeToTheFront](moveNegativeToTheFront.md)|将链表的负数val移置链表前面  |
| ![selectThreeTypes](selectThreeTypes.md)|把1个单链表分类为3个循环单链表           |


## Solution
``` c
void splitNums(int* nums, int numsize)
{
    if (nums == NULL) return;
    int target = nums[numsize - 1];

    int* sqStack_min = (int*)malloc(sizeof(int)*numsize);
    int top_min = -1;

    int* sqStack_max = (int*)malloc(sizeof(int)*numsize);
    int top_max = -1;

    for (int i = 0; i < numsize - 1; ++i) {
        if (nums[i] < target) {
            sqStack_min[++top_min] = nums[i];
        }else {
            sqStack_max[++top_max] = nums[i];
        }
    }

    int i = 0;
    while (top_min != -1) {
        nums[i++] = sqStack_min[top_min--];
    }

    nums[i++] = target;

    while (top_max != -1) {
        nums[i++] = sqStack_max[top_max--];
    }

    free(sqStack_min);
    free(sqStack_max);
    return;
}
```