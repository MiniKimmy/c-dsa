## Is Symmetrical list

Given a sigle-list, judge the elements of list  whether it is symmetrical element.

## CHINESE <br/>
设单链表的表头指针为head,判断该链表的所存储的字母元素是否中心对称.<br/>

**Example 1:**
```
Input:"xyx"
OutPut:true
```
**Example 2:**
```
Input:"xykyx"
OutPut:true
```
**Example 3:**
```
Input:"xyxy"
OutPut:false
```
**Example 4:**
```
Input:"xyxyx"
OutPut:true
```
**Example 5:**
```
Input:"a"
OutPut:true
```
**Example 5:**
```
Input:"ab"
OutPut:false
```

## hints
![reverseList](../../../../leetcode/easy/206/) : leetcode的一道题.
```
    1.copy List as new ListA and reverseList as ListB.
    2.check the elemets ListA == ListB
```

## Analogous
|                         Nav            |                   Des                 |
| :-------------------------------------:|:-------------------------------------:|
| ![validPalindrome](../../../../leetcode/easy/680/) |数组对称(允许删除其中某1个元素)  |
| ![isPalindrome](../../../../leetcode/easy/234/) |回文链表                         |


## Solution
``` c
/**
* Definition for singly-linked list.
* struct Node {
*     char val;
*     struct Node *next;
* }Node;
*/

/*true return 1, false return 0*/
int isSymmetrical(Node* head) {
    if (head == NULL) return 0;

    Node* list = (Node*)malloc(sizeof(Node));
    list->next = NULL;
    list->val = head->val;
    Node* tail = list;
    Node* p = head;

    //copy "head-list" to "list"
    while (p->next) {
        Node* node = (Node*)malloc(sizeof(Node));
        node->next = NULL;
        node->val = p->next->val;
        tail->next = node;
        tail = node;
        p = p->next;
    }

    Node* q = head;
    while (q != p) {
        Node* k = q->next;
        q->next = NULL;

        Node* o = p->next;
        p->next = q;
        q->next = o;
        q = k;
    }

    p = list;
    while (q) {
        if (q->val != p->val) {
            //dispose list
            while (list) {
                Node* temp = list->next;
                free(list);
                list = temp;
            }

            return 0;
        }
        q = q->next;
        p = p->next;
    }

    //dispose list
    while (list) {
        Node* temp = list->next;
        free(list);
        list = temp;
    }

    return 1;
}
```