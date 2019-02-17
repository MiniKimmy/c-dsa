## 58. 把数组排成最小的数
[这里](https://www.acwing.com/problem/content/54/)
输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。

**Example :**
```
Input:[3, 32, 321]
Output:"321323"
```
## hints
```
    1.先排序，排序完之后再变成字符串连接
    2.排序的比较器自定义
        (1).相同位的直接比较数的大小即可
        (2).一般情况是，按最高位位开始比较
        (3).特殊情况:ex:(47,474),(23,239),(23,231)
```
## Solution
``` c
/// 将int转化为string
char* toString(int n)
{
    char* buffer = (char*)malloc(sizeof(char) * 10);
    int index = 0;
    while(n>0){
        buffer[index++] = n % 10 + '0';
        n /= 10;
    }

    char* ret = (char*)malloc(sizeof(char) * (index+1) );
    for(int i = 0;i<index;++i){
         ret[index-i-1] = buffer[i];
    }


    ret[index] = '\0';
    free(buffer);
    return ret;
}

/// 将int转化为int[]
int* getIntArray(int n, int* length)
{
    int* buffer = (int*)malloc(sizeof(int) * 10);
    int index = 0;
    while(n>0){
        buffer[index++] = n % 10;
        n /= 10;
    }

     int* ret = (int*)malloc(sizeof(int) * index);
     for(int i = 0;i<index;++i){
         ret[index-i-1] = buffer[i];
     }

     *length = index;
     free(buffer);
     return ret;
}

/// 获取正整数的位数
int getBit(int n){
    int ret = 0;
    while(n>0){
        n /=10;
        ret++;

    }
    return ret;
}

/// 幂函数
int pow_(int a, int e)
{
    int ret = 1;
    while(e){
        ret*=a;
        e--;
    }
    return ret;
}

/// 0:a==b; 1:a>b;-1:a<b
int compare(int a, int b)
{
    int len1 = getBit(a);
    int len2 = getBit(b);
    int t1 = pow_(10,len1-1);
    int t2 = pow_(10,len2-1);
    int temp = len1>len2?a:b;

    // 分别从各自的高位来逐一比较
    if(len1 != len2){
        // 处理位数不同的2个数
        while(t1>1 || t2>1)
        {
            int a1 = a / t1;
            int b1 = b / t2;
            if(a1 > b1) {
                return 1;
            }
            else if(a1 < b1){
              return -1;
            }
            else{
                if(t1>1) {
                    a = a - a1*t1;
                    t1 /=10;
                }
                if(t2>1){
                    b = b - b1*t2;
                    t2 /=10;
                }
            }
        }
    }else{
        // 处理位数相同的2个数
        return a>b?1:b>a?-1:0;
    }

    //处理 (47,474) (23,239),(23,231)
    int len = 0;
    int* t = getIntArray(temp,&len);

    if(len2 > len1){
        for(int i = 0;i<len-1;++i){
            if(t[i] == b) continue;

            if(t[i] > b) {
                free(t);
                return 1;
            }else{
                free(t);
                return -1;
            }
        }
    }else{
        for(int i = 0;i<len-1;++i){
            if(t[i] == a) continue;

            if(t[i] > a) {
                free(t);
                return -1;
            }else{
                free(t);
                return 1;
            }
        }
    }

    return 0;


    /* TLE 时间超时
    int len1 = 0;
    int* ch1 = getIntArray(a,&len1);

    int len2 = 0;
    int* ch2 = getIntArray(b,&len2);

    int i = 0; int j = 0;
    int ret = 0;
    while(i != len1 || j != len2)
    {
        int _a = ch1[i];
        int _b = ch2[j];
        if(_a > _b){
            free(ch1);
            free(ch2);
            return 1;
        }else if(_a < _b){
            free(ch1);
            free(ch2);
            return -1;
        }else{
            if(i<len1-1) i++;
            if(j<len2-1) j++;
        }
    }

    free(ch1);
    free(ch2);
    return 0;
    */
}

/// 按一定的顺序插入排序
void insertSort(int* arr, int arrSize)
{
    for(int i = 1;i<arrSize;++i){
        int pos = i;
        int temp = arr[i];
        for(int j = i-1;j>=0 && compare(temp,arr[j]) == -1 ; j--){
            arr[j+1] = arr[j];
            pos = j;
        }
        if(pos != i) arr[pos] = temp;
    }
    return;
}

char* printMinNumber(int* nums, int numsSize) {
    if(nums == NULL || numsSize<=0) return "";

    //printf("test=%d\n",compare(474,47));
    //return "";              //用于测试某一组数的debug

    insertSort(nums,numsSize);

    char* buffer = (char*)malloc(sizeof(char)* 10000);

    int index=0;
    for(int i = 0;i<numsSize;++i){
        char* temp = toString(nums[i]);
        char* p = temp;
        while(*p){
            buffer[index++] = *p;
            p++;
        }
        //buffer[index++] = ' ';  // 用于看清string每一个数
    }

    char* ret = (char*)malloc(sizeof(char)* (index+1));
    for(int i = 0;i<index;++i){
        ret[i] = buffer[i];
    }

    ret[index] = '\0';
    free(buffer);
    return ret;
}
```