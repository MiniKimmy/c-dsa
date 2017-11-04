#pragma once
#include <stdlib.h>
#include <stdio.h>

#pragma region Status
#define FALSE 0
#define TRUE 1
typedef int Status;
#pragma endregion

typedef struct Arr {
    int* pBase;          //ָ������Data
    int Size;          //��󳤶�
    int Count;          //Ŀǰ����
    double Increment; //��������
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
//void QuickSort();    //���š�������
#pragma endregion

//Arr��ʼ��
Arr* ArrInit(int size)
{
    Arr* ret = (Arr*)malloc(sizeof(Arr));    //�ֲ�ָ�붯̬�����ڴ�
    if (NULL == ret) {
        printf("Arr��̬�����ڴ�ʧ�ܣ�\n");
        exit(-1);                            //ǿ���˳�
        return NULL;
    }
    ret->Size = size;
    ret->Count = 0;
    ret->pBase = (int *)malloc(sizeof(int) *size);
    ret->Increment = 2;                        //һ��ʼ��������Ϊ2����2���ٶ���չ���鳤��
    return ret;                                //����֮��ֲ�ָ�������ʧ�����ǵ�ַ�����value����
}

//Arr�ֶ���ʼ��
Arr* ArrInit_InputKeyCode()
{
    Arr* ret = (Arr*)malloc(sizeof(Arr));
    if (NULL == ret) {
        printf("Arr��̬�����ڴ�ʧ�ܣ�\n");
        exit(-1);
        return NULL;
    }

    int size;
    printf("�������ʼ�������Ԫ����ĿCount :");
    scanf_s("%d", &size);

    ret->Size = size * 2;    //��󳤶�����Ϊ2��
    ret->Count = 0;
    ret->pBase = (int *)malloc(sizeof(int) * ret->Size);
    ret->Increment = 2;                        //һ��ʼ��������Ϊ2����2���ٶ���չ���鳤��
    for (int i = 0; i < size; i++)
    {
        printf("��ʼ����[%d]��Ԫ�ص�valueΪ :",i);
        int arg;
        scanf_s("%d", &arg);
        Append(ret, arg);
    }
    return ret;
}

//Arrȫ����ӡ
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

//Arr�Ƿ�Ϊ��
Status IsEmpty(Arr* arr)
{
    if(arr == NULL){
        printf("����ΪNULL\n");
        exit(-1);
    }

    if (arr->Count == 0) return TRUE;
    else return FALSE;
}

//Arr�Ƿ�Ϊ��
Status IsFull(Arr* arr)
{
    if(arr == NULL){
        printf("����ΪNULL\n");
        exit(-1);
    }

    if (arr->Count == arr->Size) return TRUE;
    else return FALSE;
}

//Arr׷��
void Append(Arr* arr, int value)
{
    if (IsFull(arr)) {
        printf("Arr is full!\n");
        return;
    }
    else{
        arr->pBase[arr->Count] = value;
        arr->Count++;
        //��̬��������
        if (IsBeingFull(arr)) Allocate(arr);
    }
    return;
}

//Arr����ָ��index��value,����ֵ�ĵط�����
void Insert(Arr* arr,int index,int value)
{
    if (IsFull(arr)) {
        printf("Arr is full!\n");
        return;
    }
    if (arr->Count <= index || index < 0) {
        printf("�޷����ʵ�[%d]��λ�õ�value\n",index);
        return;
    }

    for (int i = arr->Count - 1; i >= index; i--){
        arr->pBase[i + 1] = arr->pBase[i];
    }
    arr->Count++;
    arr->pBase[index] = value;
    //��̬��������
    if (IsBeingFull(arr)) Allocate(arr);
    return;
}

//ArrDelectָ��index��value
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

//Arr��ȡָ��index��value
int Get(Arr* arr,int index)
{
    if (IsEmpty(arr)) {
        printf("Arr is Empty!\n");
        exit(-1);
    }
    if (arr->Count <= index || index < 0) {
        printf("�޷���ȡ��[%d]��λ�õ�value\n",index);
        exit(-1);
    }
    else {
        return arr->pBase[index];
    }
}

//Arr����
void Inversion(Arr* arr)
{
    if (IsEmpty(arr)){
        printf("Arr is empty!\n");
    }
    else{
        for (int i = 0; i < arr->Count / 2; i++) // 0 ~ �԰�����
        {
            int temp = arr->pBase[i];
            arr->pBase[i] = arr->pBase[arr->Count - 1 - i];
            arr->pBase[arr->Count - 1 - i] = temp;
        }
    }
    return;
}

//Arr ��Ҫ���˵�ʱ��
Status IsBeingFull(Arr* arr)
{
    if(arr == NULL){
        printf("����ΪNULL\n");
        return;
    }

    if (arr->Count + 3 == arr->Size) return TRUE;
    else return FALSE;
}

//Arr���ȶ�̬��չ
void Allocate(Arr* arr)
{
    if(arr == NULL){
        printf("����ΪNULL\n");
        return;
    }

    if (arr->Size >= 4 * 1000)    arr->Increment = 1.25;    //1.25�����ٶ�

    int* ret = (int*)malloc(sizeof(int)* arr->Size * arr->Increment);
    if (NULL == ret){
        printf("��̬��չ����ʧ��!\n");
        return;
    }
    for (int i = 0; i < arr->Count; i++)    //��int[]����value ���Ƶ�������ret
    {
        ret[i] = arr->pBase[i];
    }

    arr->Size = arr->Size * arr->Increment;    //�޸���󳤶� , Count����Ҫ��
    int* p = arr->pBase;                        //�ͷ�ԭ��������
    arr->pBase = ret;
    free(p);
    return;
}

//ArrĿǰԪ�ظ���
int GetSize(Arr* arr)
{
    if (arr == NULL) {
        printf("��������Ƿ�ΪNULL\n");
        exit(-1);
    }
    return arr->Count;
}

//Arr_BubbleSort
void Arr_BubbleSort(Arr* arr)
{
    if(arr == NULL){
        printf("����ΪNULL\n");
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
        printf("����ΪNULL\n");
        return;
    }

    for (int i = 0; i < arr->Count - 1; i++)
    {
        int index = i + 1;
        int ret_index = i;
        while ( index < arr->Count)    //��С�ķ�ǰ��
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
