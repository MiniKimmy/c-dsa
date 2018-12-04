## 437 Path Sum III

You are given a binary tree in which each node contains an integer value.

Find the number of paths that sum to a given value.

The path does not need to start or end at the root or a leaf, but it must go downwards (traveling only from parent nodes to child nodes).

The tree has no more than 1,000 nodes and the values are in the range -1,000,000 to 1,000,000.

Example:
```
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
```

## hints
```
    1.Travesre Tree as any one Order is ok.
    2.void dfs(...) check path sum.
```

## Solution1
``` c
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
```

## Solution2
``` c
/*level order && bfs 20ms beat 20%*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

void dfs(struct TreeNode* root, int x, int sum,int* ret){

    if (root == NULL) return;
    int val = root->val;
    if (sum + val == x) {
        *ret = *ret + 1;
    }

    dfs(root->left, x, sum + val, ret);
    dfs(root->right, x, sum + val, ret);
}

int pathSum(struct TreeNode* root, int sum) {
    if(root == NULL) return 0;

    int maxSize = 500;
    struct TreeNode** sqQueue = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * maxSize);
    int front = 0;
    int rear = 0;
    sqQueue[rear] = root;
    rear = (rear + 1) % maxSize;

    int ret = 0;
    while (front != rear) {
        int len = (rear - front + maxSize) % maxSize;

        for (int i = 0; i < len; ++i) {
            struct TreeNode* t = sqQueue[front];
            front = (front + 1) % maxSize;
            dfs(t, sum, 0, &ret);

            if (t->left) {
                sqQueue[rear] = t->left;
                rear = (rear + 1) % maxSize;
            }

            if (t->right) {
                sqQueue[rear] = t->right;
                rear = (rear + 1) % maxSize;
            }
        }
    }

    free(sqQueue);
    return ret;
}
```

## Solution3
```
/*pre、in、post Order Travesre 16ms beat 70% */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

void dfs(struct TreeNode* root, int x, int sum,int* ret){

    if (root == NULL) return;
    int val = root->val;
    if (sum + val == x) {
        *ret = *ret + 1;
    }

    dfs(root->left, x, sum + val, ret);
    dfs(root->right, x, sum + val, ret);
}

void pathSumInner(struct TreeNode* root, int sum, int* ret)
{
    if(root){
        dfs(root, sum, 0, ret);
        pathSumInner(root->left,sum,ret);
        pathSumInner(root->right,sum,ret);
    }
}

int pathSum(struct TreeNode* root, int sum) {
    if(root == NULL) return 0;

    int ret = 0;
    pathSumInner(root,sum,&ret);
    return ret;
}
```