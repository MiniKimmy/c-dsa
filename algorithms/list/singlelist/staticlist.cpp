// 静态链表
using namespace std;
const int N = 1e6 + 10;  // 取决于数据范围

int head;
int e[N], ne[N], idx;

// 初始化
void init() { 
    head = -1, idx = 0; 
}

// 插入一个新的元素到链表头
void add_to_head(int val) { 
    e[idx] = val, ne[idx] = head, head = idx ++; 
}

// 在第k个结点后面插入元素
void add(int k, int val) { 
    e[idx] = val, ne[idx] = ne[k], ne[k] = idx ++; 
}

// 删除第k个结点后面的元素
void remove(int k){ 
    ne[k] = ne[ne[k]]; 
}

// 遍历
void traverse(){
    for(int i = head; i != -1; i = ne[i]) printf("%d", e[i]);
}