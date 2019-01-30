## 49. 二叉搜索树与双向链表
[这里](https://www.acwing.com/problem/content/87/)
输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。

**Note**
* 要求不能创建任何新的结点，只能调整树中结点指针的指向。

**Example :**
```
Input:
        10
      /    \
     6      14
    / \    / \
   4   8 12   16
Output:[4<->6<->8<->10<->12<->14<->16]
```

## hints
```
一开始，获取一层
      10
[4 6 8] [12 14 16]
----------------------
(1)获取10的左子树[4,8] 以及10的右子树的[12,16]
(2)然后10绑定8和12
(3)返回[4 16]
(4)然后4就是双向链表的头结点.结束
        10
       / \
[4 6] 8   12 [14 16] ----------------------
(5)中间的 6,14 不用管，是因为只关心一头一尾.
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

typedef struct {
    struct TreeNode* first;
    struct TreeNode* second;
}Pair;

/// 创建pair<t1,t2>
Pair* createPair(struct TreeNode* first, struct TreeNode* second)
{
    Pair* ret = (Pair*)malloc(sizeof(Pair));
    ret->first = first;
    ret->second = second;
    return ret;
}

Pair* dfs(struct TreeNode* root)
{
    //if(!root) return NULL; 可不写这个if

    // 叶节点
    if(!root->left && !root->right){
        return createPair(root, root);
    }

    // 左右孩子都有
    if(root->left && root->right)
    {
        Pair* pairL = dfs(root->left);
        Pair* pairR = dfs(root->right);

        struct TreeNode* l = pairL->second;
        struct TreeNode* r = pairR->first;

        l->right = root;
        r->left = root;

        root->left = l;
        l->right = root;
        root->right = r;
        r->left = root;

        Pair* pair = createPair(pairL->first, pairR->second);
        return pair;
    }

    // 单独只有右孩子
    if(!root->left)
    {
        // 只去找右边
        Pair* pairR = dfs(root->right);
        Pair* pair = createPair(root, pairR->second);

        root->right = pairR->first;
        pairR->first->left = root;
        return pair;
    }

    // 单独只有左孩子
    if(!root->right)
    {
        // 只去找左边
        Pair* pairL = dfs(root->left);
        Pair* pair = createPair(pairL->first, root);

        root->left = pairL->second;
        pairL->second->right = root;

        return pair;
    }

}

struct TreeNode* convert(struct TreeNode* root) {
    if(root == NULL) return NULL;
    return dfs(root)->first;
}
```