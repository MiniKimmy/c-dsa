## 111. Minimum Depth of Binary Tree
[这里](https://leetcode.com/problems/minimum-depth-of-binary-tree/)

**Note:**
* A leaf is a node with no children.

**Example 1:**
```
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7

return its minimum depth = 2.
```
**Example 2:**
```
Given binary tree [3,null,20,15,7],
    3
     \
     20
    /  \
   15   7

return its minimum depth = 3.
```
## hints
```
    dfs.
    1.往左、右都dfs获取minDepth
    2.根节点到最近的叶节点的最短路径上的节点数。所以左或右无孩子的话是return 有孩子的那边的minDepth
    3.合并情况
        * 左或右不存在的情况 等价于 return i+j+1
        * 加0等于无加
```
## Solution
``` c
int minDepth(struct TreeNode* root)
{
    if(!root) return 0;

    int i = minDepth(root->left);
    int j = minDepth(root->right);

    if(!i || !j) return i+j+1;

    /*
    if(!root->left && root->right) return j+1;
    if(!root->right && root->left) return i+1;
    */

    return i>j?j+1:i+1;
}
```

## Solution
``` csharp
/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     public int val;
 *     public TreeNode left;
 *     public TreeNode right;
 *     public TreeNode(int x) { val = x; }
 * }
 */
public class Solution {
    public int MinDepth(TreeNode root) {
        if(root == null) return 0;
        int i = MinDepth(root.left);
        int j = MinDepth(root.right);
        if(root.left == null || root.right == null) return i + j + 1;
        return i>j?j+1:i+1;
    }
}
```