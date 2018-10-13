## 136.Single Number

Given a non-empty array of integers, every element appears twice except for one. Find that single one.

**Note:**
Your algorithm should have a linear runtime complexity. <br />
Could you implement it without using extra memory?<br />

**Example 1:**
```
Input: [2,2,1]
Output: 1
```
**Example 2:**
```
Input: [4,1,2,1,2]
Output: 4
```
## hints
```
    a ^= b means xor
    if(a==b) a^b=1
    else if(a!=b) a^b=0

    ex:2⊕2⊕1 = 1
    (1)2^2^1 = 1;  like: "0010"^"0010" = "1111"
                         "1111"^"0001" = "0001"

    (2)2^1^2 = 1;  like: "0010"^"0001" = "1100"
                         "1100"^"0010" = "0001"
```

## Solution
``` c
int singleNumber(int* nums, int numsSize) {
    if(numsSize == 1) return nums[0];

    int a = nums[0];
    for(int i = 1;i<numsSize;++i){
        a ^= nums[i];
    }
    return a;
}
```
