## 169 Majority Element

Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/2 ⌋ times.

You may assume that the array is non-empty and the majority element always exist in the array.

**Example 1:**
```
Input: [3,2,3]
Output: 3
```
**Example 2:**
```
Input: [2,2,1,1,1,2,2]
Output: 2
```

## hints
```
    hash problem
```

## Analogous
|                Nav                    |                 Des                 |
|:-------------------------------------:|:-----------------------------------:|
|![romanToInt](romanToInt.md)           |把罗马数字转化为阿拉伯数字           |


## Solution
``` csharp
public class Solution {
    public int MajorityElement(int[] nums) {
        Dictionary<int, int> dic = new Dictionary<int, int>();
            foreach (var item in nums){
                if (dic.ContainsKey(item)){
                    dic[item]++;
                }else{
                    dic.Add(item, 1);
                }
            }

        int count = 0;
        int ret = nums[0];
        foreach(var item in dic){
            if(item.Value > count) {
                count = item.Value;
                ret = item.Key;
            }else if(item.Value == count && item.Key>ret){
                ret = item.Key;
            }
        }
        return ret;
    }
}
```