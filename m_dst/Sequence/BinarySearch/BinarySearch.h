#include<stdio.h>
#include<stdlib.h>
#define PRINT_STRING(x) printf("%s\n",x)

typedef int TElement;     //import到其他文件时候需要修改该类型

#pragma region Functions
int BinarySort(TElement* arr, int size, TElement target);
int BinarySort_Inner(TElement* arr, int left, int right, TElement target);
#pragma endregion

/*二分查找-外部方法*/
/*传入有序的TElemet[]*/
int BinarySort(TElement* arr, int size,TElement target)
{
    if (arr[size - 1] < target || arr[0] > target) return;
    return BinarySort_Inner(arr, 0, size - 1,target);
}


/*二分查找[递归]-内部方法*/
int BinarySort_Inner(TElement* arr, int left, int right, TElement target)
{
    int mid = (right - left + 1) / 2 + left;  //中间的index

    if (arr[mid] == target)  return mid;
    if (arr[mid] < target) return BinarySort_Inner(arr, mid + 1, right,target);
    else return BinarySort_Inner(arr, left, mid - 1, target);
}
