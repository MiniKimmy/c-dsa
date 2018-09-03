## Select Odd and Even in a Single List
Given a single-list, split list with two list, one is only has odd elements, another only has even elements.

## CHINESE
设head为一单链表的头指针，将head链中结点分成一个奇数链和一个偶数链，分别由P,Q指向，每个链中的数据按由小到大排列。程序中不得使用malloc过程申请空间。

**Example :**
```
Input:
[7,3,6,5,4,1]

Output: [1,3,5,7],[4,6]
```
**Note** <br />
You'd better dont use "malloc".  <br />

## hints
![insertSortList](../3/insertSortLinkList.md):单链表插入排序
```
    1.select element of odd and even.
    2.sort the odd-list, even-list.
```

## Analogous
|                         Nav            |                   Des                 |
| :-------------------------------------:|:-------------------------------------:|
| ![splitP&NList](splitPositiveAndNegativeList.md)|把链表分成2个链表(正数链,负数链)    |


## Solution
``` c
/**
* Definition for singly-linked list.
* struct Node {
*     int val;
*     struct Node *next;
* }Node;
*/

Node* insertSortLinkList(Node* head)
{
    if (head == NULL) return NULL;

    Node* dummy = (Node*)malloc(sizeof(Node));
    dummy->next = head;

    Node* p = head->next;
    Node* pre = head;

    while (p) {
        Node* k = p->next;

        if (p->val < pre->val) {
            Node* q = dummy;
            p->next = NULL;
            pre->next = NULL;
            while (q->next && q->next->val < p->val) q = q->next;

            p->next = q->next;
            q->next = p;
            pre->next = k;
        }
        else {
            pre = pre->next;
        }

        p = k;
    }

    return dummy->next;
}

Node** splitParityList(Node* head)
{
    if (head == NULL) return NULL;
    Node** ret = (Node**)malloc(sizeof(Node*) * 2);
    ret[0] = NULL;
    ret[1] = NULL;

    Node* tail = NULL;

    int flag;
    if (head->val % 2 == 0) {
        ret[1] = head;
        flag = 1;
    }else {
        ret[0] = head;
        flag = 0;
    }

    Node* p = head;
    Node* q = head->next;

    //开头是偶数
    while (flag == 1 && q) {
        if (q->val % 2 == 0) {
            p = q;
            q = q->next;
        }else {
            Node* k = q->next;
            p->next = k;

            if (tail == NULL) {
                ret[0] = q;
                tail = q;
            }

            tail->next = q;
            q->next = NULL;
            tail = q;

            q = k;
        }
    }

    //开头是奇数
    while (flag == 0 && q) {
        if (q->val % 2 != 0) {
            p = q;
            q = q->next;
        }
        else {
            Node* k = q->next;
            p->next = k;

            if (tail == NULL) {
                ret[1] = q;
                tail = q;
            }

            tail->next = q;
            q->next = NULL;
            tail = q;

            q = k;
        }
    }

    ret[0] = insertSortLinkList(ret[0]);
    ret[1] = insertSortLinkList(ret[1]);

    return ret;
}

```