## 成绩排序

输入任意（用户，成绩）序列，可以获得成绩从高到低或从低到高的排列,相同成绩
都按先录入排列在前的规则处理。

**Example:**
```
jack      70
peter     96
Tom       70
smith     67

从高到低  成绩
peter     96
jack      70
Tom       70
smith     67

从低到高
smith     67
jack      70
Tom       70
peter     96
```

## Note
**Input:**
```
输入多行，先输入要排序的人的个数，然后输入排序方法0（降序）或者1（升序）再分别输入他们的名字和成绩，以一个空格隔开
```
**Output:**
```
按照指定方式输出名字和成绩，名字和成绩之间以一个空格隔开
```

**Example 1:**
```
input:
3
0
fang 90
yang 50
ning 70

output:
fang 90
ning 70
yang 50
```

## hints
```
    insertSort
    ps:name and its mark swap at the same time.
```

## Solution

``` c
#include<stdio.h>
#include<stdlib.h>
#define NameMaxSize 20
typedef char* String;

int compare(int a,int b){
    if(a > b) return 1;
    else if(a<b)return -1;
    else return 0;
}

void insertSort(int n, int order, int* marks, String* names){
    int ord = order == 1? 1:-1;

    for(int i=1;i<n;i++){
        int pos = i;
        int temp = marks[i];
        String name = names[i];

        for(int j = i-1; j>=0 && compare(marks[j],temp) == ord; --j){
            marks[j+1] = marks[j];
            names[j+1] = names[j];
            pos = j;
        }

        if(pos != i){
            marks[pos] = temp;
            names[pos] = name;
        }
    }
}

int main(void){
    int n,order;

    while(scanf("%d",&n) != EOF){
        scanf("%d\n",&order);

        int* marks = (int*)malloc(sizeof(int) * n);
        String* names = (String*)malloc(sizeof(String) * n);

        for(int i = 0;i<n;i++){
            names[i] = (String)malloc(sizeof(char) * NameMaxSize);
            scanf("%s %d\n",names[i],&marks[i]);
        }

        insertSort(n,order,marks,names);

        for(int i = 0;i<n;i++){
            printf("%s %d\n",names[i],marks[i]);
        }
    }
    return 0;
}

```