## Traverse tree in desending level order

## CHINESE
从树下到上从右到左层序遍历一棵树.

**Example 1:**
```
Input :
     4
   /   \
  2     3
 / \   / \
1  13 6   9

Output : [9,6,13,1,3,2,4]
```

## hints
```
    1.Traverse in level order with sqQueue;
    2.reverse sqQueue to print.
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
void descendingLevelOrderInner(TreeNode* root, TreeNode*** ref_queue, int* len) {

    int maxSize = 1000;
    TreeNode** sqQueue = (TreeNode**)malloc(sizeof(TreeNode*) * maxSize);
    int front = 0;
    int rear = 0;
    sqQueue[rear] = root;
    rear = (rear + 1) % maxSize;

    while (front != rear) {
        TreeNode* t = sqQueue[front];
        front = (front + 1) % maxSize;

        (*ref_queue)[*len] = t;
        *len = *len + 1;

        if (t->left) {
            sqQueue[rear] = t->left;
            rear = (rear + 1) % maxSize;
        }

        if (t->right) {
            sqQueue[rear] = t->right;
            rear = (rear + 1) % maxSize;
        }
    }

    free(sqQueue);
}

void descendingLevelOrder(TreeNode* root) {

    TreeNode** sqQueue = (TreeNode**)malloc(sizeof(TreeNode*) * 1000);
    int len = 0;

    descendingLevelOrderInner(root, &sqQueue,&len);
    for (int i = len-1; i >= 0; --i) {
        TreeNode* t = sqQueue[i];
        printf("%d\n", t->val);
    }

    free(sqQueue);
    return;
}
```