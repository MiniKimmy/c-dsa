## Move Minus to the front

Given an array, move all the minus elements to the front of the positive elements.

## CHINESE
编写函数将一整数序列中所有负数移到所有正数之前，要求时间复杂度为O（n）<br />

**Example :**
```
Input: [1,3,4,-5,-6,-7,4]
Output: [-7,-6,-5,4,3,1,4]
```

**Note**<br />
Time Complexity is O(n) <br />

## hints
```
    qSort Mind.
```

## Analogous
|                         Nav            |                   Des                 |
| :-------------------------------------:|:-------------------------------------:|
| ![putOddForward](putOddForward.md)     |把偶数放在奇数前面                     |
| ![putMinusForward2](../4/moveNegativeToTheFront.md)|把负数放在正数前面(单链表) |
| ![binarySearch1](binarySearch.md)      |二分查找1                              |

## Solution
``` c
int swap(int* arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void putMinusForward(int* nums, int numsize)
{
    int left = 0;
    int right = numsize - 1;
    while (1) {
        while (left < right && nums[left] < 0) ++left;
        while (left < right && nums[right] >= 0) --right;
        if (left >= right) break;
        swap(nums, left, right);
        left++;
        right--;
    }

    return;
}
```