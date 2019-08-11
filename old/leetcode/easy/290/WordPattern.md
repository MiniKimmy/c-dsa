## 290. Word Pattern
Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in str.

**Example 1:**
```
Input: pattern = "abba", str = "dog cat cat dog"
Output: true
```
**Example 2:**
```
Input:pattern = "abba", str = "dog cat cat fish"
Output: false
```
**Example 3:**
```
Input: pattern = "aaaa", str = "dog cat cat dog"
Output: false
```
**Example 4:**
```
Input: pattern = "abba", str = "dog dog dog dog"
Output: false
```
**Notes:**
You may assume pattern contains only lowercase letters, and str contains lowercase letters separated by a single space.

## hints
```
    hashTable || map || Dictionary

```


## Solution

``` csharp
public class Solution {
    public bool WordPattern(string pattern, string str) {

        string[] words = str.Split(' ');

        if(pattern == null || words.Length != pattern.Length) return false;

        Dictionary<string, char> dic = new Dictionary<string, char>();
        Dictionary<char, int> dicReverse = new Dictionary<char, int>();

        for (int i = 0; i < pattern.Length; ++i)
        {
            if(dic.ContainsKey(words[i]))
            {
                if (!dic[words[i]].Equals(pattern[i]))
                {
                    return false;
                }
            }
            else if (dicReverse.ContainsKey(pattern[i]))
            {
                return false;
            }
            else
            {
                dic.Add(words[i], pattern[i]);
                dicReverse.Add(pattern[i],2018);
            }
        }

        return true;
    }
}

```