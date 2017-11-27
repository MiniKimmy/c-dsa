#pragma once
#include<stdio.h>
#include<stdlib.h>
#define PRINT_STRING(x) printf("%s\n",x)

typedef int TElement;  //include到其他文件时候需要考虑修改该类型和sort的修改判断条件

#pragma region Functions
void QuickSort(TElement* arr, int arrsize);
void _QuickSort(TElement* arr, int left, int right);
int partition(TElement* arr, int left, int right);
#pragma endregion

//默认第一个元素为切分元素

/*(内部方法)快速排序*/
void _QuickSort(TElement* arr, int left, int right)
{
    if (right <= left) return;

    int j = partition(arr, left, right);
    _QuickSort(arr, left, j - 1);
    _QuickSort(arr, j + 1 , right);
}

/*(外部方法)快速排序*/
void QuickSort(TElement* arr, int arrsize)
{
    if (arr == NULL || arrsize <= 1) return;
    _QuickSort(arr, 0, arrsize - 1);
    return;
}

/*切分函数，返回切分元素的index*/
/*right:数组最右边的元素index*/
/*left:数组最左边元素的index(默认=1 初始)*/
/*e:切分元素的value*/
int partition(TElement* arr, int left, int right)
{
    int markright = right;  //右index的标记,右遍历的起始值,遇到左index标记就break,记录右子数组第一个index

    for (int i = left + 1; i < markright; i++) {
        if (arr[i] >= arr[left]) {
            for (int j = markright; j > i; j--) {
                markright = j - 1;
                if (markright <= i) break;
                if (arr[j] <= arr[left]) {
                    TElement temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                    break;
                }
            }
        }
        else if (i + 1 == markright && arr[left] > arr[markright]) {
            markright++;
        }
    }

    if (markright == right && arr[left] > arr[markright]) {
        TElement temp = arr[left];
        arr[left] = arr[markright];
        arr[markright] = temp;
        return markright;
    }
    else {
        TElement temp = arr[left];
        arr[left] = arr[markright - 1];
        arr[markright - 1] = temp;
        return markright - 1;
    }
}
