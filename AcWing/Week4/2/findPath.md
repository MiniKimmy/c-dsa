## 47. 二叉树中和为某一值的路径
[这里](https://www.acwing.com/problem/content/45/)
输入一棵二叉树和一个整数，打印出二叉树中结点值的和为输入整数的所有路径。
从树的根结点开始往下一直到叶结点所经过的结点形成一条路径。

**Example :**
```
Input:
      5
     / \
    4   6
   /   / \
  12  13  6
 /  \    / \
9    1  5   1
Output:[[5,4,12,1],[5,6,6,5]]
```

## hints
```
    1.典型的记录型递归void dfs()
        (1).总共有2个未确定长度的需要返回columnSizes和path路径
        (2).c语言特色，一个数组要配一个下标跟着
            * 在赋值的时候使用level的下标
    2.buffer数组记录

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

void dfs(struct TreeNode* root, int x, int** columnSizes, int sum, int* buffer, int level, int*** ret, int* index)
{
    if(root == NULL || sum > x) return;

    buffer[level] = root->val;
    sum += root->val;

    if(sum == x && !root->left && !root->right){
        int len = level+1;
        (*columnSizes)[(*index)] = len;
        int* item = (int*)malloc(sizeof(int) * len);
        for(int i = 0;i<len;++i){
            item[i] = buffer[i];
        }

        (*ret)[(*index)] = item;
        *index = *index+1;
    }

    dfs(root->left, x, columnSizes, sum, buffer, level+1, ret, index);
    dfs(root->right, x, columnSizes, sum, buffer, level+1, ret, index);
}

int** findPath(struct TreeNode* root, int sum, int** columnSizes, int* returnSize) {
    if(root == NULL) {
        *columnSizes = NULL;
        *returnSize = 0;
        return NULL;
    }

    int** refRet = (int**)malloc(sizeof(int*) * 1000);
    int* buffer = (int*)malloc(sizeof(int) * 200);
    *columnSizes = (int*)malloc(sizeof(int*) * 1000);

    int index = 0;
    dfs(root,sum,columnSizes, 0, buffer, 0, &refRet, &index); //从第[0]层开始数

    free(buffer);
    *returnSize = index;
    return refRet;
}
```