// trie数 | 字典树 | 串树
using namespace std;

const int N = 1e6 + 10; // 根据题目数据范围
const int M = 26;       // 根据要存什么, 例如:这里要存26个小写字母
int son[N][M], idx;     // son[数据量][分支量], idx=0表示根节点或不存在的结点.

// 插入元素
void insert(string str)
{
    int p = 0;  // 从根结点开始.
    for (int i = 0; str[i]; i ++ )
    {
        int u = str[i] - 'a';
        int &t = son[p][u]   // 获取引用
        if(!t) t = ++ idx;   // 新增结点, 递增idx, idx是内部使用的唯一标记.
        p = t;
    }

    // 新增元素完成之后的处理.. (此时p = idx, 即当前新增元素的唯一idx)

}

// 查询元素
void query(string str)
{
    int p = 0; // 从根结点开始.
    for (int i = 0; str[i]; i ++ )
    {
        int u = str[i] - 'a';
        int &t = son[p][u]
        if(!t) {
            // 若找不到
            return;
        }

        p = t;
    }
}