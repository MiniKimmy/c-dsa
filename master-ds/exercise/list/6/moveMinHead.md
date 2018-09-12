## Move the minimum to list head

Given a sigle-list, and move the min Node to list's head.

## CHINESE
已知非空线性链表由list指出,将链表中数据域值最小的那个链结点移到链表的最前面。<br />
要求:不得额外申请新的链结点。<br />

**Example :**
```
Input: [1,3,4,-5,-6,-7,4]
Output: [-7,1,3,4,-5,-6,4]
```

**Note** <br />
Space Complexity is O(1).<br />

## hints
```
    front-back pointers.
```

## Analogous
|                         Nav            |                   Des                 |
| :-------------------------------------:|:-------------------------------------:|
| ![deleteMinNode](deleteMinNode.md)     |删除单链表最小的结点                   |


## Solution
``` c
/**
* Definition for singly-linked list.
* struct Node {
*     int val;
*     struct Node *next;
* }Node;
*/

Node* moveMinHead(Node* head) {
    if (head == NULL) return NULL;

    Node* p = head->next;
    int temp = head->val;
    Node* pre = head;

    Node* min = NULL;
    while (p) {
        if (p->val < temp) {
            temp = p->val;
            min = pre;
        }

        pre = p;
        p = p->next;
    }

    Node* ret = head;
    if (min) {
        ret = min->next;
        min->next = ret->next;
        ret->next = head;
    }

    return ret;
}

```
