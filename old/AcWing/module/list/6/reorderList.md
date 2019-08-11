## 143. Reorder List
[这里](https://leetcode.com/problems/reorder-list/)

## hints1
* get the list length
* find mid node. ex:4/2=2 (pick 2);5/2=2.5 (pick 3)
* split(left/right)-list, and reverse right-list
* then insert right-list into left-list

## Solution1
``` c
void reorderList(struct ListNode* head){
    if(!head || !head->next) return head;

    // count-lenth
    int len = 0;
    for(struct ListNode* p = head;p;p=p->next) ++len;

    // find mid(up)
    int mid = (len+1) / 2;
    struct ListNode* p = head;
    while(--mid) p=p->next;

    // reverse-list
    struct ListNode* q = p->next;
    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummy->next = q;
    struct ListNode* a = dummy->next;
    struct ListNode* b = a->next;

    while(b){
        struct ListNode* c = b->next;
        b->next = a;
        a = b;
        b = c;
    }

    dummy->next->next = NULL;
    dummy->next = a;

    // insert
    q = dummy->next;
    p->next = NULL;
    p = head;
    while(q){
        struct ListNode* t = p->next;
        struct ListNode* s = q->next;
        p->next = q;
        q->next = t;
        p = t;
        q = s;
    }

    return head;
}
```

## hints2
* no "dummy" node, just use source-list as "dummy"
* for(int i = 0;i + 1 < (len+1)/2;++i)  equals for(int i = 1;i < (len+1)/2;++i)

## Solution2
``` csharp
public class Solution {
    public void ReorderList(ListNode head) {
        if(head == null) return;

        int len = 0;
        ListNode p;
        for(p = head; p!=null; p=p.next) ++len;
        if(len<=2) return;

        p = head;
        for(int i = 0;i + 1 < (len+1)/2;++i) p = p.next;

        ListNode a = p.next;
        ListNode b = a.next;
        while(b != null){
            ListNode c = b.next;
            b.next = a;
            a = b;
            b = c;
        }

        p.next.next = null;
        p.next = a;

        ListNode q = p.next;
        p.next = null;
        p = head;
        while(q != null){
            ListNode t = q.next;
            ListNode s = p.next;

            p.next = q;
            q.next = s;
            p = s;
            q = t;
        }

        return;
    }
}
```