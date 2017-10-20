#pragma once
#include <stdlib.h>
#include<stdio.h>

#pragma region StringInfo
#define MallocStrSize 100
typedef char* String;
	#pragma region StringTypeEnum
	#define Malloc_Str 1
	#define NonMalloc_Str 0
	//是否动态分配的String,Malloc_Str表示是动态内存分配的，
	//NonMalloc_Str表示是非动态内存分配的
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

//返回空字符串 str[0] == '\0' 
String StringEmpty()
{
	String ret = (String)calloc(MallocStrSize, sizeof(char));
	return ret;
}

//判断是否空字符串 "" 
int StringIsEmpty(String str)
{
	if (str == "") return 1;
	else return 0;
}

//删除字符串,均返回NULL
//StringType是枚举类型：Malloc_Str , NonMalloc_Str
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

//清空str里所有的值
//StringType是枚举类型: Malloc_Str , NonMalloc_Str
//已malloc的返回是 str[0] = '\0'，未malloc的返回空字符串""
void Clear(String * str, StringType type)
{
	//如果是动态内存分配才能free
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

//获取String的写入权限，CopyNewString 
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

//字符串A与字符串B连接 A+B ,返回新的C字符串
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

//获取字符串的首字母
String SubStr(String str)
{
	if (str == NULL || str == "") {
		return NULL;
	}
	String ret = (String)calloc(1, sizeof(char));
	ret[0] = str[0];
	return ret;
}

//获取(在index位置开始，获取size长度）的子串
String SubString(String str, int index, int size)
{
	//避免分配内存不够 size + 1
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

//去掉字符串开头的空格
void Trim(String * str) 
{
	if (*str == NULL || *str == "") {
		printf("空字符串无法操作\n");
		return NULL;
	}
	int i = 0;
	while (((*str)[i]) == ' ') {
		i++;
	}
	*str = *str + i;	//把指向[0]的指针直接指向第一个开头有字母的地方
}

//去掉字符串最后面的空格
//StringType是枚举类型: Malloc_Str , NonMalloc_Str
void TrimEnd(String * str,StringType type)
{
	if (*str == NULL || *str == "") {
		printf("空字符串无法操作\n");
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

//字符串比较 1 0 -1 ： 大于 等于 小于
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

//在匹配到的字符串里换新的字符串替换一次
//source字符串源，str_pre匹配到的字符串,str_new对匹配到的str_pre进行替换
//(不在Souce源进行操作),返回新的Source源
String* Replace(String source, String str_pre, String str_new) 
{
	if (str_new == NULL || str_new == "") {
		printf("输入替换的字符串不能为空\n");
		return NULL;
	}

	//如果匹配成功 /*分成3段读写：pos的前中后*/
	int pos = KMP_Find(source, str_pre);
	if (pos != -1)
	{
		String ret = (String)calloc(MallocStrSize,sizeof(char));
		int i = 0;	//赋值ret的下标
		while (i != pos) {
			ret[i] = source[i];
			i++;
		}
		//记录取代source之后的index
		int source_index = i + GetStringLen(str_pre);

		int j = 0;	//str_new的下标,str_new替代str_pre
		while (str_new[j])
		{
			ret[i] = str_new[j];
			++i;
			++j;
		}

		while (source[source_index])	//若pos之后source未结束
		{
			ret[i] = source[source_index];
			++i;
			++source_index;
		}

		return &ret;
	}
	else   //KMP匹配不成功
	{
		printf("无法替换\n");
		return NULL;
	}
}

//字符串反转
String Reverse(String source) 
{
	if (source == NULL || source == "") {
		printf("字符串为空\n");
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

//获取字符串长度
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
//初始化m_KMP_Str结构体，
m_KMP_Str* InitStrNextVal()
{
	m_KMP_Str* ret = (m_KMP_Str*)malloc(sizeof(m_KMP_Str));
	if (NULL == ret) {
		printf("动态分配内存初始化m_KMP_Str结构失败\n");
		exit(-1);
	}
	ret->Size = InitStrSize;
	ret->next = (int*)malloc(sizeof(int) * ret->Size);
	ret->Count = 0;
	ret->Increment = InitStrIncrement;
	return ret;
}

//NextVal[]动态扩展长度
void KMP_NextValArrAllocate(m_KMP_Str* arr)
{
	//1000个元素就按1.25倍的速度扩展数组长度
	if (arr->Count >= 1000) arr->Increment = 1.25;	

	arr->Size = arr->Size * arr->Increment;
	int* p = (int*)malloc(sizeof(int) * arr->Size);
	if (NULL == p) {
		printf("动态扩展数组分配内存失败\n");
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

//传入需要查询的字符串，获取NextVal[]
int** CreateNextValArr(String f_str)
{
	if (f_str == NULL) {
		printf("String为空串\n");
		return NULL;
	}
	//初始化相关Next[]结构体
	m_KMP_Str* ret = InitStrNextVal();		

	int i = 0;			//读取字符串index
	while (f_str[i])
	{
		//是否需要动态扩充next数组长度
		if (i + 2 == ret->Size) {
			KMP_NextValArrAllocate(ret);
		}

		if (i == 0) {
			ret->next[0] = 0;
			ret->Count++;								
		}
		else {
			String front_str = SubString(f_str, 0, i);
			int k = 1;									   //相似度k

			for (int n = 1; n < i; n++)			
			{
				String s1 = SubString(front_str, 0, n);	   //前缀部分
				String s2 = SubString(front_str, i - n, n);//后缀部分
				if (StrComparer(s1, s2) == 0) {
					k = n + 1;
				}
			}
			ret->next[i] = k;
			ret->Count++;		
		}

		//Next[]转化为NextVal[]
		if (i != 0)
		{
			if (f_str[i] == f_str[ret->next[i] - 1]) {
				ret->next[i] = ret->next[ret->next[i] - 1];
			}
		}
		i++;					//index下一个
	}

	return &(ret->next);		//返回NextVal数组
}

//KMP算法查询
//source是字符串源,f_str是需要查询的字符串
int KMP_Find(String source, String f_str)
{
	if (source == NULL || f_str == NULL || source == "" || f_str == "") {
		printf("输入的字符串为NULL,无法匹配\n");
		return -1;
	}
	
	//int SourceSize = GetStringLen(source);
	int f_strSize = GetStringLen(f_str);

	int i = 0;	//主串source的index
	int j = 0;	//子串f_str的index

	//对f_str获取NextVal数组
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
			printf("匹配成功\n");
			return i - j;
		}
	}
	printf("匹配失败\n");
	return -1;
}
