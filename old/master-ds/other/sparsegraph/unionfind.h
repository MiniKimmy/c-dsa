typedef struct {
    int* root;   //从[0]开始
    int* size;
    int count;
}UF;

#pragma region Functions
UF* initUF(int n);
void weightQuickUnion(UF* UF, int p, int q);
int find(UF* UF, int p);
int isConnected(UF* UF, int p, int q);
int getAGraphKeyUF(UF* UF, int p);
int getAGraphKeySize(UF* UF, int p);
#pragma endregion

UF* initUF(int n) {
    if (n <= 0) return NULL;

    UF* uf = (UF*)malloc(sizeof(UF));
    uf->count = n;
    uf->size = (int*)malloc(sizeof(int) * n);
    uf->root = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        uf->root[i] = i;
        uf->size[i] = 1; 
    }
    return uf;
}

int find(UF* UF, int p) {
    if (UF == NULL || p < 0) return -1;

    while (p != UF->root[p]) {
        UF->root[p] = UF->root[UF->root[p]];
        p = UF->root[p];
    }
    return p;
}

int isConnected(UF* UF, int p, int q) {
    if (UF == NULL) return 0;
    return find(UF, p) == find(UF, q);
}

int getAGraphKeyUF(UF* UF, int p) {
    if (UF == NULL || p < 0) return 0; //传入p是ArcKey-1
    return find(UF, p) + 1 ;           //默认Key从1开始
}

int getAGraphKeySize(UF* UF, int p) {
    if (UF == NULL || p < 0) return 0; //传入p是ArcKey-1
    return UF->size[find(UF, p)];      
}

void weightQuickUnion(UF* UF, int p, int q) {
    if (UF == NULL || p<0 || q<0) return ;

    int p_root = find(UF, p);
    int q_root = find(UF, q);
    if (p_root == q_root) return;

    if (UF->size[p_root] > UF->size[q_root]) {
        UF->root[q_root] = p_root;
        UF->size[p_root] += UF->size[q_root];
    }else {
        UF->root[p_root] = q_root;
        UF->size[q_root] += UF->size[p_root];
    }

    --UF->count;
    return;
}
