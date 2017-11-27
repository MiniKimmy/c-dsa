#pragma once
#include<stdio.h>
#include<stdlib.h>
#define PRINT_STRING(x) printf("%s\n",x)

typedef int TElement;  //include�������ļ�ʱ����Ҫ�����޸ĸ����ͺ�sort���޸��ж�����

#pragma region Functions
void QuickSort(TElement* arr, int arrsize);
void _QuickSort(TElement* arr, int left, int right);
int partition(TElement* arr, int left, int right);
#pragma endregion

//Ĭ�ϵ�һ��Ԫ��Ϊ�з�Ԫ��

/*(�ڲ�����)��������*/
void _QuickSort(TElement* arr, int left, int right)
{
    if (right <= left) return;

    int j = partition(arr, left, right);
    _QuickSort(arr, left, j - 1);
    _QuickSort(arr, j + 1 , right);
}

/*(�ⲿ����)��������*/
void QuickSort(TElement* arr, int arrsize)
{
    if (arr == NULL || arrsize <= 1) return;
    _QuickSort(arr, 0, arrsize - 1);
    return;
}

/*�зֺ����������з�Ԫ�ص�index*/
/*right:�������ұߵ�Ԫ��index*/
/*left:���������Ԫ�ص�index(Ĭ��=1 ��ʼ)*/
/*e:�з�Ԫ�ص�value*/
int partition(TElement* arr, int left, int right)
{
    int markright = right;  //��index�ı��,�ұ�������ʼֵ,������index��Ǿ�break,��¼���������һ��index

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
