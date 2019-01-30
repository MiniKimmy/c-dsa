## 36. 合并两个排序的链表
[这里](https://www.acwing.com/problem/content/34/)
输入两个递增排序的链表，合并这两个链表并使新链表中的结点仍然是按照递增排序的。

**Example :**
```
Input :1[->3->5->null],[2->4->5->null]
Output:1->2->3->4->5->5->null
```
## hints
```
    1.2个链表，保持1个链表A不动，链表B来插入到链表A
    2.链表A使用前后指针来插入链表B的每个元素
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

struct ListNode* merge(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummy->next = l1;

    struct ListNode* back = dummy;
    struct ListNode* front = l1;

    struct ListNode* p = l2;

    while(front && p){
        if(front->val<=p->val){
            back = back->next;
            front = front->next;
        }else{
            struct ListNode* t = p->next;
            back->next = p;
            p->next = front;
            back = p;
            p = t;
        }
    }

    if(p) back->next = p;
    return dummy->next;
}
```