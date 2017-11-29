#pragma once
#include<stdio.h>
#include<stdlib.h>
#define PRINT_STRING(x) printf("%s\n",x)

//���������Ԫ�ظ��� (�ײ�������󳤶� = MaxSizeIndexPQ + 1)
#define MaxSizeIndexPQ 15    

typedef enum Status{
    FALSE,
    TRUE,
}Status;


typedef int HeapElement; // ��include�������ļ�ʱ����Ҫ�����޸�data������
#pragma region IndexHeap
/*����������IndexHeapType*/
typedef enum IndexPQType {
    IndexMaxPQ,    //ɾ�����
    IndexMinPQ,    //ɾ����С
}IndexPQType;

/*data[]����δ�Ӷ�̬���书��*/
typedef struct IndexPQ {
    IndexPQType type;
    HeapElement* data;  //Դsource[]
    int* indexes;       //data��index
    int* reverse;       //indexex���෴����
    int count;          //Ԫ���ܸ���
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


/*IndexPQ��ʼ�� ,IndexPQTypeö������ : */
/*IndexMaxPQ:ɾ������ֵ��IndexPQ,IndexMinPQ:ɾ����С��ֵ��IndexPQ*/
IndexPQ* InitIndexHeap(IndexPQType type)
{
    IndexPQ* ret = (IndexPQ*)malloc(sizeof(IndexPQ));
    if (NULL == ret) {
        PRINT_STRING("IndexPQ��ʼ����̬�����ڴ�ʧ��");
        exit(-1);
    }

    //��[1]��ʼ��
    ret->data = (HeapElement*)malloc(sizeof(HeapElement) * (MaxSizeIndexPQ + 1));
    if (NULL == ret->data) {
        PRINT_STRING("HeapElement[]��ʼ����̬�����ڴ�ʧ��");
        exit(-1);
    }
    ret->indexes = (int*)malloc(sizeof(int) * (MaxSizeIndexPQ + 1));
    if (NULL == ret->indexes) {
        PRINT_STRING("indexes[]��ʼ����̬�����ڴ�ʧ��");
        exit(-1);
    }
    ret->reverse = (int*)malloc(sizeof(int) * (MaxSizeIndexPQ + 1));
    if (NULL == ret->reverse) {
        PRINT_STRING("reverse[]��ʼ����̬�����ڴ�ʧ��");
        exit(-1);
    }
    ret->type = type;
    ret->count = 0;
    return ret;
}

/*�ж�IndexPQ�Ƿ�Ϊ��*/
Status IsEmpey_IndexPQ(IndexPQ * PQ)
{
    if (PQ == NULL) {
        PRINT_STRING("IndexPQΪNULL");
        exit(-1);
    }

    if (PQ->count == 0) return TRUE;
    else return FALSE;
}

/*�ж�IndexPQ�Ƿ�Ϊ��*/
Status IsFull_IndexPQ(IndexPQ * PQ)
{
    if (PQ == NULL) {
        PRINT_STRING("IndexPQΪNULL");
        exit(-1);
    }

    if (PQ->count == MaxSizeIndexPQ) return TRUE;
    else return FALSE;
}

/*������Ԫ��*/
void Insert_IndexPQ(IndexPQ * PQ, HeapElement value)
{
    if (IsFull_IndexPQ(PQ)) return;

    PQ->data[++PQ->count] = value;
    PQ->indexes[PQ->count] = PQ->count;
    PQ->reverse[PQ->count] = PQ->count;
    Swim_IndexPQ(PQ);
    return;
}

/*(�ڲ�����)�ϸ�*/
void Swim_IndexPQ(IndexPQ * PQ)
{
    int flag = PQ->indexes[PQ->count];
    if (PQ->type == IndexMaxPQ){
        while (flag / 2 != 0 && PQ->data[PQ->count] > PQ->data[PQ->indexes[flag / 2]]){
            //������,reverse[]
            int temp = PQ->reverse[PQ->indexes[flag]];  
            PQ->reverse[PQ->indexes[flag]] = flag / 2;
            PQ->reverse[PQ->indexes[flag / 2]] = temp;

            //��Key,indexex[]
            temp = PQ->indexes[flag];
            PQ->indexes[flag] = PQ->indexes[flag / 2]; 
            PQ->indexes[flag / 2] = temp;
            flag = flag / 2;
        }
    }else {
        while (flag / 2 != 0 && PQ->data[PQ->count] < PQ->data[PQ->indexes[flag / 2]]) {
            //������,reverse[]
            int temp = PQ->reverse[PQ->indexes[flag]];
            PQ->reverse[PQ->indexes[flag]] = flag / 2;
            PQ->reverse[PQ->indexes[flag / 2]] = temp;

            //��data_Key,indexex[]
            temp = PQ->indexes[flag];  
            PQ->indexes[flag] = PQ->indexes[flag / 2];
            PQ->indexes[flag / 2] = temp;
            flag = flag / 2;
        }
    }
    return;
}

/*ɾ��������RootԪ��*/
void Delete_IndexPQ(IndexPQ * PQ)
{
    //������,reverse[],��������������[1]�Ľ���
    PQ->reverse[PQ->indexes[PQ->count]] = 1;
    PQ->reverse[PQ->indexes[1]] = PQ->count;

    //��KEY,indexex[]
    PQ->indexes[1] = PQ->indexes[PQ->count];
    PQ->count--;
    Sink_IndexPQ(PQ);
}

/*(�ڲ�����)�³�*/
void Sink_IndexPQ(IndexPQ * PQ)
{
    int flag = 1;
    if (PQ->type == IndexMaxPQ) {
        while (flag * 2 <= PQ->count){
            int data_key = flag * 2;    //һ��ʼĬ��2*flag�Ǵ��
            int mark = PQ->indexes[data_key];
            HeapElement Max_data = PQ->data[mark];

            if (data_key < PQ->count && Max_data < PQ->data[PQ->indexes[data_key + 1]] ) {
                data_key++;
                mark = PQ->indexes[data_key];
                Max_data = PQ->data[mark];
            }

            if (PQ->data[PQ->indexes[flag]] < Max_data) {
                //������
                int temp = PQ->reverse[mark];
                PQ->reverse[mark] = PQ->reverse[PQ->indexes[flag]];
                PQ->reverse[PQ->indexes[flag]] = temp;
                //��data_key
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
                //������
                int temp = PQ->reverse[mark];
                PQ->reverse[mark] = PQ->reverse[PQ->indexes[flag]];
                PQ->reverse[PQ->indexes[flag]] = temp;
                //��data_key
                PQ->indexes[data_key] = PQ->indexes[flag];
                PQ->indexes[flag] = mark;
            }
            flag = mark;
        }
    }
}

/*����������*/
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

/*��ȡIndexPQԪ�ظ���*/
int GetSize_IndexPQ(IndexPQ * PQ)
{
    if (PQ == NULL) {
        PRINT_STRING("IndexPQΪNULL");
        exit(-1);
    }

    return PQ->count;
}
