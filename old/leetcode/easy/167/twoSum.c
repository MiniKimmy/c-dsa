/*
Q167.Two Sum II - Input array is sorted

Given an array of integers that is already sorted in ascending order, find two numbers such that they add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2.

Note:

    Your returned answers (both index1 and index2) are not zero-based.
    You may assume that each input would have exactly one solution and you may not use the same element twice.

Example:

Input: numbers = [2,7,11,15], target = 9
Output: [1,2]
Explanation: The sum of 2 and 7 is 9. Therefore index1 = 1, index2 = 2.


/**
 * minikimmy-hints: <Collisions pointer>
 * Last Modified time: 2018-08-05 09:33:33
 * Ending-tag : left<right
 * let one side run, and the other side stop;
 * when right-pointer meet the problem(according to the question), then left-pointer(the other side) start to runing.
 * and then left-pointer may meet the problem as well, and if they didn't collided, reset the flag, and repeat the motion 'right-run && left-stop --> left-run && right-stop'.
 * keep 2 pointers running until appear the Ending-tag || done this problem.
 */

//C
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

int* twoSum(int* numbers, int numbersSize, int target, int* returnSize) {
    if(numbers==NULL || numbersSize<1) return NULL;

    int right = numbersSize-1;
    int left = 0;
    int flag = 0;
    int sum = 0;
    while(left < right){
        sum = numbers[left] + numbers[right];
        if(flag == 0 && sum > target){
            right--;
        }else if(sum<target){
            left++;
            if(right!=numbersSize-1)flag = 1;
        }else{
            if(sum>target && flag == 1){
                flag = 0;
                right--;
                continue;
            }
            break;
        }
    }

    if(left >= right) return NULL;
    if(sum == target){
        *returnSize = 2;
        int* ret=(int*)malloc(sizeof(int)*2);
        ret[0] = left+1;
        ret[1] = right+1;
        return ret;
    }
    return NULL;
}
