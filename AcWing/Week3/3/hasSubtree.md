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

Output: true
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

## hints2
```
    1.前中后序遍历树任意一个都可以
    2.如果root2的根能匹配成功则进入一起dfs同步
        (1).同步dfs就是check它们是否匹配
        (2).匹配成功的话,在外层的遍历就立即返回;
    3.使用2个全局变量refRet
        (1).记录每一次check是否成功
            * 初始默认不匹配
        (2) 记录1次check是否成功
            * 初始默认配对成功
                -->check一次直到底都不出现问题就认为check成功
            * 在check的逻辑里遇到不匹配就立即返回;
    4.全局refRet默认值的设置
        (1).假如0表示false,1表示true
        (2).一遇到情况为false就返回
            * 则设置默认值为1
            * 非错(不知道接下来的情况) 则继续做
            * 直到整个过程检查完毕后，去查看这个默认值是否有改变
            * 有改变则表示已经出现false,则就立刻返回.
        (3).嵌套refRet也是同样。
            * 业务的逻辑是针对false的问题还是true的问题
            * 如果标明在xx情况下就表示false的话,则默认一开始true先，去找bug，一有bug就跳出来.
            * 同理，非错则继续往下进行
```

## Solution2
```
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

void dfs(struct TreeNode* t1, struct TreeNode* t2, int* ans)
{
    if(t1==NULL  && t2 ){
        *ans = 0;
        return;
    }

    if(t1 && t2 == NULL){
        return;
    }

    if(t1 == NULL && t2 == NULL ){
        return;
    }

    if(t1 && t2 && t1->val == t2->val){
        dfs(t1->left, t2->left, ans);
        dfs(t1->right, t2->right, ans);
    }else{
        *ans = 0;
        return;
    }

    return;
}

void hasSubtreeInner(struct TreeNode* pRoot1, struct TreeNode* pRoot2, int* ret)
{
    if(pRoot1 && *ret == 0){
        if(pRoot1->val == pRoot2->val){
            int ans = 1; //默认能匹配
            dfs(pRoot1,pRoot2,&ans);
            if(ans == 1) {
                *ret = 1;
                return;
            }
        }

        hasSubtreeInner(pRoot1->left, pRoot2, ret);
        hasSubtreeInner(pRoot1->right, pRoot2, ret);
    }
    return;
}

bool hasSubtree(struct TreeNode* pRoot1, struct TreeNode* pRoot2) {
    if(pRoot1 == NULL || pRoot2 == NULL) return false;

    int refRet = 0;   //默认不匹配
    hasSubtreeInner(pRoot1,pRoot2,&refRet);

    return refRet == 1?true:false;
}
```