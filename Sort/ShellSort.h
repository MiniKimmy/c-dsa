#pragma once
#include<stdio.h>
#include<stdlib.h>

typedef int TElement;  //include到其他文件时候需要考虑修改该类型和sort的修改判断条件

/*希尔排序*/
/*arr:数组*/
/*arrsize:数组长度*/
void ShellSort(TElement* arr, int arrsize)
{
    int h = 1;
    while (h < arrsize / 3) h = 3 * h + 1;

    while (h >= 1)
    {
        for (int i = h; i < arrsize; i++) {
            for (int j = i - h; j >= h - 1 && arr[j] > arr[j + h]; j -= h) {
                TElement temp = arr[j];
                arr[j] = arr[j + h];
                arr[j + h] = temp;
            }
        }
        h = h / 3;
    }
    return;
}


/*希尔排序（右移的希尔排序1）*/
/*arr:数组*/
/*arrsize:数组长度*/
void _ShellSort(TElement* arr, int arrsize)
{
    int h = 1;
    while (h < arrsize / 3) h = 3 * h + 1;

    while (h >= 1){
        for (int i = h; i < arrsize; i++) {
            TElement temp = arr[i];
            int k = i;
            for (int j = i - h; j >= h - 1 && arr[j] > temp; j -= h){
                arr[j + h] = arr[j];
                k = j;
            }
            arr[k] = temp;
        }
        h = h / 3;
    }
    return;
}

/*希尔排序（右移的希尔排序2）*/
/*arr:数组*/
/*arrsize:数组长度*/
void __ShellSort(TElement* arr, int arrsize)
{
    int h = 1;
    while (h < arrsize / 3) h = 3 * h + 1;

    while (h >= 1){
        for (int i = h; i < arrsize; i++) {
            TElement temp = arr[i];
            int j = i - h;
            for (; j >= h - 1 && arr[j] > temp; j -= h) {
                arr[j + h] = arr[j];
            }
            arr[j + h] = temp;
        }
        h = h / 3;
    }
    return;
}
