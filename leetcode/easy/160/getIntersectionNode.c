/*
Q160.Intersection of Two Linked Lists
DescriptionHintsSubmissionsDiscussSolution

Write a program to find the node at which the intersection of two singly linked lists begins.

For example, the following two linked lists:

A:          a1 â†?a2
                   â†?                     c1 â†?c2 â†?c3
                   â†?B:     b1 â†?b2 â†?b3

begin to intersect at node c1.

Notes:
    If the two linked lists have no intersection at all, return null.
    The linked lists must retain their original structure after the function returns.
    You may assume there are no cycles anywhere in the entire linked structure.
    Your code should preferably run in O(n) time and use only O(1) memory.
 */

//C
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    if(headA ==NULL || headB==NULL) return NULL;

    struct ListNode *p = headA;
    struct ListNode *q = headB;

    while(p != q){
        p = p == NULL? headB : p->next;
        q = q == NULL? headA : q->next;
    }

    return p;
}
