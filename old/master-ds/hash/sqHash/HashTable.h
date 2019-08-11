#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define ARRAYSIZE 10
#define NULLTAG -2018

typedef struct {
    int** data;
    int length;
    int count;
}HashTable;

#pragma region HashTableFunctions
HashTable* initHash();
int* getHash(HashTable* H, int key);
void setHash(HashTable* H, int key);
int formularCustom(HashTable* H, int key);
void traverseHash(HashTable* H);
#pragma endregion

HashTable* initHash() {
    HashTable* hash = (HashTable*)malloc(sizeof(HashTable));
    hash->data = (int**)malloc(sizeof(int*) * ARRAYSIZE);
    hash->length = ARRAYSIZE;
    hash->count = 0;
    for (int i = 0; i < ARRAYSIZE; i++){
        (hash->data)[i] = (int*)malloc(sizeof(int));
        (hash->data)[i][0] = NULLTAG;
    }
    return hash;
}

int* getHash(HashTable* H, int key){
    if (H == NULL || key < 0) return NULL;

    int* ret = (H->data)[formularCustom(H,key)];
    int i = key;
    while (*ret != key && *ret != NULLTAG) {
        int index = formularCustom(H,++i);
        ret = (H->data)[index];
    }

    return ret; 
}

void deleteHash(HashTable* H, int key){
    if (H == NULL || H->count == H->length) return NULL;

    int* ret = (H->data)[formularCustom(H, key)];
    int i = key;
    while (*ret != key && *ret != NULLTAG) {
        int index = formularCustom(H, ++i);
        ret = (H->data)[index];
    }

}

void setHash(HashTable* H, int key) {
    if (H == NULL || H->count == H->length) return NULL;

    int* ret = (H->data)[formularCustom(H,key)];
    int i = key;
    while (*ret != NULLTAG) {
        int index = formularCustom(H,++i);
        ret = (H->data)[index];
    }

    *ret = key;
    H->count++;
    return;
}

int formularCustom(HashTable* H,int key) {
    return key % H->length;
}

void traverseHash(HashTable* H) {
    for (int i = 0; i < H->length; i++) {
        if (*(H->data[i]) == NULLTAG) {
            printf("[%d] = %x  %s\n", i, H->data[i], "null");
        }else {
            printf("[%d] = %x  %d\n", i, H->data[i], *(H->data[i]));
        }    
    }
    printf("\n");
}
