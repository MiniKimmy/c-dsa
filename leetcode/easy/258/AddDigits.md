## 258. Add Digits

Given a non-negative integer num, repeatedly add all its digits until the result has only one digit.

**Example:**
```
Input: 38
Output: 2
Explanation: The process is like: 3 + 8 = 11, 1 + 1 = 2.
             Since 2 has only one digit, return it.
```
**Follow up:**
Could you do it without any loop/recursion in O(1) runtime?

## hints
```
    每一位都求余9 ->%9
    ex:ABCDE % 9 = A*(10^5)%9 + B*(10^4)%9 + .. =  A*1 + B*1 + C*1 + D*1 + E*1 = A+B+C+D+E

    ps:10除9余1,100除9也是余1,以此类推 10^n除9也余1

```

## Solotion
``` csharp

public class Solution {
    public int AddDigits(int num) {
        return num < 9? num: num%9 == 0? 9 : num%9;
    }
}

```