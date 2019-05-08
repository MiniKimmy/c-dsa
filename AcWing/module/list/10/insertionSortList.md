## 147. Insertion Sort List
[这里](https://leetcode.com/problems/insertion-sort-list/)

## hints1
* dummy
* find the appropriate place and insert
## Solution
``` c
struct ListNode* insertionSortList(struct ListNode* head){
    if(!head || !head->next) return head;

    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummy->next = NULL;

    struct ListNode* p = head;
    while(p){
        struct ListNode* t = p->next;
        struct ListNode* q = dummy;

        while(q->next && q->next->val <= p->val) q = q->next;

        struct ListNode* s = q->next;
        q->next = p;
        p->next = s;

        p = t;
    }

    return dummy->next;
}
```
## hints2
* just use "head" node,

## Solution2
``` csharp
public class Solution {
    public ListNode InsertionSortList(ListNode head) {
        ListNode dummy = new ListNode(0);
        dummy.next = null;

        while(head != null)
        {
            ListNode t = head.next;
            ListNode p = dummy;

            while(p.next != null && p.next.val <= head.val) p=p.next;

            ListNode s = p.next;
            p.next = head;
            head.next = s;

            head = t;
        }

        return dummy.next;
    }
}
```
