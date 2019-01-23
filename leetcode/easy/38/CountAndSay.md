## 38.Count and Say

The count-and-say sequence is the sequence of integers with the first five terms as following:

1.     1
2.     11
3.     21
4.     1211
5.     111221

1 is read off as "one 1" or 11.
11 is read off as "two 1s" or 21.
21 is read off as "one 2, then one 1" or 1211.

Given an integer n where 1 ≤ n ≤ 30, generate the nth term of the count-and-say sequence.

Note: Each term of the sequence of integers will be represented as a string.

**Example 1:**
```
Input: 1
Output: "1"
```
**Example 2:**
```
Input: 4
Output: "1211"
```
## hints
```
    1. n==1,n==2 as special
    2. when n>3, "11" as Init-String
        * set str[0] as normal init
        * use j=1~str.Len to compare
            * when come to different, connect string.
            * and careful Array boundary, especially the last char element.
```

## Solution
``` csharp
public class Solution {
    public string CountAndSay(int n) {
        if(n == 1) return "1";
        if(n == 2) return "11";

        string str = "11";
        char c;
        int count;
        string temp;

        for(int i = 2;i<n;++i) {
            c = str[0];
            count = 1;
            temp = "";

            for(int j = 1;j<str.Length;++j){
                if(c == str[j]){
                    count++;
                }else {
                    temp = temp + count.ToString() + c.ToString();
                    c = str[j];
                    count = 1;
                }
            }

            if (temp == "")
                str = count.ToString() + c.ToString();
            else if(c == temp[temp.Length-1])
                str = temp + count.ToString() + c.ToString();
            else
                str = temp + count.ToString() + c.ToString();
        }

    return str;
    }
}
```

## hint2
```
    1. n==1 as special
    2. same char -->count++
        (1)normal:count = 0
        (2)count++ each time.
        (3)meet different
            use "||" --> avoid boundary overflow
```

## Solution2
``` csharp
public class Solution {
    public string CountAndSay(int n) {
        string ret = "1";
        for(int i = 2;i<=n;++i) {
            int count = 0;
            string temp = "";

            for(int j = 0;j<ret.Length;++j){
                count++;
                if(j == ret.Length - 1 || ret[j] != ret[j+1]){
                    temp = temp + count.ToString() + ret[j].ToString();
                    count = 0;
                }
            }
            ret = temp;
        }
        return ret;
    }
}
```
