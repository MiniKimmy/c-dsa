## 71. 二叉树的深度
[这里](https://www.acwing.com/problem/content/67/)

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
int treeDepth(struct TreeNode* root) {
    if(root == NULL) return 0;
    int i = treeDepth(root->left);
    int j = treeDepth(root->right);
    return i > j? i +1:j+1;
}
```