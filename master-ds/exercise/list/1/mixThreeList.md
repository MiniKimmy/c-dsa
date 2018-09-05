## MixSetion 3 ascending Lists

Given 3 single-list A,B and C with ascending order
designed algorithm let A = A U (B ∩ C), and keep A is still ascending.

## CHINESE
已知递增有序的单链表A,B和C分别存储了一个集合，设计算法
实现A = A U (B∩C)，并使求解结构A仍保持递增。

**Example 1:**
```
Input:
[1,2,3,5]
[1,2,2,3,5]
[1,3,3,4,5]

Output: [1,2,3,5]
```
**Example 2:**
```
Input:
[1,2,3,5,7,7,8,8,8]
[2,4,4,6]
[1,2,4,5]

Output: [1,2,3,4,5,7,8]
```
**Example 3:**
```
Input:
[1,2,5,5,5]
[1,2,3,4,5]
[2,2,4,4,5]

Output: [1,2,5]
```

**Note**
The time complexity of the algorithm is required to be O(|A|+|B|+|C|).

## hints
![reverseList](../../../../leetcode/easy/206/reverseList.md) : leetcode的一道题.
```
    1. Time Complexity O(n) S = "B∩C" && O(n) ret = "AUS".So I use malloc "ret".
    2. when "AUS" in the end, we need to removeDuplicate(A).
```

## Analogous
|                  Nav                  |              Des              |
|:-------------------------------------:|:-----------------------------:|
|![unionSetTowList](unionSetTowList.md) |将2个升序的链表A∪B为1个链表    |
|![interSetTowList](interSetTowList.md) |将2个升序的链表A∩B为1个链表    |
|![differentSetTowList](differentSetTowList.md)|将2个升序的链表求出其差集链表 |

## Solution
``` c
/**
* Definition for singly-linked list.
* struct Node {
*     int val;
*     struct Node *next;
* }Node;
*/

Node* removeDuplicate(Node* head) {
    if (head == NULL) return NULL;
    Node* p = head;
    Node* q = head->next;

    while (q) {
        if (q->val == p->val) {
            Node* t = q;
            q = q->next;
            p->next = q;
            free(t);
            t = NULL;
        }
        else {
            p = q;
            q = q->next;
        }
    }

    return head;
}

Node* interTowList(Node* headA, Node* headB) {
    if (headA == NULL || headB == NULL) return NULL;

    Node* p = headA;
    Node* q = headB;
    int flag = 0;

    while (p && q) {
        if (q->val < p->val) {
            q = q->next;
        }

        else if(q->val > p->val) {
            if (flag == 1) {
                if (p->next->val < q->val) {
                    Node* k = p->next;
                    p->next = k->next;
                    free(k);
                    k = NULL;
                }
            }else if (p == headA) headA = headA->next;

            p = p->next;
        }

        else {
            q = q->next;
            flag = 1;
        }
    }

    if (q == NULL && p != NULL) p->next = NULL;
    return headA;
}

Node* unionTowList(Node* headA, Node* headB) {
    Node* p = headA;
    Node* q = headB;
    Node* ret = (Node*)malloc(sizeof(Node));
    Node* tail = ret;

    while (p && q) {
        if (q->val == p->val) {
            tail->next = q;
            q = q->next;
            tail = tail->next;
            tail->next = NULL;
            p = p->next;
        }else if (q->val > p->val) {
            int temp = p->val;
            while (p->val == temp) {
                if (p->next && p->next->val == temp) {
                    p = p->next;
                }else {
                    break;
                }
            }

            tail->next = p;
            p = p->next;
            tail = tail->next;
            tail->next = NULL;
        }else {
            tail->next = q;
            q = q->next;
            tail = tail->next;
            tail->next = NULL;
        }
    }

    if (q == NULL && p != NULL) {
        Node* result = removeDuplicate(p);
        tail->next = result;
    }

    return ret->next;
}

Node* mixThreeList(Node* headA, Node* headB, Node* headC) {
    Node* result = interTowList(headB, headC);
    Node* ret = unionTowList(headA, result);
    return ret;
}

```