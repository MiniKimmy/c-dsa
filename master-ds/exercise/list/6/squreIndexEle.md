## Squre Index Element

Given a single list, start from [1] to [lenth-1], judge Node[current-index] is eaqual the squre of current-index subtract the value of its pre-pointer.

## CHINESE
已知一个单链表中每个结点存放一个整数，并且结点数不少于2，<br />
请设计算法以判断该链表中第二项起的每个元素值是否等于其序号的平方减去其前驱的值，若满足则返回ture，否则返回false. <br />

**Example 1:**
```
Input:[1,0,4,5,11]
OutPut:true
```
**Example 2:**
```
Input:[1,0,4,6,11]
OutPut:false
```

## hints
```
    pre-pointer to judge,traverse the list.
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

int squreIndexEle(Node* head) {
    Node* p = head;
    int i = 1;
    while (p->next) {
        if ((i*i) - p->val == p->next->val) {
            ++i;
            p = p->next;
        }else {
            return 0;
        }
    }
    return 1;
}
```