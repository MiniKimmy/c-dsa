## ReplaceSpace

请实现一个函数，将一个字符串中的每个空格替换成“%20”。

**Example 1:**
```
input
We Are Happy.

output
We%20Are%20Happy.
```

## Solution

``` csharp
class Solution
{
    public string replaceSpace(string str)
    {
        if(str == null) return null;

        string ret = "";
        for(int i =0;i<str.Length;i++){
            if(str[i] == ' '){
                ret +="%20";
            }else{
                ret +=str[i];
            }
        }
        return ret;
    }
}

```