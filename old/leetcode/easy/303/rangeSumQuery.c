/*
Q303.Range Sum Query - Immutable
Given an integer array nums, find the sum of the elements between indices i and j (i â‰?j), inclusive.

Example:

Given nums = [-2, 0, 3, -5, 2, -1]

sumRange(0, 2) -> 1
sumRange(2, 5) -> -1
sumRange(0, 5) -> -3

Note:
    You may assume that the array does not change.
    There are many calls to sumRange function.

 */

//C
typedef struct{
    int* dp;
}NumArray;

NumArray* numArrayCreate(int* nums, int numsSize) {
    if(nums == NULL) return NULL;

    NumArray* ret = (struct NumArray*)malloc(sizeof(NumArray));
    ret->dp = (int*)malloc(sizeof(int) * (numsSize + 1));

    ret->dp[0] = 0;
    for(int i = 0;i<numsSize;i++){
        ret->dp[i+1] = ret->dp[i] + nums[i];
    }

    return ret;
}

int numArraySumRange(NumArray* obj, int i, int j) {
    if(obj == NULL) return 0;
    return obj->dp[j+1] - obj->dp[i];
}

void numArrayFree(NumArray* obj) {
    if(obj == NULL) return;
    free(obj->dp);
    return;
}

/**
 * Your NumArray struct will be instantiated and called as such:
 * struct NumArray* obj = numArrayCreate(nums, numsSize);
 * int param_1 = numArraySumRange(obj, i, j);
 * numArrayFree(obj);
 */
