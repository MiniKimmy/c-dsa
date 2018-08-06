## Q884.Decoded String at Index

An encoded string S is given.  To find and write the decoded string to a tape, the encoded string is read one character at a time and the following steps are taken:

    If the character read is a letter, that letter is written onto the tape.
    If the character read is a digit (say d), the entire current tape is repeatedly written d-1 more times in total.

Now for some encoded string S, and an index K, find and return the K-th letter (1 indexed) in the decoded string.


**Example 1:**

```
Input: S = "leet2code3", K = 10
Output: "o"
Explanation:
The decoded string is "leetleetcodeleetleetcodeleetleetcode".
The 10th letter in the string is "o".
```

**Example 2:**
```
Input: S = "ha22", K = 5
Output: "h"
Explanation:
The decoded string is "hahahaha".  The 5th letter is "h".
```

**Example 3:**
```
Input: S = "a2345678999999999999999", K = 1
Output: "a"
Explanation:
The decoded string is "a" repeated 8301530446056247680 times.  The 1st letter is "a".
```


**Note:**<br/>
    * 2 <= S.length <= 100<br/>
    * S will only contain lowercase letters and digits 2 through 9.<br/>
    * S starts with a letter.<br/>
    * 1 <= K <= 10^9<br/>
    * The decoded string is guaranteed to have less than 2^63 letters.<br/>

## hints
```
    //Modulus && Divsion (INTRODUCTION)
    //1. You may realize that this Question can be defined as repeating do the same thing for N times, but just want one step in the ith time.

       //Effectly, you just need to find this specified step in one integral procedure.

    //2. Use 'Divsion' to reduce the scrop the N times;
    //   USe 'Modulus' to lock the specified step.
    //3. According to this problem, we didnt know the N what it is, so the first thing to do is find N, then work backward to scale back N and use 'Modulus' to find the target .

    4. (Skip 1~3 is ok)
    ex:"kimmy22"
    -->"kimmykimmykimmykimmy"   if K=13  Output:"m"
    Explanation:
        'kimmy' Length=5
        target = K%Length = 13%5 = 3

    The length of decode string is the key for this question,because it is the one integral procedure and just do N times.
    5.So we count the whole Size of the 'N times String', then we work backward.From the tail of the decode string starts, and use "div" to decrease the scrop, and use "mod" to find target while tracking the decode string.

```

## Solution

``` csharp
public class Solution {
    public string DecodeAtIndex(string S, int K) {
        if(K == 1) return ""+S[0];

        long step = 0;
        long size = 0;
        for(int i = 0; i<S.Length; ++i){
            if(S[i]<=57){
                size = size * (S[i] - 48);
            }else{
                size++;
            }
        }

        for(int i = S.Length-1; i>=0; --i){
            K = (int)(K % size);
            if(K == 0 && S[i] >=97){
                return ""+S[i];
            }else if(S[i] <= 57){
                size = size / (S[i] - 48);
            }else{
                size--;
            }
        }
        return null;
    }
}
```