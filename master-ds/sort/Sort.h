#include"CommonDefine.h"
#define SORTORDER 1    // 1 from min->max  ; -1 from max->min

#pragma region SortFunctions
void bubbleSort(R arr);
void selectSort(R arr);
void insertSort(R arr);
void shellSort(R arr);

void mergeSort(R arr);
void mergeSort_merge(R arr, int left, int right,int mid);
void mergeSort_sort(R arr, int left, int right);

void quickSort_doubleWay(R arr);
void quickSort_doubleWay_portion(R arr, int left, int right);
int quickSort_doubleWay_inner(R arr, int left, int right);

void quickSort_threeWay(R arr);
void quickSort_threeWay_inner(R arr, int left, int right);

void heapSort(int* arr,int arrSize);
void heapSort_sink(int* heap, int start, int arrSize);
#pragma endregion

void bubbleSort(R arr){
    if (arr == NULL) {
        printf("NullReferenceException. method:'bubbleSort'\n");
        return;
    }

    for (int i = 0; i < arr->len-1; i++)
        for (int j = i; j < arr->len; j++)
            if (comparerCustom(NULL,arr,i,j) == SORTORDER) {
                swapCustom(NULL, arr, i, j);
            }
}

void selectSort(R arr) {
    if (arr == NULL) {
        printf("NullReferenceException. method:'selectSort'\n");
        return;
    }

    for (int i = 0; i < arr->len - 1; i++)
    {
        int pos = i;
        for (int j = i+1; j < arr->len; j++){
            if (comparerCustom(NULL, arr, pos, j) == SORTORDER)
                pos = j;
        }

        if (pos != i) swapCustom(NULL, arr, i, pos);
    }
}

void insertSort(R arr)
{
    if (arr == NULL) {
        printf("NullReferenceException. method:'insertSort'\n");
        return;
    }

    for (int i = 1; i < arr->len; i++){
        int pos = i;
        E temp = arr->data[i];
        for (int j= i-1 ; j >= 0 && comparerDefault(NULL, arr->data[j], temp) == SORTORDER; j--){
            arr->data[j+1] = arr->data[j];
            pos = j;
        }

        if (pos != i) {
            arr->data[pos] = temp;
        }
    }
}


void shellSort(R arr)
{
    if (arr == NULL) {
        printf("NullReferenceException. method:'shellSort'\n");
        return;
    }

    int k = 1 + arr->len/3;
    while (k >= 1) {
        for (int i = k; i < arr->len; i=i+k)
        {
            int pos = i;
            E temp = arr->data[i];
            for (int j = i-k; j >= 0 && comparerDefault(NULL,arr->data[j],temp) == SORTORDER; j = j-k)
            {
                arr->data[j + k] = arr->data[j];
                pos = j;
            }
            if (pos != i) arr->data[pos] = temp;
        }
        k = k / 3;
    }
}


void mergeSort(R arr)
{
    if (arr == NULL) {
        printf("NullReferenceException. method:'mergeSort'\n");
        return;
    }
    mergeSort_sort(arr, 0, arr->len-1);
}

void mergeSort_sort(R arr, int left, int right)
{
    if (left >= right) return;
    int mid = left + (right - left ) / 2;

    mergeSort_sort(arr, left, mid);
    mergeSort_sort(arr, mid + 1, right);
    mergeSort_merge(arr, left, right, mid);
    return;
}

void mergeSort_merge(R arr, int left, int right, int mid) {

    int i = left;
    int j = mid+1;

    R temp = (R)malloc(sizeof(T));
    temp->len = right - left + 1;
    temp->data = (int*)malloc(sizeof(int) * temp->len);

    for (int k = 0; k < temp->len; k++) {
        temp->data[k] = arr->data[k+left];
    }

    for (int k = left; k < left + temp->len; k++){

        if (i > mid) arr->data[k] = temp->data[j++ - left];
        else if(j>right) arr->data[k] = temp->data[i++ - left];
        else if(comparerDefault(NULL,temp->data[i-left],temp->data[j-left]) == SORTORDER) arr->data[k] = temp->data[j++ - left];
        else arr->data[k] = temp->data[i++ - left];
    }

    disposeCustom(NULL,&temp);
}

void quickSort_doubleWay(R arr)
{
    if (arr == NULL) {
        printf("NullReferenceException. method:'quickSort_doubleWay'\n");
        return;
    }

    quickSort_doubleWay_portion(arr, 0, arr->len-1);
}

void quickSort_doubleWay_portion(R arr, int left, int right)
{
    if (left >= right) return;

    int random = rand() % (right-left +1) + left; //ex: rand()%11 + 10表示 "10~20"的整数
    swapCustom(NULL, arr, left, random);

    int j = quickSort_doubleWay_inner(arr, left, right);

    quickSort_doubleWay_portion(arr, left, j - 1);
    quickSort_doubleWay_portion(arr, j + 1, right);
}

int quickSort_doubleWay_inner(R arr, int left, int right)
{
    if (left >= right) return;

    int i = left + 1;
    int j = right;
    E temp = arr->data[left];

    while (1) {
        while (i <= right && comparerDefault(NULL, arr->data[i], temp) == -SORTORDER) ++i;
        while (j >= left + 1 && comparerDefault(NULL, arr->data[j], temp) != -SORTORDER) --j;
        if (i > j) break;
        swapCustom(NULL, arr, i++, j--);
    }

    swapCustom(NULL, arr, left, j);
    return j;
}



void quickSort_threeWay(R arr)
{
    if (arr == NULL) {
        printf("NullReferenceException. method:'quickSort_threeWay'\n");
        return;
    }
    quickSort_threeWay_inner(arr, 0, arr->len - 1);
}

void quickSort_threeWay_inner(R arr, int left, int right)
{
    if (left >= right) return;

    int i = left ;
    int j = left + 1;
    int k = right;
    E temp = arr->data[left];

    while (j <= k) {
        int flag = comparerDefault(NULL, arr->data[j], temp);
        if (flag == -SORTORDER) {
            swapCustom(NULL, arr, i, j);
            i++;
            j++;
        }else if (flag == SORTORDER) {
            swapCustom(NULL, arr, j, k);
            k--;
        }else {
            j++;
        }
    }

    quickSort_threeWay_inner(arr, left, i-1);
    quickSort_threeWay_inner(arr, k+1, right);

}

void heapSort(int* arr, int arrSize)
{
    if (arr == NULL) {
        printf("NullReferenceException. method:'heapSort'\n");
        return;
    }

    int* heap = (int*)malloc(sizeof(int) * (arrSize+1));
    for (int i = 0; i < arrSize; i++) {
        heap[i + 1] = arr[i];
    }

    int i = arrSize/2;
    while (i >= 1) {
        heapSort_sink(heap, i ,arrSize);
        i--;
    }

    int len = arrSize;
    for (int i = 0; i < arrSize; i++){
        arr[i] = heap[1];
        heap[1] = heap[len];
        len--;
        heapSort_sink(heap, 1, len);
    }

    disposeDefault(&((void*)heap));
}

void heapSort_sink(int* heap, int start, int arrSize) {
        while (start * 2 <= arrSize) {
            int k = start * 2;
#if SORTORDER == 1
            if (k + 1 <= arrSize) k = minIndexDefault(heap, k, k + 1);
            if(heap[start] > heap[k] ) swapDefault(heap, start, k);
#endif

#if SORTORDER == -1
            if (k + 1 <= arrSize) k = maxIndexDefault(heap, k, k + 1);
            if (heap[start] < heap[k]) swapDefault(heap, start, k);
#endif

            start = k;
        }
}