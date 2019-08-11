## 142. Linked List Cycle II
[这里](https://leetcode.com/problems/linked-list-cycle-ii/)

## hints1
* fast/slow ptr
* [参考](https://www.acwing.com/solution/LeetCode/content/241/)
* just move , then judge.
## Solution1
``` c
struct ListNode *detectCycle(struct ListNode *head) {
    if(!head || !head->next) return NULL;

    struct ListNode *fast = head;
    struct ListNode *slow = head;

    while(fast && slow) {
        if(fast->next) fast = fast->next->next;
        else fast = fast->next;  // "else return NULL" is ok.
        slow = slow->next;

        if(fast == slow) {
            slow = head;
            while(fast != slow){
                slow = slow->next;
                fast = fast->next;
            }
            return slow;
        }
    }

    return NULL;
}
```
## hints2
* fast/slow ptr
* judge first, then move.
## Solution2
``` csharp
public class Solution {
    public ListNode DetectCycle(ListNode head) {
        if(head == null) return head;

        ListNode fast = head.next;
        ListNode slow = head;

        while(fast != null && slow != null) {
            if(fast == slow) {
                slow = head;
                fast = fast.next;      // at the beginning, "fast" is in front of "slow".
                while(fast != slow) {
                    fast = fast.next;
                    slow = slow.next;
                }

                return slow;
            }

            if(fast.next != null) fast = fast.next.next;
            else return null;
            slow = slow.next;
        }

        return null;
    }
}
```