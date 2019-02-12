## 88. 树中两个结点的最低公共祖先
[这里](https://www.acwing.com/problem/content/84/)
给出一个二叉树，输入两个树节点，求它们的最低公共祖先。
一个树节点的祖先节点包括它本身。

**Note**
* 输入的二叉树不为空；
* 输入的两个节点一定不为空，且是二叉树中的节点；
**Example :**
```
[8, 12, 2, null, null, 6, 4, null, null, null, null]
    8
   / \
  12  2
     / \
    6   4
Explanation:
1. 如果输入的树节点为2和12，则输出的最低公共祖先为树节点8。
2. 如果输入的树节点为2和6，则输出的最低公共祖先为树节点2。
````

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

void dfs(struct TreeNode* root, struct TreeNode* target, struct TreeNode** arr, int index,struct TreeNode*** ret,int* reflen)
{
    if(!root || *ret ) return;
    if(root == target){
        arr[index++] = root;
        *ret = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * index);
        *reflen = index;
        for(int i = 0;i<index;++i){
            (*ret)[i] = arr[i];
        }
        return;
    }

    arr[index] = root;
    dfs(root->left,target,arr,index + 1,ret,reflen);
    dfs(root->right,target,arr,index + 1,ret,reflen);
}


struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    // bfs 会出现 "No enough input."

    int SIZE = 1000;
    int len1 = 0;  int len2 = 0;
    struct TreeNode** arr1 = NULL;
    struct TreeNode** arr2 = NULL;
    struct TreeNode** buffer = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * SIZE);
    dfs(root,p,buffer,0,&arr1,&len1);
    dfs(root,q,buffer,0,&arr2,&len2);

    //printf("l1=%d,l2=%d\n",len1,len2);
    while(len1 > 0 && len2 > 0){
        if(arr1[len1-1] == arr2[len2-1]) return arr1[len1-1];
        if(len1>len2){
            len1--;
        }else if(len1<len2){
            len2--;
        }else{
            len1--;
            len2--;
        }

    }

    free(arr1);
    free(arr2);
    return root;
}
```