#include<stdlib.h>
#include<stdio.h>

typedef int SqlistType;
typedef struct {
    SqlistType* data;
    int len;
    int count;
}Sqlist;


#pragma region Functions
Sqlist* initSqlist(int len);
int insertElem(Sqlist* Sq, int p, SqlistType e);
int findElem(Sqlist* Sq, int e);
int deleteElem(Sqlist* Sq, int p);
SqlistType* getElem(Sqlist* Sq, int p);
int getElem_(Sqlist* Sq, int p, SqlistType* e);
int destroySqlist(Sqlist** Sq);
#pragma endregion

Sqlist* initSqlist(int len)
{
    Sqlist* sqlist = (Sqlist*)malloc(sizeof(Sqlist));
    sqlist->data = (SqlistType*)malloc(sizeof(SqlistType) * len);
    sqlist->len = len;
    sqlist->count = 0;
    return sqlist;
}

int insertElem(Sqlist* Sq, int p, SqlistType e)
{
    if (Sq == NULL) return -1;
    if (p < 0 || p >= Sq->len) return 0;

    for (int i = Sq->count -2 ; i >= p ; i++)
    {
        Sq->data[i + 1] = Sq->data[i];
    }
    Sq->data[p] =  e;
    Sq->count++;
    return 1;
}

int findElem(Sqlist* Sq, int e)
{
    if (Sq == NULL) return -1;
    for (int i = 0; i < Sq->count; i++)
    {
        if (Sq->data[i] == e) {
            return i;
        }
    }
    return -1;
}

int deleteElem(Sqlist* Sq, int p)
{
    if (Sq == NULL) return -1;
    if (p < 0 || p >= Sq->count) return -1;
    for (int i = p; i < Sq->count-1; i++)
    {
        Sq->data[i] = Sq->data[i + 1];
    }
    Sq->count--;
    return 1;
}

SqlistType* getElem(Sqlist* Sq, int p)
{
    if (Sq == NULL) return (SqlistType*)(-1);
    if (p < 0 || p >= Sq->count) return (SqlistType*)(-1);
    return &(Sq->data[p]);
}

int getElem_(Sqlist* Sq, int p, SqlistType* e)
{
    if (Sq == NULL) return -1;
    if (p < 0 || p >= Sq->count) return 0;

    *e = Sq->data[p];
    return 1;
}

int destroySqlist(Sqlist** Sq)
{
    if (*Sq == NULL) return 0;
    free(*Sq);
    *Sq = NULL;
    return 1;
}
