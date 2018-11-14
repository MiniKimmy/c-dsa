## Calc the double branches nodes counts

## CHINESE
给出一个按数组顺序存储的二叉树,试求出双分支节点数.

**Example 1:**
```
Input :
     4
   /   \
  2     3
 / \   / \
1  13 6   9


Output : 3
Explaination:'4','2','3' with tow branches.
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

void dfs(TreeNode* root, int* count){
    if (root == NULL) return;

    if (root->left && root->right) {
        *count = *count + 1;
    }

    dfs(root->left, count);
    dfs(root->right,count);
}

int calcDoubleBranch(TreeNode* root){
    int ret = 0;
    dfs(root, &ret);
    return ret;
}
```