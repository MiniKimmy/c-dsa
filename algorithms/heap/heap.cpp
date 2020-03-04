// 手写堆(小根堆)
#include <string.h>
#include <iostream>

using namespace std;
const int N = 1e6 + 10;  // 取决于数据范围

int h[N], hp[N], ph[N], sz;

void heap_swap(int a, int b)
{
    swap(ph[hp[a]], ph[hp[b]]);
    swap(hp[a], hp[b]);
    swap(h[a], h[b]);
}

void down(int t)
{
    int u = t;
    if(t + t <= sz && h[t + t] < h[u]) u = t + t;
    if(t + t + 1 <= sz && h[t + t + 1] < h[u]) u = t + t + 1;
    if(u != t)
    {
        heap_swap(u, t);
        down(u);
    }
}

void up(int t)
{
    int u = t / 2;
    if(u && h[u] > h[t])
    {
        heap_swap(u, t);
        up(u);
    }
}

// 测试&&调用
/*
1) “I x”  ：插入一个数x;
2) “PM”   ：输出当前集合中的最小值;
3) “DM”   ：删除当前集合中的最小值（数据保证此时的最小值唯一）;
4) “D k”  ：删除第k个插入的数；
5) “C k x”：修改第k个插入的数，将其变为x;
*/
int main(){
    int T; cin >> T; // T组测试

    int idx = 0;     // 记录处理到第几个数.
    while(T --)
    {
        char op[5];
        int k, x;
        cin >> op;

        if (!strcmp(op, "I"))
        {
            scanf("%d", &x);
            sz ++, idx ++;
            hp[sz] = idx, ph[idx] = sz;
            h[sz] = x;
            up(sz);
        }

        else if (!strcmp(op, "PM"))
        {
            printf("%d\n", h[1]);
        }

        else if (!strcmp(op, "DM"))
        {
            heap_swap(1, sz);
            sz --;
            down(1);
        }

        else if (!strcmp(op, "D"))
        {
            scanf("%d", &k);
            k = ph[k];
            heap_swap(k, sz);
            sz --;
            down(k), up(k);
        }

        else
        {
            scanf("%d%d", &k, &x);
            k = ph[k];
            h[k] = x;
            down(k), up(k);
        }
    }
}

/* 测试用例
Input:
8
I -10
PM
I -10
D 1
C 2 8
I 6
PM
DM
Output:
-10
6
*/