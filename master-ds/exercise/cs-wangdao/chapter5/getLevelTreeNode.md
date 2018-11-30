## Get a tree node 's level

## CHINESE
找出某个树节点p，返回其所在的层数

**Example 1:**
```
Input :
        4
      /   \
     2     3
    / \   / \
   1  13 6   9
  / \   /
 0   2 1

*p = 6
Output : 3
```

## hints
```
    1.dfs && postOrder
    * (void)method(ref* a, ...)

    2.bfs && LevelOrder

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

void dfs(TreeNode* root, TreeNode* p, int* retLevel,int level){
    if (root == NULL) return;

    if (root == p) {
        *retLevel = level;
        return;
    }

    dfs(root->left, p, retLevel, level + 1);
    dfs(root->right, p, retLevel, level+1);
}

int getLevelTreeNode(TreeNode* root, TreeNode* p){
    int level = 0;
    dfs(root, p, &level, 1);
    return level;
}
```