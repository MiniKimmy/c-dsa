## 72. 平衡二叉树
[这里](https://www.acwing.com/problem/content/68/)
输入一棵二叉树的根结点，判断该树是不是平衡二叉树。
如果某二叉树中任意结点的左右子树的深度相差不超过1，那么它就是一棵平衡二叉树。

**Example :**
```
Input:[5,7,11,null,null,12,9,null,null,null,null]如下所示，
    5
   / \
  7  11
    /  \
   12   9
Output:true
```

## hints
```
    1.任意一种遍历树的方式
    2.枚举每个root获取左右孩子的深度进行比较即可
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

int getDepth(struct TreeNode* root){
    if(root == NULL) return 0;
    int i = getDepth(root->left);
    int j = getDepth(root->right);
    return i > j? i +1:j+1;
}

int distance(int a, int b){
    if(a>b) return a-b;
    else return b-a;
}

void dfs(struct TreeNode* root, int* ret)
{
    if(!root || *ret == 0 ) return;

    int i = getDepth(root->left);
    int j = getDepth(root->right);

    if(distance(i,j) > 1) {
        *ret = 0;
        return;
    }

    dfs(root->left,ret);
    dfs(root->right,ret);
}

bool isBalanced(struct TreeNode* root) {
    int refRet = 1;
    dfs(root, &refRet);
    return refRet==1?true:false;
}
```