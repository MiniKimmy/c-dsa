// 单调栈
using namespace std;
const int N = 1e6 + 10;

int stk[N], tt;  // 数组模拟栈

// 使用模板
int main(){
	for (int i = 1; i <= n; i ++ )
	{
		// check函数
        while (tt && check(q[tt], i)) tt -- ;

        // 具体题目逻辑..

        // 插入最新的元素
		stk[ ++ tt] = i;
	}
}