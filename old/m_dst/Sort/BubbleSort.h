#pragma once
#include<stdio.h>
#include<stdlib.h>

typedef int TElement;  //include到其他文件时候需要考虑修改该类型和sort的修改判断条件

/*冒泡排序*/
/*arr:数组*/
/*arrsize:数组长度*/
void BubbleSort(TElement* arr,int arrsize)
{
    for (int i = 0; i < arrsize - 1; i++){
        for (int j = i+1; j < arrsize; j++){
            if (arr[i] > arr[j]) {
                TElement temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    return;
}
