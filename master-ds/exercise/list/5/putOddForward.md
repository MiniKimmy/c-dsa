## Move Odd Elements to the front of Even Elements

Given an int sequence, move odd elements to the front of even elements of this sequence.

## CHINESE
知线性表（a1, a2,a3,…,an）按顺序存储，且每个元素都是整数均不相同，
设计把所有奇数移到所有偶数前边的算法。(要求时间最少，辅助空间最少)

**Example :**
```
Input: [1,3,4,5,6,7,4]
Output: [1,3,7,5,6,4,4]
```

## hints
```
    use qSort thought.
    1.left-right pointers. (Break when left>=right)
    2.find first even from "left" && find first odd from "right"
    3.swap (left,right) under the condition of "left<=right"

```

## Solution
``` c
int swap(int* arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void putOddForward(int* nums, int numsize)
{
    int left = 0;
    int right = numsize - 1;
    while (1) {
        while (left < right && nums[left] % 2 != 0) ++left;
        while (left < right && nums[right] % 2 == 0) --right;
        if (left >= right) break;
        swap(nums, left, right);
        left++;
        right--;
    }

    return;
}
```