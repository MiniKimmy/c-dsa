#pragma once
#include<stdio.h>
#include<stdlib.h>
#define PRINT_STRING(x) printf("%s\n",x)

typedef int TElement;  //include到其他文件时候需要考虑修改该类型和sort的修改判断条件



//--------------归并排序(每一次需要归并才创建temp[],temp[]数组长度根据需要分配)--------------------
//--------------归并排序(每一次需要归并才创建temp[],temp[]数组长度根据需要分配)--------------------
//--------------归并排序(每一次需要归并才创建temp[],temp[]数组长度根据需要分配)--------------------
#pragma region FunctionsMergeSort
void MergeSort(TElement* arr, int left, int right);
void Merge(TElement* arr, int left, int right, int mid);
#pragma endregion

/*归并排序*/
/*arr:数组*/
/*left:左序列最开头的index*/
/*right:右序列最后的index*/
void MergeSort(TElement* arr, int left, int right)
{
    if (right <= left)  return;            // < 小于是防止第一次传入的错误

    int mid = left + ((right - left) / 2); //获取mid的index，mid即左序列最后一个元素的index
    MergeSort(arr, left, mid);             //左序列排序
    MergeSort(arr, mid + 1, right);        //右序列排序

    if (arr[mid] > arr[mid + 1]) {
        Merge(arr, left, right, mid);
    }
    return;
}

/*(内部方法)归并2个已排序好的数组*/
/*left:左序列最开头的index*/
/*right:右序列最后的index*/
/*mid：左序列最后一个元素的index*/
/*arrsize:源Souce[]总长度*/
void Merge(TElement* arr, int left, int right, int mid)
{
    //左序列的第一个index
    int i = left;
    //右序列的第一个index
    int j = mid + 1;

    //Copy到副本数组(只是Copy需要用到的那部分)
    TElement* temp = (TElement*)malloc(sizeof(TElement) * (right-left+1));
    if (temp == NULL) {
        PRINT_STRING("副本数组[]初始化动态分配内存失败");
        exit(-1);
    }
    for (int k = 0; k < (right - left + 1); k++) {
        temp[k] = arr[left + k];
    }

    //归并
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

    free(temp); //Destroy掉temp[]
    return;
}



//----------------归并排序(每一次需要归并才创建temp[]把整个源Souce[]copy)--------------------
//----------------归并排序(每一次需要归并才创建temp[]把整个源Souce[]copy)--------------------
//----------------归并排序(每一次需要归并才创建temp[]把整个源Souce[]copy)--------------------
#pragma region Functions_MergeSort
void _MergeSort(TElement* arr, int left, int right,int arrsize);
void _Merge(TElement* arr, int left, int right, int mid,int arrsize);
#pragma endregion

/*归并排序（copy数组部分是把整个源Souce[]copy）*/
/*arr:数组*/
/*left:左序列最开头的index*/
/*right:右序列最后的index*/
/*arrsize:源Souce[]总长度*/
void _MergeSort(TElement* arr,int left,int right,int arrsize)
{
    if (right <= left)  return;                  // < 小于是防止第一次传入的错误

    int mid = left + ((right - left) / 2);       //获取mid的index，mid即左序列最后一个元素的index
    _MergeSort(arr, left, mid,arrsize);          //左序列排序
    _MergeSort(arr, mid + 1, right,arrsize);     //右序列排序

    if (arr[mid] > arr[mid + 1]) {
        _Merge(arr, left, right, mid, arrsize);
    }
    return;
}

/*(内部方法)归并2个已排序好的数组*/
/*left:左序列最开头的index*/
/*right:右序列最后的index*/
/*mid：左序列最后一个元素的index*/
/*arrsize:源Souce[]总长度*/
void _Merge(TElement* arr, int left, int right, int mid,int arrsize)
{
    //左序列的第一个index
    int i = left;
    //右序列的第一个index
    int j = mid + 1;

    //Copy到副本数组（整个源Source[]Copy）
    TElement* temp = (TElement*)malloc(sizeof(TElement) * arrsize);
    if (temp == NULL) {
        PRINT_STRING("副本数组[]初始化动态分配内存失败");
        exit(-1);
    }
    for (int k = 0; k < arrsize; k++){
        temp[k] = arr[k];
    }

    //归并
    for (int k = left; k < arrsize; k++){
        if (i > mid) arr[k] = temp[j++];
        else if (j > right) arr[k] = temp[i++];
        else if (temp[i] < temp[j])
            arr[k] = temp[i++];
        else arr[k] = temp[j++];
    }

    free(temp);   //Destroy掉temp[]数组
    return;
}



//---------------------归并排序 封装temp[]数组(一次性分配空间)--------------------
//---------------------归并排序 封装temp[]数组(一次性分配空间)--------------------
//---------------------归并排序 封装temp[]数组(一次性分配空间)--------------------
#pragma region MergeSort
typedef struct TempArrMerge {
    TElement* temp;       //副本数组temp[]
    int count;            //副本数组的长度
}TempArrMerge;
#pragma endregion
#pragma region Functions_MergeSort
void __MergeSort(TElement* arr, int arrsize);
TempArrMerge* InitMerge(TElement* arr, int arrsize);
void __MergeSort_(TempArrMerge* M, TElement* arr, int left, int right);
void __Merge(TempArrMerge* M,TElement* arr, int left, int right, int mid);
#pragma endregion

/*(外部方法)归并排序*/
/*arr:数组*/
/*arrsize:数组长度*/
void __MergeSort(TElement* arr, int arrsize)
{
    if (arr == NULL) {
        PRINT_STRING("传入数组为NULL");
        return;
    }

    if (arrsize < 0) {
        PRINT_STRING("数组总长度不能是负数");
        return;
    }

    //为temp[]一次性分配空间
    TempArrMerge* tempMerge = InitMerge(arr, arrsize);

    //归并排序
    __MergeSort_(tempMerge, arr, 0, arrsize - 1);

    //Destroy temp[]
    free(tempMerge->temp);
    free(tempMerge);
    return;
}

/*(内部方法)自顶向下的归并排序_局部变量的数组*/
/*直接一次性分配temp[]的空间*/
TempArrMerge* InitMerge(TElement* arr, int arrsize)
{
    TempArrMerge* ret = (TempArrMerge*)malloc(sizeof(TempArrMerge));
    if (ret == NULL) {
        PRINT_STRING("Merge初始化动态分配内存失败");
        exit(-1);
    }

    //一次性分配Temp[]空间
    ret->temp = (TElement*)malloc(sizeof(TElement) * arrsize);
    if (ret->temp == NULL) {
        PRINT_STRING("temp[]初始化动态分配内存失败");
        exit(-1);
    }

    ret->count = arrsize;
    return ret;
}

/*(内部方法)归并排序*/
/*M：temp[]局部变量数组*/
/*arr:源Source[]*/
/*left:第一个元素的index*/
/*right:最后一个元素的index*/
void __MergeSort_(TempArrMerge* M, TElement* arr, int left, int right)
{
    if (right <= left)  return;            // < 小于是防止第一次传入的错误

    int mid = left + ((right - left) / 2); //获取mid的index，mid即左序列最后一个元素的index
    MergeSort(arr, left, mid);             //左序列排序
    MergeSort(arr, mid + 1, right);        //右序列排序

    if (arr[mid] > arr[mid + 1]) {
        __Merge(M,arr, left, right, mid);
    }
    return;
}

/*(内部方法)归并2个已排序好的数组*/
/*M:temp[]数组*/
/*arr:源Souece[]数组*/
/*left:左序列最开头的index*/
/*right:右序列最后的index*/
/*mid：左序列最后一个元素的index*/
void __Merge(TempArrMerge* M,TElement* arr, int left, int right, int mid)
{
    int i = left;     //左序列的第一个index
    int j = mid + 1;  //右序列的第一个index

    //Copy到副本数组（copy到temp[]数组）
    for (int k = left; k < right-left+1; k++) {
        M->temp[k] = arr[k];
    }

    //归并
    for (int k = left; k < left + (right - left + 1); k++){
        if (i > mid) arr[k] = M->temp[j++];
        else if (j > right) arr[k] = M->temp[i++];
        else if (M->temp[i] < M->temp[j])
            arr[k] = M->temp[i++];
        else arr[k] = M->temp[j++];
    }
    return;
}
