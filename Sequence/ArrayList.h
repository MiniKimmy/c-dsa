#pragma once
#include <stdlib.h>
#include <stdio.h>
#define PRINT_STRING(x) printf("%s\n",x)

typedef enum Status {
    FALSE,
    TRUE
}Status;


typedef struct Array {
    int* pBase;         //ָ������Data
    int Size;           //��󳤶�
    int Count;          //Ŀǰ����
    double Increment;   //��������
}Array;

#pragma region Functions
Array* ArrInit(int size);
void CreateArray_ByInputKeyCode(Array * arr);
Status IsEmptyArray(Array * arr);
void Traverse_Array(Array * arr);
Status IsFullArray(Array * arr);
void Append_Array(Array * arr, int value);
void Insert_Array(Array * arr, int index, int value);
void Delete_Array(Array * arr, int index);
int GetValue_Array(Array * arr, int index);
void Inversion_Array(Array* arr);
void Allocate_Array(Array* arr);
int GetSize_Array(Array* arr);
#pragma endregion

//Array��ʼ��
Array* ArrInit(int size)
{
    Array* ret = (Array*)malloc(sizeof(Array));
    if (NULL == ret) {
        PRINT_STRING("Array��̬�����ڴ�ʧ��!");
        exit(-1);
        return NULL;
    }
    ret->Size = size;
    ret->Count = 0;
    ret->pBase = (int *)malloc(sizeof(int) * (size + 1));
    ret->Increment = 2;
    return ret;
}

//ͨ���ֶ���ֵArray��value
void CreateArray_ByInputKeyCode(Array * arr)
{
    if (NULL == arr) {
        PRINT_STRING("ArrayΪNUll");
        return;
    }
    printf("��ǰ����ĳ���Ϊ : %d\n",arr->Size);
    int size;
    PRINT_STRING("�������ʼ�������Ԫ����ĿCount: ");
    scanf_s("%d", &size);
    while (size > arr->Size)
    {
        printf("������һ��С�ڵ���%d����ֵ\n",arr->Size);
        scanf_s("%d", &size);
    }

    for (int i = 0; i < size; i++){
        printf("��ʼ����[%d]��Ԫ�ص�valueΪ :", i);
        int arg;
        scanf_s("%d", &arg);
        Append_Array(arr, arg);
    }
    return arr;
}

//Arrayȫ����ӡ
void Traverse_Array(Array * arr)
{
    if (IsEmptyArray(arr))
        return;
    for (int i = 0; i < arr->Count; i++){
        printf("%d ", arr->pBase[i]);
    }
    PRINT_STRING("");
    return;
}

//�ж�Array�Ƿ�Ϊ��
Status IsEmptyArray(Array * arr)
{
    if (arr == NULL) {
        PRINT_STRING("ArrayΪNULL");
        exit(-1);
    }

    if (arr->Count == 0) return TRUE;
    else return FALSE;
}

//�ж������Ƿ�����
Status IsFullArray(Array * arr)
{
    if (arr == NULL) {
        PRINT_STRING("ArrayΪNULL");
        exit(-1);
    }

    if (arr->Count == arr->Size) return TRUE;
    else return FALSE;
}

//������ĩβ׷����Ԫ��
void Append_Array(Array * arr, int value)
{
    if (IsFullArray(arr)) {
        PRINT_STRING("��������߽�");
        return;
    }

    arr->pBase[arr->Count] = value;
    arr->Count++;
    return;
}

//����ָ��index��value��������
void Insert_Array(Array * arr, int index, int value)
{
    if (IsFullArray(arr)) {
        PRINT_STRING("��������߽�");
        return;
    }

    if (arr->Count <= index || index < 0) {
        printf("�޷����ʵ�[%d]��λ�õ�value\n", index);
        return;
    }

    for (int i = arr->Count - 1; i >= index; i--) {
        arr->pBase[i + 1] = arr->pBase[i];
    }
    arr->Count++;
    arr->pBase[index] = value;
    return;
}

//Delectָ��index��value
void Delete_Array(Array * arr, int index)
{
    if (IsEmptyArray(arr)) {
        PRINT_STRING("Array���κ�Ԫ��");
        return;
    }
    if (arr->Count <= index || index < 0) {
        printf("�޷�ɾ����[%d]��λ�õ�value\n", index);
        return;
    }

    for (int i = index + 1; i < arr->Count; i++) {
        arr->pBase[i - 1] = arr->pBase[i];
    }
    arr->Count--;
    return;
}

//����Array
void Destroy_Array(Array** arr)
{
    free(*arr);
    *arr = NULL;
    return;
}

//Array��ȡָ��index��value
int GetValue_Array(Array* arr, int index)
{
    if (IsEmptyArray(arr)) {
        PRINT_STRING("Array���κ�Ԫ��");
        exit(-1);
    }
    if (arr->Count <= index || index < 0) {
        printf("�޷���ȡ��[%d]��λ�õ�value\n", index);
        exit(-1);
    }
    return arr->pBase[index];
}

//Array����
void Inversion_Array(Array* arr)
{
    if (IsEmptyArray(arr)) return;

    for (int i = 0; i < arr->Count / 2; i++)
    {
        int temp = arr->pBase[i];
        arr->pBase[i] = arr->pBase[arr->Count - 1 - i];
        arr->pBase[arr->Count - 1 - i] = temp;
    }
    return;
}

//Array���ȶ�̬��չ
void Allocate_Array(Array * arr)
{
    if (arr == NULL) {
        PRINT_STRING("ArrayΪNull");
        return;
    }

    if (arr->Size >= 4 * 1000) arr->Increment = 1.25;    //1.25�����ٶ�
    int* ret = (int*)malloc(sizeof(int)* arr->Size * arr->Increment);
    if (NULL == ret) {
        PRINT_STRING("��̬��չ����ʧ��!");
        return;
    }
    //Copy��������ret
    for (int i = 0; i < arr->Count; i++){
        ret[i] = arr->pBase[i];
    }
    arr->Size = arr->Size * arr->Increment;      //�޸���󳤶�,Count����Ҫ��
    int* p = arr->pBase;                         //�ͷ�ԭ��������
    arr->pBase = ret;
    free(p);
    return;
}

//ArrayĿǰԪ�ظ���
int GetSize_Array(Array * arr)
{
    if (arr == NULL) {
        PRINT_STRING("ArrayΪNULL");
        return 0;
    }
    return arr->Count;
}