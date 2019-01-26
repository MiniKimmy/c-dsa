## 28. 在O(1)时间删除链表结点
[这里](https://www.acwing.com/problem/content/85/)

给定单向链表的一个节点指针，定义一个函数在O(1)时间删除该结点。
假设链表一定存在，并且该节点一定不是尾节点。

**Example 1**
```
Input:1->4->6->8
删掉节点：第2个节点即6（头节点为第0个节点）
Output:1->4->8
```

## hints
```
    1.先交换val再删除free下一个.
```

## Solution
``` c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
void deleteNode(struct ListNode* node) {
    int temp = node->next->val;
    struct ListNode* p = node->next;
    struct ListNode* q = p!=NULL?p->next:NULL;
    free(p);
    node->val = temp;
    node->next = q;
}
```