## 35. 反转链表
[这里](https://www.acwing.com/problem/content/33/)
定义一个函数，输入一个链表的头结点，反转该链表并输出反转后链表的头结点。

**Example :**
```
Input:1->2->3->4->5->NULL
Output:5->4->3->2->1->NULL
```

## hints
```
    no hints.
```

## Solution
``` c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* reverseList(struct ListNode* head) {
    if(head == NULL) return NULL;

    struct ListNode* p = head;
    while(p->next){
        p = p->next;
    }

    struct ListNode* q = head;

    while(q != p)
    {
        struct ListNode* s = q->next;
        struct ListNode* r = p->next;
        q->next = NULL;
        p->next = q;
        q->next = r;
        q = s;
    }
    return p;
}
```