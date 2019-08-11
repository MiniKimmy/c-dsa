## 543. Diameter of Binary Tree
[这里](https://leetcode.com/problems/diameter-of-binary-tree/)

**Example 1:**
```
Given a binary tree
          1
         / \
        2   3
       / \
      4   5

Return 3, which is the length of the path [4,2,1,3] or [5,2,1,3].
Explanation:最长直径即横着看有多少条路径.
```
**Example 2:**
```
Given a binary tree
          1
         /
        2
       / \
      4   5
           \
            1
Return 3, which is the length of the path [4,2,5,1] or [1,2,5,1].
```
## hints
```
1.一开始想的方法是:暴搜每个结点，获取每个结点的左右孩子深度之和找max
2.后来发现，这种嵌套dfs的形式，可以在获取深度的方法里简化
    (1).在获取深度的同时也可相加左右孩子深度之和找max
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

int diameterOfBinaryTreeInner(struct TreeNode* root, int* ret)
{
    if(!root) return 0;

    int i = diameterOfBinaryTreeInner(root->left,ret);
    int j = diameterOfBinaryTreeInner(root->right,ret);

    if(i + j > *ret){
        *ret = i + j;
    }

    return (i>j?i:j) + 1;
}

int diameterOfBinaryTree(struct TreeNode* root) {
    int refRet = 0;
    diameterOfBinaryTreeInner(root,&refRet);
    return refRet;
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

    private int DiameterOfBinaryTreeInner(TreeNode root, ref int ret)
    {
        if(root == null) return 0;

        int i = DiameterOfBinaryTreeInner(root.left ,ref ret);
        int j = DiameterOfBinaryTreeInner(root.right,ref ret);

        if(i+j > ret){
            ret = i + j;
        }

        return (i>j?i:j) + 1;
    }

    public int DiameterOfBinaryTree(TreeNode root) {
        int ret = 0;
        DiameterOfBinaryTreeInner(root,ref ret);
        return ret;
    }
}
```