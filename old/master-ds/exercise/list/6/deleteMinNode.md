## Delete Minimum Node

Given a single list, delete the one min Node.

## CHINESE
试编写在带头结点的单链表中删除（一个）最小值结点的（高效）算法。

**Example :**
```
Input: [1,3,4,-5,-6,-7,4]
Output: [1,3,4,-5,-6,4]
```

## hints
```
    dummy-node.
    1.traverse the list and mark the min Node.
    2.free(min) and return dummy->next.

    ps:At the beginning of dummy->val = head->val + 1 , which means we mark the "head" node successfully.
```

## Analogous
|                         Nav            |                   Des                 |
| :-------------------------------------:|:-------------------------------------:|
| ![moveMinHead](moveMinHead.md)         |把单链表最小的结点移动到头结点         |
| ![inde](inde.md)                       |把单链表A的的子链插入到单链表B中       |
| ![deleteDumplicate](deleteDumplicate.md) |删除递增单链表的重复元素             |
| ![deleteMulNode](deleteMultipleIdenticalNodes.md) |删除单链表中所有指定val的元素 |


## Solution
``` c
/**
* Definition for singly-linked list.
* struct Node {
*     int val;
*     struct Node *next;
* }Node;
*/

Node* deleteMinNode(Node* head){
    if (head == NULL) return NULL;

    Node* dummy = (Node*)malloc(sizeof(Node));
    dummy->next = head;
    Node* p = dummy;
    int min = p->next->val+1;
    Node* minNode = NULL;

    while (p->next) {
        if (p->next->val < min) {
            min = p->next->val;
            minNode = p;
        }
        p = p->next;
    }

    Node* temp = minNode->next;
    minNode->next = temp->next;
    free(temp);

    return dummy->next;
}
```