/*
Q111.Minimum Depth of Binary Tree
Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.

Note: A leaf is a node with no children.

Example:

Given binary tree [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7

return its minimum depth = 2.
*/

//C
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int minDepth(struct TreeNode* root) {

    if(root == NULL) return 0;

    int i,j;
    i = minDepth(root->left);
    j = minDepth(root->right);

    if(root->left == NULL && root->right) return j+1;
    if(root->right == NULL && root->left) return i+1;
    else return i>j?j+1:i+1;
}

