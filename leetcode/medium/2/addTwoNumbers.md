## 2.Add Two Numbers

You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

**Example:**
```
Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
Explanation: 342 + 465 = 807.
```

## hints
```
    reverse list
```

## Solution
``` c
//beat 24.94% 24ms. not the best function.

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* reverseList(struct ListNode* list,int* getLen)
{
    struct ListNode* p = list;
    int len = 0;
    while(p->next){
        p = p->next;
        len++;
    }
    *getLen = len+1;

    struct ListNode* q = list;
    while(q != p){
        struct ListNode* k = q->next;
        q->next = NULL;

        struct ListNode* o = p->next;
        p->next = q;
        q->next = o;

        q = k;
    }

    return p;
}

struct ListNode* newNode(int val){
    struct ListNode* ret = (struct ListNode*)malloc(sizeof(struct ListNode));
    ret->next = NULL;
    ret->val = val;
    return ret;
}

struct ListNode* Refresh(struct ListNode* list){

    struct ListNode* p = list;
    int acc = 0;
    while(p->next){
        if(acc == 1){
            p->val++;
            acc = 0;
        }

        if(p->val >= 10){
            p->val %= 10;
            acc = 1;
        }

        p = p->next;
    }

    p->val +=acc;
    if(p->val >= 10)
    {
        p->val %= 10;
        struct ListNode* item = newNode(1);
        p->next = item;
    }

    return list;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    if(l1 == NULL) return l2;
    if(l2 == NULL) return l1;

    int l1size,l2size;
    struct ListNode* list1 = reverseList(l1,&l1size);
    struct ListNode* list2 = reverseList(l2,&l2size);
    struct ListNode* p = list1;
    struct ListNode* q = list2;

    struct ListNode* ret;
    if(l1size>l2size){
        int len = l1size-l2size;
        for(int i = 0;i<len;++i){
            p = p->next;
        }
        while(p){
            p->val += q->val;
            p = p->next;
            q = q->next;
        }
        ret = Refresh(reverseList(list1,&l1size));

    }else{
        int len = l2size-l1size;
        for(int i = 0;i<len;++i){
            q = q->next;
        }
        while(q){
            q->val += p->val;
            p = p->next;
            q = q->next;
        }
        ret = Refresh(reverseList(list2,&l2size));
    }

    return ret;
}
```
