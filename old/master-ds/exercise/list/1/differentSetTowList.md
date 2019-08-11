## Different Set tow single-List

Given two descending single-Lists, desgin a algorithm to "A - (A∩B)",
which means find elements in List-A that are different from the same elements of List-A and List-B.

## CHINESE
已知递增有序的单链表A、B，求出集合A和B的差集A-B(仅由A出现而B不出现的元素)
将差集保存在单链表A中,并保证元素的递增有序.

**Example :**
```
Input : [1,3,4,5,6,7,9]
Output: [1,3,4,7,8]
```

## hints
```
   dummy Node with tail-pointer and use cut "list(tail)" 置空法.
   [dummy-list->next = List-A]

   1.Traverse List-A Pointers "p" && Traverse List-B "q",
   2.classify 3 situation "=",">","<"
   3.tail-pointer is used to mark the dummy-list(tail), when Add new Node, then cut "list(tail)".
```

## Analogous
|                         Nav               |                   Des            |
| :----------------------------------------:|:--------------------------------:|
| ![descendingTowList](descendingTowList.md)|将2个升序的链表归并为1个降序的链表|
| ![interSetTowList](interSetTowList.md)    |将2个升序的链表A∩B为1个链表       |
| ![mixThreeList](mixThreeList.md)          |将3个升序的链表AU(B∩C)为1个链表   |
| ![unionSetTowList](unionSetTowList.md)    |将2个升序的链表A∪B为1个链表       |


## Solution
```c
/**
* Definition for singly-linked list.
* struct Node {
*     int val;
*     struct Node *next;
* }Node;
*/

Node* differentSetTowList(Node* headA, Node* headB) {
    if (headB == NULL || headA == NULL) return headA;

    Node* p = headA;
    Node* q = headB;
    Node* dummy = (Node*)malloc(sizeof(Node*));
    dummy->next = NULL;
    Node* tail = NULL;

    while (p && q) {
        if (p->val == q->val) {
            q = q->next;
            if (tail == NULL) p = p->next;

            else {
                Node* k = p->next;

                free(p);
                p = k;
            }
        }else if (p->val < q->val) {
            if (tail == NULL) {
                tail = p;
                dummy->next = tail;
            }else {
                Node* k = p->next;

                tail->next = p;
                tail = p;
                tail->next = NULL;
                p = k;
            }
        }else {
            q = q->next;
        }
    }
    if (p != NULL) tail->next = p;
    return tail==NULL?headA:dummy->next;
}
```