## Recursion delete single list

## CHINESE
使用递归的方式,删除单链表中值为x的元素

**Example 1:**
```
Input: [11,5,5,5,13,5,15,17,19,5],5
Output: [11,13,15,17,19]
```

## hints
```
    1.traverse list to the tail
        ex:A-B-C-D-E-F-G,  find 'G'
    2.when recursion back, F-E-D-C-B-A,
    check the node-next->val
        ex:F->G->data,
        ex:E->F->data,
                     ...

    3.free(target).
```

## Solution
``` c
Node* recursionDelSListInner(Node* head, int x) {

    if (head == NULL) return NULL;
    recursionDelSListInner(head->next, x);

    if (head->next && head->next->val == x) {
        Node* p = head->next;
        head->next = p->next;
        free(p);
        p = NULL;
    }
}

Node* recursionDelSList(Node* head, int x)
{
    Node* dummy = (Node*)malloc(sizeof(Node));
    dummy->val = x - 1;
    dummy->next = head;

    recursionDelSListInner(dummy, x);
    return dummy->next;
}
```