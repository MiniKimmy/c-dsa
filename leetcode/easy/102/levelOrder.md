## 102. Binary Tree Level Order Traversal

Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

**For example:**
```
Given binary tree [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
```
return its level order traversal as:
```
[
  [3],
  [9,20],
  [15,7]
]
```

## hints
![averageOfLevels](../637/averageOfLevels.md) : 一道类似的题目
```
    Queue + LevelOrder + BFS
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

int getDepth(struct TreeNode* root){
    if(root == NULL) return 0;
    int i = getDepth(root->left);
    int j = getDepth(root->right);
    return i>j?i+1:j+1;
}

int** levelOrder(struct TreeNode* root, int** columnSizes, int* returnSize) {
    *returnSize = getDepth(root);
    if(*returnSize == 0) {
        *columnSizes = NULL;
        return NULL;
    }

    int** ret = (int**)malloc(sizeof(int*) * (*returnSize));
    int* csize = (int*) malloc(sizeof(int*) * (*returnSize));

    int ARRAYSIZE = 1000;
    struct TreeNode** sqQueue = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * ARRAYSIZE);

    int front = 0;
    int rear = 0;
    sqQueue[rear] = root;
    rear = (rear + 1 ) % ARRAYSIZE;
    int level = 0;

    while(front != rear){
        csize[level] = (rear - front + ARRAYSIZE) %ARRAYSIZE;
        int* levelNodes = (int*)malloc(sizeof(int) * csize[level]);

        for(int i=0;i<csize[level];++i){
            struct TreeNode* node = sqQueue[front];
            front = (front + 1) % ARRAYSIZE;
            levelNodes[i] = node->val;

            if(node->left) {
                sqQueue[rear] = node->left;
                rear = (rear + 1) % ARRAYSIZE;
            }

            if(node->right){
                sqQueue[rear] = node->right;
                rear = (rear + 1) % ARRAYSIZE;
            }
        }
        ret[level++] = levelNodes;
    }

    *columnSizes = csize;
    return ret;
}
```