## 50. 序列化二叉树
[这里](https://www.acwing.com/problem/content/46/)
请实现两个函数，分别用来序列化和反序列化二叉树。
您需要确保二叉树可以序列化为字符串，并且可以将此字符串反序列化为原始树结构。

**Example : **
```
Input:
    8
   / \
  12  2
     / \
    6   4
Output:[Anyone Order is ok]
levelOrder_Str:"8, 12, 2, null, null, 6, 4, null, null, null, null"
preOrder_Str:"8, 12, 2, null, null, 6, 4, null, null, null, null"
inOrder_Str:"null, 12, null, 8, null, 6, null, 2, null, 4,null"
```

## hints
```
    1.前中后层序的方式去序列化都可以
    2.只需要实现序列化和反序列化的即可
    3.之前需要“前序+中序”or“中序+后序”才能构建一棵树，而这里
    是因为,把null的点也记录了string，所以也能通过这种字符串来构造一棵树.
    4.序列化的字符串可以任意的字符串都可以的，只要能反序列化成功即可。
    5.序列化的字符串可以用空格、逗号等等隔开每一个val:' '、','
```

## Solution
``` c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/** Encodes a tree to a single string. */

int getLen(char* str){
    int len = 0;
    while(str[len]){
        len++;
    }
    return len;
}

/// int转为string
char* toString(int n){
    int temp = n >= 0? n:-n;
    char* buffer = (char*)malloc(sizeof(char) * 10);
    int index = 0;
    while(temp>0){
        buffer[index++] = temp % 10 + '0';
        temp /= 10;
    }

    if(n<0){
        buffer[index++] = '-';
    }

    char* ret = (char*)malloc(sizeof(char) * (index+1));
    for(int i = 0;i<index;++i){
        ret[index-i-1] = buffer[i];
    }

    ret[index] = '\0';
    free(buffer);
    return ret;
}

void dfs_s(struct TreeNode* root, char** ret, int* index)
{
    if(!root){
        char str[5] = "null ";
        for(int i = 0;i<5;++i){
            (*ret)[(*index)++] = str[i];
        }
        return;
    }

    char* tempStr = toString(root->val);
    char* p = tempStr;

    while(*p){
        (*ret)[(*index)++] = *p;
        p++;
    }
    free(tempStr);
    (*ret)[(*index)++] = ' ';

    dfs_s(root->left, ret, index);
    dfs_s(root->right, ret, index);
}

char* serialize(struct TreeNode* root) {
    //10000 取决于测试例子.
    char* buffer = (char*)malloc(sizeof(char) * 10000);
    int index = 0;
    dfs_s(root, &buffer, &index);

    char* ret = (char*)malloc(sizeof(char) * (index+1));
    for(int i = 0;i<index;++i){
        ret[i] = buffer[i];
    }

    ret[index] = '\0';
    free(buffer);
    return ret;
}

struct TreeNode* dfs_d(char* data,int n, int* cur){
    int k = *cur;
    while(k<n && data[k] != ' ') k++; //截取1段str -- 表示一个val

    if(data[*cur] == 'n'){
        *cur += 5;
        return NULL;
    }

    //intParse
    int res = 0;
    for(int i = *cur; i<k;++i){
       res = res * 10 + data[i] - '0';
    }

    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = res;
    *cur = k+1;

    root->left = dfs_d(data, n, cur);
    root->right = dfs_d(data, n, cur);
    return root;
}

/** Decodes your encoded data to tree. */
struct TreeNode* deserialize(char* data) {
    int len = getLen(data);
    int cur = 0;
    return dfs_d(data,len,&cur);
}
```