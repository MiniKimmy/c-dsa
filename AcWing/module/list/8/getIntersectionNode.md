## 160. Intersection of Two Linked Lists
[这里](https://leetcode.com/problems/intersection-of-two-linked-lists/)

## hints1
* just only can run one circle.
* catch boundary situation:any one list is "null" return "null"
## Solution1
``` csharp
public class Solution {
    public ListNode GetIntersectionNode(ListNode headA, ListNode headB) {
        if(headA == null || headB == null) return null;

        ListNode p = headA;
        ListNode q = headB;

        bool st1 = false;
        bool st2 = false;
        while(p != q) {
            p = p.next;
            q = q.next;
            if(p == null && !st1) {
                p = headB;
                st1 = true;
            }
            if(q == null && !st2) {
                q = headA;
                st2 = true;
            }
        }

        return p;
    }
}
```
## hints2
* use less space, don't need bool
* run a circle.
* when no intersection, one ptr will stop at 'null'.
## Solution2
``` c
struct ListNode* getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {

    struct ListNode* p = headA;
    struct ListNode* q = headB;
    while(p != q)
    {
        if(p) p = p->next;
        else p = headB;
        if(q) q = q->next;
        else q = headA;
    }

    return p;
}
```