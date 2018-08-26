## Union set tow ascending lists

Two linear tables A and B with Pointers of headA and headB represent two sets, respectively.
The elements in both tables are in ascending order.
Please write an algorithm to find the union of A and B AUB.

## CHINESE
指针为ha和hb的两线性表A和B 分别表示两个集合。
两表中的元素皆为递增有序。请写一算法求A和B的并集AUB。
要求该并集中的元素仍保持递增有序。且要利用A和B的原有结点空间。

**Notes**
Requires that the elements in the merge set remain ascending in order.
And we want to use the original node space of A and B.

**Example 1:**
```
Input:
[1,2,3,10]
[1,2,2,2]

Output: [1,2,3,10]
```
**Example 2:**
```
Input:
[2,3,3,4]
[1,4,4,5]

Output: [1,2,3,4,5]
```

## hints
```
    1.front-back pointers to removeDuplicate because of the ordered List.
    2.merge tow lists.

    ps: Alternatively, step2 also can do first , then do step 1, but I think 1->2 is better than 2->1
```

## Analogous
|                         Nav                               |
| :--------------------------------------------------------:|
| ![descendingTowList](descendingTowList.md)                |


## Solution
``` c
/**
* Definition for singly-linked list.
* struct Node {
*     int val;
*     struct Node *next;
* }Node;
*/

Node* removeDuplicate(Node* head){
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

//step1->step2
Node* unionSetTowList(Node* headA, Node* headB) {
    Node* p = removeDuplicate(headA);
    Node* q = removeDuplicate(headB);

    while (p && q) {
        if (q->val == p->val) {
            q = q->next;
            if (p->next == NULL && q != NULL) {
                p->next = q;
                break;
            }else {
                p = p->next;
            }
        }

        if (q->val < p->val) {
            Node* k = q->next;
            q->next = p;
            if (headA->val > q->val) headA = q;
            q = k;
        }
        else {
            if (p->next && p->next->val > q->val) {
                Node* k = p->next;
                Node* s = q->next;
                p->next = q;
                q->next = k;
                p = k;
                q = s;
            }else {
                p = p->next;
            }
        }
    }

    return headA == NULL? headB: headA;

    /*    step2->step1

    Node* p = headA;
    Node* q = headB;
    while (p && q) {
        if (q->val < p->val) {
            Node* k = q->next;
            q->next = p;
            if (headA->val > q->val) headA = q;
            q = k;
        }
        else if(q->val > p->val){
            if (p->next && p->next->val > q->val) {
                Node* k = p->next;
                Node* s = q->next;

                p->next = q;
                q->next = k;
                p = k;
                q = s;
            }else {
                p = p->next;
            }
        }
        else {
            q = q->next;
            if (q != NULL && p->next == NULL) {
                p->next = q;
                break;
            }
            else {
                p = p->next;
            }
        }
    }

    return removeDuplicate(headA);
    */
}
```