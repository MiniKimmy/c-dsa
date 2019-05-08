## 206. Reverse Linked List
[这里](https://leetcode.com/problems/reverse-linked-list/)

## hints1
```
1.a->b->c->d->null
2.dummy->a->b->c->d->null
         ↑  ↑  ↑
  (ptr)  A  B  C
3.loop
    first circle:  "b"->"a",
    second circle: "c"->"b",
    ......
    until B == bull
4.dummy->next->next = null, dummy->next = A;
```
## Solution1
``` c
struct ListNode* reverseList(struct ListNode* head){
    if(!head || !head->next) return head;

    struct ListNode* a = (struct ListNode*)malloc(sizeof(struct ListNode));
    a->next = head;
    struct ListNode* b = a->next;
    struct ListNode* c = b->next;

    while(c){
        struct ListNode* d = c->next;
        c->next = b;
        b = c;
        c = d;
    }

    a->next->next = NULL;
    return b;
}
```
## hints2
* dummy + "head-insert"

## Solution2
``` csharp
public class Solution {
    public ListNode ReverseList(ListNode head) {

        ListNode dummy = new ListNode(-1);

        ListNode p = head;
        while(p != null)
        {
            ListNode o = p.next;
            p.next = null;

            ListNode t = dummy.next;
            dummy.next = p;
            p.next = t;
            p = o;
        }

        return dummy.next;
    }
}
```
