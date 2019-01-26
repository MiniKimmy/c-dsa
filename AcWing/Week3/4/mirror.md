## 38. 二叉树的镜像
[这里](https://www.acwing.com/problem/content/37/)
输入一个二叉树，将它变换为它的镜像。

**Example :**
```
Input:
      8
     / \
    6  10
   / \ / \
  5  7 9 11

 [8,6,10,5,7,9,11,null,null,null,null,null,null,null,null]

Output:
      8
     / \
    10  6
   / \ / \
  11 9 7  5

 [8,10,6,11,9,7,5,null,null,null,null,null,null,null,null]
```
## hints
```
    后序遍历
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

void mirror(struct TreeNode* root) {
    if(root == NULL) return;

    mirror(root->left);
    mirror(root->right);

    if(root == NULL) return;
    else{
        struct TreeNode* t = root->left;
        root->left = root->right;
        root->right = t;
    }
}
```