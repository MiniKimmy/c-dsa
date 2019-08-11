## 64. 字符流中第一个只出现一次的字符
[这里](https://www.acwing.com/problem/content/60/)
请实现一个函数用来找出字符流中第一个只出现一次的字符。

**Example :**
```
Input:"google"
Output:"ggg#ll"
Explanation:
(1).当从字符流中只读出前两个字符”go”时，第一个只出现一次的字符是’g’。
(2).当从该字符流中读出前六个字符”google”时，第一个只出现一次的字符是’l’。
(3).如果当前字符流没有存在出现一次的字符，返回#字符。
(4).每当字符流读入一个字符，就进行一次判断并输出当前的第一个只出现一次的字符。
```
## hints
```
    1.hash记录次数，char[]记录所有添加的字母元素
```
## Solution
``` c
int* hash = NULL;
char* str = NULL;
int index = 0;

//Insert one char from stringstream
void insert(char ch){

    /// 实例化hash和源char[]
    if(hash == NULL || str == NULL){
        hash = (int*)malloc(sizeof(int) * 255);
        for(int i = 0;i<255;++i){
            hash[i] = 0;
        }

        str = (char*)malloc(sizeof(char) * 1000);
    }


    hash[(int)ch]++;
    str[index++] = ch;
    return;
}


//return the first appearence once char in current stringstream
char firstAppearingOnce(){
    str[index] = '\0';
    char* p = str;
    while(*p){
        if(hash[(int)(*p)] == 1){
            return *p;
        }
        ++p;
    }

    return '#';
}
```