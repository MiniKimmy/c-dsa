## Q110.Balanced Binary Tree

Given a binary tree, determine if it is height-balanced.<br\>
For this problem, a height-balanced binary tree is defined as:<br\>
a binary tree in which the depth of the two subtrees of every node never differ by more than 1.<br\>

**Example 1:**<br\>

Given the following tree [3,9,20,null,null,15,7]:
```
    3
   / \
  9  20
    /  \
   15   7
```
Return true.<br\>


**Example 2:**<br\>

Given the following tree [1,2,2,3,3,null,null,4,4]:<br\>
```
       1
      / \
     2   2
    / \
   3   3
  / \
 4   4
```
Return false.<br\>

## hints:
   1. compare the length of node->left with the length node->right and claculate abs(len_left-len_right).
   2. Then if root is balanced, and it will have 2 situation. You can consider that "A U B" in math, and for this problem it means 'A' false or 'B' false will return false.
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



int abs(int a){
    if(a < 0 ) return -a;
    else return a;
}

int getSize(struct TreeNode* root){
    if(root == NULL) return 0;
    int i = getSize(root->left);
    int j = getSize(root->right);
    return i>j?i+1:j+1;
}

bool isBalanced(struct TreeNode* root) {
    if(root == NULL) return true;

    int a = getSize(root->left);
    int b = getSize(root->right);

    if(abs(a-b)>=2)return false;
    else{
        if(!isBalanced(root->left))
            return false;
        if(!isBalanced(root->right))
            return false;
    }

    return true;
}

```