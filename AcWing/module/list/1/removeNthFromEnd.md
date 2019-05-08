## 19. Remove Nth Node From End of List
[这里](https://leetcode.com/problems/remove-nth-node-from-end-of-list/)

## hints1
* traverse list one time and get its length
* traverse list for(i=0; i < length - n;++i)
* use pre (front/back ptr)

## Solution1
``` c
struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
    if(!head) return head;

    struct ListNode* k = head;
    int len = 0;
    while(k){
        len++;
        k = k->next;
    }

    struct ListNode* pre = NULL;
    struct ListNode* p = head;
    for(int i = 0;i<len-n;++i){
        pre = p;
        p = p->next;
    }

    if(!pre) return head->next;
    pre->next = p->next;
    return head;
}
```
## hints2
* traverse list for(i<n), and reach ptr1
* use ptr2 start at "head"
* ptr1,ptr2 move next at the same time, until ptr1==null

## Solution2
``` csharp
public class Solution {
    public ListNode RemoveNthFromEnd(ListNode head, int n) {
        if(head == null) return head;

        ListNode k = head;
        for(int i = 0;i<n;++i) k = k.next;
        if(k == null) return head.next;

        ListNode p = head;
        ListNode pre = null;
        while(k != null) {
            pre = p;
            p = p.next;
            k = k.next;
        }

        pre.next = p.next;
        return head;
    }
}
```