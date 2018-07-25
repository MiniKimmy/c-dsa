/*
Q437.Path Sum III
You are given a binary tree in which each node contains an integer value.

Find the number of paths that sum to a given value.

The path does not need to start or end at the root or a leaf, but it must go downwards (traveling only from parent nodes to child nodes).

The tree has no more than 1,000 nodes and the values are in the range -1,000,000 to 1,000,000.

 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

//下面这样做法�?找到符合'sum'就立刻返回不继续往下找.
//ps:[不是原来题目的要求那样就算符合了‘sum’也继续往下找到树底~]

int getRes(struct TreeNode* root, int sum){
    if(root->val == sum) return 1;
    int ret = 0;
    match(root,sum,0,&ret);
    return ret;
}

int match(struct TreeNode* root, int sum, int s, int* ret){
    if(root == NULL) {
        return 0;
    }

    s = s + root->val;
    if(s > sum) return 0;
    else if(s < sum){
        int i = match(root->left, sum,s ,ret);
        int j = match(root->right,sum,s ,ret);
        *ret = i + j > *ret? i+j : *ret;
        return 0;
    }else{
        *ret = *ret+1;
        return 1;
    }
}


int pathSum(struct TreeNode* root, int sum) {
    if(root == NULL) return 0;

    int rear = 0;
    int front = 0;
    struct TreeNode** Q = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * 1000);
    Q[rear++] = root;

    int ret = 0;
    while(front != rear){
        struct TreeNode* t = Q[front++];
        ret += getRes(t,sum);
        if(t->left) Q[rear++] = t->left;
        if(t->right) Q[rear++] = t->right;
    }
    return ret;
}
