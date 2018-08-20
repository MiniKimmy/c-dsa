## 107.Binary Tree Level Order Traversal II

Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).

**For example:**
Given binary tree [3,9,20,null,null,15,7],
```
    3
   / \
  9  20
    /  \
   15   7
```
return its bottom-up level order traversal as:
```
[
  [15,7],
  [9,20],
  [3]
]
```

## hints
![Tree每层的平均值](../637/averageOfLevels.md) : 可以类比这题.
```
    BFS Traverse.
    1. getDepth of this tree first, then we can init the arraySize.
    2. we can use SqQueue or LinkQueue to as LeverTraverse.
    3. traverse one level ,then handle all the node in the same level (BFS).
    4. inverse the Array means we can store the data from tail to head cause we know the depth which can confirm the Array's max length.

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

#define MaxSqQueue 1000

int getDepth(struct TreeNode* T){
    if(T == NULL) return 0;
    int i = getDepth(T->left);
    int j = getDepth(T->right);
    return i>j?i+1:j+1;
}

int** levelOrderBottom(struct TreeNode* root, int** columnSizes, int* returnSize) {
    int len = getDepth(root);
    if(len == 0) return NULL;

    int** ret = (int**)malloc(sizeof(int*) * len);
    (*columnSizes) = (int*)malloc(sizeof(int) * len);
    *returnSize = len;

    struct TreeNode** SqQueue = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * MaxSqQueue);
    int front = 0;
    int rear = 0;
    SqQueue[rear] = root;
    rear = (rear + 1) % MaxSqQueue;

    int level = 0;
    while(front != rear){
        (*columnSizes)[len- level - 1] = (rear - front + MaxSqQueue) % MaxSqQueue;
        ret[len - level - 1] = (int*)malloc(sizeof(int) * ( (*columnSizes)[len- level - 1] ));

        for(int i = 0; i< (*columnSizes)[len- level - 1] ;i++){
            struct TreeNode* t = SqQueue[front];
            front = (front+1) % MaxSqQueue;
            ret[len - level - 1][i] = t->val;

            if(t->left) {
                SqQueue[rear] = t->left;
                rear = (rear + 1) % MaxSqQueue;
            }

            if(t->right) {
                SqQueue[rear] = t->right;
                rear = (rear + 1) % MaxSqQueue;
            }
        }
        level ++;
    }

    return ret;
}

```