## Check two trees is similar?

## CHINESE
把树的叶节点链接成一个以最后一层的第一个元素为头结点的单链表.

**Example 1:**
```
Input :
   1         -11
 /   \      /   \
2     3    1     3
  (A)        (B)

Output: true
```
**Example 2:**
```
Input :
   1         -11
 /   \      /   \
2     3   null   3
  (A)        (B)

Output: false
```
**Example 3:**
```
Input :
   1         -11
 /   \      /   \
2     3    2    null
            \
             null
  (A)         (B)

Output: false
```

## hints
```
    1.traverse the tree in any order is ok.
    2.check the NULL Node.
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

void isSimilarTreeInner(TreeNode* root1, TreeNode* root2, int* ret) {
    if (root1 == NULL && root2 != NULL) {
        *ret = 1;
        return;
    }

    if (root2 == NULL && root1 != NULL) {
        *ret = 1;
        return;
    }

    if (root1 && root2) {
        isSimilarTreeInner(root1->left, root2->left,ret);
        isSimilarTreeInner(root1->right, root2->right,ret);
    }

}

int isSimilarTree(TreeNode* root1, TreeNode* root2) {
    int ret = 0;
    isSimilarTreeInner(root1, root2,&ret);
    return ret == 1 ? 0 : 1;
}
```