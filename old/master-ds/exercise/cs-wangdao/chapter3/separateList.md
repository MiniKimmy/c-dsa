## Separate single list

## CHINESE
设C={a1,a2,..,b1,b2,b3..}的单链表,已知{an}的长度m,{bn}的长度n,
试拆开2组数为{a1,a2,..an},{bn,...b2,b1}.

**Example :**
```
Input :
[11,13,15,17,19],m=2, n=3
Output : [11,13],[19,17,15]
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

void separateList(Node* head, int n, Node** outA, Node** outB)
{
    Node* p = head;
    for (int i = 1; i < n; ++i) {
        p = p->next;
    }

    *outA = head;
    Node* pre = p;
    Node* q = pre->next;
    Node* o = q->next;

    q->next = NULL;
    while (o) {
        pre = q;
        q = o;
        o = o->next;
        q->next = pre;
    }

    *outB = q;
    p->next = NULL;
    return;
}
```