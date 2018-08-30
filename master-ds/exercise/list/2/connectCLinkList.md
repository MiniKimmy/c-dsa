## Combine whth circle-list to single-list

Given two lists, listA is single-list, and listB circle-list.
design a algorithm  to combine listA with listB into a single-list.

## CHINESE
设有两个链表，list_a为单向链表，list_b为单向循环链表。
编写算法，将两个链表合并成一个单向链表，要求算法所需时间与链表长度无关。

**Example 1:**
```
Input:
[1,2,3,4] -sList
[1,2,3]   -cList

Output: [Not unique]
```
**Example 2:**
```
Input:
[1,2,3,4] -sList
[]        -cList

Output: [1,2,3,4]
```

**Note** <br />
The Time complexity is irrelevant to the length of the list. <br />

## hints
```
    ex 1: [1,2,3]   -cList

    1.As we all known "1->2->3->1-..", and one key point is the first element of circle-list must be a point that make it "circle".
    2.So we can let "1"(head)->NULL, means "1->null" and the whole link will change into "2->3->1->NULL" -->cList-->sList sucessfully.
    3.so the next time we just need to tail-insert the Given sList like this"2->3->1->sList(head)".
```

## Analogous
|                         Nav            |                   Des                 |
| :-------------------------------------:|:-------------------------------------:|
| ![mergeTwoCircleLinkList](mergeTwoCircleLinkList.md)|将2个循环列表合并为1个的循环链表|

## Solution
``` c
/**
* Definition for singly-linked list.
* struct Node {
*     int val;
*     struct Node *next;
* }Node;
*/

Node* connectCLinkList(Node* sList, Node* cList) {
    if (cList == NULL) return sList;
    Node* p = cList->next;
    cList->next = sList;
    return p;
}

```