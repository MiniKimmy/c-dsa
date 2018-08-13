## 手机键盘

按照手机键盘输入字母的方式，计算所花费的时间.

ex 1:
a,b,c都在“1”键上，输入a只需要按一次，输入c需要连续按三次。 如果连续两个字符不在同一个按键上，则可直接按，

ex 2:
ad需要按2下，kz需要按2+4=6下 如果连续两字符在同一个按键上，则两个按键之间需要等一段时间，如ac，在按了a之后，需要等一会儿才能按c,即相当于按1+2+3=6下

**Input**
一个长度不大于100的字符串，其中只有手机按键上有的小写字母

**Output:**
输入可能包括多组数据，对于每组数据，输出按出Input所给字符串所需要的时间

**Example 1 :**
```
input:
bob
www

output:
7
7
```

## hints
```
    stable-size region △x

    |______________|___________|____ ... ___
    o              a    △x     b

    △x =   b        -    a      =  (b-o) - (a-o)
         key[ch1]   -  key[ch2] == ch1   - che2

    which means that they are at the same key.

```

## Solution

``` c
#include<stdio.h>
#include<stdlib.h>

int check(int* tab, char a, char b){
    if(tab[a]-tab[b] == a-b) return 1;
    else return 0;
}

int main(void){
    int* tab = (int*)malloc(sizeof(int)*255);

    tab['a'] = 1; tab['d'] = 1; tab['g'] = 1; tab['j'] = 1; tab['m'] = 1; tab['t'] = 1;
    tab['b'] = 2; tab['e'] = 2; tab['h'] = 2; tab['k'] = 2; tab['n'] = 2; tab['u'] = 2;
    tab['c'] = 3; tab['f'] = 3; tab['i'] = 3; tab['l'] = 3; tab['o'] = 3; tab['v'] = 3;

    tab['p'] = 1;  tab['w'] = 1;
    tab['q'] = 2;  tab['x'] = 2;
    tab['r'] = 3;  tab['y'] = 3;
    tab['s'] = 4;  tab['z'] = 4;

    char* S =(char*)malloc(sizeof(char) * 100);
    while(gets(S)){

        int ret = 0;
        char pre = *S;
        ret = tab[(int)(*S)];
        S++;

        while(*S){
            char c = *S;
            if(check(tab,c,pre)){
                ret = ret + 2 + tab[c];
            }else{
                ret += tab[c];
            }
            pre = c;
            S++;
        }

        printf("%d\n",ret);
        ret = 0;
    }

    return 0;
}

```