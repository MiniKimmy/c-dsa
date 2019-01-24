## 16. 替换空格
[这里](https://www.acwing.com/problem/content/17/)
请实现一个函数，把字符串中的每个空格替换成"%20"。

**Note:**
* 你可以假定输入字符串的长度最大是1000。
* 输出字符串的长度可能大于1000。

**Example:**
```
Input:"We are happy."
Output:"We%20are%20happy."
```

## hints
```
    1.统计空格的数量，为了返回值char*的初始化.
    2.使用index作为char*的下标添加数据
```

## Solution
``` c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char* replaceSpaces(char *str){
    int len = 0;
    int spaceCount = 0;
    while(str[len]){
        if(str[len] == ' ') spaceCount++;
        len++;
    }

    int returnSize = (len - spaceCount) + (spaceCount * 3);
    char* ret = (char*)malloc(sizeof(char) * (returnSize+1));

    int index = 0;
    for(int i = 0;i<len;++i){
        if(str[i] == ' '){
            ret[index++] = '%';
            ret[index++] = '2';
            ret[index++] = '0';
        }else{
            ret[index++] = str[i];
        }
    }
    ret[index] = '\0';
    return ret;
}
```