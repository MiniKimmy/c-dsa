#pragma once
#include<stdlib.h>
#include<stdio.h>
#define PRINT_STRING(x) printf("%s\n",x)

#define MaxSizePQ 15    //底层数组最大长度

//删除最大 和 插入  的优先队列 从[1]开始存


typedef int PQElement;  //#include到其他文件的时候要考虑是否更改data的类型
typedef struct MaxPQ {
    PQElement* pBase;
    int count;
}MaxPQ;


#pragma region Functions
MaxPQ* InitMaxPQ();
void Insert_MaxPQ(MaxPQ* PQ, PQElement value);
void Swim(MaxPQ* PQ);
void Delete_MaxPQ(MaxPQ* PQ);
void Sink(MaxPQ* PQ);
void Traverse_MaxPQ(MaxPQ* PQ);
int GetSize(MaxPQ* PQ);
#pragma endregion


/*初始化MaxPQ*/
MaxPQ* InitMaxPQ()
{
    MaxPQ* ret = (MaxPQ*)malloc(sizeof(MaxPQ));
    if (ret == NULL) {
        PRINT_STRING("MaxPQ初始化动态分配内存失败");
        exit(-1);
    }
    ret->count = 0;
    ret->pBase = (PQElement*)malloc(sizeof(PQElement) * MaxSizePQ);
    if (ret->pBase == NULL) {
        PRINT_STRING("PQ_pBase[]初始化动态分配内存失败");
        exit(-1);
    }
    return ret;
}

/*插入新元素*/
void Insert_MaxPQ(MaxPQ* PQ,PQElement value)
{
    if (PQ->count + 1 == MaxSizePQ) {
        PRINT_STRING("PQ已满");
        return;
    }

    PQ->pBase[++PQ->count] = value;
    Swim(PQ);
    return;
}

/*(内部方法)上浮*/
void Swim(MaxPQ* PQ)
{
    int flag = PQ->count;
    while (PQ->pBase[flag] > PQ->pBase[flag/2] && flag / 2 != 0){
        PQElement temp = PQ->pBase[flag];
        PQ->pBase[flag] = PQ->pBase[flag / 2];
        PQ->pBase[flag / 2] = temp;
        flag = flag / 2;
    }
    return;
}

/*删除最大的元素*/
void Delete_MaxPQ(MaxPQ* PQ)
{
    Sink(PQ);
    PQ->count--;
    return;
}

/*(内部方法)下沉*/
void Sink(MaxPQ* PQ)
{
    int flag = 1;
    while (flag * 2 <= PQ->count) { //value为垃圾值时候
        if (PQ->pBase[flag * 2] > PQ->pBase[flag * 2 + 1] || flag * 2 == PQ->count) {
            PQElement temp = PQ->pBase[flag * 2];
            PQ->pBase[flag * 2] = PQ->pBase[flag];
            PQ->pBase[flag] = temp;
            flag = flag * 2;
        }
        else {
            PQElement temp = PQ->pBase[flag * 2 + 1];
            PQ->pBase[flag * 2 + 1] = PQ->pBase[flag];
            PQ->pBase[flag] = temp;
            flag = flag * 2 + 1;
        } 
    }
    if (flag * 2 > PQ->count && flag * 2 != PQ->count)
    {
        PQElement temp = PQ->pBase[flag];
        PQ->pBase[flag] = PQ->pBase[PQ->count];
        PQ->pBase[PQ->count] = temp;
    }
    return;
}
/*遍历*/
void Traverse_MaxPQ(MaxPQ* PQ)
{
    for (int i = 0; i <= PQ->count; i++){
        printf("[%d] = %d\n", i, PQ->pBase[i]);
    }
    return;
}

int GetSize(MaxPQ* PQ)
{
    if (PQ) {
        return PQ->count;
    }
}
