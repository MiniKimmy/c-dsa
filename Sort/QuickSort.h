#include<stdio.h>
#include<stdlib.h>
/*brief An implementation of QuickSort, including QuickSort_TwoWay and QuickSort_ThreeWay,*/


//排序整形数组
typedef int TElement;

/*bool布尔枚举*/
typedef enum Status {
    FALSE,
    TRUE,
}Status;

#pragma region MyRegion
#pragma region Basic
    void Swap(TElement* arr, int i, int j);
    Status Comparer(TElement* arr, int i, int j);
#pragma endregion

void QuickSort_TwoWay(TElement* arr, int size);
void QuickSort_TwoWay_Inner(TElement* arr, int left, int right);
void QuickSort_TwoWay__Inner(TElement* arr, int left, int right);
void QuickSort_TwoWay___Inner(TElement* arr, int left, int right);

void QuickSort_TwoWay_(TElement* arr, int size);
void partition(TElement* arr, int left, int right);
int QuickSort_TwoWay_Inner_(TElement* arr, int left, int right);
void QuickSort_TwoWay_Inner_InsertSort(TElement* arr, int left, int right);

void QuickSort_ThreeWay(TElement* arr, int size);
void QuickSort_ThreeWay_Inner(TElement* arr, int left, int right);
#pragma endregion


/*交换函数*/
void Swap(TElement* arr, int i, int j)
{
    TElement temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

/*比较函数*/
/*第[i]个 > 第[j]个 返回TRUE*/
Status Comparer(TElement* arr, int i, int j)
{
    if (arr[i] > arr[j]) return TRUE;
    return FALSE;
}

/*快排-2路[普通]-外部方法*/
void QuickSort_TwoWay(TElement* arr, int size)
{
    //检测参数
    if (arr == NULL) return;

    //QuickSort_TwoWay_Inner(arr, 0, size - 1 );  //while X 2
    //QuickSort_TwoWay__Inner(arr, 0, size - 1);  //for+while
    QuickSort_TwoWay___Inner(arr, 0, size - 1);   //for X 2
    return;
}

/*快排-2路[普通whileX2]-内部方法*/
void QuickSort_TwoWay_Inner(TElement* arr, int left, int right)
{
    if (left >= right) return;

    int i = left + 1;
    int j = right;

    //闭区间[i<=right，j>=left+1]
    while (TRUE){
        while (i <= right && Comparer(arr,left,i)) ++i;
        while (j >= left + 1 && arr[j] >= arr[left]) --j;
        if (i > j) break;
        Swap(arr, i, j);
        --j;
        ++i;
    }

    Swap(arr, left, j);
    QuickSort_TwoWay_Inner(arr, left, j - 1);
    QuickSort_TwoWay_Inner(arr, j + 1, right);
}

/*快排-2路[普通for+while]-内部方法*/
void QuickSort_TwoWay__Inner(TElement* arr, int left, int right)
{
    if (left >= right) return;
    
    int j = right;

    for (int i = left + 1; i <= j; i++){
        if (Comparer(arr,i,left)) {
            while (j >= left + 1 && arr[left] <= arr[j]) --j;

            if (i > j) break;
            Swap(arr, i, j);
            --j;
        }
    }

    Swap(arr, left, j);
    QuickSort_TwoWay__Inner(arr, left, j - 1);
    QuickSort_TwoWay__Inner(arr, j + 1, right);
}

/*快排-2路[普通forX2]-内部方法*/
void QuickSort_TwoWay___Inner(TElement* arr, int left, int right)
{
    if (left >= right) return;

    int pos = right;

    for (int i = left + 1; i <= pos; i++){
        if (Comparer(arr, i, left)) {
            for (int j = pos; j >= left + 1; j--){
                if (Comparer(arr, left, j)) break; //必须先判断再--pos
                --pos;
            }
            if (i > pos) break;
            Swap(arr, i, pos);
            pos--;
        }
    }

    Swap(arr, left, pos);
    QuickSort_TwoWay___Inner(arr, left, pos - 1);
    QuickSort_TwoWay___Inner(arr, pos + 1, right);
}

/*快排-2路[优化随机+插入]*/
void QuickSort_TwoWay_(TElement* arr, int size)
{
    srand(0);        //随机种子
    partition(arr, 0, size - 1);
}

/*快排-2路[优化-切分函数]-内部方法*/
void partition(TElement* arr, int left, int right)
{
    //少量数据-插入排序
    if (left + 15 >= right) {
        QuickSort_TwoWay_Inner_InsertSort(arr, left, right);
        return;
    }

    //随机[left~right]
    int random = rand()%(right - left + 1) + left; 
    Swap(arr, random, left);
    
    int j = QuickSort_TwoWay_Inner_(arr, left, right);
    partition(arr, left, j - 1);
    partition(arr, j + 1, right);
}
/*快排-2路[优化whileX2]-内部方法*/
int QuickSort_TwoWay_Inner_(TElement* arr, int left, int right)
{
    if (left >= right) return;

    int i = left + 1;
    int j = right;

    //闭区间[i<=right，j>=left+1]
    while (TRUE) {
        while (i <= right && Comparer(arr, left, i)) ++i;
        while (j >= left + 1 && arr[j] >= arr[left]) --j;
        if (i > j) break;
        Swap(arr, i, j);
        --j;
        ++i;
    }

    Swap(arr, left, j);
    return j;
}

/*快排-2路[优化-插入排序]-内部方法*/
void QuickSort_TwoWay_Inner_InsertSort(TElement* arr, int left, int right)
{
    for (int i = left + 1; i <= right; i++)
    {
        TElement temp = arr[i];
        int pos = i;
        for (int j = i - 1; j >= left && arr[j] > temp; j--){
            arr[j + 1] = arr[j];
            pos = j;
        }
        if (pos != i) {
            arr[pos] = temp;
        }
    }
}

/*快排-3路[普通]-外部方法*/
void QuickSort_ThreeWay(TElement* arr, int size)
{
    if (arr == NULL) return;

    QuickSort_ThreeWay_Inner(arr, 0, size - 1);
}

/*快排-3路[普通]-内部方法*/
void QuickSort_ThreeWay_Inner(TElement* arr, int left, int right)
{
    if (left >= right) return;

    int i = left;      //左序列最后一个index
    int j = left + 1;  //中序列最后一个index
    int k = right;     //右序列最后一个index
    TElement temp = arr[left];

    //闭区间[中序列index~右序列index]
    while (j <= k)
    {
        if (arr[j] < temp) {
            //和左序列最后一个交换
            Swap(arr, j, i);
            i++;
            j++;
        }else if (arr[j] > temp) {
            //和右序列最后一个交换
            Swap(arr, j, k);
            k--;
        }else {
            j++;
        }
    }

    QuickSort_ThreeWay_Inner(arr, left, i - 1); //处理[left,左序列最后一个index）
    QuickSort_ThreeWay_Inner(arr, k + 1, right);//处理(右最后一个index,right]
} 
