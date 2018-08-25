## Merge Two ascending Lists in descending.

It is assumed that there are two linear tables in an ascending order of element values, both stored as single linked lists.

Write an algorithm to merge the two single-linked lists into a single-linked list in descending order of element values.

It is also required to use the nodes of the original two single-linked lists to store the merged single-linked lists.

## CHINESE
假设有两个按元素值递增次序排列的线性表，均以单链表形式存储。
请编写算法将这两个单链表归并为一个按元素值递减次序排列的单链表，
并要求利用原来两个单链表的结点存放归并后的单链表。

**Example:**
```
Input:
[2,5,6,8,10]
[1,3,7,9]

Output: [10,9,8,7,6,5,3,2,1]
```

## hints
![reverseList](../../../../leetcode/easy/206/reverseList.md) : leetcode的一道题.
```
    tow simple pointers.
    headA "p1" and headB "p2" , regarding as return headA (headB is also OK)
    1. merge headA and headB as ascending order first and then reverse in the end.
    2. min{p1->val, p2->val} and use head-insert or tail-insert to connect into List headA.
    3. when p2 is min, use head-insert "p2".
    4. when p1 is min, find the last min p1 at first, then tail-insert "p2".

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

Node* reverseList(Node* head) {
    if (head == NULL) return NULL;

    Node* p = head;
    while (p->next != NULL) {
        p = p->next;
    }

    Node* q = head;
    while (q != p) {
        Node* t = q->next;
        q->next = NULL;

        Node* o = p->next;
        p->next = q;
        q->next = o;

        q = t;
    }

    return p;
}


Node* descendingTowList(Node* headA, Node* headB) {
    Node* p = headA;
    Node* q = headB;

    while (p && q) {
        if (q->val < p->val) {
            Node* k = q->next;
            q->next = p;

            if (headA->val > q->val) headA = q;
            q = k;

        }else {
            if (p->next == NULL ||  p->next && p->next->val > q->val) {
                Node* k = p->next;
                Node* s = q->next;

                p->next = q;
                p->next->next = k;
                q = s;
                p = k;
            }else {
                p = p->next;
            }
        }
    }

    return reverseList(headA);
}

```