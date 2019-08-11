#pragma once
#include<stdio.h>
#include<stdlib.h>
#define PRINT_STRING(x) printf("%s\n",x)

typedef int PQElement;  //Include时要考虑是否修改该类型
#pragma region Heap
typedef struct Heap {
    PQElement* pBase;   //从[1]开始的数组
    int count;          //元素总数
}Heap;
#pragma endregion

#pragma region Functions
Heap* InitHeap(int* arr, int size);
void Delete(Heap * H);
PQElement* HeapSort(PQElement* arr, int size);
void Sink(int* arr, int size, int k);
#pragma endregion

/*初始化Heap:把数组从[1]开始存*/
/*arr:底层数组*/
/*size:数组长度*/
Heap* InitHeap(int* arr, int size)
{
    Heap* ret = (Heap*)malloc(sizeof(Heap));
    if (ret == NULL) {
        PRINT_STRING("Heap初始化动态分配内存失败");
        exit(-1);
    }

    ret->pBase = (PQElement*)malloc(sizeof(PQElement) * (size + 1));
    if (ret->pBase == NULL) {
        PRINT_STRING("pBase[]初始化动态分配内存失败");
        exit(-1);
    }

    //数组右移到[1]开始
    for (int i = 0; i < size; i++){
        ret->pBase[i + 1] = arr[i];
    }
    ret->count = size;
    return ret;
}

/*arr:数组【必须是malloc的数组】*/
/*size:数组大小*/
/*默认从小到大排序*/
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

/*（内部方法）删除Root*/
void Delete(Heap * H)
{
    H->pBase[1] = H->pBase[H->count];
    H->count--;
    Sink(H->pBase,H->count, 1);
    return;
}

/*（内部方法）下沉*/
/*arr : 底层数组*/
/*size : 数组元素总个数*/
/*k : 开始下沉的key*/
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
