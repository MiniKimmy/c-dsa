## Find Median

Given two ascending arrays, find the pos “[n/2 - 1]” of arr1+arr2.

## CHINESE
一个长度为L(L>1)的升序序列,处于L/2（取上限）位置的数称为中位数.
试设计一个时间和空间两方面都尽可能高效率的算法,找中位数.

**Example 1:**
```
Input:
[11,13,15,17,19]
[2,4,6,8,20]

Output: 11
```

## hints
```
    * Solution 1 :
    1.merge as an whole arr.
    2.return arr[size/2-1]

    * Solution 2 :
    1.binary search, find each Median in nums1[],nums2[] as mid1,mid2
    2.when nums1[mid1] == nums2[mid1] return .
    3.otherwise,we should judge the remainding count in MaxCount{nums1.Len,nums2.Len}
        * count % 2 == 0, do it as usual
        * count % 2 != 0, the Max{num1[mid1],num2[mid2]} move step +1 incase neglect one digit.
```

## Solution
``` c
int getMedian(int* nums1, int num1Size, int* nums2,int num2Size){

    int size = num1Size + num2Size;
    int* arr = (int*)malloc(sizeof(int) * size);

    int left = 0;
    int right = 0;
    int index = 0;
    for (int i = 0; left < num1Size && right< num2Size; ++i) {
        if (nums1[left] > nums2[right]) {
            arr[index++] = nums2[right++];
        }else {
            arr[index++] = nums1[left++];
        }
    }

    if (left >= num1Size) {
        for (int i = right; i < num2Size; ++i) {
            arr[index++] = nums2[i];
        }
    }else {
        for (int i = left; i < num1Size; ++i) {
            arr[index++] = nums1[i];
        }
    }

    int ret = arr[size / 2 - 1];
    free(arr);
    return ret;
}
```

## Solution2
``` c
/*binary search O(nlogn) + O(1) Space*/

int getMedian(int* nums1, int nums1Size, int*nums2, int nums2Size)
{
    int s1 = 0;
    int s2 = 0;
    int d1 = nums1Size - 1;
    int d2 = nums2Size - 1;
    int m1, m2;

    while (s1 != d1 || s2 != d2) {
        m1 = (d1 + s1) / 2;
        m2 = (d2 + s2) / 2;
        if (nums1[m1] == nums2[m2]) return nums1[m1];
        if (nums1[m1] < nums2[m2]) {
            s1 = (d1 + s1) % 2 == 0? m1 : m1+1;
            d2 = m2;
        }
        else {
            s2 = (d1 + s1) % 2 == 0 ? m2 : m2 + 1;
            d1 = m1;
        }
    }
    return nums1[s1] > nums2[s2] ? nums2[s2] : nums1[s1];
}
```