## Print single list in turn.

## CHINESE
在单链表中从尾到头反向输出每个结点值.

**Example 1:**
```
Input  :[11,13,15,17,19]
Output : 19,17,15,13,11
```

## hints
```
    1.recursion to the last node
    2.while in turn, go back to printf each val.
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

void upsidePrintSList(Node* head)
{
    if(head)
        upsidePrintSList(head->next);

    if (head) {
        printf("val = %d\n", head->val);
    }
}
```