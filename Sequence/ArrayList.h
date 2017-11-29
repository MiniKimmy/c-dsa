#pragma once
#include <stdlib.h>
#include <stdio.h>
#define PRINT_STRING(x) printf("%s\n",x)

typedef enum Status {
    FALSE,
    TRUE
}Status;


typedef struct Array {
    int* pBase;         //指向数组Data
    int Size;           //最大长度
    int Count;          //目前长度
    double Increment;   //增长因子
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

//Array初始化
Array* ArrInit(int size)
{
    Array* ret = (Array*)malloc(sizeof(Array));
    if (NULL == ret) {
        PRINT_STRING("Array动态分配内存失败!");
        exit(-1);
        return NULL;
    }
    ret->Size = size;
    ret->Count = 0;
    ret->pBase = (int *)malloc(sizeof(int) * (size + 1));
    ret->Increment = 2;
    return ret;
}

//通过手动赋值Array的value
void CreateArray_ByInputKeyCode(Array * arr)
{
    if (NULL == arr) {
        PRINT_STRING("Array为NUll");
        return;
    }
    printf("当前数组的长度为 : %d\n",arr->Size);
    int size;
    PRINT_STRING("请输入初始化数组的元素数目Count: ");
    scanf_s("%d", &size);
    while (size > arr->Size)
    {
        printf("请输入一个小于等于%d的数值\n",arr->Size);
        scanf_s("%d", &size);
    }

    for (int i = 0; i < size; i++){
        printf("初始化第[%d]个元素的value为 :", i);
        int arg;
        scanf_s("%d", &arg);
        Append_Array(arr, arg);
    }
    return arr;
}

//Array全部打印
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

//判断Array是否为空
Status IsEmptyArray(Array * arr)
{
    if (arr == NULL) {
        PRINT_STRING("Array为NULL");
        exit(-1);
    }

    if (arr->Count == 0) return TRUE;
    else return FALSE;
}

//判断数组是否已满
Status IsFullArray(Array * arr)
{
    if (arr == NULL) {
        PRINT_STRING("Array为NULL");
        exit(-1);
    }

    if (arr->Count == arr->Size) return TRUE;
    else return FALSE;
}

//向数组末尾追加新元素
void Append_Array(Array * arr, int value)
{
    if (IsFullArray(arr)) {
        PRINT_STRING("超出数组边界");
        return;
    }

    arr->pBase[arr->Count] = value;
    arr->Count++;
    return;
}

//插入指定index的value到数组内
void Insert_Array(Array * arr, int index, int value)
{
    if (IsFullArray(arr)) {
        PRINT_STRING("超出数组边界");
        return;
    }

    if (arr->Count <= index || index < 0) {
        printf("无法访问第[%d]个位置的value\n", index);
        return;
    }

    for (int i = arr->Count - 1; i >= index; i--) {
        arr->pBase[i + 1] = arr->pBase[i];
    }
    arr->Count++;
    arr->pBase[index] = value;
    return;
}

//Delect指定index的value
void Delete_Array(Array * arr, int index)
{
    if (IsEmptyArray(arr)) {
        PRINT_STRING("Array无任何元素");
        return;
    }
    if (arr->Count <= index || index < 0) {
        printf("无法删除第[%d]个位置的value\n", index);
        return;
    }

    for (int i = index + 1; i < arr->Count; i++) {
        arr->pBase[i - 1] = arr->pBase[i];
    }
    arr->Count--;
    return;
}

//销毁Array
void Destroy_Array(Array** arr)
{
    free(*arr);
    *arr = NULL;
    return;
}

//Array获取指定index的value
int GetValue_Array(Array* arr, int index)
{
    if (IsEmptyArray(arr)) {
        PRINT_STRING("Array无任何元素");
        exit(-1);
    }
    if (arr->Count <= index || index < 0) {
        printf("无法获取第[%d]个位置的value\n", index);
        exit(-1);
    }
    return arr->pBase[index];
}

//Array倒置
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

//Array长度动态扩展
void Allocate_Array(Array * arr)
{
    if (arr == NULL) {
        PRINT_STRING("Array为Null");
        return;
    }

    if (arr->Size >= 4 * 1000) arr->Increment = 1.25;    //1.25倍的速度
    int* ret = (int*)malloc(sizeof(int)* arr->Size * arr->Increment);
    if (NULL == ret) {
        PRINT_STRING("动态扩展分配失败!");
        return;
    }
    //Copy到新数组ret
    for (int i = 0; i < arr->Count; i++){
        ret[i] = arr->pBase[i];
    }
    arr->Size = arr->Size * arr->Increment;      //修改最大长度,Count不需要变
    int* p = arr->pBase;                         //释放原来的数组
    arr->pBase = ret;
    free(p);
    return;
}

//Array目前元素个数
int GetSize_Array(Array * arr)
{
    if (arr == NULL) {
        PRINT_STRING("Array为NULL");
        return 0;
    }
    return arr->Count;
}