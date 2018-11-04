## 443.String Compression

Given an array of characters, compress it in-place.

The length after compression must always be smaller than or equal to the original array.

Every element of the array should be a character (not int) of length 1.

After you are done modifying the input array in-place, return the new length of the array.

**Follow up:**
Could you solve it using only O(1) extra space?

**Example 1:**
```
Input:
["a","a","b","b","c","c","c"]

Output:
Return 6, and the first 6 characters of the input array should be: ["a","2","b","2","c","3"]

Explanation:
"aa" is replaced by "a2". "bb" is replaced by "b2". "ccc" is replaced by "c3".
```
**Example 2:**
```
Input:
["a"]

Output:
Return 1, and the first 1 characters of the input array should be: ["a"]

Explanation:
Nothing is replaced.
```
**Example 3:**
```
Input:
["a","b","b","b","b","b","b","b","b","b","b","b","b"]

Output:
Return 4, and the first 4 characters of the input array should be: ["a","b","1","2"].

Explanation:
Since the character "a" does not repeat, it is not compressed. "bbbbbbbbbbbb" is replaced by "b12".
Notice each digit has it's own entry in the array.
```

**Note:**
```
    All characters have an ASCII value in [35, 126].
    1 <= len(chars) <= 1000.
```

## hints
```
    1.mark the pre-word,when meet different write into SourceChar.
    2.use buffer int[] to filter the count.
    3.recheck the last element.
```

## Analogous
|                         Nav               |                   Des            |
| :----------------------------------------:|:--------------------------------:|
| ![customSortString](../../medium/791/customSortString.md)|自定义模板排序字母 |
| ![rotateString](rotateString.md)         |检查旋转字符串                     |


## Solution
``` c
int compress(char* chars, int charsSize) {
    if(chars == NULL || charsSize<=0) return 0;

    int len = 0;
    int count = 1;
    char c = chars[0];

    for(int i = 1; i<charsSize; ++i){
        if(c == chars[i]){
            count++;
        }else{
            chars[len++] = c;

            if(count > 1) {

                // handle the 'count' with multiply digit.
                if(count >= 10){
                    int* buffer = (int*)malloc(sizeof(int)*4);
                    int j = 0;
                    while(count > 0){
                        buffer[j++] = count % 10;
                        count /=10;
                    }
                    for(int k = j-1;k>=0;--k){
                        chars[len++] = buffer[k] + '0';
                    }

                    free(buffer);
                }

            // just one digit in the 'count'.
                else{
                    chars[len++] = count+'0';
                }

            }

            //reset the 'count'
            c = chars[i];
            count = 1;
        }
    }

    // handle the last element.
    if(count==1) chars[len++] = chars[charsSize-1];
    else {
        chars[len++] = c;

        // handle the 'count' with multiply digit.
        if(count >= 10){
            int* buffer = (int*)malloc(sizeof(int)*4);
            int j = 0;
            while(count > 0){
                buffer[j++] = count % 10;
                    count /=10;
                }
                for(int k = j-1;k>=0;--k){
                    chars[len++] = buffer[k] + '0';
                }
                free(buffer);
                }
        // just one digit in the 'count'.
        else{
            chars[len++] = count +'0';
        }
    }

    return len;
}
```