// 静态双链表
using namespace std;
const int N = 1e6 + 10  // 取决于数据范围

int e[N], l[N], r[N], idx;

// 初始化
// 0 : 左端点(哨兵)
// 1 ：右边界(哨兵)
void init() { 
    r[0], l[1], idx = 1, 0, 2
}

// 在第k个结点右边插入元素
void add(int k, int val) { 
    e[idx] = val, l[idx] = k, r[idx] = r[k], l[r[k]] = idx, r[k] = idx ++;
}

// 删除第k个结点
void remove(int k){
    l[r[k]] = l[k];
    r[l[k]] = r[k];
}

// 遍历
void traverse(){
    for(int i = r[0]; i != 1; i = r[i]) printf("%d", e[i]);
}