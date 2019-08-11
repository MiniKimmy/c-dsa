## 70. 二叉搜索树的第k个结点
[这里](https://www.acwing.com/problem/content/66/)
给定一棵二叉搜索树，请找出其中的第k小的结点。
你可以假设树和k都存在，并且1≤k≤树的总结点数

**Example :**
```
Input:
root = [2, 1, 3, null, null, null, null] ，k = 3
    2
   / \
  1   3
Output:3
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

void inorder(struct TreeNode* root, int k, int* count, struct TreeNode** ret)
{
    if(!root || *ret) return;

    inorder(root->left,k,count,ret);
    ++(*count);
    if(*count == k){
        *ret = root;
    }
    inorder(root->right,k,count,ret);
}

struct TreeNode* kthNode(struct TreeNode* root, int k) {
    struct TreeNode* refRet = NULL;
    int count = 0;
    inorder(root,k, &count, &refRet);
    return refRet;
}
```