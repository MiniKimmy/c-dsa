## Put Minor to the front of the list

Given a single-list, list-val has negative and positive,
set all the minor val to the front of the list.

## CHINESE
已知线性表（a1 a2 a3 …an）,an有正数有负数也有零.<br />
试设计用最少时间把所有值为负数的元素移到全部正数值元素前边.(不包括零)<br />

**Example :**
```
Input: [-7,-3,6,0,-5,4,0,-1]
Output: [-7,-3,-5,-1,6,4]
```

## hints
![splitPositiveAndNegativeList](splitPositiveAndNegativeList.md) : 基本一样的思路
```
    1.split negative-list and positive-list
    2.connect them again.
```

## Analogous
|                         Nav            |                   Des                 |
| :-------------------------------------:|:-------------------------------------:|
| ![splitParityList](splitParityList.md)|把链表分成2个升序链表(偶数链,奇数链)    |
| ![putMinusForward1](../5/putMinusForward.md)|把负数放在正数前面(数组)          |
| ![selectThreeTypes](selectThreeTypes.md)|把1个单链表分类为3个循环单链表        |

## Solution
```c
/**
* Definition for singly-linked list.
* struct Node {
*     int val;
*     struct Node *next;
* }Node;
*/

Node* moveNegativeToTheFront(Node* head)
{
    if (head == NULL) return NULL;
    Node** ret = (Node**)malloc(sizeof(Node*) * 2);
    ret[0] = NULL;  //negative-list
    ret[1] = NULL;  //positive-list

    Node* tail = NULL;

    int flag;
    if (head->val > 0) {
        ret[1] = head;
        flag = 1;
    }else {
        ret[0] = head;
        flag = 0;
    }

    Node* p = head;
    Node* q = head->next;

    //开头是正数
    while (flag == 1 && q) {
        if (q->val > 0) {
            p = q;
            q = q->next;
        }else if(q->val < 0){
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
        else {
            Node* k = q->next;
            p->next = k;
            free(q);
            q->next = NULL;
            q = k;
        }
    }

    //开头是负数
    while (flag == 0 && q) {
        if (q->val < 0) {
            p = q;
            q = q->next;
        }
        else if(q->val > 0){
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
        else {
            Node* k = q->next;
            p->next = k;
            free(q);
            q->next = NULL;
            q = k;
        }
    }

    if (flag == 0) {
        p->next = ret[1];
    }else {
        tail->next = ret[1];
    }

    return flag==0?head:ret[0];
}

```