## 43. 不分行从上往下打印二叉树
[这里](https://www.acwing.com/problem/content/description/41/)
从上往下打印出二叉树的每个结点，同一层的结点按照从左到右的顺序打印。

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
Output:[8, 12, 2, 6, 4]
```

## hints
```
    levelOrder
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
 * Return an array of  size *returnSize.
 * Note: returned array must be malloced, assume caller calls free().
 */
int* printFromTopToBottom(struct TreeNode* root , int* returnSize){
    if(root == NULL) {
        *returnSize = 0;
        return NULL;
    }

    int SIZE = 10000;
    struct TreeNode** queue = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * SIZE);
    int front = 0; int rear = 0;
    queue[rear] = root;
    rear = (rear +1)%SIZE;

    int count = 0;
    int* buffer = (int*)malloc(sizeof(int) * 5000);
    while(front != rear)
    {
        struct TreeNode* t = queue[front];
        front = (front+1)%SIZE;

        buffer[count++] = t->val;
        if(t->left){
            queue[rear] = t->left;
            rear = (rear +1)%SIZE;
        }

        if(t->right)
        {
            queue[rear] = t->right;
            rear = (rear +1)%SIZE;
        }

    }

    int* ret = (int*)malloc(sizeof(int) * count);
    for(int i = 0;i<count;++i){
        ret[i] = buffer[i];
    }

    free(queue);
    free(buffer);
    *returnSize = count;
    return ret;
}
```