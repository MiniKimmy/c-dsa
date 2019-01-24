## 18. 重建二叉树
[这里](https://www.acwing.com/problem/content/23/)
输入一棵二叉树前序遍历和中序遍历的结果，请重建该二叉树。

**Note:**
* 二叉树中每个节点的值都互不相同；
* 输入的前序遍历和中序遍历一定合法；

**Example:**
```
Input:
前序遍历是：[3, 9, 20, 15, 7]
中序遍历是：[9, 3, 15, 20, 7]

OutPut:[3, 9, 20, null, null, 15, 7, null, null, null, null]
返回的二叉树如下所示：
    3
   / \
  9  20
    /  \
   15   7
```

## hints
```
    1.抽屉原理 && 二分法(分治法)
    2.前序、中序的性质
        * 以前序作为根结点A
        * 在中序遍历找到A的位置，在A位置的左边是A的左子树--同时A左孩子的数量k在'前序遍历'恰好就是A紧接着的k个即是左孩子
        * A的右边同理
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

 /// 创建树节点
 struct TreeNode* createTreeNode(int val){
     struct TreeNode* ret = (struct TreeNode*)malloc(sizeof(struct TreeNode*));
     ret->left = NULL;
     ret->right = NULL;
     ret->val = val;
     return ret;
 }

/// 根据value获取对应的下标
int getReverseIndex(int* hash, int size, int value){
    for(int i = 0;i<size;++i){
        if(hash[i] == value){
            return i;
        }
    }
}

struct TreeNode* dfs(int* hash, int size, int* preorder, int* inorder, int preLeft, int preRight, int inLeft,int inRight)
{
    if(preLeft>preRight) return NULL;
    int count = getReverseIndex(hash,size,preorder[preLeft]) - inLeft;
    struct TreeNode* node = createTreeNode(preorder[preLeft]);

    node->left  = dfs(hash, size, preorder, inorder, preLeft+1, preLeft+count, inLeft, inLeft+count-1 );
    node->right = dfs(hash, size, preorder, inorder, preLeft+count+1, preRight, inLeft+count+1, inRight );
    return node;
}

struct TreeNode* buildTree(int* preorder, int preorder_size, int* inorder, int inorder_size) {
    int size = preorder_size;

    int* hash = (int*)malloc(sizeof(int) * size);
    for(int i = 0;i<size;++i) {
        hash[i] = inorder[i];
    }

    struct TreeNode* ret = dfs(hash, size, preorder, inorder, 0, size-1, 0, size-1);

    free(hash);
    return ret;
}
```