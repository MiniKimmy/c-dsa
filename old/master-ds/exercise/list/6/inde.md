## deleteNode And InsertNode

Given tow single-list, delete k size of index[i] in ListA,and insert to the front of headB at index[j].

## CHINESE <br />
h1、h2为两个单链表,写出算法inde(h1,h2,i,j,k),将链表h1从第[i] <br />个结点起的k个结点删除，并插入到h2表的第[j]个结点之前。 <br />

**Example 1:**
```
Input:[1,2,3,4,5,6]
[5,9,7,2,1]
5
2
1

OutPut:[1,2,3,4,5]
[5,6,9,7,2,1]
```
**Example 2:**
```
Input:[1,2,3,4,5,6]
[5,9,7,2,1]
4
3
2

OutPut:[1,2,3,4]
[5,9,7,5,6,2,1]
```

## hints
```
    find the target list, and link into ListB.
```

## Analogous
|                         Nav            |                   Des                 |
| :-------------------------------------:|:-------------------------------------:|
| ![deleteMinNode](deleteMinNode.md)     |删除单链表最小的结点                   |
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

void inde(Node* headA, Node* headB, int i, int j, int len, Node** retHeadA, Node** retHeadB){
    Node* p = (Node*)malloc(sizeof(Node));
    p->next = headA;

    for (int k = 0; k < i; ++k) p = p->next;

    Node* n = p->next;
    Node* tail_A = n;
    for (int k = 1; k < len; ++k) tail_A = tail_A->next;

    p->next = tail_A->next;
    headA = p->next;
    if(tail_A->next) tail_A->next = NULL;

    Node* q = (Node*)malloc(sizeof(Node));
    q->next = headB;

    for (int k = 1; k < j; ++k) q = q->next;

    Node* m = q->next;
    q->next = n;
    tail_A->next = m;

    *retHeadA = headA;
    *retHeadB = q;
}
```