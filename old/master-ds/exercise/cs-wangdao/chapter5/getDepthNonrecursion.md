## Get Depth of tree with nonrecursion

## CHINESE
用非递归的方式求树的高度.

**Example 1:**
```
Input :
     4
   /   \
  2     3
 / \   / \
1  13 6   9

Output : 3
```

## hints
```
    * bfs and levelOrder
    1.count the queueSize and Traverse each level
    2.before next level, depth++.
```

## Solution
```
/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     struct TreeNode *left;
*     struct TreeNode *right;
* };
*/

void getDepthNonrecursionInner(TreeNode* root, int* len) {
    int maxSize = 1000;
    TreeNode** sqQueue = (TreeNode**)malloc(sizeof(TreeNode*) * maxSize);
    int front = 0;
    int rear = 0;
    sqQueue[rear] = root;
    rear = (rear + 1) % maxSize;

    while (front != rear) {
        int QSize = (rear - front + maxSize) % maxSize;

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

        *len = *len + 1;
    }

    free(sqQueue);
}

int getDepthNonrecursion(TreeNode* root){
    int len = 0;

    getDepthNonrecursionInner(root, &len);
    return len;
}
```