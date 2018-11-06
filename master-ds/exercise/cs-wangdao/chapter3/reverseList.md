## Reverse single list

## CHINESE
在单链表中翻转链表 Time O(n) Space O(1).
【不用头插法方式】

**Example 1:**
```
Input :
[11,13,15,17,19]
Output : [19,17,15,13,11]
```

## hints
```
  Strat: dummy -> head -> n1 -> n2 -> n3 -> ...
          pre      p      o

  Step1: dummy -> head    n1 -> n2 -> n3 -> ...
          pre      p       o

  Step2: dummy -> head    n1 -> n2 -> n3 -> ...
                  pre     p     o

  Step3: dummy -> head <- n1 -> n2 -> n3 -> ...
                  pre     p     o
  ...
          →---------------------------------→
          ↑                                 ↓
  Last:  dummy   head  <-n1<-n2<-...<-n <- last  null
                                     pre    p     o
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

Node* reverseList(Node* head){
    if (head == NULL) return NULL;
    Node* dummy = (Node*)malloc(sizeof(Node));
    dummy->val = 10;
    dummy->next = head;

    Node* pre = dummy;
    Node* p = head;
    Node* o = head->next;
    p->next = NULL;

    while (o) {
        pre = p;
        p = o;
        o = o->next;
        p->next = pre;
    }

    dummy->next = p;
    Node* ret = dummy->next;
    free(dummy);
    return ret;
}
```