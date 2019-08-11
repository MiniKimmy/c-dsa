## Tree Level and treenode val

Given a binary tree, preOrder Traverse, return each node's val and its level.

## CHINESE
给一个普通二叉树，前序遍历输出结点的val以及结点所在的层号

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

void getLevelpreOrderTraverseInner(TreeNode* root, int level){
    if (root == NULL) return;

    printf("val=%d level=%d\n", root->val, level + 1);
    getLevelpreOrderTraverseInner(root->left, level + 1);
    getLevelpreOrderTraverseInner(root->right, level + 1);
}

void getLevelpreOrderTraverse(TreeNode* root){
    int level = 0;
    getLevelpreOrderTraverseInner(root, level);
}
```