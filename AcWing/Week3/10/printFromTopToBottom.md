## 44. 分行从上往下打印二叉树
[这里](https://www.acwing.com/problem/content/42/)

从上到下按层打印二叉树，同一层的结点按从左到右的顺序打印，每一层打印到一行

**Example :**
```
Input:[8, 12, 2, null, null, 6, null, 4, null, null, null]
    8
   / \
  12  2
     /
    6
   /
  4
Output:[[8], [12, 2], [6], [4]]
```

## hints
```
    levelOrder+bfs
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
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

int getDepth(struct TreeNode* root)
{
    if(root == NULL) return 0;
    int i = getDepth(root->left);
    int j = getDepth(root->right);
    return i>j?i+1:j+1;
}

// levelOrder+bfs
int** printFromTopToBottom(struct TreeNode* root, int** columnSizes, int* returnSize) {
    if(root == NULL) {
        *returnSize = 0;
        *columnSizes = NULL;
        return NULL;
    }

    int depth = getDepth(root);
    int** ret = (int**)malloc(sizeof(int*) * depth);
    *columnSizes = (int*)malloc(sizeof(int) * depth);
    *returnSize = depth;

    int SIZE = 5000;
    struct TreeNode** queue = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * SIZE);
    int front = 0; int rear = 0;
    queue[rear] = root;
    rear = (rear +1) % SIZE;

    int level = 0;
    while(front != rear)
    {
        int len = (rear-front + SIZE)%SIZE;
        int* item = (int*)malloc(sizeof(int) * len);

        // bfs
        for(int i = 0;i<len;++i){
            struct TreeNode* t = queue[front];
            front = (front+1)%SIZE;
            item[i] = t->val;

            if(t->left){
                queue[rear] = t->left;
                rear = (rear + 1)%SIZE;
            }

            if(t->right){
                queue[rear] = t->right;
                rear = (rear + 1)%SIZE;
            }
        }

        ret[level] = item;
        (*columnSizes)[level] = len;
        level++;
    }

    free(queue);
    return ret;
}
```