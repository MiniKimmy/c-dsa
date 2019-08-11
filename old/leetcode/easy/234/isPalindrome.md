## 234.Palindrome Linked List

Given a singly linked list, determine if it is a palindrome.

**Example 1:**
```
Input: 1->2
Output: false
```
**Example 2:**
```
Input: 1->2->2->1
Output: true
```

## hints
```
    fast-slow pointers && reverseList
    1.fast-pointer move 2 steps and slow-pointer move 1 step.
    2.when fast == NULL, and stop the slow-pointer.
    3.reverseList(slow->next) as ListA.
    4.match the ListA == SourceList which means left-list == right-list.
    [Caution]: the counts 'left-list >= right-list'.
```

## Analogous
|                         Nav            |                   Des                 |
| :-------------------------------------:|:-------------------------------------:|
| ![validPalindrome](../680/validPalindrome.c) |数组对称(允许删除其中某1个元素)  |

## Solution
``` c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* reverseList(struct ListNode* head){
    struct ListNode* p = head;
    while(p->next){
        p =p->next;
    }

    struct ListNode* q = head;
    while(q != p){
        struct ListNode* k = q->next;
        q->next = NULL;

        struct ListNode* o = p->next;
        p->next = q;
        q->next = o;

        q = k;
    }
    return q;
}

bool isPalindrome(struct ListNode* head) {
    if(head == NULL) return true;

    struct ListNode* slow = head;
    struct ListNode* fast = head->next;
    if(fast && fast->next){
        fast = fast->next;
    }else if(fast == NULL || fast->val == slow->val){
        return true;
    }else{
        return false;
    }

    while(fast){
        fast = fast->next?fast->next->next:NULL;
        slow = slow->next;
    }

    struct ListNode* p = head;
    struct ListNode* q = reverseList(slow->next);
    while(p != slow->next && q){
        if(p->val != q->val){
            return false;
        }
        p = p->next;
        q = q->next;
    }

    return true;
}
```