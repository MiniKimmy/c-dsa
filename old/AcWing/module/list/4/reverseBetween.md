## 92. Reverse Linked List II
[这里](https://leetcode.com/problems/reverse-linked-list-ii/)

## hints1
* [在这题基础上](https://leetcode.com/problems/reverse-linked-list/)
* ![或参考这里](../3/reverseList.md)
* find the mth node's pre
* loop m-n times,reverse [m,n]
* reset the pre's ptr
## Solution1
``` c
struct ListNode* reverseBetween(struct ListNode* head, int m, int n){
    if(!head || m == n) return head;

    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummy->next = head;
    dummy->val = -1;

    struct ListNode* k = dummy;
    for(int i = 0;i < m-1;++i) k = k->next;

    struct ListNode* b = k->next;
    struct ListNode* c = b->next;

    int len = n-m;
    while(len--)
    {
        struct ListNode* d = c->next;
        c->next = b;
        b = c;
        c = d;
    }

    k->next->next = c;
    k->next = b;

    return dummy->next;
}
```
## hints2
* dummy + head-insert
* find mth node's pre && find nth node
* cut it as tow lists
```
ex:
1.dummy->head->..->pre->[m,n]->tail->..->null
2.ptr1 = m;
3.pre.next= tail or n.next;
4.n.next = null;
5.now we can see it turn as tow lists:
    (1) dummy->head->..->pre->tail->..->null
    (2) [m,n]->null

6.loop and head-insert.
```
## Solution2
``` csharp
public class Solution {
    public ListNode ReverseBetween(ListNode head, int m, int n) {
        if(head == null || m==n) return head;

        ListNode dummy = new ListNode(-1);
        dummy.next = head;

        ListNode p = dummy;
        int k = m-1;
        while(k > 0) {
            p = p.next;
            --k;
        }

        k = n;
        ListNode tail = dummy;
        while(k > 0) {
            tail = tail.next;
            --k;
        }

        ListNode q = p.next;
        p.next = tail.next;
        tail.next = null;
        while(q != null)
        {
            ListNode s = p.next;
            ListNode t = q.next;
            p.next = q;
            q.next = s;
            q = t;
        }

        return dummy.next;
    }
}
```