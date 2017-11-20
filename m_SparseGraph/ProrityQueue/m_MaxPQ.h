#pragma once
#include<stdlib.h>
#include<stdio.h>
#define PRINT_STRING(x) printf("%s\n",x)

#define MaxSizePQ 15    //�ײ�������󳤶�

//ɾ����� �� ����  �����ȶ��� ��[1]��ʼ��


typedef int PQElement;  //#include�������ļ���ʱ��Ҫ�����Ƿ����data������
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


/*��ʼ��MaxPQ*/
MaxPQ* InitMaxPQ()
{
    MaxPQ* ret = (MaxPQ*)malloc(sizeof(MaxPQ));
    if (ret == NULL) {
        PRINT_STRING("MaxPQ��ʼ����̬�����ڴ�ʧ��");
        exit(-1);
    }
    ret->count = 0;
    ret->pBase = (PQElement*)malloc(sizeof(PQElement) * MaxSizePQ);
    if (ret->pBase == NULL) {
        PRINT_STRING("PQ_pBase[]��ʼ����̬�����ڴ�ʧ��");
        exit(-1);
    }
    return ret;
}

/*������Ԫ��*/
void Insert_MaxPQ(MaxPQ* PQ,PQElement value)
{
    if (PQ->count + 1 == MaxSizePQ) {
        PRINT_STRING("PQ����");
        return;
    }

    PQ->pBase[++PQ->count] = value;
    Swim(PQ);
    return;
}

/*(�ڲ�����)�ϸ�*/
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

/*ɾ������Ԫ��*/
void Delete_MaxPQ(MaxPQ* PQ)
{
    Sink(PQ);
    PQ->count--;
    return;
}

/*(�ڲ�����)�³�*/
void Sink(MaxPQ* PQ)
{
    int flag = 1;
    while (flag * 2 <= PQ->count) { //valueΪ����ֵʱ��
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
/*����*/
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
