#pragma once
#include<stdio.h>
#include<stdlib.h>

typedef int TElement;  //include�������ļ�ʱ����Ҫ�����޸ĸ����ͺ�sort���޸��ж�����

/*ð������*/
/*arr:����*/
/*arrsize:���鳤��*/
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
