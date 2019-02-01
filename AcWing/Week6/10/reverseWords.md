## 77. 翻转单词顺序
[这里](https://www.acwing.com/problem/content/73/)
输入一个英文句子，翻转句子中单词的顺序，但单词内字符的顺序不变。

**Note:**
* 为简单起见，标点符号和普通字母一样处理。

**Example :**
```
Input:"I am a student."
Output:"student. a am I"
```

## hints
```
    1.split一段段word
    2.然后再翻转
```

## Solution
``` c
int getLen(char* str)
{
    int len = 0;
    while(str[len]){
        len++;
    }
    return len;
}

char** split(char* str, int length, char symbol, int* returnSize)
{
    int i = 0;
    char** ret = (char**)malloc(sizeof(char*) * length);
    int index = 0;
    while(str[i])
    {
        int k = i;
        while(k < length && str[k] != symbol) k++;
        char* item = (char*)malloc(sizeof(char) * (k-i+1));

        for(int j = i;j<k;++j){
            item[j-i] = str[j];
        }

        item[k-i] = '\0';
        ret[index++] = item;
        i = k+1;
    }
    *returnSize = index;
    return ret;
}

char* reverseWords(char* s) {
    int len = getLen(s);
    int count = 0;
    char** temp = split(s,len,' ',&count);
    char* ret = (char*)malloc(sizeof(char) * (len+1));
    int index = 0;
    for(int i = count-1;i>=0;--i){
        char* p = temp[i];
        int j = 0;
        while(p[j]){
            ret[index++] = p[j];
            ++j;
        }
        free(p);
        ret[index++] = ' ';
    }

    free(temp);
    ret[len] = '\0';
    return ret;
}
```