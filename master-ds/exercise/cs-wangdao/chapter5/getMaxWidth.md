## Get max width of binary tree

Given a binary tree, count the most amount of its elements in the level.

## CHINESE
求出二叉树的宽度.即最多元素的那一层的元素个数

**Example 1:**
```
Input :
        4
      /   \
     2     3
    / \   / \
   1  13 6   9
  / \   /
 0   2 1

Output : 4
```

## hints
```
    levelOrder && bfs
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

void getMaxWidthInner(TreeNode* root, int* max) {
    int maxSize = 1000;
    TreeNode** sqQueue = (TreeNode**)malloc(sizeof(TreeNode*) * maxSize);
    int front = 0;
    int rear = 0;
    sqQueue[rear] = root;
    rear = (rear + 1) % maxSize;

    while (front != rear) {
        int QSize = (rear - front + maxSize) % maxSize;
        if (QSize > *max) *max = QSize; //mark the max

        //bfs
        for (int i = 0; i < QSize; ++i) {
            TreeNode* t = sqQueue[front];
            front = (front + 1) % maxSize;

            if (t->left) {
                sqQueue[rear] = t->left;
                rear = (rear + 1) % maxSize;
            }

            if (t->right) {
                sqQueue[rear] = t->right;
                rear = (rear + 1) % maxSize;
            }
        }
    }

    free(sqQueue);
}

int getMaxWidth(TreeNode* root){
    int max = 0;

    getMaxWidthInner(root, &max);
    return max;
}
```