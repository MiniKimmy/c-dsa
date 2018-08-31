## Sort List

Sort a single-list from small to big.

## CHINESE
已知不带头结点的线性链表list，
请写一算法，将该链表按结点数据域的值的大小从小到大重新链接。
(要求链接过程中不得使用除该链表以外的任何链结点空间)

**Example :**
```
Input:
[7,3,4,1]

Output: [1,3,4,7]
```

## hints
```
    just like sort array.
```

**Note**<br />
The complexity of the space is O(1). <br />

## Solution
``` c
/**
* Definition for singly-linked list.
* struct Node {
*     int val;
*     struct Node *next;
* }Node;
*/

Node* sortLinkList(Node* head)
{
    //selectSort- Only swap val
    Node* p = head;
    while (p) {
        Node* q = p->next;
        Node* k = p;
        while (q) {
            if (q->val < k->val) {
                k = q;
            }
            q = q->next;
        }
        if (k != p) {
            int temp = k->val;
            k->val = p->val;
            p->val = temp;
        }
        p = p->next;
    }
    return head;

    /*
    //bubbleSort- Only swap val
    Node* p = head;
    while (p) {
        Node* q = p->next;
        while (q) {
            if (q->val < p->val) {
                int temp = q->val;
                q->val = p->val;
                p->val = temp;
            }
            q = q->next;
        }
        p = p->next;
    }
    return head;
    */
}
```