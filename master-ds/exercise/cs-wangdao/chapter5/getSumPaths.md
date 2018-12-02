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