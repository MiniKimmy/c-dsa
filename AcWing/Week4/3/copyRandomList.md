## 48. 复杂链表的复刻
[这里](https://www.acwing.com/problem/content/89/)
请实现一个函数可以复制一个复杂链表。
在复杂链表中，每个结点除了有一个指针指向下一个结点外，还有一个额外的指针指向链表中的任意结点或者null。

**Example :**
```
Input:[[1, 1], [0, 2], [1, 4], [3, -1], [3, 2]]
Output:[[1, 1], [0, 2], [1, 4], [3, -1], [3, 2]]
Explanation:Input和Output的数值是一模一样的，Output的链表是copy原Input的链表，2条链表的地址是不一样的。
```

## hints
```
    * copy新的list的功能
    * ex:A->B->C->D->NULL
        (1).先遍历一遍copy自身，random先不管
            * 变成:A->A'->B->B'->C->C'->D->D'->NULL
        (2).然后再遍历一遍copy原[A->B->C->D->NULL]里的random引用
            * 需要跳过一个X'，
            * 然后把对应的random放到对应的X’上[需要前驱结点来赋值]
                p->next->random = p->random->next
```

## Solution
``` c
/**
 * Definition for singly-linked list with a random pointer.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 *     struct ListNode *random;
 * };
 */

struct ListNode *copyRandomList(struct ListNode *head) {
    if(head == NULL) return NULL;

    struct ListNode* p = head;
    while(p){
        struct ListNode * k = p->next;
        struct ListNode* copy = (struct ListNode*)malloc(sizeof(struct ListNode));
        copy->val = p->val;
        copy->random = NULL;

        p->next = copy;
        copy->next = k;
        p = k;
    }

    p = head;
    while(p){
        struct ListNode* k = p->next->next;  // 跳过copy的结点
        if(p->random){
            p->next->random = p->random->next;
        }
        p = k;
    }

    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummy->next = head;
    struct ListNode* tail = dummy;
    p = head;
    while(p){
        tail->next = p->next;
        tail = tail->next;
        p = p->next->next;
    }

    return dummy->next;
}
```