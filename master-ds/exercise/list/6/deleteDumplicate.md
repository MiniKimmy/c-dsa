## Delete dumplicate list

Given a ascending single list, remove the repeat value elements.

## CHINESE
一个有数值相同的元素存在递增有序的单链表，<br />
设计算法去掉数值相同的元素，使表中不再有重复的元素。 <br />

**Example 1:**
```
Input : [7,7,10,10,21,30,42,42,42,51,70 ]
OutPut: [7,10,21,30,42,51,70]
```
**Example 2:**
```
Input:[1,1,1,1,1,1,1]
OutPut:[1]
```

## hints
![deleteDuplicates](../../../../leetcode/easy/83/deleteDuplicates.c) : leetcode的一道题.
```
     front-back pointers.
```
## Analogous
|                         Nav            |                   Des                 |
| :-------------------------------------:|:-------------------------------------:|
| ![moveMinHead](moveMinHead.md)         |把单链表最小的结点移动到头结点         |
| ![inde](inde.md)                       |把单链表A的的子链插入到单链表B中       |


## Solution
``` c
/**
* Definition for singly-linked list.
* struct Node {
*     int val;
*     struct Node *next;
* }Node;
*/

Node* deleteDumplicate(Node* head) {
    if (head == NULL) return NULL;

    Node* pre = head;
    Node* p = head->next;
    while (p) {
        if (pre->val == p->val) {
            Node* k = p->next;
            pre->next = k;
            free(p);
            p = k;
        }
        else {
            pre = p;
            p = p->next;
        }
    }

    return head;
}
```