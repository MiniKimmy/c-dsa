## Get less k min in BST

## CHINESE
求BST里倒数第k个小的值

**Example 1:**
```
Input : [7,3,9,1,4,null,11,-2,2, null ,5], k=3
        7
      /   \
     3     9
    / \   / \
   1   4    11
  / \   \
-2   2   5

Output : 2
Explanation: -2<2<1<3<4<5<7<9<11 , 2 as the rank min-3.
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

void inOrder(TreeNode* root, int k, int* count, int* ret){
    if (root == NULL) return;

    inOrder(root->left,k,count, ret);
    *count = *count + 1;
    if (*count == k) {
        *ret = root->val;
    }
    inOrder(root->right, k, count, ret);
}

int getSpecialMinVal(struct TreeNode* root,int k) {
    if (root == NULL) return 0;

    int count = 0;
    int ret;
    inOrder(root, k, &count, &ret);
    return ret;
}
```