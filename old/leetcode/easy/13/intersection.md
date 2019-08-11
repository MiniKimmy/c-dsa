## 349.Intersection of Tow Arrays

Given two arrays, write a function to compute their intersection.

**Example 1:**
```
Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2]
```
**Example 2:**
```
Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
Output: [9,4]
```
**Note:**
```
    Each element in the result must be unique.
    The result can be in any order.
```

## hints
```
    1.sort nums1[] && nums2[]
    2.find the last dumplicate element of nums1 and nums2
    3.if not equals, let one side ++ and the other side stop.
```

## Solution
``` c
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

void insertSort(int* arr,int size){
    for(int i = 1;i<size;++i){
        int pos = i;
        int temp = arr[i];
        for(int j = i-1;j>= 0 && arr[j]<temp;j--){
            arr[j+1] = arr[j];
            pos = j;
        }
        if(pos != i) arr[pos] = temp;
    }
}

int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    if(nums1 == NULL || nums2 == NULL) return NULL;
    insertSort(nums1,nums1Size);
    insertSort(nums2,nums2Size);

    int i = 0;
    int j = 0;
    int size = nums1Size>nums2Size?nums2Size:nums1Size;
    int* ret = (int*)malloc(sizeof(int) * size);
    int index = 0;

    while(i< nums1Size && j< nums2Size){
        int p = nums1[i];
        int q = nums2[j];
        while(i+1<nums1Size && p == nums1[i+1]) ++i;
        while(j+1<nums2Size && q == nums2[j+1]) ++j;
        if(p == q){
            ret[index++] = p;
            ++i;
            ++j;
        }else if(p>q){
            ++i;
        }else{
            ++j;
        }
    }

    *returnSize = index;
    return ret;

}
```
