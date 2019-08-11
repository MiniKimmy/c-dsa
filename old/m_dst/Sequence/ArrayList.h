#include<stdio.h>
#include<stdlib.h>
#define PRINT_STRING(x) printf("%s\n",x)

#define INCREMENT 2       //��������
#define ALLOCATIONCOUNT 3 //�����ٸ�Ԫ������ArrayListʱ����ж�̬����


typedef int TElement;     //import�������ļ�ʱ����Ҫ�޸ĸ�����

/*�Ƿ���Ҫ��̬����ArrayList*/
typedef enum AllocationType{
    UNALLOCATED,
    ALLOCATED,
}AllocationType;

/*Boolö��*/
typedef enum Status{
    FALSE,
    TRUE,
}Status;

typedef struct ArrayList { 
    TElement* arr;
    int count;           //��ǰԪ�ظ���
    int size;            //��󳤶�
    float increment;     //��������
    AllocationType type; //�Ƿ���Ҫ��̬����
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

/*��ʼ��ArrayList.*/
ArrayList* InitArrayList(int size)
{
    if (size < 0) {
        PRINT_STRING("ArrayListԪ�ظ�������Ϊ����");
        exit(-1);
    }

    ArrayList* ret = (ArrayList*)malloc(sizeof(ArrayList));
    if (NULL == ret) {
        PRINT_STRING("ArrayList��ʼ����̬�����ڴ�ʧ��!");
        exit(-1);
    }

    ret->arr = (TElement*)malloc(sizeof(TElement) * (size));
    if (ret->arr == NULL) {
        PRINT_STRING("TElement[]��ʼ����̬�����ڴ�ʧ��!");
        exit(-1);
    }

    ret->size = size;
    ret->count = 0;
    ret->increment = INCREMENT;
    ret->type = UNALLOCATED;
    return ret;
}

/*�����Ƿ���Զ�̬����ArrayList.*/
/*AllocationTypeö������:
ALLOCATED:��̬����,
UNALLOCATED:����̬����.*/
void SetAllocatedType_ArrayList(ArrayList* arr, AllocationType type)
{
    if (arr != NULL) arr->type = type;
    return;
}

/*�ж�ArrayList�Ƿ�Ϊ��.*/
Status IsEmpty_ArrayList(ArrayList* arr)
{
    if (arr == NULL) {
        PRINT_STRING("ArrayListΪNULL");
        exit(-1);
    }

    if (arr->count == 0) return TRUE;
    else return FALSE;
}

/*�ж�ArrayList�Ƿ�����.*/
Status IsFull_ArrayList(ArrayList* arr)
{
    if (arr == NULL) {
        PRINT_STRING("ArrayListΪNULL");
        exit(-1);
    }

    if (arr->count == arr->size) return TRUE;
    else return FALSE;
}

/*����ArrayList.*/
void Traverse_ArrayList(ArrayList* arr)
{
    for (int i = 0; i < arr->count; i++)
    {
        printf("%d ", arr->arr[i]);
    }
    PRINT_STRING("");
}

/*����ArrayList��ǰԪ�ظ���.*/
int GetSize_ArrayList(ArrayList* arr)
{
    if (arr == NULL) {
        PRINT_STRING("ArrayListΪNULL");
        return 0;
    }
    return arr->count;
}

/*���ظ�index��Ԫ�ص�ָ��.*/
TElement* GetValue_ArrayList(ArrayList* arr, int index)
{
    if (IsEmpty_ArrayList(arr)) return;
    if (arr->count <= index || index < 0) {
        printf("�޷����ʵ�[%d]��λ�õ�value\n", index);
        return;
    }

    return &(arr->arr[index]);
}

/*׷��Ԫ��ArrayList.*/
void Append_ArrayList(ArrayList* arr, TElement value)
{
    if (IsFull_ArrayList(arr)) return;

    arr->arr[arr->count++] = value;

    //�Ƿ���Ҫ��̬����
    if (arr->type == ALLOCATED && arr->count + ALLOCATIONCOUNT >= arr->size) {
        Allocate_ArrayList(arr);
    }
    return;
}

/*����Ԫ��ArrayList.*/
/*index:������±�*/
/*value:�����Ԫ��data*/
void Insert_ArrayList(ArrayList* arr, int index, TElement value)
{
    if (IsFull_ArrayList(arr)) return;

    if (arr->count <= index || index < 0) {
        printf("�޷����ʵ�[%d]��λ�õ�value\n", index);
        return;
    }

    //[����]
    for (int i = arr->count - 1; i>= index; i--) {
        arr->arr[i+1] = arr->arr[i];
    }
    arr->arr[index] = value;
    arr->count++;

    //�Ƿ���Ҫ��̬����
    if (arr->type == ALLOCATED && arr->count + ALLOCATIONCOUNT >= arr->size) {
        Allocate_ArrayList(arr);
    }
    return;
}

/*��̬����ArrayList.*/
void Allocate_ArrayList(ArrayList* arr)
{
    if (arr->count > 1000) arr->increment = 1.25f;
    arr->size = arr->size * arr->increment;
    TElement* temp = (TElement*)malloc(sizeof(TElement) * (arr->size));
    if (temp == NULL) {
        PRINT_STRING("��̬����TElement[]��ʼ�������ڴ�ʧ��");
        exit(-1);
    }

    //Copyԭ��ArrayList������
    for (int i = 0; i < arr->count; i++){
        temp[i] = arr->arr[i];
    }

    //free����TElement[]���ڴ�
    TElement* p = arr->arr;
    arr->arr = temp;
    free(p);
    p = NULL;
    return;
}

/*ɾ��Ԫ��ArrayList*/
/*index:ɾ��Ԫ�ص��±�*/
void Delete_ArrayList(ArrayList* arr, int index)
{
    if (IsEmpty_ArrayList(arr)) return;

    if (arr->count <= index || index < 0) {
        printf("�޷�ɾ����[%d]��λ�õ�value\n", index);
        return;
    }

    //[����]
    for (int i = index; i < arr->count - 1 ; i++){
        arr[i] = arr[i + 1];
    }

    arr->count--;
    return;
}

/*����ArrayList.*/
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

/*����Array.*/
void Destroy_ArrayList(ArrayList** arr)
{
    free(*arr);
    *arr = NULL;
    return;
}
