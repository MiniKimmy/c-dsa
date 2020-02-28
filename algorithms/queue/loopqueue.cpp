// 循环队列
using namespace std;
const int N = 1e6 + 10  // 取决于数据范围

int q[N], hh, tt;       // 数组模拟队列

// 初始化, 从[0]开始存val, hh 队头指针, tt 队尾指针.
void init() { 
    hh = 0, tt = -1;
}

// 判空
bool empty(){
    return !(hh != tt);
}

// 新增元素
void push(int x){
    q[tt] = x;
    tt = (tt + 1) % N
}

// 弹出队头
void pop(){
    if (empty()) return;
    hh = (hh + 1) % N
}

// 查询队头
int getTop(){
    return q[hh];
}

// 查询队列有效元素个数
int getCount(){
    return (tt - hh + N) % N;
}