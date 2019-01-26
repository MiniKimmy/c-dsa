## 39. 对称的二叉树
[这里](https://www.acwing.com/problem/content/38/)
请实现一个函数，用来判断一棵二叉树是不是对称的。
如果一棵二叉树和它的镜像一样，那么它是对称的。
**Note**空树的时候返回true

**Example 1:**
```
Input:[1,2,2,3,4,4,3,null,null,null,null,null,null,null,null]
    1
   / \
  2   2
 / \ / \
3  4 4  3
Output:true
```
**Example 2:**
```
Input:[1,2,2,null,4,4,3,null,null,null,null,null,null]
    1
   / \
  2   2
   \ / \
   4 4  3
Output:false
```
## hints
```
    1.传入同一个root
    2.分别按2个方向dfs
    3.一边先左后右，一边先右后左
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

void dfs(struct TreeNode* t1, struct TreeNode* t2, int* ret){
    if(!t1 && !t2) return;

    if((!t1 && t2) || (t1 && !t2)){
        *ret = 0;
        return;
    }

    if(t1->val != t2->val){
        *ret = 0;
        return;
    }

    dfs(t1->left,t2->right,ret);
    dfs(t1->right,t2->left,ret);
}

bool isSymmetric(struct TreeNode* root) {
    if(root == NULL) return true;

    int refRet = 1;
    dfs(root,root,&refRet);

    if(refRet == 1) return true;
    else return false;
}
```