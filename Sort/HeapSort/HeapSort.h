#pragma once
#include<stdio.h>
#include<stdlib.h>
#define PRINT_STRING(x) printf("%s\n",x)

typedef int PQElement;  //IncludeʱҪ�����Ƿ��޸ĸ�����
#pragma region Heap
typedef struct Heap {
    PQElement* pBase;   //��[1]��ʼ������
    int count;          //Ԫ������
}Heap;
#pragma endregion

#pragma region Functions
Heap* InitHeap(int* arr, int size);
void Delete(Heap * H);
PQElement* HeapSort(PQElement* arr, int size);
void Sink(int* arr, int size, int k);
#pragma endregion

/*��ʼ��Heap:�������[1]��ʼ��*/
/*arr:�ײ�����*/
/*size:���鳤��*/
Heap* InitHeap(int* arr, int size)
{
    Heap* ret = (Heap*)malloc(sizeof(Heap));
    if (ret == NULL) {
        PRINT_STRING("Heap��ʼ����̬�����ڴ�ʧ��");
        exit(-1);
    }

    ret->pBase = (PQElement*)malloc(sizeof(PQElement) * (size + 1));
    if (ret->pBase == NULL) {
        PRINT_STRING("pBase[]��ʼ����̬�����ڴ�ʧ��");
        exit(-1);
    }

    //�������Ƶ�[1]��ʼ
    for (int i = 0; i < size; i++){
        ret->pBase[i + 1] = arr[i];
    }
    ret->count = size;
    return ret;
}

/*arr:���顾������malloc�����顿*/
/*size:�����С*/
/*Ĭ�ϴ�С��������*/
PQElement* HeapSort(PQElement* arr,int size)
{
    Heap* H = InitHeap(arr,size);
    for (int i = H->count/ 2; i >= 1; i--){
        Sink(arr,H->count,i);
    }

    while (H->count >= 1) {
        arr[size - H->count] = H->pBase[1];
        printf("[%d] = %d\n", size - H->count, arr[size - H->count]);
        Delete(H);
    }
    free(H);
    return arr;
}

/*���ڲ�������ɾ��Root*/
void Delete(Heap * H)
{
    H->pBase[1] = H->pBase[H->count];
    H->count--;
    Sink(H->pBase,H->count, 1);
    return;
}

/*���ڲ��������³�*/
/*arr : �ײ�����*/
/*size : ����Ԫ���ܸ���*/
/*k : ��ʼ�³���key*/
void Sink(int* arr, int size ,int k)
{
    int flag = k;
    while (flag * 2 <= size) {
        int index = 2 * flag;
        if (index < size && arr[index] > arr[index + 1]) {
            index++;
        }
        if (arr[flag] > arr[index]) {
            PQElement temp = arr[flag];
            arr[flag] = arr[index];
            arr[index] = temp;
        }
        flag = index;
    }
}
