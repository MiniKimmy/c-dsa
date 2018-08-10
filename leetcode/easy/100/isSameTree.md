## 100. Same Tree
Given two binary trees, write a function to check if they are the same or not.

Two binary trees are considered the same if they are structurally identical and the nodes have the same value.

**Example 1:**
```
Input:     1         1
          / \       / \
         2   3     2   3

        [1,2,3],   [1,2,3]

Output: true
```
**Example 2:**
```
Input:     1         1
          /           \
         2             2

        [1,2],     [1,null,2]

Output: false
```
**Example 3:**
```
Input:     1         1
          / \       / \
         2   1     1   2

        [1,2,1],   [1,1,2]

Output: false
```

## hints
```
    [Th]: 1.preorder && inorder confirm a unique tree.
          2.postorder && inorder confirm a unique tree.
          3.preorder %% postorder failed.

    caution:DONT UES GLOBAL VARIABLE.
    because leetcode 'Submit Solution' is one-off test all data.
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

//bool flag = true;   //don't use global variable!

bool equals(struct TreeNode* p, struct TreeNode* q){
    if(p->val == q->val) return true;
    else return false;
}

int reference(struct TreeNode* p, struct TreeNode* q){
    return q==NULL && p!=NULL? 1
        :p==NULL && q!=NULL?-1
        :0;
}

void inorder(struct TreeNode* p, struct TreeNode* q, int* flag){
    if(p != NULL && q != NULL){
        inorder(p->left,q->left,flag);

        if(!equals(p,q)){
            *flag = 0;
            return;
        }

        inorder(p->right,q->right,flag);
    }else{
        int a = reference(p,q);
        if(a == 1 || a == -1)
            *flag = 0;
        return;
    }
}

void preorder(struct TreeNode* p, struct TreeNode* q,int* flag){
    if(p != NULL && q != NULL){
        if(!equals(p,q)){
            *flag = 0;
            return;
        }

        preorder(p->left,q->left,flag);
        preorder(p->right,q->right,flag);
    }else{
        int a = reference(p,q);
        if(a == 1 || a ==-1)
            *flag = 0;
        return;
    }
}


bool isSameTree(struct TreeNode* p, struct TreeNode* q) {
    if(p == NULL && q==NULL) return true;

    int* flag = (int*)malloc(sizeof(int));
    *flag = 1;

    inorder(p,q,flag);
    if(*flag == 0)
        return false;

    preorder(p,q,flag);
    if(*flag == 0)
        return false;

    return true;
}
```
