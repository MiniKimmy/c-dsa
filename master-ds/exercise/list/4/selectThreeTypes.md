## Select Character

Given a single list with type of "char" element, and select alphabet,digit,other character of it, and use 3 circle list to store the same kind value.

## CHINESE
给定一个单链表L(char val, struct Node* next),每个结点数据域存放一个字符,该字符可能是英文字母字符或数字字符或其它字符,请构造3个单循环链表,这3个链表各自只存同一类字符元素.（要求用最少的时间和最少的空间）

**Example 1:**
```
Input : ['a','b','2','#']
OutPut: ['a','b']
['2']
['#']
```
**Example 2:**
```
Input : ['s','d']
OutPut: ['s','d']
[]
[]
```

## hints
```
    use 3 dummy pointers and 3 tail-pointers to select characters.
    Finally, combine with head-tail as circleLink.
```

## Analogous
|                         Nav            |                   Des                 |
| :-------------------------------------:|:-------------------------------------:|
| ![splitParityList](splitParityList.md)|把链表分成2个升序链表(偶数链,奇数链)    |
| ![putMinusForward1](../5/putMinusForward.md)|把负数放在正数前面(数组)          |
| ![splitNums](splitNums.md)              |以某个值为参考将数组分成2半           |

## Solution
``` c
/**
* Definition for singly-linked list.
* struct Node {
*     int val;
*     struct Node *next;
* }Node;
*/

int isCharacter(char c) {
    int a = (int)c;
    if ((a >= 65 && a <= 90) || (a >= 97 && a <= 122)) return 1;
    else return 0;
}

int isDigit(char c) {
    int a = (int)c - '0';
    if (a >= 0 && a <= 9) return 1;
    else return 0;
}

void selectThreeTypes(Node* head,Node** retCharacter, Node** retDigit, Node** other) {
    if (head == NULL) return NULL;

    Node* dummyA = (malloc(sizeof(Node)));
    Node* pA = dummyA;
    pA->next = NULL;

    Node* dummyB = (malloc(sizeof(Node)));
    Node* pB = dummyB;
    pB->next = NULL;

    Node* dummyC = (malloc(sizeof(Node)));
    Node* pC = dummyC;
    pC->next = NULL;

    Node* p = head;
    while (p) {
        Node* q = p->next;
        if (isCharacter(p->val) == 1) {
            pA->next = p;
            pA = p;
        }else if(isDigit(p->val) == 1){
            pB->next = p;
            pB = p;
        }else {
            pC->next = p;
            pC = p;
        }
        p->next = NULL;
        p = q;
    }

    *retCharacter = dummyA->next;
    *retDigit = dummyB->next;
    *other = dummyC->next;

    pA->next = *retCharacter;
    pB->next = *retDigit;
    pC->next = *other;

    free(dummyA);
    free(dummyB);
    free(dummyC);
    return ;
}
```