#include<stdio.h>
#include<stdlib.h>
#define PRINT_STRING(x) printf("%s\n",x)

typedef int TElement;     //import�������ļ�ʱ����Ҫ�޸ĸ�����

#pragma region Functions
int BinarySort(TElement* arr, int size, TElement target);
int BinarySort_Inner(TElement* arr, int left, int right, TElement target);
#pragma endregion

/*���ֲ���-�ⲿ����*/
/*���������TElemet[]*/
int BinarySort(TElement* arr, int size,TElement target)
{
    if (arr[size - 1] < target || arr[0] > target) return;
    return BinarySort_Inner(arr, 0, size - 1,target);
}


/*���ֲ���[�ݹ�]-�ڲ�����*/
int BinarySort_Inner(TElement* arr, int left, int right, TElement target)
{
    int mid = (right - left + 1) / 2 + left;  //�м��index

    if (arr[mid] == target)  return mid;
    if (arr[mid] < target) return BinarySort_Inner(arr, mid + 1, right,target);
    else return BinarySort_Inner(arr, left, mid - 1, target);
}
