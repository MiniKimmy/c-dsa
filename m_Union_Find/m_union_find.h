#pragma once
#include<stdlib.h>
#include<stdio.h>
#define PRINT_STRING(x) printf("%s\n",x)

typedef struct UF {
    int* id;
    int* size;
    int count;        //连通分量个数
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

/*初始化UF*/
UF* InitUF(int n)
{
    UF* ret = (UF*)malloc(sizeof(UF));
    if (ret == NULL) {
        PRINT_STRING("UF初始化动态分配内存失败\n");
        exit(-1);
    }
    ret->count = n;

    ret->id = (int*)malloc(sizeof(int) * n);
    if (ret->id == NULL) {
        PRINT_STRING("id[]初始化动态分配内存失败\n");
        exit(-1);
    }

    ret->size = (int*)malloc(sizeof(int) * n);
    if (ret->size == NULL) {
        PRINT_STRING("size[]初始化动态分配内存失败\n");
        exit(-1);
    }

    for (int i = 0; i < n; i++){
        ret->id[i] = i;
        ret->size[i] = 1;
    }
    return ret;
}

/*普通连接*/
void Union(UF * UF,int p, int q)
{
    if (UF == NULL) return;
    int pRoot = Find(UF,p);
    int qRoot = Find(UF,q);

    if (pRoot == qRoot) return;
    //全部都变成同一个分量标识符
    for (int i = 0; i < UF->count; i++){
        if (UF->id[i] == qRoot) {
            UF->id[i] = pRoot;
        }
    }
    UF->count--;
    return;
}

/*快速连接*/
void Quick_Union(UF * UF, int p, int q)
{
    if (UF == NULL) return;
    int pRoot = Find(UF, p);
    int qRoot = Find(UF, q);

    if (pRoot == qRoot) return;
    //只要把A根的分量标识符连接到B根
    UF->id[pRoot] = qRoot;
    UF->count--;
    return;
}

/*加权快速连接*/
void WeightQuick_Union(UF * UF, int p, int q)
{
    if (UF == NULL) return;
    int pRoot = Find(UF, p);
    int qRoot = Find(UF, q);

    if (pRoot == qRoot) return;
    //如果未连通，把小树的根接到大树的根(保证整棵树的层数不变)
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

/*加权快速连接（重复连接时优化）*/
void WeightQuick_Union_m(UF * UF, int p, int q)
{
    if (UF == NULL) return;
    int pRoot = Find(UF, p);
    int qRoot = Find(UF, q);

    //出现重复连接，减少大树的层
    if (pRoot == qRoot)
    {
        //小树已经连接到大树上，小树的weight其实改不改都没必要了
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

    //如果未连通，把小树的根接到大树的根(保证整棵树的层数不变)
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

/*找到p的Root(普通Find)*/
int Find(UF * UF,int p)
{
    while (p != UF->id[p] ){
        p = UF->id[p];
    }
    return p;
}

/*找到p的Root(优化的Find)*/
int Find_Optimize(UF * UF, int p)
{
    //每次find都可能压缩一层(Root的Root即自身)
    while (p != UF->id[p]) {
        UF->id[p] = UF->id[UF->id[p]];
        p = UF->id[p];
    }
    return p;
}

/*检测p和q是否连通*/
int IsConnected(UF * UF,int p, int q)
{
    if (UF == NULL) return 0;
    return Find(UF,UF->id[p]) == Find(UF,UF->id[q]);
}

/*返回UF的连通分量总数*/
int GetCount(UF * UF)
{
    if (UF == NULL) return 0;
    return UF->count;
}
