## 101.Symmetric Tree

Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

For example, this binary tree [1,2,2,3,4,4,3] is symmetric:
```
    1
   / \
  2   2
 / \ / \
3  4 4  3
```
But the following [1,2,2,null,3,null,3] is not:
```
    1
   / \
  2   2
   \   \
   3    3

**Note:**
Bonus points if you could solve it both recursively and iteratively.

## hints
```
    1.normal BFS add nodes.
    2.at the beginning of BFS, mark the old-front and old-right.
    3.judge len/2, and left-arr equals right-arr

    ex: a = left-arr, b = right-arr with 4 situations as follows:

    * (Val) a[leftIndex]->left ?= b[rightIndex]->right
    * (Val) a[leftIndex]->right ?= b[rightIndex]->left

    * (Reference) a[leftIndex]->left ?= b[rightIndex]->right
    * (Reference) a[leftIndex]->right ?= b[rightIndex]->left
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

bool isSymmetric(struct TreeNode* root) {
    if(root==NULL) return true;

    int MAXSIZE = 1000;
    struct TreeNode** sqQueue = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * MAXSIZE);
    int top = -1;

    int front = 0;
    int rear = 0;
    int level = 0;
    sqQueue[rear] = root;
    rear = (rear+1)%MAXSIZE;


    while(rear != front){
        int size = (rear-front+MAXSIZE)%MAXSIZE;

        int left_flag = front;
        int rear_flag = rear;

        for(int i = 0;i<size;i++){
            struct TreeNode* node = sqQueue[front];
            front = (front + 1) % MAXSIZE;

            if(node->left) {
                sqQueue[rear] = node->left;
                rear = (rear + 1) % MAXSIZE;
            }

            if(node->right){
                sqQueue[rear] = node->right;
                rear = (rear + 1) % MAXSIZE;
            }

            if(rear_flag != left_flag){
                struct TreeNode* a = sqQueue[left_flag];
                struct TreeNode* b = sqQueue[(rear_flag-1)%MAXSIZE];
                left_flag = (left_flag+1)% MAXSIZE;
                rear_flag= (rear_flag-1)%MAXSIZE;

                if(a->left && b->right && a->left->val != b->right->val){
                    return false;
                }

                if(a->right && b->left && a->right->val != b->left->val){
                   return false;
                }
                if(a->left && b->right == NULL || a->right && b->left == NULL)
                    return false;
                if(a->left == NULL && b->right  || a->right == NULL && b->left )
                    return false;
            }
        }


    }

    free(sqQueue);
    return true;
}
```