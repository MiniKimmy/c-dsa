## 888. Uncommon Words from Two Sentences

We are given two sentences A and B.  (A sentence is a string of space separated words.  Each word consists only of lowercase letters.)

A word is uncommon if it appears exactly once in one of the sentences, and does not appear in the other sentence.

Return a list of all uncommon words.

You may return the list in any order.



**Example 1:**
```
Input: A = "this apple is sweet", B = "this apple is sour"
Output: ["sweet","sour"]
```
**Example 2:**
```
Input: A = "apple apple", B = "banana"
Output: ["banana"]
```

**Note:**
```
    0 <= A.length <= 200
    0 <= B.length <= 200
    A and B both contain only spaces and lowercase letters.
```

## hints
```
    dictionary<string,int>  --means <wordName,word's count>
    get the words whose count == 1 to return

```

## Solution

``` csharp
public class Solution {
    public string[] UncommonFromSentences(string A, string B)
        {
            string[] listA = A.Split(' ');
            string[] listB = B.Split(' ');
            Dictionary<string, int> map = new Dictionary<string, int>();

            foreach (var item in listA){
                if (map.ContainsKey(item)){
                    map[item]++;
                }else{
                    map.Add(item, 1);
                }
            }

            foreach (var item in listB)
            {
                if (map.ContainsKey(item)){
                    map[item]++;
                }
                else{
                    map.Add(item, 1);
                }
            }

            List<string> ret = new List<string>();

            foreach (var item in map.Keys)
            {
                if(map[item]==1){
                    ret.Add(item);
                }
            }

            return ret.ToArray();
        }
}
```