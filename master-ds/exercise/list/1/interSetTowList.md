## InterSetion tow ascending Lists

Given two lists, represent two sets, each with an ascending array of elements.
Find the intersection of ListA and ListB (means 'A∩B') and store it in ListA.

## CHINESE
已知两个链表A和B分别表示两个集合，其元素递增排列。编一函数，求A与B的交集，并存放于A链表中。

**Example 1:**
```
Input:
[1,2,3,5]
[1,2,2,2,5]

Output: [1,2,5]
```
**Example 2:**
```
Input:
[1,3,5,7]
[2,4,4,6]

Output: []
```
**Example 3:**
```
Input:
[1,2,5,5,5]
[1,2,3,4,5]

Output: [1,2,5]
```

## hints
```
    use two simple pointers and a flag.

    [I'd use p as A.element q as B.element]

    1.we can assume that ListB is ReadOnly.
    2.Start : q < p  , just let q move next merely.
    3.when q > p, we had to move headA's pos.
    4.when q == p at the first time, set up the flag, which means we couldn't move headA's pos any more.
    5.Hence, we just need to tail-delete pointer "p", and move next pointer "q".

```

## Analogous
|                         Nav               |                   Des            |
| :----------------------------------------:|:--------------------------------:|
| ![descendingTowList](descendingTowList.md)|将2个升序的链表归并为1个降序的链表|
| ![unionSetTowList](unionSetTowList.md)    |将2个升序的链表A∪B为1个链表       |
| ![mixThreeList](mixThreeList.md)          |将3个升序的链表AU(B∩C)为1个链表   |
| ![differentSetTowList](differentSetTowList.md)|将2个升序的链表求出其差集链表 |


## Solution

``` c
/**
* Definition for singly-linked list.
* struct Node {
*     int val;
*     struct Node *next;
* }Node;
*/

Node* interSetTowList(Node* headA, Node* headB) {
    if (headA == NULL || headB == NULL) return NULL;

    Node* p = headA;
    Node* q = headB;
    int flag = 0;

    while (p && q) {
        if (q->val < p->val) {
            q = q->next;
        }

        else if(q->val > p->val) {
            if (flag == 1) {
                if (p->next->val < q->val) {
                    Node* k = p->next;
                    p->next = k->next;
                    free(k);
                    k = NULL;
                }
            }else if (p == headA) headA = headA->next;

            p = p->next;
        }

        else {
            q = q->next;
            flag = 1;
        }
    }

    if (q == NULL && p != NULL) {
        p->next = NULL;
    }

    return headA;
}


```