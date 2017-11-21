#pragma once
#include<stdlib.h>
#include<stdio.h>
#define PRINT_STRING(x) printf("%s\n",x)

//队列最大元素个数 (底层数组最大长度 = MaxSizePQ + 1)
#define MaxSizePQ 15


/*标志位TURE/FALSE*/
typedef enum Status {
    FALSE,
    TRUE,
}Status;


typedef int PQElement;  //#include到其他文件的时候要考虑是否更改data的类型

#pragma region PriorityQueue
/*优先队列类型*/
typedef enum PriorityQueueType {
    MaxPQ,    //删除最大
    MinPQ,    //删除最小
}PriorityQueueType;

typedef struct PriorityQueue {
    PriorityQueueType type;    //优先队列类型
    PQElement* pBase;
    int count;
}PriorityQueue;
#pragma endregion


#pragma region Functions
PriorityQueue* InitPQ(PriorityQueueType PQType);
Status IsEmptyPQ(PriorityQueue * PQ);
Status IsFullPQ(PriorityQueue * PQ);
void Insert_PQ(PriorityQueue* PQ, PQElement value);
void Swim(PriorityQueue* PQ);
void Delete_PQ(PriorityQueue* PQ);
void Sink(PriorityQueue* PQ);
void Traverse_PQ(PriorityQueue* PQ);
int GetSize(PriorityQueue* PQ);
#pragma endregion


/*初始化PriorityQueue*/
/*PriorityQueueType枚举类型:*/
/*MaxPQ:删除最大键值的PQ,MinPQ:删除最小键值的PQ*/
PriorityQueue* InitPQ(PriorityQueueType PQType)
{
    PriorityQueue* ret = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    if (ret == NULL) {
        PRINT_STRING("PriorityQueue初始化动态分配内存失败");
        exit(-1);
    }

    //因为[0]不存PQElement,从[1]开始,初始化时候Size + 1
    ret->pBase = (PQElement*)malloc(sizeof(PQElement) * (MaxSizePQ + 1));
    if (ret->pBase == NULL) {
        PRINT_STRING("PQ_pBase[]初始化动态分配内存失败");
        exit(-1);
    }

    ret->count = 0;
    ret->type = PQType;
    return ret;
}

/*判断PQ是否为空*/
Status IsEmptyPQ(PriorityQueue * PQ)
{
    if (PQ == NULL) {
        PRINT_STRING("PQ为NULL");
        exit(-1);
    }

    if (PQ->count == 0) return TRUE;
    else return FALSE;
}

/*判断PQ是否已满*/
Status IsFullPQ(PriorityQueue * PQ)
{
    if (PQ == NULL) {
        PRINT_STRING("PQ为NULL");
        exit(-1);
    }

    if (PQ->count == MaxSizePQ) return TRUE;
    else return FALSE;
}

/*(外部方法)插入新元素 + (内部方法)上浮*/
void Insert_PQ(PriorityQueue * PQ,PQElement value)
{
    if (IsFullPQ(PQ)) return;
    PQ->pBase[++PQ->count] = value;
    Swim(PQ);
    return;
}

/*(内部方法)上浮*/
/*(外部方法里检测参数)*/
void Swim(PriorityQueue* PQ)
{
    int flag = PQ->count;
    if (PQ->type == MaxPQ) {
        while (PQ->pBase[flag] > PQ->pBase[flag / 2] && flag / 2 != 0) {
            PQElement temp = PQ->pBase[flag];
            PQ->pBase[flag] = PQ->pBase[flag / 2];
            PQ->pBase[flag / 2] = temp;
            flag = flag / 2;
        }
    }else {
        while (PQ->pBase[flag] < PQ->pBase[flag / 2] && flag / 2 != 0) {
            PQElement temp = PQ->pBase[flag];
            PQ->pBase[flag] = PQ->pBase[flag / 2];
            PQ->pBase[flag / 2] = temp;
            flag = flag / 2;
        }
    }
    return;
}

/*(外部方法)删除Root的元素 + (内部方法)下沉*/
void Delete_PQ(PriorityQueue* PQ)
{
    if (IsEmptyPQ(PQ)) return;

    PQElement temp = PQ->pBase[1];
    PQ->pBase[1] = PQ->pBase[PQ->count];
    PQ->pBase[PQ->count] = temp;
    PQ->count--;
    Sink(PQ);
    return;
}

/*(内部方法)下沉*/
/*(外部方法检查参数)*/
void Sink(PriorityQueue * PQ)
{
    int flag = 1;
    if (PQ->type == MaxPQ){
        while (flag * 2 <= PQ->count) {
            int index = 2 * flag;
            if (index < PQ->count && PQ->pBase[index] < PQ->pBase[index + 1]) { //保证有右Child  index < count
                index++;
            }
            if (PQ->pBase[flag] < PQ->pBase[index]) {
                PQElement temp = PQ->pBase[flag];
                PQ->pBase[flag] = PQ->pBase[index];
                PQ->pBase[index] = temp;
            }
            flag = index;
        }
    }else {
        while (flag * 2 <= PQ->count) {
            int index = 2 * flag;
            if (index < PQ->count && PQ->pBase[index] > PQ->pBase[index + 1]) { //保证有右Child  index < count
                index++;
            }
            if (PQ->pBase[flag] > PQ->pBase[index]) {
                PQElement temp = PQ->pBase[flag];
                PQ->pBase[flag] = PQ->pBase[index];
                PQ->pBase[index] = temp;
            }
            flag = index;
        }
    }
    return;
}

/*遍历*/
void Traverse_PQ(PriorityQueue * PQ)
{
    for (int i = 0; i <= PQ->count; i++){
        printf("[%d] = %d\n", i, PQ->pBase[i]);
    }
    return;
}

/*获取元素个数*/
int GetSize(PriorityQueue * PQ)
{
    if (PQ == NULL) {
        PRINT_STRING("PQ为NULL");
        exit(-1);
    }

    return PQ->count;
}
