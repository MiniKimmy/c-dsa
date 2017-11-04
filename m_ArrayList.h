#pragma once
#include <stdlib.h>
#include <stdio.h>

#pragma region Status
#define FALSE 0
#define TRUE 1
typedef int Status;
#pragma endregion

typedef struct Arr {
    int* pBase;          //指向数组Data
    int Size;          //最大长度
    int Count;          //目前长度
    double Increment; //增长因子
}Arr;

#pragma region Functions
Arr* ArrInit(int size);
Arr* ArrInit_InputKeyCode();
Status IsEmpty(Arr* arr);
void ShowArr(Arr* arr);
Status IsFull(Arr* arr);
void Append(Arr* arr, int value);
void Insert(Arr* arr, int index, int value);
void Delete(Arr* arr, int index);
int Get(Arr* arr, int index);
void Inversion(Arr* arr);
void Arr_BubbleSort(Arr* arr);
void Arr_InsetSort(Arr* arr);
Status IsBeingFull(Arr* arr);
void Allocate(Arr* arr);
int GetSize(Arr* arr);
//void QuickSort();    //快排【待整理】
#pragma endregion

//Arr初始化
Arr* ArrInit(int size)
{
    Arr* ret = (Arr*)malloc(sizeof(Arr));    //局部指针动态分配内存
    if (NULL == ret) {
        printf("Arr动态分配内存失败！\n");
        exit(-1);                            //强制退出
        return NULL;
    }
    ret->Size = size;
    ret->Count = 0;
    ret->pBase = (int *)malloc(sizeof(int) *size);
    ret->Increment = 2;                        //一开始增长因子为2倍，2倍速度扩展数组长度
    return ret;                                //返回之后局部指针变量消失，但是地址里面的value还在
}

//Arr手动初始化
Arr* ArrInit_InputKeyCode()
{
    Arr* ret = (Arr*)malloc(sizeof(Arr));
    if (NULL == ret) {
        printf("Arr动态分配内存失败！\n");
        exit(-1);
        return NULL;
    }

    int size;
    printf("请输入初始化数组的元素数目Count :");
    scanf_s("%d", &size);

    ret->Size = size * 2;    //最大长度设置为2倍
    ret->Count = 0;
    ret->pBase = (int *)malloc(sizeof(int) * ret->Size);
    ret->Increment = 2;                        //一开始增长因子为2倍，2倍速度扩展数组长度
    for (int i = 0; i < size; i++)
    {
        printf("初始化第[%d]个元素的value为 :",i);
        int arg;
        scanf_s("%d", &arg);
        Append(ret, arg);
    }
    return ret;
}

//Arr全部打印
void ShowArr(Arr* arr)
{
    if (IsEmpty(arr))
        printf("Arr is Null");
    else
    {
        for (int i = 0; i < arr->Count; i++)
        {
            printf("%d ", arr->pBase[i]);
        }
        printf("\n");
    }
    return;
}

//Arr是否为空
Status IsEmpty(Arr* arr)
{
    if(arr == NULL){
        printf("参数为NULL\n");
        exit(-1);
    }

    if (arr->Count == 0) return TRUE;
    else return FALSE;
}

//Arr是否为满
Status IsFull(Arr* arr)
{
    if(arr == NULL){
        printf("参数为NULL\n");
        exit(-1);
    }

    if (arr->Count == arr->Size) return TRUE;
    else return FALSE;
}

//Arr追加
void Append(Arr* arr, int value)
{
    if (IsFull(arr)) {
        printf("Arr is full!\n");
        return;
    }
    else{
        arr->pBase[arr->Count] = value;
        arr->Count++;
        //动态扩充数组
        if (IsBeingFull(arr)) Allocate(arr);
    }
    return;
}

//Arr插入指定index的value,已有值的地方后移
void Insert(Arr* arr,int index,int value)
{
    if (IsFull(arr)) {
        printf("Arr is full!\n");
        return;
    }
    if (arr->Count <= index || index < 0) {
        printf("无法访问第[%d]个位置的value\n",index);
        return;
    }

    for (int i = arr->Count - 1; i >= index; i--){
        arr->pBase[i + 1] = arr->pBase[i];
    }
    arr->Count++;
    arr->pBase[index] = value;
    //动态扩充数组
    if (IsBeingFull(arr)) Allocate(arr);
    return;
}

//ArrDelect指定index的value
void Delete(Arr* arr,int index)
{
    if (IsEmpty(arr)) {
        printf("Arr is Empty!\n");
        return;
    }
    if (arr->Count <= index || index < 0) {
        printf("Please input a right index!\n");
        return;
    }
    else{
        for (int i = index + 1; i < arr->Count; i++){
            arr->pBase[i-1] = arr->pBase[i];
        }
        arr->Count--;
    }
    return;
}

//Arr获取指定index的value
int Get(Arr* arr,int index)
{
    if (IsEmpty(arr)) {
        printf("Arr is Empty!\n");
        exit(-1);
    }
    if (arr->Count <= index || index < 0) {
        printf("无法获取第[%d]个位置的value\n",index);
        exit(-1);
    }
    else {
        return arr->pBase[index];
    }
}

//Arr倒置
void Inversion(Arr* arr)
{
    if (IsEmpty(arr)){
        printf("Arr is empty!\n");
    }
    else{
        for (int i = 0; i < arr->Count / 2; i++) // 0 ~ 对半整除
        {
            int temp = arr->pBase[i];
            arr->pBase[i] = arr->pBase[arr->Count - 1 - i];
            arr->pBase[arr->Count - 1 - i] = temp;
        }
    }
    return;
}

//Arr 将要满了的时候
Status IsBeingFull(Arr* arr)
{
    if(arr == NULL){
        printf("参数为NULL\n");
        return;
    }

    if (arr->Count + 3 == arr->Size) return TRUE;
    else return FALSE;
}

//Arr长度动态扩展
void Allocate(Arr* arr)
{
    if(arr == NULL){
        printf("参数为NULL\n");
        return;
    }

    if (arr->Size >= 4 * 1000)    arr->Increment = 1.25;    //1.25倍的速度

    int* ret = (int*)malloc(sizeof(int)* arr->Size * arr->Increment);
    if (NULL == ret){
        printf("动态扩展分配失败!\n");
        return;
    }
    for (int i = 0; i < arr->Count; i++)    //把int[]所有value 复制到新数组ret
    {
        ret[i] = arr->pBase[i];
    }

    arr->Size = arr->Size * arr->Increment;    //修改最大长度 , Count不需要变
    int* p = arr->pBase;                        //释放原来的数组
    arr->pBase = ret;
    free(p);
    return;
}

//Arr目前元素个数
int GetSize(Arr* arr)
{
    if (arr == NULL) {
        printf("请检查参数是否为NULL\n");
        exit(-1);
    }
    return arr->Count;
}

//Arr_BubbleSort
void Arr_BubbleSort(Arr* arr)
{
    if(arr == NULL){
        printf("参数为NULL\n");
        return;
    }

    for (int i = 0; i < arr->Count - 1; ++i)
    {
        for (int j = i+1; j < arr->Count; ++j)
        {
            if (arr->pBase[i] > arr->pBase[j])
            {
                int temp = arr->pBase[i];
                arr->pBase[i] = arr->pBase[j];
                arr->pBase[j] = temp;
            }
        }
    }
    return;
}

//Arr InsertSort
void Arr_InsetSort(Arr* arr)
{
    if(arr == NULL){
        printf("参数为NULL\n");
        return;
    }

    for (int i = 0; i < arr->Count - 1; i++)
    {
        int index = i + 1;
        int ret_index = i;
        while ( index < arr->Count)    //最小的放前面
        {
            if (arr->pBase[ret_index] > arr->pBase[index])
            {
                ret_index = index;
                index++;
            }
            else{
                index++;
            }
        }
        int temp = arr->pBase[i];
        arr->pBase[i] = arr->pBase[ret_index];
        arr->pBase[ret_index] = temp;
    }
    return;
}
