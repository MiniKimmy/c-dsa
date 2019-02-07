* https://www.nowcoder.com/activity/oj
* https://www.nowcoder.com/kaoyan/detail/12002/68

## Env
* Need predefined
* Need typedef
``` c
#include <stdio.h>

typedef struct example{
    struct Node* lchild;
    struct Node* rchild;
    char val;
}Node;
```
## INPUT
### Read a Line string
**Example 1:**
``` c
 input:"abcdefg" \n  //('\n' is ending)
 str = "abcdefg"
//--------------------------------------

unsigned pos; //cur_str
char str[N];  //get testdata from console.

int getLen(char* s){
    char* p = s;
    int ret = 0;

    while(*p){
        ret++;
        p++;
    }

    return ret;
}

int main(void){
  pos = 0;
  gets(str);
  int len = getLen(str);

  return 0;
}
```
### read int[]
**Example 1:**
``` c
int test[5]
   intput: 1 2 3 4
   test = {1,2,3,4, 1118823424};

int test[5]
   intput: 1 2 3 4 5
   test = {1,2,3,4,5};
//-----------------------------

int main(){
  int test[5];
  int i = 0;
  while(scanf("%d", &(test[i++])) != EOF);
}
```
### Read Temp and int[]
**Example 3:**
``` c
intput:100 1 2 3 4 5
test[5] test={1,2,3,4,5};
temp=100;
//---------------------------

int main(){
    int temp;
    scanf("%d",&temp);

    int test[5];
    int i = 0;
    while(i<5){
        scanf("%d", &(test[i++]));
    }

```
### read Temp1 and Temp2
**Example 4:**
``` c
input 100 200
temp1 = 100
temp2 = 200
//------------------------

int main(void){
    int temp1,temp2;
    scanf("%d%d",&temp1,&temp2);

    return 0;
}
```