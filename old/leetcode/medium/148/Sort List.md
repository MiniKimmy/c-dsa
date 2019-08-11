## 148. Sort List
Sort a linked list in O(n log n) time using constant space complexity.

**Example 1:**
```
Input: 4->2->1->3
Output: 1->2->3->4
```
**Example 2:**
```
Input: -1->5->3->4->0
Output: -1->0->3->4->5
```
## hints
* [连接2个有序链表](https://leetcode.com/problems/merge-two-sorted-lists/description/)
* 找链表的中点(快慢指针)
* 每次递归拆成2半链表

## Solution
``` c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2){
    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummy->next = NULL;
    struct ListNode* tail = dummy;

    while(l1 && l2)
    {
        if(l1->val > l2->val)
        {
            struct ListNode* t = l2->next;
            l2->next = NULL;
            tail->next = l2;
            l2 = t;
        }else{
            struct ListNode* t = l1->next;
            l1->next = NULL;
            tail->next = l1;
            l1 = t;
        }

        tail = tail->next;
    }

    tail->next = l1?l1:l2;
    return dummy->next;
}

struct ListNode* sortList(struct ListNode* head){
    if(!head || !head->next) return head;

    struct ListNode *slow = head;
    struct ListNode *fast = head;
    struct ListNode *pre = head;
    while (fast && fast->next) {
           pre = slow;
           slow = slow->next;
           fast = fast->next->next;
    }
    pre->next = NULL;
    struct ListNode *left = sortList(head);
    struct ListNode *right = sortList(slow);

    return mergeTwoLists(left,right);
}
```

## Solution2
``` csharp
public class Solution {
    public ListNode MergeInner(ListNode l1, ListNode l2)
    {
        ListNode dummy = new ListNode(0);
        ListNode tail = dummy;

        while(l1 != null && l2 != null)
        {
            if(l1.val > l2.val)
            {
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

    // [l,mid-1],[mid,r]
    public ListNode MergeSort(ListNode head, int l, int r) {
        if(head == null || l >= r) return head;

        int mid = l + r + 1 >> 1;
        ListNode k = head;
        for(int i = l+1; i < mid; ++i) k = k.next; //因为从head开始，所以index=1开始遍历就拿到左链表的最后一个结点

        ListNode rHead = k.next;
        k.next = null;

        ListNode left  = MergeSort(head,l,mid-1);  //[l,mid-1]
        ListNode right = MergeSort(rHead,mid,r);   //[mid,r]

        return MergeInner(left,right);
    }

    public ListNode SortList(ListNode head) {
        if(head == null || head.next == null) return head;
        int len = 0;
        for(ListNode p = head;p != null; p = p.next) ++len;
        return MergeSort(head,0,len-1);
    }
}
```