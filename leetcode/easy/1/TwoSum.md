## 1. Two Sum
Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

Example:

Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].

## hints
```
    hashTable.
    1. Dictionary<int,int> means <digit needed, index>
    2. Traverse Source nums ,check if dic.Contain(nums[i])
    ps: But it is luckily that leetcode don't set negative digit, so I can pass the test data.

    IF it exists negative digit:
    Example:
    input: [2,7,-1,10] target:9
    output:[2,3]
    because -1<2, so the smaller one to return.

```

## Solution

``` csharp
// this Solution beats 69%, not beats 100%.
public class Solution {
    public int[] TwoSum(int[] nums, int target) {
        if(nums==null || nums.Length <= 1) return null;
        Dictionary<int, int> dic = new Dictionary<int, int>();

        for(int i =0;i<nums.Length;i++){
            if (dic.ContainsKey(nums[i])){
                return new int[]{dic[nums[i]] , i};
            }else if(!(dic.ContainsKey(target - nums[i]))){
                dic.Add(target - nums[i],i);
            }
        }

        return null;
    }
}
```