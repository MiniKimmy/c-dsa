## CHINESE
试编写算法找到2个单链表第一个共同结点的元素.

**Example 1:**
```
Input :
11-->13-->15-->17-->19
          ↑
22-->23-->16

Output : [15]
```

## hints
```
    1.two-pointers,run at the same time.
    2.they will meet in a whole circle.

    Like:
    11-->13-->15-->17-->19  22->23..
    ↑                       ↑
    p ----------------------p

    22-->23-->16  11->..
    ↑             ↑
    q ------------q

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

Node* getFirstCommonNode(Node* headA, Node* headB){
    Node* p = headA;
    Node* q = headB;
    while (q != p){
        p = p->next;
        q = q->next;
        if (p == NULL) p = headB;
        if (q == NULL) q = headA;
    }
    return p;
}
```
