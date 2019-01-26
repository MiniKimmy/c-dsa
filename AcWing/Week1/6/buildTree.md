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
    1.闭包dfs && 二分法(分治法)
    2.前序、中序的性质
        * 以前序作为根结点A
        * 在中序遍历找到A的位置，在A位置的左边是A的左子树--同时A左孩子的数量k在'前序遍历'恰好就是A紧接着的k个即是左孩子
        * A的右边同理
    3.（比较限制的方式）无字典的话，直接写一个方法接收value去查index。但是这个前提是这个value是唯一。恰好这个题目注明是各个value不同。
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

/// 根据value获取index位置
int getIndex(int* arr,int arrSize ,int value){
    for(int i = 0;i<arrSize;++i){
        if(arr[i] == value){
            return i;
        }
    }
}

/// 创建树节点
struct TreeNode* createTreeNode(int val)
{
    struct TreeNode* ret =  (struct TreeNode*)malloc(sizeof(struct TreeNode));
    ret->val = val;
    ret->left=NULL;
    ret->right =NULL;
    return ret;
}

/// 二分法+dfs
struct TreeNode* dfs(int* preorder, int size, int* inorder, int preL, int preR, int inL, int inR){
    if(preL>preR) return NULL;

    int root = preorder[preL];
    int mid = getIndex(inorder, size, root); // 获取分界处

    struct TreeNode* node =  createTreeNode(root);
    node->left  = dfs(preorder, size, inorder, preL+1, preL+mid-inL, inL,  mid-1  );    //[l,mid]
    node->right = dfs(preorder, size, inorder, preL+mid-inL+1 ,preR, mid+1,inR  );  //[mid+1,r]
    return node;
}

struct TreeNode* buildTree(int* preorder, int preorder_size, int* inorder, int inorder_size) {
    if(preorder == NULL || preorder_size <= 0) return NULL;

    int n = preorder_size;
    return dfs(preorder,n,inorder,0,n-1,0,n-1);
}
```