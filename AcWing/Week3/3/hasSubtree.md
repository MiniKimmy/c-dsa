## 37. 树的子结构
[这里](https://www.acwing.com/problem/content/35/)
输入两棵二叉树A，B，判断B是不是A的子结构。
我们规定空树不是任何树的子结构。

**Example :**
```
Input:
TreeA:
     8
    / \
   8   7
  / \
 9   2
    / \
   4   7

TreeB:
   8
  / \
 9   2

Output: true;
```
## hints
```
    1.双重dfs
    2.外层dfs是遍历树A
    3.在树A的每一个点都枚举一下看看，然后有机会的就进行第二层dfs
    4.第二层dfs即树A和树B同步dfs，看看是否能配对成功.
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

void dfsInner(struct TreeNode* t1, struct TreeNode* t2, int* ret){
    if(t1 == NULL && t2 != NULL){
        *ret = -1;
        return;
    }

    if(t2 == NULL && t1 == NULL){
        return;
    }

    if(t2 == NULL && t1 != NULL){
        return;
    }else{
        if(t2->val == t1->val){
            dfsInner(t1->left,t2->left,ret);
            dfsInner(t1->right,t2->right,ret);

        }else{
            *ret = -1;
            return;
        }
    }

    return;
}

void dfs(struct TreeNode* pRoot1, struct TreeNode* pRoot2, int* ret){
    if(pRoot1 == NULL) return;

    if(pRoot1->val == pRoot2->val){
        int ans = 1;
        dfsInner(pRoot1,pRoot2,&ans);
        if(ans == 1) {
            *ret = 1;
            return;
        }
    }

    dfs(pRoot1->left,pRoot2,ret);
    dfs(pRoot1->right,pRoot2,ret);
    return;
}

bool hasSubtree(struct TreeNode* pRoot1, struct TreeNode* pRoot2) {
    if(pRoot1 == NULL || pRoot2 == NULL) return false;
    int refRet = 0;
    dfs(pRoot1,pRoot2, &refRet);

    if(refRet == 1) return true;
    else return false;
}
```