#pragma once
#include<stdio.h>
#include<stdlib.h>

typedef int TElement;  //include�������ļ�ʱ����Ҫ�����޸ĸ����ͺ�sort���޸��ж�����

/*��������*/
/*arr:����*/
/*arrsize:���鳤��*/
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

/*�����������ƵĲ�������1��*/
/*arr:����*/
/*arrsize:���鳤��*/
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

/*�����������ƵĲ�������2��*/
/*arr:����*/
/*arrsize:���鳤��*/
void __InsertSort(TElement* arr, int arrsize)
{
    for (int i = 1; i < arrsize; i++) {
        TElement temp = arr[i];
        int j = i - 1;
        for (; j >= 0 && arr[j] > temp; j--) {
            arr[j + 1] = arr[j];
        }

        //����j == -1 ����ѭ����� + ��������ʱ[j+1]λ�� = temp��� --> [j+1] = temp
        arr[j + 1] = temp;
    }
    return;
}
