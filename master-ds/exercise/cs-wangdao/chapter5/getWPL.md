## Get tree WPL

## CHINESE
求一个正则二叉树的WPL.

**Example 1:**
```
Input :
        *
      /   \
     *     *
    / \   / \
   *   4 7   9
  / \
 2   3

Output : WPL = (2+3)*3 + (4+7+9)*2 = 55
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

void dfs(TreeNode* root, int level, int* sum){
    if (root == NULL) return;

    if (root->left == NULL &&root->right == NULL) {
        *sum += root->val * (level+1);
    }

    dfs(root->left, level+1, sum);
    dfs(root->right, level+1, sum);
}

int getWPL(struct TreeNode* root) {
    if (root == NULL) return 0;
    int ret = 0;
    dfs(root, 0, &ret);
    return ret;
}
```