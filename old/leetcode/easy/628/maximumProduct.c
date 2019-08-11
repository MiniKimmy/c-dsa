/*
Q628.Maximum Product of Three Numbers
Given an integer array, find three numbers whose product is maximum and output the maximum product.

Example 1:
Input: [1,2,3]
Output: 6

Example 2:
Input: [1,2,3,4]
Output: 24
*/

//C
void swap(int* arr,int i ,int j);
void qSort(int* arr,int size);
void qSortPortion(int* arr, int left, int right);
int qSortInner(int* arr, int left, int right);

void swap(int* arr,int i ,int j){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void qSort(int* arr,int size){
    //srand(time(0));   //add random -->28ms
    qSortPortion(arr, 0, size-1);
}

void qSortPortion(int* arr, int left, int right){
    //if (left >= right) return;

    if(left + 10 > right){
        insertIndexSort(arr,left,right);
        return;
    }
    //int random = rand() % (right-left +1) + left; //ex: rand()%11 + 10 --> integer from 10 to 20.
    //swap(arr, left, random);

    int j = qSortInner(arr, left, right);
    qSortPortion(arr, left, j - 1);
    qSortPortion(arr, j + 1, right);
}

int qSortInner(int* arr, int left, int right){
    if (left >= right) return;

    int i = left + 1;
    int j = right;
    int temp = arr[left];
    while (1) {
        while (i <= right && arr[i]<temp ) ++i;
        while (j >= left + 1 && arr[j]>=temp) --j;
        if (i > j) break;
        swap(arr, i++, j--);
    }

    swap(arr, left, j);
    return j;
}

/*
//min->max
void insertSort(int* arr,int size){
    for(int i = 1;i<size;i++){
        int pos = i;
        int temp = arr[i];
        for(int j = i-1;j>=0 && arr[j] > temp ;j--){
            arr[j+1] = arr[j];
            pos = j;
        }
        if(pos != i) arr[pos] = temp;
    }
}
*/
//min->max index
void insertIndexSort(int* arr,int left, int right){
    for(int i = left;i<=right;i++){
        int pos = i;
        int temp = arr[i];
        for(int j = i-1;j>=left && arr[j] > temp ;j--){
            arr[j+1] = arr[j];
            pos = j;
        }
        if(pos != i) arr[pos] = temp;
    }
}



int maximumProduct(int* nums, int numsSize) {
    qSort(nums,numsSize);
    /*
    insertSort(nums,numsSize); //1528ms only inserSort
    qSort(nums,numsSize);     // 44ms only qSort
    */

    int a = nums[0] * nums[1] * nums[numsSize-1] ;
    int b = nums[numsSize-1]*nums[numsSize-2]*nums[numsSize-3];
    return a>b?a:b;
}
