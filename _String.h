#pragma once
#include <stdlib.h>
#include<stdio.h>

#pragma region StringInfo
#define MallocStrSize 100
typedef char* String;
	#pragma region StringTypeEnum
	#define Malloc_Str 1
	#define NonMalloc_Str 0
	//�Ƿ�̬�����String,Malloc_Str��ʾ�Ƕ�̬�ڴ����ģ�
	//NonMalloc_Str��ʾ�ǷǶ�̬�ڴ�����
	typedef int StringType;
	#pragma endregion
	#pragma region m_KMP
	#define InitStrSize 10 
	#define InitStrIncrement 2
		typedef struct m_KMP_Str
		{
			int* next;
			int Size;
			int Count;
			int Increment;
		}m_KMP_Str;
	#pragma endregion
#pragma endregion

#pragma region Funtions_Details
String StringEmpty();
int StringIsEmpty(String str);
void Destroy(String * str, StringType type);
void Clear(String * str, StringType type);
String StrCopy(String str);
String StringConcat(String first, String second);
String SubStr(String str);
String SubString(String str, int index, int size);
void Trim(String * str);
void TrimEnd(String * str, StringType type);
int StrComparer(String first, String second);
String* Replace(String source, String str_pre, String str_new);
String Reverse(String source);
int GetStringLen(String str);
	#pragma region KMP_Functions
	m_KMP_Str* InitStrNextVal();
	int** CreateNextValArr(String f_str);
	void KMP_NextValArrAllocate(m_KMP_Str* arr);
	int KMP_Find(String source, String f_str);
	#pragma endregion
#pragma endregion

//-------------------------String--------------------------

//���ؿ��ַ��� str[0] == '\0' 
String StringEmpty()
{
	String ret = (String)calloc(MallocStrSize, sizeof(char));
	return ret;
}

//�ж��Ƿ���ַ��� "" 
int StringIsEmpty(String str)
{
	if (str == "") return 1;
	else return 0;
}

//ɾ���ַ���,������NULL
//StringType��ö�����ͣ�Malloc_Str , NonMalloc_Str
void Destroy(String * str, StringType type)
{
	if (type == Malloc_Str)
	{
		free(*str);
		*str = NULL;
	}

	if (type == NonMalloc_Str)
	{
		*str = NULL;
	}
}

//���str�����е�ֵ
//StringType��ö������: Malloc_Str , NonMalloc_Str
//��malloc�ķ����� str[0] = '\0'��δmalloc�ķ��ؿ��ַ���""
void Clear(String * str, StringType type)
{
	//����Ƕ�̬�ڴ�������free
	if (type == Malloc_Str)
	{
		String p = *str;
		*str = (String)calloc(100, sizeof(char));
		free(p);
	}

	if (type == NonMalloc_Str)
	{
		*str = "";
	}
}

//��ȡString��д��Ȩ�ޣ�CopyNewString 
String StrCopy(String str)
{
	String ret = (String)calloc(MallocStrSize, sizeof(char));
	int index = 0;
	while (str[index])
	{
		ret[index] = str[index];
		index++;
	}
	return ret;
}

//�ַ���A���ַ���B���� A+B ,�����µ�C�ַ���
String StringConcat(String first, String second)
{
	String ret = (String)calloc(MallocStrSize, sizeof(char));
	int index = 0;
	while (first[index])
	{
		ret[index] = first[index];
		index++;
	}
	int temp_index = index;
	while (second[index - temp_index])
	{
		ret[index] = second[index - temp_index];
		index++;
	}
	return ret;
}

//��ȡ�ַ���������ĸ
String SubStr(String str)
{
	if (str == NULL || str == "") {
		return NULL;
	}
	String ret = (String)calloc(1, sizeof(char));
	ret[0] = str[0];
	return ret;
}

//��ȡ(��indexλ�ÿ�ʼ����ȡsize���ȣ����Ӵ�
String SubString(String str, int index, int size)
{
	//��������ڴ治�� size + 1
	String ret = (String)calloc(size + 1, sizeof(char));
	if (size <= 0 && ((index + size) > GetStringLen(str))) {
		return NULL;
	}
	else {
		int i = 0;
		while (i < size)
		{
			ret[i] = str[index + i];
			i++;
		}
		return ret;
	}
}

//ȥ���ַ�����ͷ�Ŀո�
void Trim(String * str) 
{
	if (*str == NULL || *str == "") {
		printf("���ַ����޷�����\n");
		return NULL;
	}
	int i = 0;
	while (((*str)[i]) == ' ') {
		i++;
	}
	*str = *str + i;	//��ָ��[0]��ָ��ֱ��ָ���һ����ͷ����ĸ�ĵط�
}

//ȥ���ַ��������Ŀո�
//StringType��ö������: Malloc_Str , NonMalloc_Str
void TrimEnd(String * str,StringType type)
{
	if (*str == NULL || *str == "") {
		printf("���ַ����޷�����\n");
		return NULL;
	}
	
	int i = GetStringLen(*str);
	String ret = (String)calloc(i + 1, sizeof(char));
	while ( ((*str)[i - 1]) == ' ') {
		i--;
	}

	for (int j = 0; j < i; j++)
	{
		ret[j] = (*str)[j];
	}

	if (type == Malloc_Str) {
		String * p = *str;
		*str = ret;
		free(p);
	}
	else {
		*str = ret;
	}
}

//�ַ����Ƚ� 1 0 -1 �� ���� ���� С��
int StrComparer(String first, String second)
{
	int index = 0;
	while (first[index] || second[index])
	{
		if (first[index] > second[index]) return 1;
		if (first[index] < second[index]) return -1;
		else index++;
	}
	return 0;
}

//��ƥ�䵽���ַ����ﻻ�µ��ַ����滻һ��
//source�ַ���Դ��str_preƥ�䵽���ַ���,str_new��ƥ�䵽��str_pre�����滻
//(����SouceԴ���в���),�����µ�SourceԴ
String* Replace(String source, String str_pre, String str_new) 
{
	if (str_new == NULL || str_new == "") {
		printf("�����滻���ַ�������Ϊ��\n");
		return NULL;
	}

	//���ƥ��ɹ� /*�ֳ�3�ζ�д��pos��ǰ�к�*/
	int pos = KMP_Find(source, str_pre);
	if (pos != -1)
	{
		String ret = (String)calloc(MallocStrSize,sizeof(char));
		int i = 0;	//��ֵret���±�
		while (i != pos) {
			ret[i] = source[i];
			i++;
		}
		//��¼ȡ��source֮���index
		int source_index = i + GetStringLen(str_pre);

		int j = 0;	//str_new���±�,str_new���str_pre
		while (str_new[j])
		{
			ret[i] = str_new[j];
			++i;
			++j;
		}

		while (source[source_index])	//��pos֮��sourceδ����
		{
			ret[i] = source[source_index];
			++i;
			++source_index;
		}

		return &ret;
	}
	else   //KMPƥ�䲻�ɹ�
	{
		printf("�޷��滻\n");
		return NULL;
	}
}

//�ַ�����ת
String Reverse(String source) 
{
	if (source == NULL || source == "") {
		printf("�ַ���Ϊ��\n");
		return NULL;
	}

	int index = 0;
	String ret = (String)calloc(MallocStrSize, sizeof(char));
	while (source[index]) {
		ret[index] = source[index];
		index++;
	}
	
	for (int i = 0; i < index/2; i++)
	{
		char temp = ret[i];
		ret[i] = ret[index - 1 - i];
		ret[index - 1 - i] = temp;
	}
	return ret;
}

//��ȡ�ַ�������
int GetStringLen(String str)
{
	int ret = 0;
	while (str[ret])
	{
		ret++;
	}
	return ret;
}



//------------------------------------m_KMP--------------------------------
//��ʼ��m_KMP_Str�ṹ�壬
m_KMP_Str* InitStrNextVal()
{
	m_KMP_Str* ret = (m_KMP_Str*)malloc(sizeof(m_KMP_Str));
	if (NULL == ret) {
		printf("��̬�����ڴ��ʼ��m_KMP_Str�ṹʧ��\n");
		exit(-1);
	}
	ret->Size = InitStrSize;
	ret->next = (int*)malloc(sizeof(int) * ret->Size);
	ret->Count = 0;
	ret->Increment = InitStrIncrement;
	return ret;
}

//NextVal[]��̬��չ����
void KMP_NextValArrAllocate(m_KMP_Str* arr)
{
	//1000��Ԫ�ؾͰ�1.25�����ٶ���չ���鳤��
	if (arr->Count >= 1000) arr->Increment = 1.25;	

	arr->Size = arr->Size * arr->Increment;
	int* p = (int*)malloc(sizeof(int) * arr->Size);
	if (NULL == p) {
		printf("��̬��չ��������ڴ�ʧ��\n");
		return;
	}

	for (int i = 0; i < arr->Count; i++)
	{
		p[i] = arr->next[i];
	}

	int* q = arr->next;
	arr->next = p;
	free(q);
	q = NULL;
	return;
}

//������Ҫ��ѯ���ַ�������ȡNextVal[]
int** CreateNextValArr(String f_str)
{
	if (f_str == NULL) {
		printf("StringΪ�մ�\n");
		return NULL;
	}
	//��ʼ�����Next[]�ṹ��
	m_KMP_Str* ret = InitStrNextVal();		

	int i = 0;			//��ȡ�ַ���index
	while (f_str[i])
	{
		//�Ƿ���Ҫ��̬����next���鳤��
		if (i + 2 == ret->Size) {
			KMP_NextValArrAllocate(ret);
		}

		if (i == 0) {
			ret->next[0] = 0;
			ret->Count++;								
		}
		else {
			String front_str = SubString(f_str, 0, i);
			int k = 1;									   //���ƶ�k

			for (int n = 1; n < i; n++)			
			{
				String s1 = SubString(front_str, 0, n);	   //ǰ׺����
				String s2 = SubString(front_str, i - n, n);//��׺����
				if (StrComparer(s1, s2) == 0) {
					k = n + 1;
				}
			}
			ret->next[i] = k;
			ret->Count++;		
		}

		//Next[]ת��ΪNextVal[]
		if (i != 0)
		{
			if (f_str[i] == f_str[ret->next[i] - 1]) {
				ret->next[i] = ret->next[ret->next[i] - 1];
			}
		}
		i++;					//index��һ��
	}

	return &(ret->next);		//����NextVal����
}

//KMP�㷨��ѯ
//source���ַ���Դ,f_str����Ҫ��ѯ���ַ���
int KMP_Find(String source, String f_str)
{
	if (source == NULL || f_str == NULL || source == "" || f_str == "") {
		printf("������ַ���ΪNULL,�޷�ƥ��\n");
		return -1;
	}
	
	//int SourceSize = GetStringLen(source);
	int f_strSize = GetStringLen(f_str);

	int i = 0;	//����source��index
	int j = 0;	//�Ӵ�f_str��index

	//��f_str��ȡNextVal����
	int* NextVal = *(CreateNextValArr(f_str));
	while (source[i] && j < f_strSize)
	{
		if (j == 0 || source[i] == f_str[j])
		{
			if (source[i] != f_str[j]) j--; 
			++i;
			++j;
		}
		else {
			j = NextVal[j - 1];
		}

		if (j == f_strSize) {
			printf("ƥ��ɹ�\n");
			return i - j;
		}
	}
	printf("ƥ��ʧ��\n");
	return -1;
}
