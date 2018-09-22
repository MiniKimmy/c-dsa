## Delete Special Node

Given a non-empty single list, delete a Node *p which is not the last node.

## CHINESE
给定一个非空单链表交换p所指的结点与其下一个结点在链表中的位置,并且假设p指向的不是链表最后那个结点。

**Example 1:**
```
Input : [1,2,3,4,5]
delete p->val == 4

OutPut: [1,2,3,5]
```

## hints
```
      delete *p
      means ..->p->q->k->..-----> ..->p->k->..
      like delete *q and let p.val = q.val.
```

## Solution
``` c
/**
* Definition for singly-linked list.
* struct Node {
*     int val;
*     struct Node *next;
* }Node;
*/

void exchangeOneNode(Node* p) {
    Node* q = p->next;
    Node* k = q->next;
    p->val = q->val;
    p->next = k;
    free(q);
    q = NULL;
}
```