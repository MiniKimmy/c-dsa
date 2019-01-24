## 17. 从尾到头打印链表

输入一个链表的头结点，按照 从尾到头 的顺序返回节点的值。
返回的结果用数组存储。

**Example:**
```
Input:[2,3,5]
Output:[5,3,2]
```
## hints
```
    1.把链表赋值给数组，翻转数组
    2.先链表翻转，再赋值给数组
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

/// 获取链表长度
int getCount(struct ListNode* head){
    if(head == NULL) return 0;
    int len = 1;
    struct ListNode* p = head;
    while(p->next){
        len++;
        p = p->next;
    }
    return len;
}

/// 交换
void swap(int* arr, int i, int j){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int* printListReversingly(struct ListNode* head) {
    if(head == NULL) return NULL;

    int len = getCount(head);
    int* ret = (int*)malloc(sizeof(int) * len);
    struct ListNode* p = head;
    for(int i = 0;i<len;++i){
         ret[i] = p->val;
         p = p->next;
    }

    for(int i = 0;i<len/2;++i){
        swap(ret,i,len-i-1);
    }

    return ret;
}
```

## Solution2
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

int* printListReversingly(struct ListNode* head) {
    if(head == NULL) return NULL;

    int len = 0;
    struct ListNode* p = head;
    while(p->next){
        p = p->next;
        len++;
    }

    if(len == 0){
        int* ret = (int*)malloc(sizeof(int));
        ret[0] = p->val;
        return ret;
    }
    len++;  // last element

    // reverse-list
    struct ListNode* q = head;
    while(q != p){
        struct ListNode* s = q->next;
        struct ListNode* r = p->next;
        q->next = NULL;

        p->next = q;
        q->next = r;
        q = s;
    }

    struct ListNode* k = p;
    int* ret = (int*)malloc(sizeof(int) * len);
    for(int i = 0;i<len;++i){
        ret[i] = k->val;
        k=k->next;
    }
    return ret;
}
```