// 字符串哈希(预处理字符串->转化为数字)
using namespace std;
typedef unsigned long long ULL; // 存储的时候一般要 mod Q (Q 一般是2^64), ULL溢出相当于mod 2^64
const int P = 131;              // 131是经验值, P也可以用13331

// h[i] = 前i个字母的hash值, 特殊: h[0] = 0 (不能映射为0)
// p[i] : P进制数 => p^i
ULL h[N], p[N];

// 初始化, 字符串下标从1开始
void init(string str){
    for (int i = 1; i <= str.size(); i ++)
    {
        p[i] = p[i - 1] * P;
        h[i] = h[i - 1] * P + str[i];
    }
}

// 获取任意[L~R]子串的hash值
ULL getHash(int l, int r)
{
    return h[r] - h[l - 1] * p[r - l + 1];
}