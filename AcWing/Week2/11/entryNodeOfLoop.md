## 34. 链表中环的入口结点

给定一个链表，若其中包含环，则输出环的入口节点。
若其中不包含环，则输出null。

**Example :**
```
Input:[1, 2, 3, 4, 5, 6],2
Output:3
Explanation:2表示在第[2]个结点上出现环的起点，结点从0开始数。返回3是返回第[2]个结点的val
```
## hints
```
             ______________
             ↓            ↑
    A--------B-----D------C
    ↑____x___↑__y__↑

A:链表起点
B:环的起点
C:环的最后一个点,c->next == B
D:第一次相遇（快慢指针）
ps:x表示x步，y表示y步.

原理：1.第一次相遇的时候在D点,slow走了x+y，fast走了2*(x+y)
      2.slow往回走y步回到B点
      3.fast往回走2y步时候此时fast走了2x；2x表明x+x，在slow到达B的时候,fast已经在圈里走了x步
      4.那么当slow到达B的时候，fast与slow距离y（因为再移动y次就相遇）
      5.那么当相遇的时候,在D点slow再走x步就会回到B点.
      （因为fast在圈里走了x步且与slow在B的距离是y）
      即slow从B->D的已经走了y步（相遇），slow再走x步（slow重新走fast之前在圈里走过的x步）
```
## Solution
``` c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* entryNodeOfLoop(struct ListNode *head) {
    if(head == NULL) return NULL;

    struct ListNode* fast = head->next;
    struct ListNode* slow = head;

    // 默认一开始fast走2步，slow走1步
    while(fast && slow){
        slow = slow->next;
        fast = fast->next? fast->next->next:NULL;

        // 相遇之后，重置2个指针的位置.
        if(fast == slow){
            fast = head;
            slow = slow->next; // fast回到head的时候（默认已经走了1步），所以slow->next同步这1步。

            // 每次只走1步
            while(fast != slow){
                fast = fast->next;
                slow = slow->next;
            }
            return slow;  //return fast;也可以
        }
    }

    return NULL;
}

```