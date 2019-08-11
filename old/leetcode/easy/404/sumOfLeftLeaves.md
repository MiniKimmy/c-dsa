## 404.Sum of Left Leaves

Find the sum of all left leaves in a given binary tree.

**Example:**
```
    3
   / \
  9  20
    /  \
   15   7

There are two left leaves in the binary tree, with values 9 and 15 respectively.
Output:24
```

## hints
```
    inorder traverse.
```

## Analogous
|                       Nav                 |                   Des            |
| :----------------------------------------:|:--------------------------------:|
| ![inorderTraversal](../../medium/94/inorderTraversal.md)|无递归中序遍历二叉树|

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

void sumOfLeftLeavesInner(struct TreeNode* root, int* ret){
    if(root){
        sumOfLeftLeavesInner(root->left, ret);
        if(root->left
        && root->left->left == NULL
        && root->left->right == NULL) {
            *ret = *ret + root->left->val;
        }
        sumOfLeftLeavesInner(root->right, ret);
    }
}

int sumOfLeftLeaves(struct TreeNode* root) {
    int ret = 0;
    sumOfLeftLeavesInner(root,&ret);
    return ret;
}
```

