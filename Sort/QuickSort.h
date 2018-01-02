#pragma once
#include<stdio.h>
#include<stdlib.h>
#define PRINT_STRING(x) printf("%s\n",x)

typedef int TElement;  //include�������ļ�ʱ����Ҫ�����޸ĸ����ͺ�sort���޸��ж�����

//������ʽ
typedef enum QuickSortType{
    TwoWay,     //˫·����
    ThreeWay,   //��·����
}QuickSortType;

#pragma region Functions
void QuickSort(TElement* arr, int arrsize);
void QuickSortTwoWay(TElement* arr, int left, int right);
void QuickSortThreeWay(TElement* arr, int left, int right);
int partition(TElement* arr, int left, int right);
int _partition(TElement* arr, int left, int right);
int __partition(TElement* arr, int left, int right);
void InsertSort(TElement* arr, int left, int right);
void _QuickSortThreeWay(TElement* arr, int left, int right);
#pragma endregion

/*(�ⲿ����)��������*/
/*arr: ����*/
/*arrsize: ���鳤��*/
/*QuickSortType: ������ʽenum: TwoWay:˫·����, ThreeWay:��·����*/
void QuickSort(TElement* arr, int arrsize, QuickSortType type)
{
    if (arr == NULL || arrsize <= 1) return;

    if (type == TwoWay) {
        //�����һ��Ԫ��
        if (arrsize > 2) {
            int mid = arrsize / 2;
            TElement* temp = arr[0];
            arr[0] = arr[mid];
            arr[mid] = temp;
        }
        QuickSortTwoWay(arr, 0, arrsize - 1);
    }else {
        _QuickSortThreeWay(arr, 0, arrsize - 1);
    }

    return;
}

/*(�ڲ�����)˫·����*/
void QuickSortTwoWay(TElement* arr, int left, int right)
{
    //���鳤���ڵ���10ʱ�ò�������
    if (right <= left + 10) return InsertSort(arr, left, right);

    int j = __partition(arr, left, right);
    QuickSortTwoWay(arr, left, j - 1);
    QuickSortTwoWay(arr, j + 1, right);
}

/*�зֺ�����forѭ��X2���������з�Ԫ�ص�index*/
/*right:�������ұߵ�Ԫ��index*/
/*left:���������Ԫ�ص�index*/
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

/*�зֺ���(whileѭ��x2),�����з�Ԫ�ص�index*/
/*right:�������ұߵ�Ԫ��index*/
/*left:���������Ԫ�ص�index*/
int _partition(TElement* arr, int left, int right)
{
    int i = left + 1;
    int j = right;

    while (1){
        while (i <= right && arr[i] <= arr[left])     i++;
        while (j >= left + 1 && arr[j] >= arr[left])  j--;

        if (i > j) break;
        TElement temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        i++;
        j--;
    }

    TElement temp = arr[left];
    arr[left] = arr[j];
    arr[j] = temp;
    return j;
}

/*�зֺ���(for+while)�������з�Ԫ�ص�index*/
/*right:�������ұߵ�Ԫ��index*/
/*left:���������Ԫ�ص�index*/
int __partition(TElement* arr, int left, int right)
{
    int j = right + 1;

    for (int i = left + 1; i < j; i++) {
        if (arr[i] >= arr[left]) {
            while (j > i && arr[--j] >= arr[left]);

            if (j <= i) break;
            TElement temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    j--;
    TElement temp = arr[left];
    arr[left] = arr[j];
    arr[j] = temp;
    return j;
}

/*����5~15֮��ʱ����ʹ�ò�������*/
void InsertSort(TElement* arr, int left, int right)
{
    if (right <= left) return;

    for (int i = left + 1; i <= right; i++) {
        for (int j = i - 1; j >= left && arr[j] > arr[j + 1]; j--) {
            TElement temp = arr[j + 1];
            arr[j + 1] = arr[j];
            arr[j] = temp;
        }
    }
    return;
}

/*(�ڲ�����)��·����*/
void QuickSortThreeWay(TElement* arr, int left, int right)
{
    if (right <= left) return;

    int i = left;
    int j = left + 1;
    int k = right;

    TElement v = arr[left];

    while (j <= k) {
        if (arr[j] < v) {
            TElement temp = arr[j];
            arr[j] = arr[i];
            arr[i] = temp;
            i++;
            j++;
        }
        else if (arr[j] > v) {
            TElement temp = arr[j];
            arr[j] = arr[k];
            arr[k] = temp;
            k--;
        }
        else {
            j++;
        }
    }

    QuickSortThreeWay(arr, left, i - 1);
    QuickSortThreeWay(arr, k + 1, right);
    return;
}

/*(�ڲ�����)��·����*/
/*[����v��¼arr[left]��д��]*/
void _QuickSortThreeWay(TElement* arr, int left, int right)
{
    if (right <= left) return;

    int i = left;        //���������һ��index
    int j = left + 1;    //���������һ��index
    int k = right;       //���������һ��index

    while (j <= k) {
        if (arr[j] < arr[i]) {
            TElement temp = arr[j];
            arr[j] = arr[i];
            arr[i] = temp;
            i++;
            j++;
        }else if (arr[j] > arr[i]) {
            TElement temp = arr[j];
            arr[j] = arr[k];
            arr[k] = temp;
            k--;
        }else {
            j++;
        }
    }

    _QuickSortThreeWay(arr, left, i - 1);
    _QuickSortThreeWay(arr, k + 1, right);
    return;
}
