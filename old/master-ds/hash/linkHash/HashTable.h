#include<stdlib.h>
#include<stdio.h>
#include"linklist.h"

typedef struct {
    SLinkList** hashList;
    int length;
}HashTable;

#pragma region HashTableFunctions
HashTable* initHash(int size);
LNode* getHash(HashTable* H, int key);
void setHash(HashTable* H, int key);
int formularCustom(HashTable* H, int key);
void traverseHash(HashTable* H);
#pragma endregion

HashTable* initHash(int size){
    if (size <= 0) return NULL;

    HashTable* hash = (HashTable*)malloc(sizeof(HashTable));
    hash->length = size;
    hash->hashList = (SLinkList**)malloc(sizeof(SLinkList*) * size);
    for (int i = 0; i < size; i++){
        hash->hashList[i] = initSLinkList();
    }
    return hash;
}

void setHash(HashTable* H, int key){
    if (H == NULL || key < 0) return;
    SLinkList* list = H->hashList[formularCustom(H, key)];
    Add(list, key);
    return;
}

int formularCustom(HashTable* H, int key){
    if (H == NULL || key < 0) return -1;
    else return key % H->length;
}

LNode* getHash(HashTable* H, int key) {
    if (H == NULL || key < 0) return;

    SLinkList* list = H->hashList[formularCustom(H, key)];
    LNode* p = list->head;
    while (p->next != NULL) {
        p = p->next;
        if (p->data == key) return p;
    }
    return NULL;
}

void traverseHash(HashTable* H) {
    if (H == NULL) return;

    for (int i = 0; i < H->length; i++)
    {
        SLinkList* list = H->hashList[i];
        printf("[%d]= ", i);
        if (list->count == 0) {
            printf("null\n");
            continue;
        }
        LNode* p = list->head;
        while (p->next) {
            p = p->next;
            printf("%d  ", p->data);
        }
        printf("\n");
    }
}
#include<stdlib.h>
#include<stdio.h>
#include"linklist.h"

typedef struct {
    SLinkList** hashList;
    int length;
}HashTable;

#pragma region HashTableFunctions
HashTable* initHash(int size);
LNode* getHash(HashTable* H, int key);
void setHash(HashTable* H, int key);
int formularCustom(HashTable* H, int key);
void traverseHash(HashTable* H);
#pragma endregion

HashTable* initHash(int size){
    if (size <= 0) return NULL;

    HashTable* hash = (HashTable*)malloc(sizeof(HashTable));
    hash->length = size;
    hash->hashList = (SLinkList**)malloc(sizeof(SLinkList*) * size);
    for (int i = 0; i < size; i++){
        hash->hashList[i] = initSLinkList();
    }
    return hash;
}

void setHash(HashTable* H, int key){
    if (H == NULL || key < 0) return;
    SLinkList* list = H->hashList[formularCustom(H, key)];
    Add(list, key);
    return;
}

int formularCustom(HashTable* H, int key){
    if (H == NULL || key < 0) return -1;
    else return key % H->length;
}

LNode* getHash(HashTable* H, int key) {
    if (H == NULL || key < 0) return;

    SLinkList* list = H->hashList[formularCustom(H, key)];
    LNode* p = list->head;
    while (p->next != NULL) {
        p = p->next;
        if (p->data == key) return p;
    }
    return NULL;
}

void traverseHash(HashTable* H) {
    if (H == NULL) return;

    for (int i = 0; i < H->length; i++)
    {
        SLinkList* list = H->hashList[i];
        printf("[%d]= ", i);
        if (list->count == 0) {
            printf("null\n");
            continue;
        }
        LNode* p = list->head;
        while (p->next) {
            p = p->next;
            printf("%d  ", p->data);
        }
        printf("\n");
    }
}
