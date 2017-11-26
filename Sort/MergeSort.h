#pragma once
#include<stdio.h>
#include<stdlib.h>
#define PRINT_STRING(x) printf("%s\n",x)

typedef int TElement;  //include�������ļ�ʱ����Ҫ�����޸ĸ����ͺ�sort���޸��ж�����



//--------------�鲢����(ÿһ����Ҫ�鲢�Ŵ���temp[],temp[]���鳤�ȸ�����Ҫ����)--------------------
//--------------�鲢����(ÿһ����Ҫ�鲢�Ŵ���temp[],temp[]���鳤�ȸ�����Ҫ����)--------------------
//--------------�鲢����(ÿһ����Ҫ�鲢�Ŵ���temp[],temp[]���鳤�ȸ�����Ҫ����)--------------------
#pragma region FunctionsMergeSort
void MergeSort(TElement* arr, int left, int right);
void Merge(TElement* arr, int left, int right, int mid);
#pragma endregion

/*�鲢����*/
/*arr:����*/
/*left:�������ͷ��index*/
/*right:����������index*/
void MergeSort(TElement* arr, int left, int right)
{
    if (right <= left)  return;            // < С���Ƿ�ֹ��һ�δ���Ĵ���

    int mid = left + ((right - left) / 2); //��ȡmid��index��mid�����������һ��Ԫ�ص�index
    MergeSort(arr, left, mid);             //����������
    MergeSort(arr, mid + 1, right);        //����������

    if (arr[mid] > arr[mid + 1]) {
        Merge(arr, left, right, mid);
    }
    return;
}

/*(�ڲ�����)�鲢2��������õ�����*/
/*left:�������ͷ��index*/
/*right:����������index*/
/*mid�����������һ��Ԫ�ص�index*/
/*arrsize:ԴSouce[]�ܳ���*/
void Merge(TElement* arr, int left, int right, int mid)
{
    //�����еĵ�һ��index
    int i = left;
    //�����еĵ�һ��index
    int j = mid + 1;

    //Copy����������(ֻ��Copy��Ҫ�õ����ǲ���)
    TElement* temp = (TElement*)malloc(sizeof(TElement) * (right-left+1));
    if (temp == NULL) {
        PRINT_STRING("��������[]��ʼ����̬�����ڴ�ʧ��");
        exit(-1);
    }
    for (int k = 0; k < (right - left + 1); k++) {
        temp[k] = arr[left + k];
    }

    //�鲢
    for (int k = left; k < left + (right - left + 1); k++)
    {
        if (i > mid) {
            arr[k] = temp[j-left];
            j++;
        }else if (j > right) {
            arr[k] = temp[i - left];
            i++;
        }else if (temp[i - left] < temp[j - left])
        {
            arr[k] = temp[i-left];
            i++;
        }else {
            arr[k] = temp[j - left];
            j++;
        }
    }

    free(temp); //Destroy��temp[]
    return;
}



//----------------�鲢����(ÿһ����Ҫ�鲢�Ŵ���temp[]������ԴSouce[]copy)--------------------
//----------------�鲢����(ÿһ����Ҫ�鲢�Ŵ���temp[]������ԴSouce[]copy)--------------------
//----------------�鲢����(ÿһ����Ҫ�鲢�Ŵ���temp[]������ԴSouce[]copy)--------------------
#pragma region Functions_MergeSort
void _MergeSort(TElement* arr, int left, int right,int arrsize);
void _Merge(TElement* arr, int left, int right, int mid,int arrsize);
#pragma endregion

/*�鲢����copy���鲿���ǰ�����ԴSouce[]copy��*/
/*arr:����*/
/*left:�������ͷ��index*/
/*right:����������index*/
/*arrsize:ԴSouce[]�ܳ���*/
void _MergeSort(TElement* arr,int left,int right,int arrsize)
{
    if (right <= left)  return;                  // < С���Ƿ�ֹ��һ�δ���Ĵ���

    int mid = left + ((right - left) / 2);       //��ȡmid��index��mid�����������һ��Ԫ�ص�index
    _MergeSort(arr, left, mid,arrsize);          //����������
    _MergeSort(arr, mid + 1, right,arrsize);     //����������

    if (arr[mid] > arr[mid + 1]) {
        _Merge(arr, left, right, mid, arrsize);
    }
    return;
}

/*(�ڲ�����)�鲢2��������õ�����*/
/*left:�������ͷ��index*/
/*right:����������index*/
/*mid�����������һ��Ԫ�ص�index*/
/*arrsize:ԴSouce[]�ܳ���*/
void _Merge(TElement* arr, int left, int right, int mid,int arrsize)
{
    //�����еĵ�һ��index
    int i = left;
    //�����еĵ�һ��index
    int j = mid + 1;

    //Copy���������飨����ԴSource[]Copy��
    TElement* temp = (TElement*)malloc(sizeof(TElement) * arrsize);
    if (temp == NULL) {
        PRINT_STRING("��������[]��ʼ����̬�����ڴ�ʧ��");
        exit(-1);
    }
    for (int k = 0; k < arrsize; k++){
        temp[k] = arr[k];
    }

    //�鲢
    for (int k = left; k < arrsize; k++){
        if (i > mid) arr[k] = temp[j++];
        else if (j > right) arr[k] = temp[i++];
        else if (temp[i] < temp[j])
            arr[k] = temp[i++];
        else arr[k] = temp[j++];
    }

    free(temp);   //Destroy��temp[]����
    return;
}



//---------------------�鲢���� ��װtemp[]����(һ���Է���ռ�)--------------------
//---------------------�鲢���� ��װtemp[]����(һ���Է���ռ�)--------------------
//---------------------�鲢���� ��װtemp[]����(һ���Է���ռ�)--------------------
#pragma region MergeSort
typedef struct TempArrMerge {
    TElement* temp;       //��������temp[]
    int count;            //��������ĳ���
}TempArrMerge;
#pragma endregion
#pragma region Functions_MergeSort
void __MergeSort(TElement* arr, int arrsize);
TempArrMerge* InitMerge(TElement* arr, int arrsize);
void __MergeSort_(TempArrMerge* M, TElement* arr, int left, int right);
void __Merge(TempArrMerge* M,TElement* arr, int left, int right, int mid);
#pragma endregion

/*(�ⲿ����)�鲢����*/
/*arr:����*/
/*arrsize:���鳤��*/
void __MergeSort(TElement* arr, int arrsize)
{
    if (arr == NULL) {
        PRINT_STRING("��������ΪNULL");
        return;
    }

    if (arrsize < 0) {
        PRINT_STRING("�����ܳ��Ȳ����Ǹ���");
        return;
    }

    //Ϊtemp[]һ���Է���ռ�
    TempArrMerge* tempMerge = InitMerge(arr, arrsize);

    //�鲢����
    __MergeSort_(tempMerge, arr, 0, arrsize - 1);

    //Destroy temp[]
    free(tempMerge->temp);
    free(tempMerge);
    return;
}

/*(�ڲ�����)�Զ����µĹ鲢����_�ֲ�����������*/
/*ֱ��һ���Է���temp[]�Ŀռ�*/
TempArrMerge* InitMerge(TElement* arr, int arrsize)
{
    TempArrMerge* ret = (TempArrMerge*)malloc(sizeof(TempArrMerge));
    if (ret == NULL) {
        PRINT_STRING("Merge��ʼ����̬�����ڴ�ʧ��");
        exit(-1);
    }

    //һ���Է���Temp[]�ռ�
    ret->temp = (TElement*)malloc(sizeof(TElement) * arrsize);
    if (ret->temp == NULL) {
        PRINT_STRING("temp[]��ʼ����̬�����ڴ�ʧ��");
        exit(-1);
    }

    ret->count = arrsize;
    return ret;
}

/*(�ڲ�����)�鲢����*/
/*M��temp[]�ֲ���������*/
/*arr:ԴSource[]*/
/*left:��һ��Ԫ�ص�index*/
/*right:���һ��Ԫ�ص�index*/
void __MergeSort_(TempArrMerge* M, TElement* arr, int left, int right)
{
    if (right <= left)  return;            // < С���Ƿ�ֹ��һ�δ���Ĵ���

    int mid = left + ((right - left) / 2); //��ȡmid��index��mid�����������һ��Ԫ�ص�index
    MergeSort(arr, left, mid);             //����������
    MergeSort(arr, mid + 1, right);        //����������

    if (arr[mid] > arr[mid + 1]) {
        __Merge(M,arr, left, right, mid);
    }
    return;
}

/*(�ڲ�����)�鲢2��������õ�����*/
/*M:temp[]����*/
/*arr:ԴSouece[]����*/
/*left:�������ͷ��index*/
/*right:����������index*/
/*mid�����������һ��Ԫ�ص�index*/
void __Merge(TempArrMerge* M,TElement* arr, int left, int right, int mid)
{
    int i = left;     //�����еĵ�һ��index
    int j = mid + 1;  //�����еĵ�һ��index

    //Copy���������飨copy��temp[]���飩
    for (int k = left; k < right-left+1; k++) {
        M->temp[k] = arr[k];
    }

    //�鲢
    for (int k = left; k < left + (right - left + 1); k++){
        if (i > mid) arr[k] = M->temp[j++];
        else if (j > right) arr[k] = M->temp[i++];
        else if (M->temp[i] < M->temp[j])
            arr[k] = M->temp[i++];
        else arr[k] = M->temp[j++];
    }
    return;
}
