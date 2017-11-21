#pragma once
#include<stdlib.h>
#include<stdio.h>
#define PRINT_STRING(x) printf("%s\n",x)

//�������Ԫ�ظ��� (�ײ�������󳤶� = MaxSizePQ + 1)
#define MaxSizePQ 15


/*��־λTURE/FALSE*/
typedef enum Status {
    FALSE,
    TRUE,
}Status;


typedef int PQElement;  //#include�������ļ���ʱ��Ҫ�����Ƿ����data������

#pragma region PriorityQueue
/*���ȶ�������*/
typedef enum PriorityQueueType {
    MaxPQ,    //ɾ�����
    MinPQ,    //ɾ����С
}PriorityQueueType;

typedef struct PriorityQueue {
    PriorityQueueType type;    //���ȶ�������
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


/*��ʼ��PriorityQueue*/
/*PriorityQueueTypeö������:*/
/*MaxPQ:ɾ������ֵ��PQ,MinPQ:ɾ����С��ֵ��PQ*/
PriorityQueue* InitPQ(PriorityQueueType PQType)
{
    PriorityQueue* ret = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    if (ret == NULL) {
        PRINT_STRING("PriorityQueue��ʼ����̬�����ڴ�ʧ��");
        exit(-1);
    }

    //��Ϊ[0]����PQElement,��[1]��ʼ,��ʼ��ʱ��Size + 1
    ret->pBase = (PQElement*)malloc(sizeof(PQElement) * (MaxSizePQ + 1));
    if (ret->pBase == NULL) {
        PRINT_STRING("PQ_pBase[]��ʼ����̬�����ڴ�ʧ��");
        exit(-1);
    }

    ret->count = 0;
    ret->type = PQType;
    return ret;
}

/*�ж�PQ�Ƿ�Ϊ��*/
Status IsEmptyPQ(PriorityQueue * PQ)
{
    if (PQ == NULL) {
        PRINT_STRING("PQΪNULL");
        exit(-1);
    }

    if (PQ->count == 0) return TRUE;
    else return FALSE;
}

/*�ж�PQ�Ƿ�����*/
Status IsFullPQ(PriorityQueue * PQ)
{
    if (PQ == NULL) {
        PRINT_STRING("PQΪNULL");
        exit(-1);
    }

    if (PQ->count == MaxSizePQ) return TRUE;
    else return FALSE;
}

/*(�ⲿ����)������Ԫ�� + (�ڲ�����)�ϸ�*/
void Insert_PQ(PriorityQueue * PQ,PQElement value)
{
    if (IsFullPQ(PQ)) return;
    PQ->pBase[++PQ->count] = value;
    Swim(PQ);
    return;
}

/*(�ڲ�����)�ϸ�*/
/*(�ⲿ�����������)*/
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

/*(�ⲿ����)ɾ��Root��Ԫ�� + (�ڲ�����)�³�*/
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

/*(�ڲ�����)�³�*/
/*(�ⲿ����������)*/
void Sink(PriorityQueue * PQ)
{
    int flag = 1;
    if (PQ->type == MaxPQ){
        while (flag * 2 <= PQ->count) {
            int index = 2 * flag;
            if (index < PQ->count && PQ->pBase[index] < PQ->pBase[index + 1]) { //��֤����Child  index < count
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
            if (index < PQ->count && PQ->pBase[index] > PQ->pBase[index + 1]) { //��֤����Child  index < count
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

/*����*/
void Traverse_PQ(PriorityQueue * PQ)
{
    for (int i = 0; i <= PQ->count; i++){
        printf("[%d] = %d\n", i, PQ->pBase[i]);
    }
    return;
}

/*��ȡԪ�ظ���*/
int GetSize(PriorityQueue * PQ)
{
    if (PQ == NULL) {
        PRINT_STRING("PQΪNULL");
        exit(-1);
    }

    return PQ->count;
}
