## 19. 二叉树的下一个节点
[这里](https://www.acwing.com/problem/content/31/)
给定一棵二叉树的其中一个节点，请找出中序遍历序列的下一个节点。

**Note：**
* 如果给定的节点是中序遍历序列的最后一个，则返回空节点;
* 二叉树一定不为空，且给定的节点一定不是空节点；

**Example 1:**
```
Input：[2, 1, 3, null, null, null, null],
2
Output:3

Input：[2, 1, 3, null, null, null, null],
3
Output:null

Input：[2, 1, 3, null, null, null, null],
1
Output:2

Explanation：该二叉树的结构如下，2的后继节点是3。3的后继是null。1的后继是2
  2
 / \
1   3
```

## hints
```
    1.分情况讨论是最简单的思路。
    2.注意给的这个二叉树的定义，是有father的指针的。
```

## Solution
``` c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 *     struct TreeNode *father;
 * };
 */

 /// 找右孩子的最左边
struct TreeNode* inorderSuccessorInner(struct TreeNode* p){
    if(p->left){
        return inorderSuccessorInner(p->left);
    }else{
        return p;
    }
}

/// 分情况
struct TreeNode* inorderSuccessor(struct TreeNode* p) {

    // 有右child
    if(p->right){
        return inorderSuccessorInner(p->right);
    }

    // 无右child，但在左边
    if(p->father && p->father->left == p){
        return p->father;
    }

    // 无右child，但在右边
    while(p->father && p->father->right == p){
        p = p->father;
    }

    return p->father;
}
```