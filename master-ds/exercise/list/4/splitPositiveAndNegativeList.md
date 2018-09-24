## Split a single-list in Positive-list And Negative-list

Given a single-list "A", split "A" with in two lists "B" AND "C"
"B" is Negative-list,"C" is Positive-list.

## CHINESE
设计算法将一个带头结点的单链表A分解为两个具有相同结构的链表B、C，
其中B表的结点为A表中值小于零的结点(负数链)
而C表的结点为A表中值大于零的结点(正数链）

**Example :**
```
Input:
[-7,-3,6,0,-5,4,0,-1]

Output: [-7,-3,-5,-1],[6,4]
```

## hints
```
    classify 2 situation.
    1.first element >0 or first element >0
    2.and then handle val > 0, val<0 , val == 0.
```

**Note** <br />
List-B and List-C only can use List-A's Nodes。<br />

## Analogous
|                         Nav            |                   Des                    |
| :-------------------------------------:|:----------------------------------------:|
| ![splitParityList](splitParityList.md) |把链表分成2个升序链表(偶数链,奇数链)      |
| ![moveNegativeToTheFront](moveNegativeToTheFront.md)|将链表的负数val移置链表前面  |
| ![splitP&NList](splitPositiveAndNegativeList.md)|把链表分成2个链表(正数链,负数链) |
| ![selectThreeTypes](selectThreeTypes.md)|把1个单链表分类为3个循环单链表           |

## Solution
``` c
/**
* Definition for singly-linked list.
* struct Node {
*     int val;
*     struct Node *next;
* }Node;
*/

Node** splitPositiveAndNegativeList(Node* head)
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

    return ret;
}

```