## InsertSort LinkList

Given a sigle-list , sort single-list with insertSort.

**Example :**
```
Input: [7,3,4,1]
Output: [1,3,4,7]
```

## hints
```
    use dummy-head.

    1.Traverse list with pointer"p" ,and mark the previous of "p"-->pre
    2.cut the p->next("tail-list"), and just sort "p" into its front("front-list"), then use "pre" link the "tail-list".
    3.use while to find the "target" in "front-list", like q->next = "target"
    4.insert "p" into "front-list",  like [..->"q"->"p"->"target"->..]
    5.then link "tail-list",  like [..->"pre"->"tail-list"]
    6.Sometimes the "tail-list" == NULL, we need to move "pre", pre=pre->next;

    Another Method is classfy 3 Situations.[Slowly than the upper]
    1."target" is list-head.
    2."target" in the mid of the list.
    3."target" in the "front-list"(tail), ex: [1,2,7,3,...], "7" is the "front-list"(tail).
    4.finally, we need to traverse the list again to sort the last one element.

```

## Analogous
|                         Nav            |                   Des                 |
| :-------------------------------------:|:-------------------------------------:|
| ![sortLinkList](sortLinkList.md)       |单链表排序(冒泡、选择)                 |

## Solution
``` c
/**
* Definition for singly-linked list.
* struct Node {
*     int val;
*     struct Node *next;
* }Node;
*/

Node* insertSortLinkList(Node* head)
{
    if (head == NULL) return NULL;

    Node* dummy = (Node*)malloc(sizeof(Node));
    dummy->next = head;

    Node* p = head->next;
    Node* pre = head;

    while (p) {
        Node* k = p->next;

        if (p->val < pre->val) {
            Node* q = dummy;
            p->next = NULL;
            pre->next = NULL;
            while (q->next && q->next->val < p->val) q = q->next;

            p->next = q->next;
            q->next = p;
            pre->next = k;
        }else {
            pre = pre->next;
        }

        p = k;
    }

    return dummy->next;

    /*
    if (head == NULL) return NULL;

    Node* p = head->next;
    Node* pre = head;

    while (p) {
        Node* q = head;
        while (q != pre && q->next->val < p->val) q = q->next;
        if (q == pre) {
            int temp = p->val;
            p->val = pre->val;
            pre->val = temp;
        }else if(q == head && q->val >= p->val){
            Node* k = p->next;
            pre->next = k;
            p->next = head;
            head = p;
        }else {
            Node* k = q->next;
            int temp = p->val;
            p->val = k->val;
            k->val = temp;

            pre->next = p->next;
            p->next = k->next;
            k->next = p;
        }

        //Traverse('L', head, NULL);

        pre = pre->next!=p?pre:pre->next;
        p = pre!=NULL?pre->next:NULL;
    }

    Node* n = head;
    Node* k = head;
    while (n->next != pre) {
        if (n->val <= pre->val) {
            k = n;
        }
        n = n->next;
    }
    pre->next = k->next;
    k->next = pre;
    n->next = NULL;

    return head;
    */
}

```