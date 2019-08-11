## 144.Binary Tree Preorder Traversal

Given a binary tree, return the preorder traversal of its nodes' values.

**Example:**
```
Input: [1,null,2,3]
   1
    \
     2
    /
   3

Output: [1,2,3]
```
**Follow up**: Recursive solution is trivial, could you do it iteratively?

## Analogous
|                         Nav               |                   Des            |
| :----------------------------------------:|:--------------------------------:|
| ![inorderTraversal](inorderTraversal.md)|无递归中序遍历二叉树                |

## hints
```
    1.stack problem
    2.push right-child first, then push left-child
    3.each time, pop stack[top]
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

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

int* preorderTraversal(struct TreeNode* root, int* returnSize) {
    if(root == NULL) return NULL;

    int* ret = (int*)malloc(sizeof(int) * 10000);
    struct TreeNode** sqStack = (struct TreeNode**)malloc(sizeof(struct TreeNode*)*1000);
    int top = -1;
    sqStack[++top] = root;

    int index = 0;
    while(top != -1){
        struct TreeNode* t = sqStack[top--];
        ret[index++] = t->val;
        if(t->right){
            sqStack[++top] = t->right;
        }

        if(t->left){
            sqStack[++top] = t->left;
        }
    }

    *returnSize = index;
    free(sqStack);
    return ret;
}
```