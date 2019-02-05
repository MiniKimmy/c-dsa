## 66. 两个链表的第一个公共结点
[这里](https://www.acwing.com/problem/content/62/)
输入两个链表，找出它们的第一个公共结点。
**Example :**
```
Input:
A：        a1 → a2
                   ↘
                     c1 → c2 → c3
                   ↗
B:     b1 → b2 → b3
Output:c1
```
## hints
```
1.2个指针一起跑，跑1圈相遇
2.这个一圈代表，A链跑完再抛B链。（或者B链跑完再跑A链）
3.注：有2种写法
    (1).从A链跑到null的时候立即变成B链的head
        * 这种写法处理“一定有公共结点”的情况是对的。
        * 而如果“不存在公共结点”的情况时候，就通过不了。见下面代码注释。
    (2).从A链跑到null时候不立即变，而是等下一回合再变成B链的head。
        * 这种写法处理“一定有公共结点”或“不一定有公共结点”的情况都是对的。
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
struct ListNode *findFirstCommonNode(struct ListNode *headA, struct ListNode *headB) {
    if(!headA || !headB) return NULL;

    struct ListNode* p = headA;
    struct ListNode* q = headB;

    while(p!=q)
    {
        if(p) p=p->next;
        else p = headB;

        if(q) q=q->next;
        else q = headA;
    }

    return p;


    /* 下面这种写法有一种情况通过不了，即“若输入的2个链表，不存在公共结点”。

    while(p != q){
        p = p->next;
        q = q->next;
        if(!q) q = headA;
        if(!p) p = headB;
    }

    return p;
    */
}
```