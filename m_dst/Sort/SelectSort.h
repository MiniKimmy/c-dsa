#pragma once
#include<stdio.h>
#include<stdlib.h>

typedef int TElement;  //include�������ļ�ʱ����Ҫ�����޸ĸ����ͺ�sort���޸��ж�����

/*ѡ������*/
/*arr:����*/
/*arrsize:���鳤��*/
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
