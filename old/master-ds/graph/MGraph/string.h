#if SETINFO==0
#include<stdio.h>
#include<stdlib.h>
#endif 

typedef struct {
    char* ch;
    int length;
}String;

#pragma region StringFunctions
int equalString(String* str1, String* str2);
int compareString(String* str1, String* str2);
int getLength(String* str);
String* concatStr(char* str1, char* str2);
String* concat(String* str1, String* str2);
String* subString(String* str, int start, int len);
String* subStr(String* str, int start, int end);
int clearString(String* str);
int destroyString(String** str);
#pragma region CharArray
String* charArrayToString(char* ch);
int equalsStr(char* ch1, char* ch2);
int compareCharArray(char* ch1, char* ch2);
int getCharArrayLength(char* ch);
String* subCharArray(char* ch, int pos, int end);
String* subCharArr(char* ch, int start, int end);
#pragma endregion


#pragma endregion

String* charArrayToString(char* ch)
{
    int charSize = getCharArrayLength(ch);

    if (charSize == 0) return NULL;

    String* str = (String*)malloc(sizeof(String));
    str->ch = (char*)malloc(sizeof(char)*(charSize + 1));
    str->length = charSize;

    for (int i = 0; i < charSize; i++)
        str->ch[i] = ch[i];

    str->ch[charSize] = '\0';
    return str;
}

int getCharArrayLength(char* ch)
{
    if (ch == NULL) return 0;

    int len = 0;
    char* c = ch;  //获取ch的第一个元素的地址
                   //若使用char str[maxsize]配合gets_s赋值来传入给ch也可以
    while (*c) {   //必须以 "hello" 或者 {'h','i','\0'} 的形式传参给ch
        len++;
        c++;       //指向下一个地址
    }

    return len;
}

int equalsStr(char* ch1, char* ch2)
{
    String* str1 = charArrayToString(ch1);
    String* str2 = charArrayToString(ch2);
    int ret = compareString(str1, str2);
    destroyString(&str1);
    destroyString(&str2);
    return ret == 0 ? 1 : 0;
}

int equalString(String* str1, String* str2)
{
    if (compareString(str1, str2) == 0) return 1;
    else return 0;
}

/*str1>str2 return 1*/
int compareString(String* str1, String* str2) {

    if (str1 == NULL || str2 == NULL) return 0;

    int len, flag;
    if (str1->length < str2->length) {
        len = str1->length;
        flag = -1;
    }
    else {
        len = str2->length;
        flag = 1;
    }

    for (int i = 0; i < len; i++) {
        if (str1->ch[i] > str2->ch[i]) return 1;
        else if (str1->ch[i] < str2->ch[i]) return -1;
    }

    return str1->length == str2->length ? 0 : flag;
}

int compareCharArray(char* ch1, char* ch2) {

    char* i = ch1;
    char* j = ch2;
    while (*i && *j) {
        if (*i > *j) return 1;
        else if (*i < *j) return -1;
        else {
            ++i;
            ++j;
        }
    }

    int ret = (*i == '\0') ? -1 : 1;
    return (*i == '\0' && *j == '\0') ? 0 : ret;
}


String* subString(String* str, int start, int len)
{
    if (str == NULL || start < 0 || start >= str->length || len < 0 || len >= str->length) return NULL;

    String* ret = (String*)malloc(sizeof(String));
    ret->length = len;
    ret->ch = (char*)malloc(sizeof(char) * (len + 1));

    for (int i = start; i < start + len; i++) {
        ret->ch[i - start] = str->ch[i];
    }
    ret->ch[len] = '\0';
    return ret;
}

//sub 从"下标[start]~下标[end]"
String* subStr(String* str, int start, int end)
{
    if (str == NULL || start < 0 || start >= str->length || end < start || end >= str->length) return NULL;

    String* ret = (String*)malloc(sizeof(String));
    ret->length = end - start + 1;
    ret->ch = (char*)malloc(sizeof(char) * (ret->length + 1));

    for (int i = start; i <= end; i++)
        ret->ch[i - start] = str->ch[i];

    ret->ch[ret->length] = '\0';
    return ret;
}

String* subCharArr(char* ch, int start, int end)
{
    if (ch == NULL) return NULL;
    return subStr(charArrayToString(ch), start, end);
}

String* subCharArray(char* ch, int pos, int end)
{
    if (ch == NULL) return NULL;
    return subString(charArrayToString(ch), pos, end);
}


String* concatStr(char* str1, char* str2)
{
    String* s1 = charArrayToString(str1);
    String* s2 = charArrayToString(str2);
    String* ret = concat(s1, s2);
    destroyString(&s1);
    destroyString(&s2);
    return ret;
}

String* concat(String* str1, String* str2)
{
    String* ret = (String*)malloc(sizeof(String));

    ret->length = str1->length + str2->length;
    ret->ch = (char*)malloc(sizeof(char) * (ret->length + 1));
    for (int i = 0; i < str1->length; i++)
        ret->ch[i] = str1->ch[i];

    for (int i = 0; i < str2->length; i++)
        ret->ch[i + str1->length] = str2->ch[i];

    ret->ch[ret->length + 1] = '\0';
    return ret;
}

int getLength(String* str)
{
    if (str == NULL) return -1;
    return str->length;
}

int clearString(String* str)
{
    if (str == NULL || str->length == 0) return 0;

    str->ch[0] = '\0';
    str->length = 0;
    return 1;
}

int destroyString(String** str)
{
    if (!clearString(*str)) return 0;

    free((*str)->ch);
    free(*str);
    *str = NULL;
    return 1;
}
