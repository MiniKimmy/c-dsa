## Number Steps

Starting from point (0,0) on a plane, we have written all non-negative integers 0,1,2, ... as shown in the figure. For example, 1, 2, and 3 has been written at points (1,1), (2,0), and (3, 1) respectively and this pattern has continued.

You are to write a program that reads the coordinates of a point (x, y), and writes the number (if any) that has been written at that point. (x, y) coordinates in the input are in the range 0...5000.
<br/>
<img src="https://raw.githubusercontent.com/MiniKimmy/c-dsa/master/nowcoder/Peking%20University/easy/numberSteps/img.png" alt="can't find.png" width="250px">
<br/>

## Input
each line, there is x, and y representing the coordinates (x, y) of a point.

## Output
For each point in the input, write the number written at that point or write No Number if there is none.

## hint:
```
    1.see the graph, and find the regulation between x or y with (x,y)
    2.watch out the points didnt exist.
```


## Solution
```c
#include<stdio.h>
#include<stdlib.h>

int abs(int a){
    if(a<0) return -a;
    else return a;
}

void getNumber(int x,int y){
    if(y>x || x-1==y || y+2<x){
         printf("%s","No Number");
    }else{
        int ret = -1;
        if(x%2==0 && y%2==0) ret = x+y;
        else if(x>y) ret = y*2+1;
        else ret = x*2-1;

        printf("%d",ret);
    }
}

int main(void){
    int x;
    int y;
    scanf("%d%d",&x,&y);
    getNumber(x,y);
    return 0;
}

```
