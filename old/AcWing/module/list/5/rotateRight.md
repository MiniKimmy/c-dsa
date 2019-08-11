## 61. Rotate List
[这里](https://leetcode.com/problems/rotate-list/)

## hints1
* count the list's length
* front/back ptr find the Kth node from end of the list
* split tow list, and resort it.

## Solution1
``` c
struct ListNode* rotateRight(struct ListNode* head, int k){
    if(!head || !k || !head->next) return head;

    int len = 0;
    for(struct ListNode* p = head;p;p=p->next) ++len;

    k %= len;
    if(!k) return head;

    struct ListNode* p = head;
    while(k--) p = p->next;

    struct ListNode* q = head;
    while(p->next){
        q = q->next;
        p = p->next;
    }

    struct ListNode* ret = q->next;
    q->next = NULL;
    p->next = head;

    return ret;
}
```

## hints2
* it means that the Kth Node From End of List as "head"
* count the list, and get the [Kth Node From End of List]()

## Solution2
``` csharp
public class Solution {
    public ListNode RotateRight(ListNode head, int k) {
        if(head == null || k == 0) return head;

        int len = 0;
        for(ListNode p = head;p!=null;p=p.next) ++len;

        k %=len;
        if(k==0) return head;

        ListNode pre = null;
        ListNode ret = head;
        for(int i = 0;i<len-k;++i) {
            pre = ret;
            ret = ret.next;
        }

        ListNode tail = ret;
        pre.next = null;

        while(tail.next != null) tail = tail.next;
        tail.next = head;

        return ret;
    }
}
```