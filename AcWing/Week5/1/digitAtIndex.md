## 57. 数字序列中某一位的数
[这里](https://www.acwing.com/problem/content/52/)
数字以0123456789101112131415…的格式序列化到一个字符序列中。
在这个序列中，第5位（从0开始计数）是5，第13位是1，第19位是4，等等。
请写一个函数求任意位对应的数字。

**Example :**
```
Input:13
Output:1
```

## hints
```
1.使用减法，找出对应的范围
    (1).1~9 一位（9个数字），10~99两位（90个数字），100~999三位（900个数字）
    (2).其中一位即x1，两位即x2，三位即x3..
    (3).注:避免溢出，强转为使用long类型计算，溢出则使用INT_MAX.
2.然后确定在某个范围之后。假如是[100,999]的范围
    * 模拟
    * 这里是3位数，所以for一遍从（100~999），每次位置+3（即继续使用减法找确定的某个数）
    * 最终会锁定到某个数val。
    * 最终得到这个数val的位置偏移量
3.然后这个数val再toString。根据偏移量得到对应的位。
```

## Solution
``` c
/// int转化为string
char* toString(int n)
{
    char* buffer = (char*)malloc(sizeof(char) * 10);
    int index = 0;
    while(n)
    {
        buffer[index++] = n%10;
        n/=10;
    }

    char* ret = (char*)malloc(sizeof(char)* (index+1));
    for(int i = 0;i<index;++i){
        ret[index-1-i] = buffer[i];
    }

    ret[index] = '\0';
    free(buffer);
    return ret;
}

/// 返回第n个位置的数字
int digitAtIndex(int n) {

    /// 一位数处理
    if(n < 10) return n;

    /// 二位数以上的处理
    int e = 10;     // 底数
    int count = 9;  // 一位数已有9个数字，所以是9
    int len = 1;    // 一位数已经处理，所以是1
    int start = 1;  // start即1,10,100,1000的数

    while(n > count){
        n-=count;
        len++;         // 记录循环次数【即当前的数是多少位】
        count = (long)9*e*len>2147483647?2147483647:9*e*len;   //【注】：避免溢出
        e *= 10;
        start *= 10;
        //printf("n=%d,count=%d\n",n,count);
    }

    //printf("n=%d,count=%d,e=%d,len=%d,start=%d\n",n,count,e,len,start);

    int temp = start;
    int range = start * 10;
    for(int i = start;i<range;++i){
        if(n - len > 0) {
            n-=len;
        }
        else {
            temp = i;
            break;
        }
    }

    //printf("val=%d\n",temp);
    char* str = toString(temp);
    int ret = (int)str[n-1];
    free(str);
    return ret;
}
```