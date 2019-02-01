## 78. 左旋转字符串
[这里](https://www.acwing.com/problem/content/74/)
字符串的左旋转操作是把字符串前面的若干个字符转移到字符串的尾部。
请定义一个函数实现字符串左旋转操作的功能。

**Note:**
* 数据保证n小于等于输入字符串的长度。

**Example :**
```
Input:"abcdefg" , n=2
Output:"cdefgab"
Explanation:n=2表示将前面[0,2)到结尾变成"cdefgab"
```
## hints
```
    1.直接修改源字符串
    2.类似插入insertSort思路
```
## Solution
``` c
char* leftRotateString(char* str, int n){
    if(str == NULL || n<=0 ) return str;

    for(int i = n;str[i];++i){
        char temp = str[i];
        for(int j = i-1;j>=i-1-n;--j){
            str[j+1] = str[j];
        }
        str[i-n] = temp;
    }
    return str;
}
```