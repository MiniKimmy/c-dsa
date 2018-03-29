typedef struct UF {
	int* id;   //从[0]开始
	int* size; //加权快速union
	int count; //连通分量的数量
}UF;

#pragma region Functions
UF* InitUF(int n);
void WeightQuick_Union(UF * UF, int p, int q);
int Find(UF * UF, int p);
int IsConnected(UF * UF, int p, int q);
int GetCount(UF * UF);
#pragma endregion


//初始化UF
//n:顶点数
UF* InitUF(int n) {
	UF* ret = (UF*)malloc(sizeof(UF));
	if (ret == NULL) {
		PRINT_STRING("UF初始化动态分配内存失败");
		exit(-1);
	}

	ret->id = (int*)malloc(sizeof(int) * n);
	if (ret->id == NULL) {
		PRINT_STRING("id[]初始化动态分配内存失败");
		exit(-1);
	}

	ret->size = (int*)malloc(sizeof(int) * n);
	if (ret->size == NULL) {
		PRINT_STRING("size[]初始化动态分配内存失败");
		exit(-1);
	}

	for (int i = 0; i < n; i++)
	{
		ret->id[i] = i;
		ret->size[i] = 1;
	}

	ret->count = n;
	return ret;	
}

//连通2个点
void WeightQuick_Union(UF * UF, int p, int q)
{
	int p_root = Find(UF, p);
	int q_root = Find(UF, q);

	if (p_root == q_root) return;

	//小树连接到大树上
	if (UF->size[p_root] > UF->size[q_root]) {
		UF->id[q_root] = p_root;
		UF->size[p_root] = UF->size[p_root] + UF->size[q_root];
	}else {
		UF->id[p_root] = q_root;
		UF->size[q_root] = UF->size[q_root] + UF->size[p_root] ;
	}
	//考虑是否把所有的q都连接到root。..

	UF->count--;
	return;
}

//查找
int Find(UF * UF, int p)
{
	while (p != UF->id[p])
	{
		UF->id[p] = UF->id[UF->id[p]];
		p = UF->id[p];
	}
	return p;
}

//检测是否连通
int IsConnected(UF * UF, int p, int q)
{
	if (UF == NULL) return 0;
	return Find(UF, UF->id[p]) == Find(UF, UF->id[q]);
}

//获取连通分量数
int GetCount(UF * UF)
{
	if (UF == NULL) return 0;
	return UF->count;
}
