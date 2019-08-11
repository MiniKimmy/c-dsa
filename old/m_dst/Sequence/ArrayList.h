#include<stdio.h>
#include<stdlib.h>
#define PRINT_STRING(x) printf("%s\n",x)

#define INCREMENT 2       //增长因子
#define ALLOCATIONCOUNT 3 //相差多少个元素填满ArrayList时候进行动态分配


typedef int TElement;     //import到其他文件时候需要修改该类型

/*是否需要动态扩充ArrayList*/
typedef enum AllocationType{
    UNALLOCATED,
    ALLOCATED,
}AllocationType;

/*Bool枚举*/
typedef enum Status{
    FALSE,
    TRUE,
}Status;

typedef struct ArrayList { 
    TElement* arr;
    int count;           //当前元素个数
    int size;            //最大长度
    float increment;     //增长因子
    AllocationType type; //是否需要动态扩充
}ArrayList;

#pragma region Functions
ArrayList* InitArrayList(int size);
void SetAllocatedType_ArrayList(ArrayList * arr, AllocationType type);
Status IsEmpty_ArrayList(ArrayList * arr);
Status IsFull_ArrayList(ArrayList * arr);
void Traverse_ArrayList(ArrayList * arr);
int GetSize_ArrayList(ArrayList* arr);
TElement* GetValue_ArrayList(ArrayList * arr, int index);
void Append_ArrayList(ArrayList * arr, TElement value);
void Insert_ArrayList(ArrayList * arr, int index, TElement value);
void Delete_ArrayList(ArrayList * arr, int index);
void Inversion_ArrayList(ArrayList * arr);
void Allocate_ArrayList(ArrayList * arr);
void Destroy_ArrayList(ArrayList** arr);
#pragma endregion

/*初始化ArrayList.*/
ArrayList* InitArrayList(int size)
{
    if (size < 0) {
        PRINT_STRING("ArrayList元素个数不能为负数");
        exit(-1);
    }

    ArrayList* ret = (ArrayList*)malloc(sizeof(ArrayList));
    if (NULL == ret) {
        PRINT_STRING("ArrayList初始化动态分配内存失败!");
        exit(-1);
    }

    ret->arr = (TElement*)malloc(sizeof(TElement) * (size));
    if (ret->arr == NULL) {
        PRINT_STRING("TElement[]初始化动态分配内存失败!");
        exit(-1);
    }

    ret->size = size;
    ret->count = 0;
    ret->increment = INCREMENT;
    ret->type = UNALLOCATED;
    return ret;
}

/*设置是否可以动态扩充ArrayList.*/
/*AllocationType枚举类型:
ALLOCATED:动态扩充,
UNALLOCATED:不动态扩充.*/
void SetAllocatedType_ArrayList(ArrayList* arr, AllocationType type)
{
    if (arr != NULL) arr->type = type;
    return;
}

/*判断ArrayList是否为空.*/
Status IsEmpty_ArrayList(ArrayList* arr)
{
    if (arr == NULL) {
        PRINT_STRING("ArrayList为NULL");
        exit(-1);
    }

    if (arr->count == 0) return TRUE;
    else return FALSE;
}

/*判断ArrayList是否已满.*/
Status IsFull_ArrayList(ArrayList* arr)
{
    if (arr == NULL) {
        PRINT_STRING("ArrayList为NULL");
        exit(-1);
    }

    if (arr->count == arr->size) return TRUE;
    else return FALSE;
}

/*遍历ArrayList.*/
void Traverse_ArrayList(ArrayList* arr)
{
    for (int i = 0; i < arr->count; i++)
    {
        printf("%d ", arr->arr[i]);
    }
    PRINT_STRING("");
}

/*返回ArrayList当前元素个数.*/
int GetSize_ArrayList(ArrayList* arr)
{
    if (arr == NULL) {
        PRINT_STRING("ArrayList为NULL");
        return 0;
    }
    return arr->count;
}

/*返回该index的元素的指针.*/
TElement* GetValue_ArrayList(ArrayList* arr, int index)
{
    if (IsEmpty_ArrayList(arr)) return;
    if (arr->count <= index || index < 0) {
        printf("无法访问第[%d]个位置的value\n", index);
        return;
    }

    return &(arr->arr[index]);
}

/*追加元素ArrayList.*/
void Append_ArrayList(ArrayList* arr, TElement value)
{
    if (IsFull_ArrayList(arr)) return;

    arr->arr[arr->count++] = value;

    //是否需要动态扩充
    if (arr->type == ALLOCATED && arr->count + ALLOCATIONCOUNT >= arr->size) {
        Allocate_ArrayList(arr);
    }
    return;
}

/*插入元素ArrayList.*/
/*index:插入的下标*/
/*value:插入的元素data*/
void Insert_ArrayList(ArrayList* arr, int index, TElement value)
{
    if (IsFull_ArrayList(arr)) return;

    if (arr->count <= index || index < 0) {
        printf("无法访问第[%d]个位置的value\n", index);
        return;
    }

    //[右移]
    for (int i = arr->count - 1; i>= index; i--) {
        arr->arr[i+1] = arr->arr[i];
    }
    arr->arr[index] = value;
    arr->count++;

    //是否需要动态扩充
    if (arr->type == ALLOCATED && arr->count + ALLOCATIONCOUNT >= arr->size) {
        Allocate_ArrayList(arr);
    }
    return;
}

/*动态扩充ArrayList.*/
void Allocate_ArrayList(ArrayList* arr)
{
    if (arr->count > 1000) arr->increment = 1.25f;
    arr->size = arr->size * arr->increment;
    TElement* temp = (TElement*)malloc(sizeof(TElement) * (arr->size));
    if (temp == NULL) {
        PRINT_STRING("动态扩充TElement[]初始化分配内存失败");
        exit(-1);
    }

    //Copy原来ArrayList的数据
    for (int i = 0; i < arr->count; i++){
        temp[i] = arr->arr[i];
    }

    //free掉旧TElement[]的内存
    TElement* p = arr->arr;
    arr->arr = temp;
    free(p);
    p = NULL;
    return;
}

/*删除元素ArrayList*/
/*index:删除元素的下标*/
void Delete_ArrayList(ArrayList* arr, int index)
{
    if (IsEmpty_ArrayList(arr)) return;

    if (arr->count <= index || index < 0) {
        printf("无法删除第[%d]个位置的value\n", index);
        return;
    }

    //[左移]
    for (int i = index; i < arr->count - 1 ; i++){
        arr[i] = arr[i + 1];
    }

    arr->count--;
    return;
}

/*倒置ArrayList.*/
void Inversion_ArrayList(ArrayList* arr)
{
    int i = arr->count-1;
    for (int j = 0; j < arr->count/2 && i != j; j++)
    {
        TElement temp = arr->arr[i];
        arr->arr[i] = arr->arr[j];
        arr->arr[j] = temp;
        i--;
    }
    return;
}

/*销毁Array.*/
void Destroy_ArrayList(ArrayList** arr)
{
    free(*arr);
    *arr = NULL;
    return;
}
