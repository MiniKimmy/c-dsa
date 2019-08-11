## Is Child Subsequence

Given tow single-list,judge listB is whether a subsequence of listA.

## CHINESE
两个整数序列A=a1,a2,a3,…,am和B=b1,b2,b3,…,bn已经存入两个单链表中，
设计一个算法，判断序列B是否是序列A的子序列。

**Example 1:**
```
Input:[ 1,0,4,6,11]
      [1,0,4]

OutPut:true
```
**Example 2:**
```
Input:[1,0,4,6,11]
      [1,0,3]

OutPut:false
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

/*return 1 ->true, return 0 ->false */
int isChildSequence(Node* headA, Node* headB) {
    if (headA == NULL) return 0;
    if (headB == NULL) return 1;

    Node* p = headA;
    Node* q = headB;

    int len = 0;
    while (q) {
        ++len;
        q = q->next;
    }

    q = headB;
    while (p) {
        int i = 0;
        while (p != NULL && q != NULL && i < len && p->val == q->val) {
            ++i;
            p = p->next;
            q = q->next;
        }
        if (i == len) return 1;
        q = headB;
        p = p->next;
    }

    return 0;
}
```