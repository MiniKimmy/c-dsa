#pragma once
#include<stdio.h>
#include<stdlib.h>
#define PRINT_STRING(x) printf("%s\n",x)

typedef int TElement;  //include到其他文件时候需要考虑修改该类型和sort的修改判断条件

#pragma region Functions
void QuickSort(TElement* arr, int arrsize);
void _QuickSort(TElement* arr, int left, int right);
int partition(TElement* arr, int left, int right);
int _partition(TElement* arr, int left, int right);
int __partition(TElement* arr, int left, int right);
void InsertSort(TElement* arr, int left, int right);
#pragma endregion


/*(外部方法)快速排序*/
void QuickSort(TElement* arr, int arrsize)
{
    if (arr == NULL || arrsize <= 1) return;

    //随机第一个元素
    if (arrsize > 2) {
        int mid = arrsize / 2;
        TElement* temp = arr[0];
        arr[0] = arr[mid];
        arr[mid] = temp;
    }
    
    _QuickSort(arr, 0, arrsize - 1);
    return;
}

/*(内部方法)快速排序*/
void _QuickSort(TElement* arr, int left, int right)
{
    //数组长度在低于10时用插入排序
    if (right <= left + 10) return InsertSort(arr, left, right);

    int j = __partition(arr, left, right);
    _QuickSort(arr, left, j - 1);
    _QuickSort(arr, j + 1, right);
}

/*切分函数（for循环X2），返回切分元素的index*/
/*right:数组最右边的元素index*/
/*left:数组最左边元素的index*/
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

/*切分函数(while循环x2),返回切分元素的index*/
/*right:数组最右边的元素index*/
/*left:数组最左边元素的index*/
int _partition(TElement* arr, int left, int right)
{
    int i = left + 1;
    int j = right;

    while (1){
        while (i <= right && arr[i] <= arr[left])     i++;
        while (j >= left + 1 && arr[j] >= arr[left])  j--;

        if (i > j) break;
        TElement temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        i++;
        j--;
    }
    
    TElement temp = arr[left];
    arr[left] = arr[j];
    arr[j] = temp;
    return j;
}

/*切分函数(for+while)，返回切分元素的index*/
/*right:数组最右边的元素index*/
/*left:数组最左边元素的index*/
int __partition(TElement* arr, int left, int right)
{
    int j = right + 1;

    for (int i = left + 1; i < j; i++) {
        if (arr[i] >= arr[left]) {
            while (j > i && arr[--j] >= arr[left]);

            if (j <= i) break;
            TElement temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    j--;
    TElement temp = arr[left];
    arr[left] = arr[j];
    arr[j] = temp;
    return j;
}

/*当在5~15之间时，可使用插入排序*/
void InsertSort(TElement* arr, int left, int right)
{
    if (right <= left) return;

    for (int i = left + 1; i <= right; i++) {
        for (int j = i - 1; j >= left && arr[j] > arr[j + 1]; j--) {
            TElement temp = arr[j + 1];
            arr[j + 1] = arr[j];
            arr[j] = temp;
        }
    }
    return;
}
