## Get Sum Path II

## CHINESE
从根节点到某一结点结束的路径值上之和等于x的所有路径数量.

**Example 1:**
```
Input : x=8
        4
      /   \
     2     3
    / \   / \
   1   2 6   1
  / \   /
 5   0 2


Output : [[4,2,2],[4,3,1],[2,1,5],[6,2]]
Explanation: 4+2+2=8, 4+3+1=8, 2+1+5=8, 6+2=8
```

## hints
```
    1.Traverse Tree with any one Order.
    2.(void)dfs(..)
    3.temp-buffer, mark-count
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

void dfs(TreeNode* root, int x, int sum, int* buffer,int index, int** ret, int** lens, int* count){

    if (root == NULL) return;
    buffer[index] = root->val;

    if (sum + root->val == x) {
        int len = index + 1;
        (*lens)[(*count)] = len;

        int* item = (int*)malloc(sizeof(int) * len );
        for (int i = 0; i < len; ++i) {
            item[i] = buffer[i];
        }

        ret[(*count)] = item;
        *count = *count + 1;
    }

    dfs(root->left, x, sum + root->val, buffer, index +1, ret,lens, count);
    dfs(root->right, x, sum + root->val, buffer, index +1, ret,lens, count);
}

void pathSumInner(struct TreeNode* root, int x, int* buffer, int** ret, int** lens, int* count){
    if (root) {
        dfs(root, x, 0, buffer, 0, ret, lens, count);
        pathSumInner(root->left, x, buffer,ret, lens, count);
        pathSumInner(root->right, x, buffer, ret, lens, count);
    }
}

int** getSpecialPathII(struct TreeNode* root, int x, int* returnSize, int** returnSize1) {
    if (root == NULL) return 0;

    int** ret = (int**)malloc(sizeof(int*) * 100);
    int* buffer = (int*)malloc(sizeof(int) * 100);
    int* lens = (int*)malloc(sizeof(int) * 100);
    int count = 0;

    pathSumInner(root, x, buffer, ret, &lens, &count);
    *returnSize1 = (int*)malloc(sizeof(int) * count);
    for (int i = 0; i < count; ++i) {
        (*returnSize1)[i] = lens[i];
    }

    *returnSize = count;
    free(buffer);
    free(lens);
    return ret;
}
```