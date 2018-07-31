/*
Q203.Remove Linked List Elements
Remove all elements from a linked list of integers that have value val.

Example:
Input:  1->2->6->3->4->5->6, val = 6
Output: 1->2->3->4->5
*/

//C
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* removeElements(struct ListNode* head, int val) {

    if(head == NULL) return NULL;

    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummy->val = 2018;    //random value
    dummy->next = head;

    struct ListNode* p1 = dummy;
    struct ListNode* p2 = dummy->next;

    while(p2 != NULL){
         if(p2->val == val){
            struct ListNode* temp = p2;
            p2 = p2->next;
            p1->next = p2;
            free(temp);
            temp = NULL;
        }else{
             p1 = p2;
             p2 = p2->next;
        }
    }

    return dummy->next;


    /*
    if(head == NULL) return NULL;

    struct ListNode* p1 = head;
    struct ListNode* p2 = head->next;

    while(p2 != NULL){
        if(p1->val == val){
            struct ListNode* temp = p1;
            p1 = p2;
            p2 = p2->next;
            free(temp);
            temp = NULL;
            head = p1;
        }
        else if(p2->val == val){
            struct ListNode* temp = p2;
            p2 = p2->next;
            p1->next = p2;
            free(temp);
            temp = NULL;
        }else{
            p1=p2;
            p2 = p2->next;
        }
    }

    return head->val == val ? NULL : head;
    */
}
