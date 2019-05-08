## 148. Sort List
[这里](https://leetcode.com/problems/sort-list/)

## hints1
* [参考](https://www.acwing.com/solution/LeetCode/content/85/)
* find mid node each recursive
## Solution1
``` c
struct ListNode* merge(struct ListNode* l1, struct ListNode* l2){
    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummy->next = NULL;
    struct ListNode* tail = dummy;

    while(l1 && l2){
        if(l1->val > l2->val){
            tail->next = l2;
            l2 = l2->next;
        }else{
            tail->next = l1;
            l1 = l1->next;
        }
        tail = tail->next;
    }

    tail->next = l1?l1:l2;
    return dummy->next;
}

struct ListNode* sortList(struct ListNode* head){
    if(!head || !head->next) return head;

    int len = 0;
    for(struct ListNode* p = head;p;p=p->next) ++len;

    int mid = len / 2;
    struct ListNode* pre = NULL;
    struct ListNode* p = head;

    while(mid--) {
        pre = p;
        p = p->next;
    }

    pre->next = NULL;
    struct ListNode* left = sortList(head);
    struct ListNode* right = sortList(p);

    return merge(left,right);
}

```
## hints2
* find mid node (don't count list)
## Solution2
``` csharp
public class Solution {
    public ListNode Merge(ListNode l1, ListNode l2) {
        ListNode dummy = new ListNode(0);
        ListNode tail = dummy;

        while(l1 != null && l2 != null) {
            if(l1.val > l2.val){
                tail.next = l2;
                l2 = l2.next;
            }else{
                tail.next = l1;
                l1 = l1.next;
            }

            tail = tail.next;
        }

        tail.next = l1==null?l2:l1;
        return dummy.next;
    }

    public ListNode SortList(ListNode head) {
        if(head == null || head.next == null) return head;

        ListNode fast = head;
        ListNode slow = head;
        ListNode pre = null;

        while(fast != null && fast.next != null) {
            pre = slow;
            fast = fast.next.next;
            slow = slow.next;
        }

        pre.next = null;
        ListNode left = SortList(head);
        ListNode right = SortList(slow);

        return Merge(left,right);
    }
}
```