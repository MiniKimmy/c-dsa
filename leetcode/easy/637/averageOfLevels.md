## 637. Average of Levels in Binary Tree

Given a non-empty binary tree, return the average value of the nodes on each level in the form of an array.

**Example 1:**
```
Input:
    3
   / \
  9  20
    /  \
   15   7
Output: [3, 14.5, 11]
Explanation:
The average value of nodes on level 0 is 3,  on level 1 is 14.5, and on level 2 is 11. Hence return [3, 14.5, 11].
```

**Note:**<br/>
    The range of node's value is in the range of 32-bit signed integer.<br/>

## hints:
    * BFS Skill
```
    1. When first time got the whole 'Border Path' in one Node, we can let it flush all this Paths at this moment.
    2. It means we finds all ways in a crossroad such as called "A-Road", we can show around.
    Every path we also can see another crossroads, and mark down this crossroad in Queue with the order the path of "A-Road" you comes first.

    just like this Question Example:
    ex: "A-Road"(3)  : 9 20
        "B-Road"(9)  :
        "C-Road"(20) : 15 7
        "E-Road"(15) :
        "F-Road"(7)  :

    3. We got "9","20", then we show arount in "A-Road".
       <1>in "9",  no any other crossroad, so nothing to mark.
       <2>in "20", first "15" , mark it to Queue.
                    then "20" , mark it to Queue.
        Rules：which one first meet is the first one enter to Queue.
    Now,we finished "A-Road", and we can average all the Paths in "A-Road".
    And the last thing is that repeat this 'run and mark' motion until the Queue is empty.

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

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

int getSize(struct TreeNode* root)
{
    if(root == NULL) return 0;
    int i = getSize(root->left);
    int j = getSize(root->right);
    return i>j?i+1:j+1;
}


double* averageOfLevels(struct TreeNode* root, int* returnSize) {
    if(root == NULL) return NULL;

    int size = getSize(root);
    double* ret = (double*)malloc(sizeof(double) * size);

    long ARRAYSIZE = 10000000;
    struct TreeNode** SqQueue = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * ARRAYSIZE);
    long front = 0;
    long rear = 0;
    SqQueue[rear] = root;
    rear = (rear + 1) % ARRAYSIZE;

    double sum = 0;
    int level = 0;

    long n = 0;
    while(rear != front){
        long curNodeCount = (rear - front + ARRAYSIZE) % ARRAYSIZE;
        sum = 0.0f;

        for(long i=0;i<curNodeCount;++i){
            struct TreeNode* node = SqQueue[front];
            front = (front + 1) % ARRAYSIZE;
            sum += node->val;

            if(node->left) {
                SqQueue[rear] = node->left;
                rear = (rear + 1) % ARRAYSIZE;
            }
            if(node->right){
                SqQueue[rear] = node->right;
                rear = (rear + 1) % ARRAYSIZE;
            }
        }
        ret[level++] = sum/curNodeCount;
    }

    free(SqQueue);
    *returnSize = size;
    return ret;
}



/*Memory Limit
double* averageOfLevelsInner(struct TreeNode* root, int* returnSize){
    int size = getSize(root);

    double* ret = (double*)malloc(sizeof(double)*size);
    long ARRAYSIZE = 10000000;

    struct TreeNode** SqQueue = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * ARRAYSIZE);
    long front = 0;
    long rear = 0;


    SqQueue[rear] = root;
    rear = (rear + 1) % ARRAYSIZE;

    long count = 0;
    long sum = 0;
    int level = 1;

    long n = 0;
    while(rear != front && level <= size){
        struct TreeNode* node = SqQueue[front];
        ++n;

        front = (front + 1) % ARRAYSIZE;
        if(node != NULL){
            sum += node->val;
            count++;
        }

        if((int)(pow(2,level)) == (n+1)){
            double a = (sum+0.0) / (count);
            ret[level-1] = a;
            sum = 0;
            count = 0;
            level++;
        }

        if(node == NULL){
            SqQueue[rear] = NULL;
            rear = (rear + 1) % ARRAYSIZE;
            SqQueue[rear] = NULL;
            rear = (rear + 1) % ARRAYSIZE;
        }else{
            if(node->left) {
                SqQueue[rear] = node->left;
                rear = (rear + 1) % ARRAYSIZE;
            }else{
                SqQueue[rear] = NULL;
                rear = (rear + 1) % ARRAYSIZE;
            }

            if(node->right){
                SqQueue[rear] = node->right;
                rear = (rear + 1) % ARRAYSIZE;
            }else{
                SqQueue[rear] = NULL;
                rear = (rear + 1) % ARRAYSIZE;
            }

        }
    }


    free(SqQueue);
    *returnSize = size;
    return ret;
}
*/

```
