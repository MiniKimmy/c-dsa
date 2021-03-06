// 数组模拟栈
using namespace std;

const int N = 1e6 + 10;  // 取决于数据范围
int stk[N], tt;          // 从[1]开始存val

// 判空
bool empty()
{
    return tt == 0;
}

// 新增元素
void push(int x)
{
    stk[++ tt] = x;
}

// 弹出
void pop()
{
    if (tt == 0) return;
    tt --;
}

// 查询堆顶元素
int top()
{
    return stk[tt];
}