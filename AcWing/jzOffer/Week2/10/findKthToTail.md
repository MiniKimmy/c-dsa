## 33. 链表中倒数第k个节点
[这里](https://www.acwing.com/problem/content/32/)
输入一个链表，输出该链表中倒数第k个结点。

**Note**
* k >= 0;
* 如果k大于链表长度，则返回 NULL;

**Example :**
```
Input:1->2->3->4->5 ，k=2
Output:4
Explanation:返回倒数第2个结点，即4是倒数第二个结点的val
```
## hints
```
    1.指针p先遍历k次
    2.然后重置指针，使用新的指针q从头开始，和p同步遍历，直至p==NULL
    3.避免k>链表长度
        (1).先遍历一次获取链表长度，
        (2).或者for循环k次看看链表在k次之内是不是已经出现过null
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
struct ListNode* findKthToTail(struct ListNode* pListHead, int k) {
    if(k<0 || pListHead == NULL) return NULL;

    struct ListNode* front = pListHead;
    int flag = 0;
    for(int i=0;i<k;++i){
        if(front){
            front = front->next;
        }else{
            return NULL;
        }
    }

    struct ListNode* back = pListHead;
    while(front!=NULL){
        front = front->next;
        back = back->next;
    }
    return back;
}
```