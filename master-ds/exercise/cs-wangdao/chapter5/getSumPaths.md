## Get Sum Path

## CHINESE
从根节点到叶节点能路径值上之和等于所给的x的所有路径.

**Example 1:**
```
Input : x=16
        4
      /   \
     2     5
    / \   / \
   1  10 6   7
  / \   /
 0   2 1

Output: [ [4,2,10],[4,5,6,1],[4,5,7] ]
Explanation: 4+2+10=16, 4+5+6+1=16, 4+5+7=16
```

## hints
```
    1.temp-index && temp-maked.
    2.(void) _preOrderTraverse
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

void traverseArray(int* arr, int n)
{
    for (int i = 0; i < n; ++i){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void dfs(TreeNode* root, int* buffer, int level, int sum, int x){
    if (root == NULL) return;

    int val = root->val;
    if (sum + val == x) {
        buffer[level] = val;
        traverseArray(buffer,level + 1);
    }else {
        buffer[level] = val;
    }

    dfs(root->left, buffer, level + 1, sum + val, x);
    dfs(root->right, buffer, level + 1, sum + val, x);
}

void getSumPaths(TreeNode* root, int x){
    int* buffer = (int*)malloc(sizeof(int) * 100);
    dfs(root, buffer, 0, 0, x);
}
```

## Solution2
``` c
/*Store int[][] as return*/

/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     struct TreeNode *left;
*     struct TreeNode *right;
* };
*/

void dfs(TreeNode* root, int* buffer, int level, int sum, int x, int** ret, int* count, int* lens){
    if (root == NULL) return;
    int val = root->val;
    if (sum + val == x) {
        buffer[level] = val;
        int len = level + 1;
        lens[(*count)] = len;

        int* item = (int*)malloc(sizeof(int) * len);
        for (int i = 0; i < len; ++i) {
            item[i] = buffer[i];
        }
        ret[(*count)] = item;
        *count = *count + 1;

    }else {
        buffer[level] = val;
    }

    dfs(root->left, buffer, level + 1, sum + val, x,ret,count,lens);
    dfs(root->right, buffer, level + 1, sum + val, x,ret,count,lens);
}

int** getSpecialPaths(TreeNode* root, int x, int* returnSize,int** returnSize1){
    if(root==NULL) {
        *returnSize1 = (int*)malloc(sizeof(int) * 1);
        returnSize1[0] = 0;
        return NULL;
    }

    int* buffer = (int*)malloc(sizeof(int) * 100);
    int** ret = (int**)malloc(sizeof(int*) * 100);
    int* lens = (int*)malloc(sizeof(int) * 100);

    int count = 0;
    dfs(root, buffer, 0, 0, x, ret, &count, lens);
    *returnSize = count;

    *returnSize1 = (int*)malloc(sizeof(int) * count);
    for (int i = 0; i < count; ++i) {
        (*returnSize1)[i] = lens[i];
    }

    free(lens);
    free(buffer);
    return ret;
}
```