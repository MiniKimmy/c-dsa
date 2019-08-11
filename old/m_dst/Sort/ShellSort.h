#pragma once
#include<stdio.h>
#include<stdlib.h>

typedef int TElement;  //include�������ļ�ʱ����Ҫ�����޸ĸ����ͺ�sort���޸��ж�����

/*ϣ������*/
/*arr:����*/
/*arrsize:���鳤��*/
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


/*ϣ���������Ƶ�ϣ������1��*/
/*arr:����*/
/*arrsize:���鳤��*/
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

/*ϣ���������Ƶ�ϣ������2��*/
/*arr:����*/
/*arrsize:���鳤��*/
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
