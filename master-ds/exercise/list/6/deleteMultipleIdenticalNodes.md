## Delete Multiple Identical Nodes

Given a single list and k=value, delete element whose value equals k in the list.

## CHINESE
已知长度为n的单链表，删除单链表中所有值为k的元素结点。<br />
时间复杂度为0(n),空间复杂度要求O(1)。<br />

**Example 1:**
```
Input : [1,1,3,1,5,1,1,1], 1
OutPut: [3,5]
```
**Example 2:**
```
Input : [1,1,3,1,5], 0
OutPut: [1,1,3,1,5]
```

**Note**
Time Complexity is O(n), Space Complexity is O(1).

## hints
```
    dummy && front-back pointers.
    ps: When meet a node.val == k,
    we could just skip "it" rather than free("it").
```

## Analogous
|                         Nav            |                   Des                 |
| :-------------------------------------:|:-------------------------------------:|
| ![deleteDumplicate](deleteDumplicate.md) |删除递增单链表的重复元素             |
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
Node* deleteMultipleIdenticalNodes(Node* head,int k) {
    if (head == NULL) return NULL;

    Node* dummy = (malloc(sizeof(Node)));
    dummy->next = head;
    Node* pre = dummy;

    Node* p = head;
    while (p) {
        if (p->val == k) {
            Node* o = p->next;
            pre->next = p->next;
            //free(p);
            //p = NULL;
            p = o;
        }else {
            pre = p;
            p = p->next;
        }
    }

    Node* ret = dummy->next;
    free(dummy);
    return ret;
}
```