## Delete same val in single list

## CHINESE
在单链表中删除值为x的所有元素的结点.

**Example 1:**
```
Input :[11, 13, 15, 5, 5, 5, 17, 5, 19, 5], x = 5
Output : [11,13,15,17,19]
```

## hints
```
    recursion in single list.
    1.use dummy-node to handle first node.
    2.use recursion, when go back, check the next->val == x? delete it.
```

## Solution
``` c
/**
* Definition for singly-linked list.
* struct Node {
*     int val;
*     struct Node *next;
* }Node;
*/

void deleteSameValInner(Node* head, int x){
    if (head == NULL) return;
    deleteSameValInner(head->next,x);
    if (head->next && head->next->val == x) {
        Node* p = head->next;
        head->next = p->next;
        free(p);
    }
}

Node* recursionDeleteSameVal(Node* head, int x)
{
    Node* dummy = (Node*)malloc(sizeof(Node));
    dummy->next = head;
    dummy->val = x - 1;
    deleteSameValInner(dummy, x);

    Node* ret = dummy->next;
    free(dummy);
    return ret;
}

/*
void deleteSameValInner(Node* head, int x) {
    deleteSameVal(head->next, x);
    if (head->val == x) {
        if (head->next) {
            Node* p = head->next;
            head->next = p->next;
            head->val = p->val;
            free(p);
            p = NULL;
        }else {
            free(head);
        }
    }
}
*/
```