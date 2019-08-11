## 206. Reverse Linked List

Reverse a singly linked list.

**Example:**
```
Input: 1->2->3->4->5->NULL
Output: 5->4->3->2->1->NULL
```
**Follow up:**
A linked list can be reversed either iteratively or recursively. Could you implement both?

## hints
```
    head insert linklist.
    1.find the tail of the original list -- as the NEW Head.
    2.traverse the OLD Head again, and use 'head insert linklist' add at the NEW Head.
```

## Solution

``` c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* reverseList(struct ListNode* head) {
    if(head == NULL) return NULL;

    struct ListNode* p = head;
    while(p->next != NULL){
        p = p->next;
    }

    struct ListNode* q = head;
    while(q != p){
        struct ListNode* t = q->next;
        q->next = NULL;

        struct ListNode* o = p->next;
        p->next = q;
        q->next = o;

        q = t;
    }


    return p;
}

```