#include<stdio.h>
#include<stdlib.h>


#include "HeapSort.h"

int main()
{
    int* arr = (int*)malloc(sizeof(int) * 8);
    arr[0] = 0;
    arr[1] = 7;
    arr[2] = 2;
    arr[3] = 8;
    arr[4] = 10;
    arr[5] = 5;
    arr[6] = 20;
    arr[7] = 1;
    //int arr[] = { 0,7,2,8,10,5,20,1 };  //±ØÐëmalloc
    HeapSort(arr, 8);

    for (int i = 0; i < 8; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    system("pause");
    return 0;
}
