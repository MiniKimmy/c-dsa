## 67. Add Binary

Given two binary strings, return their sum (also a binary string).

The input strings are both non-empty and contains only characters 1 or 0.

## Example 1:
```
Input: a = "11", b = "1"
Output: "100"
```
## Example 2:
```
Input: a = "1010", b = "1011"
Output: "10101"
```

## hints
```
    not very well.
```

## Solution
``` c
char* addBinary(char* a, char* b) {

    //int* s1 = (int*)malloc(sizeof(int*) * 500);
    int top1 = -1;

    while(a[++top1]){
        //s1[top1] = a[top1];
    }

    //int*  s2 = (int*)malloc(sizeof(int*) * 500);
    int top2 = -1;
    while(b[++top2]){
        //s2[top2] = b[top2];
    }

    int len ;
    char* pi =NULL;
    int temp;
    if(top2 > top1)
    {
        len = top2;
        temp = top1;
        pi = b;
    }else{
        len = top1;
        temp = top2;
        pi = a;
    }
    char* p = NULL;
    p = (char*)malloc(sizeof(char) * len);

    top1--;
    top2--;
    int c = 0;

    //char* ret = (char*)malloc(sizeof(char) * len);
    int i = 0;


    while(top1!=-1 && top2!= -1){
        //int sum = s1[top1--] -'0' + s2[top2--] - '0' + c;
        int sum = a[top1--] -'0' + b[top2--] - '0' + c;

        switch(sum){
            case 2:
                c = 1;
                //ret[i++] = '0';
                p[len-i-1] = '0';
                ++i;
                break;
            case 3:
                c = 1;
                //ret[i++] = '1';
                p[len-i-1] = '1';
                ++i;
                break;
            case 1:
                c = 0;
                //ret[i++] = '1';
                p[len-i-1] = '1';
                ++i;
                break;
            case 0:
                c = 0;
                //ret[i++] = '0';
                p[len-i-1] = '0';
                ++i;
                break;
        }
    }


    while(top1 != -1){
        //int sum = s1[top1--] -'0' + c;
        int sum = a[top1--] -'0' + c;

        if(c != 0){
            switch(sum){
            case 2:
                c = 1;
                //ret[i++] = '0';
                p[len-i-1] = '0';
                ++i;
                break;
            case 1:
                c = 0;
                //ret[i++] = '1';
                p[len-i-1] = '1';
                ++i;
                break;
            case 0:
                c = 0;
                //ret[i++] = '0';
                p[len-i-1] = '0';
                ++i;
                break;
            }
        }else{
            //ret[i++] = sum + '0';
            p[len-i-1] = '0';
            ++i;
        }
    }

    while(top2 != -1){
        //int sum = s2[top2--] -'0'+ c;
        int sum = b[top2--] -'0'+ c;
        if(c!=0){
            switch(sum){
                case 2:
                    c = 1;
                    //ret[i++] = '0';
                    p[len-i-1] = '0';
                    i++;
                    break;
                case 1:
                    c = 0;
                    //ret[i++] = '1';
                    p[len-i-1] = '1';
                      i++;
                    break;
                case 0:
                    c = 0;
                    //ret[i++] = '0';
                    p[len-i-1] = '0';
                    ++i;
                    break;
                }
            }
        else{
            //ret[i++] = sum + '0';
            p[len-i-1] = '0';
            i++;
        }
    }


    //free(s1);
    //free(s2);

    char* backup = NULL;

    if(c == 1) {
        //ret[i++] = '1';
        backup = (char*)malloc(sizeof(char)* (i+2) );
        backup[i+2] = '\0';
        backup[0] = '1';
        for(int j = 1;j<len+1;++j){
            backup[j] = p[j-1];
        }
    }
        else{
            backup = (char*)malloc(sizeof(char)* (i+1) );
            backup[i] = '\0';
            for(int j = 0;j<len-temp;++j){
                backup[j] = pi[j];
            }

            backup[len-temp-1] = '1';
            for(int j = 0;j<temp;++j){
                backup[len-j-1] = p[len-1-j];
            }
        }


    return backup;

    /*
    char* res = (char*)malloc(sizeof(char) * (i+1));
    res[i] = '\0';

    for(int j = 0;j<i;j++){
        res[i-j-1] = ret[j];
    }

    free(ret);
    return res;
    */
}


```