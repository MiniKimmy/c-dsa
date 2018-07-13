#include"string.h"

typedef struct {
    int* next;
    int count;
    int capacity;
}KMP;

#pragma region KMPFunctions
KMP* initKmp(char* ch);
KMP* getNext(char* ch);
void getNextVal(KMP* K, char* ch);
int kmpFind(char* source, char* findStr);
void destroyKMP(KMP** K);
#pragma endregion

KMP* initKmp(char* ch)
{
    if (ch == NULL) return NULL;

    KMP* kmp = (KMP*)malloc(sizeof(KMP));
    kmp->capacity = getCharArrayLength(ch);
    kmp->count = 0;
    kmp->next = (int*)malloc(sizeof(int) * (kmp->capacity));
    return kmp;
}

KMP* getNext(char* ch)
{
    if (ch == NULL) return NULL;

    KMP* kmp = initKmp(ch);
    kmp->next[kmp->count++] = 0;
    if (kmp->capacity > 1) kmp->next[kmp->count++] = 1;

    for (int i = 2; i < kmp->capacity;i++)
    {    
        int k = 1; // (min)similarity = 1
        for (int n = 1; n < i; n++){
            String* s1 = subCharArray(ch, 0, n);
            String* s2 = subCharArray(ch, i - n, n);
            
            if (compareString(s1, s2) == 0) {
                k = n + 1;
            }
            destroyString(&s1);
            destroyString(&s2);
        }

        kmp->next[kmp->count++] = k;
    }

    getNextVal(kmp, ch);
    return kmp;
}

void getNextVal(KMP* K, char* ch)
{
    for (int i = 1; i < K->capacity; i++)
    {
        if (ch[i] == ch[K->next[i] - 1]) 
            K->next[i] = K->next[K->next[i] - 1];
    }
    return;
}

void destroyKMP(KMP** K)
{
    if (*K == NULL) return;

    free((*K)->next);
    *K = NULL;
    return;
}

int kmpFind(char* source, char* findStr)
{
    KMP* kmp = getNext(findStr);
    int sLen = getCharArrayLength(source);

    if (sLen <= 0 || kmp->capacity > sLen) {
        destroyKMP(&kmp);
        printf("match failured!");
        return 0;
    }

    int j = 0;   //子串的动态下标
    for (int i = 0; i < sLen && j< kmp->capacity; i++){
        if (source[i] == findStr[j] || j == 0) {
            ++j;
        }else {
            j = kmp->next[j - 1];
            --i; //匹配失败时,保持i不变.j调整.
        }
    }
    int fLen = kmp->capacity;
    destroyKMP(&kmp);

    if (sLen == 1) { 
        //防止source只有一个字母时候的情况
        return source[0] == findStr[0];
    }
    
    if (j == fLen) {
        printf("match successfully!");
        return 1;
    }        
    
    printf("match failured!");
    return 0;
}
