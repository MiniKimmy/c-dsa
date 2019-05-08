## 141. Linked List Cycle
[这里](https://leetcode.com/problems/linked-list-cycle/)

## hints1
* fast/slow ptr
* fast/slow start at different node.
## Solution1
``` csharp
public class Solution {
    public bool HasCycle(ListNode head) {
        if(head == null) return false;

        ListNode fast = head.next;
        ListNode slow = head;
        while(fast != null) {
            if(fast.next != null) fast = fast.next.next;
            else fast = fast.next;

            slow = slow.next;
            if(fast == slow) return true;
        }


        return false;
    }
}
```
## hints2
* just move, then judge (fast/slow start at the same node)
* careful the situation when list only one node.
## Solution2
``` c
bool hasCycle(struct ListNode *head) {
    struct ListNode *p = head; // slow-ptr
    struct ListNode *q = head; // fast-ptr

    while(q) {
        if(q->next) q = q->next->next;
        else q = q->next;

        p = p->next;
        if(p && p == q) return true;
    }

    return false;
}
```