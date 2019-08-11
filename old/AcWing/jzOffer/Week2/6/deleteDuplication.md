## 29. 删除链表中重复的节点
[这里](https://www.acwing.com/problem/content/27/)
在一个排序的链表中，存在重复的结点，请删除该链表中重复的结点，重复的结点不保留。

**Example 1**
```
Input:1->2->3->3->4->4->5
Output:1->2->5
```
**Example 2**
```
Input:1->1->1->2->3
Output:2->3
```

## hints
```
    1.前后指针。使用3个指针.
    2.使用dummy的伪头结点
```

## Solution
``` c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 *
 * Note: The returned array must be malloced, assume caller calls free().
 */

struct ListNode* deleteDuplication(struct ListNode* head) {
    if(head==NULL) return NULL;

    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummy->val = head->val-1;
    dummy->next = head;

    struct ListNode* front = head->next;
    struct ListNode* back = head;
    struct ListNode* pre =  dummy;
    int last = dummy->val;
    while(front!=NULL){
        if(front->val==back->val){
            last = front->val;
            struct ListNode* temp = front;
            front = front->next;
            free(temp);
            back->next = front;
        }else{
            if(back->val == last){
                struct ListNode* temp = back;
                back = front;
                front = front->next;
                free(temp);
                pre->next = back;
            }else{
                pre = pre->next;
                front = front->next;
                back = back->next;
            }
        }
    }

    // last element
    if(back->val == last){
            struct ListNode* temp = back;
            back = front;
            free(temp);
            pre->next = back;
    }

    struct ListNode* ret = dummy->next;
    free(dummy);
    return ret;
}
```