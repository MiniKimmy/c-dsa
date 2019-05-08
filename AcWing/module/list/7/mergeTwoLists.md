## 21. Merge Two Sorted Lists
[这里](https://leetcode.com/problems/merge-two-sorted-lists/)

## hints1
* dummy + tail, insert
## Solution
``` c
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2){

    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummy->next = NULL;
    struct ListNode* tail = dummy;

    while(l1 && l2)
    {
        if(l1->val > l2->val)
        {
            struct ListNode* t = l2->next;
            l2->next = NULL;
            tail->next = l2;
            l2 = t;
        }else{
            struct ListNode* t = l1->next;
            l1->next = NULL;
            tail->next = l1;
            l1 = t;
        }

        tail = tail->next;
    }

    if(l1) tail->next = l1;
    else tail->next = l2;
    return dummy->next;
}
```
## hints2
* no cut as "NULL", just move next
## Solution2
``` csharp
public class Solution {
    public ListNode MergeTwoLists(ListNode l1, ListNode l2) {
        ListNode dummy = new ListNode(0);
        dummy.next = null;
        ListNode tail = dummy;

        while(l1 != null && l2 != null)
        {
            if(l1.val > l2.val)
            {
                tail.next = l2;
                l2 = l2.next;
            }else{
                tail.next = l1;
                l1 = l1.next;
            }
            tail=tail.next;
        }

        tail.next = l1 == null?l2:l1;
        return dummy.next;
    }
}
```