#pragma once
#include<stdio.h>
#include<stdlib.h>

typedef int TElement;  //include到其他文件时候需要考虑修改该类型和sort的修改判断条件

/*选择排序*/
/*arr:数组*/
/*arrsize:数组长度*/
void SelectSort(TElement* arr, int arrsize)
{
    for (int i = 0; i < arrsize - 1; i++) {
        int k = i;
        for (int j = i + 1; j < arrsize; j++) {
            if (arr[k] > arr[j])   k = j;
        }
        if (i != k) {
            TElement temp = arr[i];
            arr[i] = arr[k];
            arr[k] = temp;
        }
    }
    return;
}
