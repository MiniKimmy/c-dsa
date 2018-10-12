## 94.Binary Tree Inorder Traversal

Given a binary tree, return the inorder traversal of its nodes' values.

**Example:**
```
Input: [1,null,2,3]
   1
    \
     2
    /
   3

Output: [1,3,2]
```
**Follow up:** Recursive solution is trivial, could you do it iteratively?

## hints
```
    stack -- NonRecursion.

    1.move----left., then mark the current->right
    2.if mark != NULL, repeat 1
    3.if mark == NULL, do nothing.
    4.when top != -1, add to ret[]
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


int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    if(root==NULL)return NULL;

    struct TreeNode** sqStack = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * 1000);
    int top = -1;
    sqStack[++top] = root;

    int* ret = (int*)malloc(sizeof(int) * 10000);
    int index = 0;

    struct TreeNode* t = root;
    while(top!=-1){
        while(t && t->left){
            sqStack[++top] = t->left;
            t = t->left;
        }

        if(top != -1){
            struct TreeNode* temp = sqStack[top];
            ret[index++] = temp->val;
            top--;
            t = temp->right;
            if(t){
                sqStack[++top] = t;
            }
        }
    }

    free(sqStack);
    *returnSize = index;
    return ret;

}

/* Recursive solution
void inorderTraversalInner(struct TreeNode* root, int* ref, int* index){
    if(root){
        inorderTraversalInner(root->left,ref,index);
        ref[*index] = root->val;
        *index = *index + 1;
        inorderTraversalInner(root->right,ref,index);
    }
}

int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    if(root==NULL)return NULL;
    int* ret = (int*)malloc(sizeof(int) * 10000);

    int index=0;
    inorderTraversalInner(root,ret,&index);
    *returnSize = index;
    return ret;
}
*/
```
