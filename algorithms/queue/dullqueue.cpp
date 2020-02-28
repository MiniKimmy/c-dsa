// 单调队列
using namespace std;
const int N = 1e6 + 10;

int q[N], hh, tt;  // 数组模拟队列

// 使用模板
int main(){

    hh = 0, tt = -1;
	for (int i = 0; i < n; i ++ )
	{
		// check队头是否滑出
        while (hh <= tt && check_out(q[hh], i)) hh ++ ;

        // check队列单调
        while (hh <= tt && check(q[tt], i)) tt --;

        // 更新队列
		qq[ ++ tt] = i;

        // 具体题目逻辑..
	}

}