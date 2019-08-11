#pragma once
#include<stdio.h>
#include<stdlib.h>

typedef int TElement;  //include到其他文件时候需要考虑修改该类型和sort的修改判断条件

/*插入排序*/
/*arr:数组*/
/*arrsize:数组长度*/
void InsertSort(TElement* arr, int arrsize)
{
    for (int i = 1; i < arrsize; i++) {
        for (int j = i - 1; j >= 0 && arr[j] > arr[j+1]; j--){
            TElement temp = arr[j+1];
            arr[j+1] = arr[j];
            arr[j] = temp;
        }
    }
    return;
}

/*插入排序（右移的插入排序1）*/
/*arr:数组*/
/*arrsize:数组长度*/
void _InsertSort(TElement* arr, int arrsize)
{
    for (int i = 1; i < arrsize; i++) {
        TElement temp = arr[i];
        int k = i;
        for (int j = i - 1; j >= 0 && arr[j] > temp; j--) {
            arr[j + 1] = arr[j];
            k = j;
        }
        arr[k] = temp;
    }
    return;
}

/*插入排序（右移的插入排序2）*/
/*arr:数组*/
/*arrsize:数组长度*/
void __InsertSort(TElement* arr, int arrsize)
{
    for (int i = 1; i < arrsize; i++) {
        TElement temp = arr[i];
        int j = i - 1;
        for (; j >= 0 && arr[j] > temp; j--) {
            arr[j + 1] = arr[j];
        }

        //跳出j == -1 跳出循环情况 + 遇到右移时[j+1]位置 = temp情况 --> [j+1] = temp
        arr[j + 1] = temp;
    }
    return;
}
