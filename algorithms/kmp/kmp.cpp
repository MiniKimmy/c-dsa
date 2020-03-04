// kmp算法
#include <iostream>
#include <string.h>

using namespace std;
const int N = 1e5 + 10; // 模板串p最大长度
const int M = 1e6 + 10;     // 模式串s最大长度

// 短的串: p
// 长的串: s
// next[j] : 以[j]结尾的后缀能和前缀子串匹配的最大长度
// 一般下标从1开始
char p[N], s[M];
int ne[N];

// 模板
int main(){
    cin >> p + 1 >> s + 1;
    int n = strlen(p + 1);
    int m = strlen(s + 1);

    // 求next[]数组, 默认: ne[1] = 0
    for (int i = 2, j = 0; i <= n; i ++ )
    {
        while(j && p[j + 1] != p[i]) j = ne[j];
        if (p[j + 1] == p[i]) j ++;
        ne[i] = j;
    }

    // kmp 过程
    for (int i = 1, j = 0; i <= m; i ++ )
    {
        while(j && p[j + 1] != s[i]) j = ne[j];
        if (p[j + 1] == s[i]) j ++;
        if (j == n)    // 匹配成功
        {
            j = ne[j]; // 继续匹配

            // 具体题目逻辑..
            
        }
    }

    return 0;
}