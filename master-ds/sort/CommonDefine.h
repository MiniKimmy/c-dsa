#include<stdio.h>
#include<stdlib.h>
#define RandomRange 100 // 0~100

#pragma region example
typedef struct {
    int* data;
    int len;
}Array_example;

typedef Array_example T;
typedef T* R;
typedef int E; //E data[]

R initEnv(int n) {
    printf("-----initEnv-----\nex:\t");
    R ret = (R)malloc(sizeof(T));
    ret->data = (int*)malloc(sizeof(int) * n);
    ret->len = n;

    srand(time(0));
    for (int i = 0; i < n; i++) {
        ret->data[i] = rand() % RandomRange;
        printf("%d ", ret->data[i]);
    }

    printf("\n-----init OK-----\n");
    return ret;
}

//----default-example -------
int ComparerDefauleExample(E e1, E e2) {
    if (e1 > e2) return 1;
    else if (e1 < e2) return -1;
    else return 0;
}

int ComparerExample(R r, int i,int j) {
    if (r->data[i] > r->data[j]) return 1;
    else if (r->data[i] < r->data[j]) return -1;
    else return 0;
}

E maxExample(E e1, E e2) {
    return e1 > e2 ? e1 : e2;
}


E minExample(E e1, E e2) {
    return e1 < e2 ? e1 : e2;
}


int maxIndexExample(R r, int i, int j ) {
    return comparerDefault(ComparerExample,r->data[i], r->data[j]) != 1 ? j : i;
}

int minIndexExample(R r, int i, int j) {
    return comparerDefault(ComparerExample, r->data[i], r->data[j]) != -1 ? j : i;
}

void swapExample(R r, int i, int j) {
    int temp = r->data[i];
    r->data[i] = r->data[j];
    r->data[j] = temp;
    return;
}

void traverseExample(R r) {
    for (int i = 0; i < r->len; i++){
        printf("%d ", r->data[i]);
    }
    printf("\n");
    return;
}

void disposeExample(R* r) {
    if (*r == NULL) return;
    free((*r)->data);
    free(*r);
    *r = NULL;
    return;
}
#pragma endregion

/* ------------SPECIFICATION----------------*/
#pragma region SPECIFICATION
/*
 * typedef int T;
 * typedef T* R;
 * typedef int E  --E T.data
 */

void swapCustom(void(*swap)(R r, int i, int j), R r, int i, int j);
int comparerDefault(int(*CompareDefault)(E e1, E e2), E e1, E e2);
int comparerCustom(int(*Comparer)(R r, int i, int j), R r, int i, int j);
E minCustom(int(*m_min)(E e1, E e2), E e1, E e2);
E maxCustom(int(*m_max)(E e1, E e2), E e1, E e2);
int maxIndexCustom(int(*maxIndex)(R r, int i, int j), R r, int i, int j);
int minIndexCustom(int(*minIndex)(R r, int i, int j), R r, int i, int j);
void traverseCustom(void(*traverse)(R r), R r);
void disposeCustom(void(*dispose)(R* r), R* r);
void swapDefault(int* t, int i, int j);
int maxIndexDefault(int* t, int i, int j);
int minIndexDefault(int* t, int i, int j);
void disposeDefault(void** t);
#pragma endregion


void swapCustom(void(*swap)(R r, int i, int j), R r, int i, int j)
{
    if (*swap == NULL) swapExample(r, i, j);
    else swap(r, i, j);
}

void swapDefault(int* t, int i, int j)
{
    if (t == NULL) {
        printf("NullReferenceException. method:'swapDefault' ");
    }

    int temp = t[i];
    t[i] = t[j];
    t[j] = temp;
}

int minIndexDefault(int* t, int i, int j)
{
    if (t == NULL) {
        printf("NullReferenceException. method:'minIndexDefault' ");
        return -1;
    }
    return t[i] > t[j] ? j : i;
}

int maxIndexDefault(int* t, int i, int j)
{
    if (t == NULL) {
        printf("NullReferenceException. method:'maxIndexDefault' ");
        return -1;
    }
    return t[i] < t[j] ? j : i;
}

void disposeDefault(void** t) {
    if (t == NULL) {
        printf("NullReferenceException. method:'disposeDefault' ");
    }
    free(*t);
    *t = NULL;
}


int maxIndexCustom(int(*maxIndex)(R r,int i,int j), R r, int i, int j) {
    if (*maxIndex == NULL) maxIndexExample(r, i, j);
    else maxIndex(r, i, j);
}

int minIndexCustom(int(*minIndex)(R r, int i, int j), R r, int i, int j) {
    if (*minIndex == NULL) minIndexExample(r, i, j);
    else minIndex(r, i, j);
}

E maxCustom(int(*m_max)(E e1, E e2), E e1, E e2) {
    if (*m_max == NULL) return maxExample(e1, e2);
    else m_max(e1, e2);
}

E minCustom(int(*m_min)(E e1, E e2), E e1, E e2) {
    if (*m_min == NULL) return minExample(e1, e2);
    else m_min(e1, e2);
}

int comparerDefault(int(*CompareDefault)(E e1, E e2),E e1, E e2) {
    if (*CompareDefault == NULL) return ComparerDefauleExample(e1, e2);
    else CompareDefault(e1, e2);
}

int comparerCustom(int(*Comparer)(R r, int i,int j), R r, int i,int j) {
    if(*Comparer == NULL) return ComparerExample(r, i, j);
    else return Comparer(r,i,j);
}

void traverseCustom(void(*traverse)(R r), R r) {
    if (*traverse == NULL) traverseExample(r); 
    else traverse(r);
}

void disposeCustom(void(*dispose)(R* r), R* r) {
    if (*dispose == NULL) disposeExample(r); 
    else dispose(r);
}
