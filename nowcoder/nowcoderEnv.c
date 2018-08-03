/*
* @Author: minikimmy
* @Date:   2018-08-03 21:49:26
* commit " nowcoder.com for C language coding Env"
* https://www.nowcoder.com/activity/oj
* https://www.nowcoder.com/kaoyan/detail/12002/68
*/

#include <stdio.h>
#include <stdlib.h>
#define N 101 //stringMAXSIZE

unsigned pos; //cur_str
char str[N];  //get testdata from console.

typedef struct example{
    struct Node* lchild;
    struct Node* rchild;
    char val;
}Node;


int getLen(char* s){
    char* p = s;
    int ret = 0;

    while(*p){
        ret++;
        p++;
    }
    return ret;
}


int main(){
    gets(str);
    pos=0;
    int len = getLen(str);

    return 0;
}
