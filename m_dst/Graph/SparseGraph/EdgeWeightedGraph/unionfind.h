typedef struct UF {
	int* id;   //��[0]��ʼ
	int* size; //��Ȩ����union
	int count; //��ͨ����������
}UF;

#pragma region Functions
UF* InitUF(int n);
void WeightQuick_Union(UF * UF, int p, int q);
int Find(UF * UF, int p);
int IsConnected(UF * UF, int p, int q);
int GetCount(UF * UF);
#pragma endregion


//��ʼ��UF
//n:������
UF* InitUF(int n) {
	UF* ret = (UF*)malloc(sizeof(UF));
	if (ret == NULL) {
		PRINT_STRING("UF��ʼ����̬�����ڴ�ʧ��");
		exit(-1);
	}

	ret->id = (int*)malloc(sizeof(int) * n);
	if (ret->id == NULL) {
		PRINT_STRING("id[]��ʼ����̬�����ڴ�ʧ��");
		exit(-1);
	}

	ret->size = (int*)malloc(sizeof(int) * n);
	if (ret->size == NULL) {
		PRINT_STRING("size[]��ʼ����̬�����ڴ�ʧ��");
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

//��ͨ2����
void WeightQuick_Union(UF * UF, int p, int q)
{
	int p_root = Find(UF, p);
	int q_root = Find(UF, q);

	if (p_root == q_root) return;

	//С�����ӵ�������
	if (UF->size[p_root] > UF->size[q_root]) {
		UF->id[q_root] = p_root;
		UF->size[p_root] = UF->size[p_root] + UF->size[q_root];
	}else {
		UF->id[p_root] = q_root;
		UF->size[q_root] = UF->size[q_root] + UF->size[p_root] ;
	}
	//�����Ƿ�����е�q�����ӵ�root��..

	UF->count--;
	return;
}

//����
int Find(UF * UF, int p)
{
	while (p != UF->id[p])
	{
		UF->id[p] = UF->id[UF->id[p]];
		p = UF->id[p];
	}
	return p;
}

//����Ƿ���ͨ
int IsConnected(UF * UF, int p, int q)
{
	if (UF == NULL) return 0;
	return Find(UF, UF->id[p]) == Find(UF, UF->id[q]);
}

//��ȡ��ͨ������
int GetCount(UF * UF)
{
	if (UF == NULL) return 0;
	return UF->count;
}
