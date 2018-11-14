## Get binary path of node

## CHINESE
给出一个按数组顺序存储的二叉树,试编写算法找到结点编号i的所有父节点

**Example 1:**
```
Input :
     4
   /   \
 -22    7
 / \   / \
1  13 6   9

i=13
Output : ["4"->"-22"->"13"]
```

## hints
```
    1.String method
        * intParse() Like int n=22 -> str = "-22"
        * concat() Like: str = str1+str2
    2.dfs
        * Add(item)
        * Copy buffer str.
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

char* toString(int n) {
    if (n == 0) {
        char* ret = (char*)malloc(sizeof(char*) * 2);
        ret[0] = '0';
        ret[1] = '\0';
        return ret;
    }

    int* buffer = (int*)malloc(sizeof(int) * 10);
    int index = 0;
    int abs = n < 0 ? -n : n;

    while (abs>0) {
        int a = abs % 10;
        buffer[index++] = a;
        abs = abs / 10;
    }

    if (n<0) index++;
    char* ret = (char*)malloc(sizeof(char) * (index + 1));

    for (int i = index - 1; i >= 0; --i) {
        ret[index - i - 1] = buffer[i] + '0';
    }

    if (n<0) ret[0] = '-';
    ret[index] = '\0';

    free(buffer);
    return ret;
}

void dfs(TreeNode* root, int x, char* str, int index, char** ret){
    if (root == NULL) return;

    char* item = toString(root->val);

    char* p = item;
    while (*p) {
        str[index++] = *p;
        ++p;
    }
    free(item);

    if (root->val == x) {
        *ret = (char*)malloc(sizeof(char)* (index+1));

        for (int i = 0; i < index; ++i)
            (*ret)[i] = str[i];

        (*ret)[index] = '\0';
        return;
    }else {
        str[index++] = '-';
        str[index++] = '>';
    }

    dfs(root->left, x, str, index, ret);
    dfs(root->right, x, str, index, ret);
}

char* getBinaryPath(TreeNode* root, int x){

    char* ret = NULL;
    char* str = (char*)malloc(sizeof(char) * 1000);
    dfs(root, x, str, 0, &ret);
    free(str);
    return ret;
}
```