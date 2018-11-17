## Link the tree Node of the bottom level

## CHINESE
把树的叶节点链接成一个以最后一层的第一个元素为头结点的单链表.

**Example 1:**
```
Input :
        4
      /   \
     2     3
    / \   / \
   1  13 6   9
  / \   /
 0   2 1

Output : [0,2,1]
```

## hints
```
    1.bfs && levelOrder
    2.getDepth,then mark the level Count.
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
* Definition for Node.
* struct Node {
*     int val;
*     struct Node *next;
* }Node;
*/

Node* linkTreeNodeInner(TreeNode* root, int height) {
    int maxSize = 1000;
    TreeNode** sqQueue = (TreeNode**)malloc(sizeof(TreeNode*) * maxSize);
    int front = 0;
    int rear = 0;
    sqQueue[rear] = root;
    rear = (rear + 1) % maxSize;

    int level = 0;
    Node* dummy = NULL;
    Node* tail = NULL;

    while (front != rear) {
        int QSize = (rear - front + maxSize) % maxSize;

        // init
        if (level + 1 == height) {
            dummy = (Node*)malloc(sizeof(Node));
            dummy->val = 2019;
            dummy->next = NULL;
            tail = dummy;
        }

        for (int i = 0; i < QSize; ++i) {
            TreeNode* t = sqQueue[front];
            front = (front + 1) % maxSize;

            //Add item
            if (dummy != NULL) {
                Node* item = (Node*)malloc(sizeof(Node));
                item->next = NULL;
                item->val = t->val;

                tail->next = item;
                tail = item;
            }

            if (t->left) {
                sqQueue[rear] = t->left;
                rear = (rear + 1) % maxSize;
            }

            if (t->right) {
                sqQueue[rear] = t->right;
                rear = (rear + 1) % maxSize;
            }
        }

        level++; //mark level.
    }

    free(sqQueue);
    Node* ret = dummy->next;
    free(dummy);
    return ret;
}

int getDepth(TreeNode* root)
{
    if (root == NULL) return 0;
    int i = getDepth(root->left);
    int j = getDepth(root->right);
    return i > j ? i + 1 : j + 1;
}

Node* linkTreeNode(TreeNode* root){
    int height = getDepth(root);
    if (height == 0) return NULL;
    Node* ret = linkTreeNodeInner(root, height);
    return ret;
}

```