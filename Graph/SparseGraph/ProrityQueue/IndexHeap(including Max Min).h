#pragma once
#include<stdio.h>
#include<stdlib.h>
#define PRINT_STRING(x) printf("%s\n",x)

//索引堆最大元素个数 (底层数组最大长度 = MaxSizeIndexPQ + 1)
#define MaxSizeIndexPQ 15    

typedef enum Status{
    FALSE,
    TRUE,
}Status;


typedef int HeapElement; // 在include到其他文件时，需要考虑修改data的类型
#pragma region IndexHeap
/*索引堆类型IndexHeapType*/
typedef enum IndexPQType {
    IndexMaxPQ,    //删除最大
    IndexMinPQ,    //删除最小
}IndexPQType;

/*data[]数组未加动态扩充功能*/
typedef struct IndexPQ {
    IndexPQType type;
    HeapElement* data;  //源source[]
    int* indexes;       //data的index
    int* reverse;       //indexex的相反数组
    int count;          //元素总个数
}IndexPQ;
#pragma endregion

#pragma region Functions
IndexPQ* InitIndexHeap(IndexPQType type);
Status IsEmpey_IndexPQ(IndexPQ * PQ);
Status IsFull_IndexPQ(IndexPQ * PQ);
void Insert_IndexPQ(IndexPQ * PQ, HeapElement value);
void Swim_IndexPQ(IndexPQ * PQ);
void Delete_IndexPQ(IndexPQ * PQ);
void Sink_IndexPQ(IndexPQ * PQ);
void Traverse_IndexPQ(IndexPQ * PQ);
int GetSize_IndexPQ(IndexPQ * PQ);
#pragma endregion


/*IndexPQ初始化 ,IndexPQType枚举类型 : */
/*IndexMaxPQ:删除最大键值的IndexPQ,IndexMinPQ:删除最小键值的IndexPQ*/
IndexPQ* InitIndexHeap(IndexPQType type)
{
    IndexPQ* ret = (IndexPQ*)malloc(sizeof(IndexPQ));
    if (NULL == ret) {
        PRINT_STRING("IndexPQ初始化动态分配内存失败");
        exit(-1);
    }

    //从[1]开始存
    ret->data = (HeapElement*)malloc(sizeof(HeapElement) * (MaxSizeIndexPQ + 1));
    if (NULL == ret->data) {
        PRINT_STRING("HeapElement[]初始化动态分配内存失败");
        exit(-1);
    }
    ret->indexes = (int*)malloc(sizeof(int) * (MaxSizeIndexPQ + 1));
    if (NULL == ret->indexes) {
        PRINT_STRING("indexes[]初始化动态分配内存失败");
        exit(-1);
    }
    ret->reverse = (int*)malloc(sizeof(int) * (MaxSizeIndexPQ + 1));
    if (NULL == ret->reverse) {
        PRINT_STRING("reverse[]初始化动态分配内存失败");
        exit(-1);
    }
    ret->type = type;
    ret->count = 0;
    return ret;
}

/*判断IndexPQ是否为空*/
Status IsEmpey_IndexPQ(IndexPQ * PQ)
{
    if (PQ == NULL) {
        PRINT_STRING("IndexPQ为NULL");
        exit(-1);
    }

    if (PQ->count == 0) return TRUE;
    else return FALSE;
}

/*判断IndexPQ是否为空*/
Status IsFull_IndexPQ(IndexPQ * PQ)
{
    if (PQ == NULL) {
        PRINT_STRING("IndexPQ为NULL");
        exit(-1);
    }

    if (PQ->count == MaxSizeIndexPQ) return TRUE;
    else return FALSE;
}

/*插入新元素*/
void Insert_IndexPQ(IndexPQ * PQ, HeapElement value)
{
    if (IsFull_IndexPQ(PQ)) return;

    PQ->data[++PQ->count] = value;
    PQ->indexes[PQ->count] = PQ->count;
    PQ->reverse[PQ->count] = PQ->count;
    Swim_IndexPQ(PQ);
    return;
}

/*(内部方法)上浮*/
void Swim_IndexPQ(IndexPQ * PQ)
{
    int flag = PQ->indexes[PQ->count];
    if (PQ->type == IndexMaxPQ){
        while (flag / 2 != 0 && PQ->data[PQ->count] > PQ->data[PQ->indexes[flag / 2]]){
            //换排名,reverse[]
            int temp = PQ->reverse[PQ->indexes[flag]];  
            PQ->reverse[PQ->indexes[flag]] = flag / 2;
            PQ->reverse[PQ->indexes[flag / 2]] = temp;

            //换Key,indexex[]
            temp = PQ->indexes[flag];
            PQ->indexes[flag] = PQ->indexes[flag / 2]; 
            PQ->indexes[flag / 2] = temp;
            flag = flag / 2;
        }
    }else {
        while (flag / 2 != 0 && PQ->data[PQ->count] < PQ->data[PQ->indexes[flag / 2]]) {
            //换排名,reverse[]
            int temp = PQ->reverse[PQ->indexes[flag]];
            PQ->reverse[PQ->indexes[flag]] = flag / 2;
            PQ->reverse[PQ->indexes[flag / 2]] = temp;

            //换data_Key,indexex[]
            temp = PQ->indexes[flag];  
            PQ->indexes[flag] = PQ->indexes[flag / 2];
            PQ->indexes[flag / 2] = temp;
            flag = flag / 2;
        }
    }
    return;
}

/*删除索引堆Root元素*/
void Delete_IndexPQ(IndexPQ * PQ)
{
    //换排名,reverse[],最后的排名和排名[1]的交换
    PQ->reverse[PQ->indexes[PQ->count]] = 1;
    PQ->reverse[PQ->indexes[1]] = PQ->count;

    //换KEY,indexex[]
    PQ->indexes[1] = PQ->indexes[PQ->count];
    PQ->count--;
    Sink_IndexPQ(PQ);
}

/*(内部方法)下沉*/
void Sink_IndexPQ(IndexPQ * PQ)
{
    int flag = 1;
    if (PQ->type == IndexMaxPQ) {
        while (flag * 2 <= PQ->count){
            int data_key = flag * 2;    //一开始默认2*flag是大的
            int mark = PQ->indexes[data_key];
            HeapElement Max_data = PQ->data[mark];

            if (data_key < PQ->count && Max_data < PQ->data[PQ->indexes[data_key + 1]] ) {
                data_key++;
                mark = PQ->indexes[data_key];
                Max_data = PQ->data[mark];
            }

            if (PQ->data[PQ->indexes[flag]] < Max_data) {
                //换排名
                int temp = PQ->reverse[mark];
                PQ->reverse[mark] = PQ->reverse[PQ->indexes[flag]];
                PQ->reverse[PQ->indexes[flag]] = temp;
                //换data_key
                PQ->indexes[data_key] = PQ->indexes[flag];
                PQ->indexes[flag] = mark;
            }
            flag = mark;
        }
    }else {
        while (flag * 2 <= PQ->count) {
            int data_key = flag * 2;
            int mark = PQ->indexes[data_key];
            HeapElement Min_data = PQ->data[mark];

            if (data_key < PQ->count && Min_data > PQ->data[PQ->indexes[data_key + 1]]) {
                data_key++;
                mark = PQ->indexes[data_key];
                Min_data = PQ->data[mark];
            }

            if (PQ->data[PQ->indexes[flag]] > Min_data) {
                //换排名
                int temp = PQ->reverse[mark];
                PQ->reverse[mark] = PQ->reverse[PQ->indexes[flag]];
                PQ->reverse[PQ->indexes[flag]] = temp;
                //换data_key
                PQ->indexes[data_key] = PQ->indexes[flag];
                PQ->indexes[flag] = mark;
            }
            flag = mark;
        }
    }
}

/*遍历索引堆*/
void Traverse_IndexPQ(IndexPQ * PQ)
{
    printf("----data-----\n");
    for (int i = 0; i <= MaxSizeIndexPQ; i++)
    {
        printf("[%d] = %d\n", i, PQ->data[i]);
    }
    
    printf("----indexes----\n");
    for (int i = 0; i <= PQ->count; i++)
    {
        printf("[%d] = %d\n", i, PQ->indexes[i]);
    }
    
    printf("----reverse----\n");
    for (int i = 0; i <= MaxSizeIndexPQ; i++)
    {
        printf("[%d] = %d\n", i, PQ->reverse[i]);
    }
    

    return;
}

/*获取IndexPQ元素个数*/
int GetSize_IndexPQ(IndexPQ * PQ)
{
    if (PQ == NULL) {
        PRINT_STRING("IndexPQ为NULL");
        exit(-1);
    }

    return PQ->count;
}
