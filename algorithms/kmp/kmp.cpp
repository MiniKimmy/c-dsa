// kmp
#include <iostream>
#include <string.h>

using namespace std;
const int N = 1e5, M = 1e6 + 10; // N 是模板串p最大长度, M 是模式串s最大长度

// 短的串: p
// 长的串: s
// next[j] : 以[j]结尾的后缀能和前缀子串匹配的最大长度
char p[N], s[M];
int ne[N];

int main(){
    // 下标从1开始
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

    for (int i = 1, j = 0; i <= m; i ++ )
    {
        while(j && p[j + 1] != s[i]) j = ne[i];
        if (p[j + 1] == s[i]) j ++;

        if (j == n) 
        {
            // 匹配成功 ..

            j = ne[j];  // 继续匹配
        }
    }

    return 0;
}