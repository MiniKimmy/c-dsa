## Merge Two Circle Lists

Given two circle single-lists L1 L2, ane L1.Count = m and L2.Count = n
design an algorithm to combine the two lists into a single linked list.

## CHINESE
已知L1、L2分别为两循环单链表的头结点指针，m,n分别为L1、L2表中数据结点个数。
要求设计一算法，用最快速度将两表合并成一个带头结点的循环单链表。

**Example:**
```
Input:
[1,2,3,4]
4
[1,2,3]
3

Output: [1,2,3,1,2,3,4]

Explaination: order min_List->max_List, min Count is front of the max Count and make sure tail"4"->next = head"1".
```
**Note**<br />
The Output is unique. Count minList->maxList, or L1->L2 when they are same count.<br />

## hints
```
    two simple pointers.

    1.traverse two list in minStep.
    2.when the minList come to its tail(min), let tail(min)->next = head(max).
    3.continue to traverse maxList to its tail(max), let tail(max)->next = head(min).
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

Node* mergeTwoCircleLinkList(Node* headA, int ACount, Node* headB, int BCount) {
    if (ACount < 0 || BCount < 0) return NULL;
    if (headA == NULL || ACount == 0) return headB;
    if (headB == NULL || BCount == 0) return headA;

    Node* p = headA;
    Node* q = headB;
    int len,flag;

    if (ACount > BCount) {
        len = BCount;
        flag = 1;
    } else {
        len = ACount;
        flag = 0;
    }

    for (int i = 1; i < len; i++) {
        p = p->next;
        q = q->next;
    }

    if (flag == 0) {
        p->next = headB;
        while (q) {
            if (q->next == headB) {
                q->next = headA;
                return headA;
            }
            q = q->next;
        }

    }else {
        q->next = headA;
        while (p) {
            if (p->next == headA) {
                p->next = headB;
                return headB;
            }
            p = p->next;
        }
    }

    return NULL;
}
```