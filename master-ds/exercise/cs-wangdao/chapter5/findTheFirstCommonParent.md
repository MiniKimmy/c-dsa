## Get the first common parent node

## CHINESE
给出一个按数组顺序存储的二叉树,试编写算法找到结点编号i和结点编号j的第一个共同父节点的编号

**Example 1:**
```
Input : i = 3,j = 6
     4
   /   \
  2     7
 / \   / \
1   3 6   9

Output : 4
```

## hints
```
    bad script..

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

void findTheFirstCommonParentInner(TreeNode* root, int i, int j,int* ref_i,int* ref_j,int* ret,int* flag){

    if (root == NULL) return -1;

    if(*ref_i == -1 || *ref_j == -1) findTheFirstCommonParentInner(root->left, i, j, ref_i, ref_j, ret, flag);
    if (*ref_i == -1 || *ref_j == -1) findTheFirstCommonParentInner(root->right, i, j, ref_i, ref_j, ret, flag);

    if (*ref_i != -1 && *ref_i != -1) {
        *ret = *ret == *ref_j && flag == j || *ret == *ref_i && flag == i? *ret : root->val;
    }

    if (*ref_i == -1 && *ref_j != 1) {
        *flag = i;
        *ref_i = *ref_i == *ret ? *ref_i : root->val;
    }

    if (*ref_j == -1 && *ref_i != 1) {
        flag = j;
        *ref_j = *ref_j == *ret ? *ref_j : root->val;
    }

    if (root->val == i) *ref_i = -1;
    if (root->val == j) *ref_j = -1;
    printf("val = %d i=%d, j=%d ret=%d\n", root->val, *ref_i, *ref_j, *ret);
}

int findTheFirstCommonParent(TreeNode* root, int i, int j){
    if (root == NULL) return -1;

    int ref_i = -1;
    int ref_j = -1;
    int ret = -2;
    int flag = 0;
    findTheFirstCommonParentInner(root, i, j, &ref_i, &ref_j,&ret,&flag);
    return ret!=-1?ret:0;
}
```