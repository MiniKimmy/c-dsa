## 143. Reorder List
Given a singly linked list L: L0→L1→…→Ln-1→Ln,
reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…

You may not modify the values in the list's nodes, only nodes itself may be changed.

**Example 1:**
```
Given 1->2->3->4, reorder it to 1->4->2->3.
```
**Example 2:**
```
Given 1->2->3->4->5, reorder it to 1->5->2->4->3.
```

## hints
* find the mid node, split as two list, left-list && right-list
* reverse the right-list
* insert right-list into left-list with one interval

## Solution
``` c
void reorderList(struct ListNode* head){
    if(!head) return;

    int n = 0;
    struct ListNode* p = head;
    while(p)
    {
        p = p->next;
        ++n;
    }

    if(n<2) return;

    struct ListNode* mid = head;
    for(int i = 0; i + 1 < (n/2); ++i ) mid = mid->next;
    struct ListNode* a = mid->next;

    struct ListNode *b = mid, *c = b->next, *d = c->next;
    while(d)
    {
        struct ListNode* e = d->next;
        d->next = c;
        c = d;
        d = e;
    }
    b->next->next = d;
    b->next = c;

    a = mid->next;
    mid->next = NULL;

    while(a && head)
    {
        struct ListNode* o = a->next;
        struct ListNode* t = head->next;
        a->next = NULL;
        head->next = a;
        a->next = t;
        head = head->next->next;
        if(head) a = o;
        else a->next = o;
    }
}
```