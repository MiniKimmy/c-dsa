#pragma once
#include<stdlib.h>
#include<stdio.h>
#define PRINT_STRING(x) printf("%s\n",x)

typedef struct UF {
    int* id;
    int* size;
    int count;        //��ͨ��������
}UF;

#pragma region Functions
UF* InitUF(int n);
void Union(UF * UF, int p, int q);
void Quick_Union(UF * UF, int p, int q);
void WeightQuick_Union(UF * UF, int p, int q);
void WeightQuick_Union_m(UF * UF, int p, int q);
int Find(UF * UF, int p);
int Find_Optimize(UF * UF, int p);
int IsConnected(UF * UF, int p, int q);
int GetCount(UF * UF);
#pragma endregion

/*��ʼ��UF*/
UF* InitUF(int n)
{
    UF* ret = (UF*)malloc(sizeof(UF));
    if (ret == NULL) {
        PRINT_STRING("UF��ʼ����̬�����ڴ�ʧ��\n");
        exit(-1);
    }
    ret->count = n;

    ret->id = (int*)malloc(sizeof(int) * n);
    if (ret->id == NULL) {
        PRINT_STRING("id[]��ʼ����̬�����ڴ�ʧ��\n");
        exit(-1);
    }

    ret->size = (int*)malloc(sizeof(int) * n);
    if (ret->size == NULL) {
        PRINT_STRING("size[]��ʼ����̬�����ڴ�ʧ��\n");
        exit(-1);
    }

    for (int i = 0; i < n; i++){
        ret->id[i] = i;
        ret->size[i] = 1;
    }
    return ret;
}

/*��ͨ����*/
void Union(UF * UF,int p, int q)
{
    if (UF == NULL) return;
    int pRoot = Find(UF,p);
    int qRoot = Find(UF,q);

    if (pRoot == qRoot) return;
    //ȫ�������ͬһ��������ʶ��
    for (int i = 0; i < UF->count; i++){
        if (UF->id[i] == qRoot) {
            UF->id[i] = pRoot;
        }
    }
    UF->count--;
    return;
}

/*��������*/
void Quick_Union(UF * UF, int p, int q)
{
    if (UF == NULL) return;
    int pRoot = Find(UF, p);
    int qRoot = Find(UF, q);

    if (pRoot == qRoot) return;
    //ֻҪ��A���ķ�����ʶ�����ӵ�B��
    UF->id[pRoot] = qRoot;
    UF->count--;
    return;
}

/*��Ȩ��������*/
void WeightQuick_Union(UF * UF, int p, int q)
{
    if (UF == NULL) return;
    int pRoot = Find(UF, p);
    int qRoot = Find(UF, q);

    if (pRoot == qRoot) return;
    //���δ��ͨ����С���ĸ��ӵ������ĸ�(��֤�������Ĳ�������)
    if (UF->size[pRoot] > UF->size[qRoot]){
        UF->id[q] = pRoot;
        UF->size[pRoot] = UF->size[pRoot] + UF->size[qRoot];
    }
    else {
        UF->id[p] = qRoot;
        UF->size[qRoot] = UF->size[pRoot] + UF->size[qRoot];
    }
    UF->count--;
    return;
}

/*��Ȩ�������ӣ��ظ�����ʱ�Ż���*/
void WeightQuick_Union_m(UF * UF, int p, int q)
{
    if (UF == NULL) return;
    int pRoot = Find(UF, p);
    int qRoot = Find(UF, q);

    //�����ظ����ӣ����ٴ����Ĳ�
    if (pRoot == qRoot)
    {
        //С���Ѿ����ӵ������ϣ�С����weight��ʵ�Ĳ��Ķ�û��Ҫ��
        if (UF->size[UF->id[p]] != UF->size[pRoot]){
            UF->id[p] = pRoot;
            //UF->size[UF->size[q]]--;
        }

        if (UF->size[UF->id[q]] != UF->size[pRoot]){
            UF->id[p] = pRoot;
            //UF->size[UF->size[p]]--;
        }
        return;
    }

    //���δ��ͨ����С���ĸ��ӵ������ĸ�(��֤�������Ĳ�������)
    if (UF->size[pRoot] > UF->size[qRoot]) {
        UF->id[q] = pRoot;
        UF->size[pRoot] = UF->size[pRoot] + UF->size[qRoot];
    }
    else {
        UF->id[p] = qRoot;
        UF->size[qRoot] = UF->size[pRoot] + UF->size[qRoot];
    }
    UF->count--;
    return;
}

/*�ҵ�p��Root(��ͨFind)*/
int Find(UF * UF,int p)
{
    while (p != UF->id[p] ){
        p = UF->id[p];
    }
    return p;
}

/*�ҵ�p��Root(�Ż���Find)*/
int Find_Optimize(UF * UF, int p)
{
    //ÿ��find������ѹ��һ��(Root��Root������)
    while (p != UF->id[p]) {
        UF->id[p] = UF->id[UF->id[p]];
        p = UF->id[p];
    }
    return p;
}

/*���p��q�Ƿ���ͨ*/
int IsConnected(UF * UF,int p, int q)
{
    if (UF == NULL) return 0;
    return Find(UF,UF->id[p]) == Find(UF,UF->id[q]);
}

/*����UF����ͨ��������*/
int GetCount(UF * UF)
{
    if (UF == NULL) return 0;
    return UF->count;
}
