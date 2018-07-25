/*
Q437.Path Sum III
You are given a binary tree in which each node contains an integer value.

Find the number of paths that sum to a given value.

The path does not need to start or end at the root or a leaf, but it must go downwards (traveling only from parent nodes to child nodes).

The tree has no more than 1,000 nodes and the values are in the range -1,000,000 to 1,000,000.

Example:

root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8

      10
     /  \
    5   -3
   / \    \
  3   2   11
 / \   \
3  -2   1

Return 3. The paths that sum to 8 are:

1.  5 -> 3
2.  5 -> 2 -> 1
3. -3 -> 11
*/

//C
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int getRes(struct TreeNode* root, int sum){
    int ret = 0;
    match(root,sum,0,&ret);
    return ret;
}

void match(struct TreeNode* root, int sum, int s, int* ret){
    if(root == NULL) return ;

    s = s + root->val;
    if(s == sum) *ret = *ret+1;

    match(root->left, sum, s,ret);
    match(root->right,sum, s,ret);
}


int pathSum(struct TreeNode* root, int sum) {
    if(root == NULL) return 0;

    int rear = 0;
    int front = 0;
    struct TreeNode** Q[1000];

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
