/*
Given a sorted linked list, delete all duplicates such that each element appear only once.

Example 1:

Input: 1->1->2
Output: 1->2

Example 2:

Input: 1->1->2->3->3
Output: 1->2->3
*/

//C
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* deleteDuplicates(struct ListNode* head) {
    if(head == NULL) return NULL;

    struct ListNode* p1 = head;
    struct ListNode* p2 = head->next;
    while (p2 != NULL)
    {
        if(p1->val == p2->val){
            struct ListNode* temp = p2;
            p1->next = p2->next;
            p2 = p2->next;
            free(temp);
        } else {
            p1 = p2;
            p2 = p2->next;
        }

    }

    /*
    struct ListNode* p = head;
    while(true){
        struct ListNode* q = p->next;
        if(q == NULL) break;

        while(q->val == p->val){
            struct ListNode* m = q->next;
            p->next = m;
            free(q);
            q = NULL;
            if(m) q = m;
            else break;
        }
        if(p->next) p = p->next;
        else break;
    }
    */
    return head;
}
