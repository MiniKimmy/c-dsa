## 83. Remove Duplicates from Sorted List
[这里](https://leetcode.com/problems/remove-duplicates-from-sorted-list/)

## hints1
* use (front/back) ptr, without "dummy"
* compare front.val == back.val, if yes move "front" && stop "back", if no "front/back" move next.
* until front == null

## Solution1
``` c
struct ListNode* deleteDuplicates(struct ListNode* head){
    if(!head || !head->next) return head;

    struct ListNode* pre = head;
    struct ListNode* p = head->next;

    while(p){
        if(p->val == pre->val){
            pre->next = p->next;
        }else{
            pre = p;
        }

        p = p->next;
    }

    return head;
}
```

## hints2
* just use one ptr as (front/back ptr)

## Solution2
``` csharp
public class Solution {
    public ListNode DeleteDuplicates(ListNode head) {
        if(head == null) return head;

        ListNode p = head;
        while(p.next != null) {
            if(p.val == p.next.val) p.next = p.next.next;
            else p = p.next;
        }

        return head;
    }
}
```