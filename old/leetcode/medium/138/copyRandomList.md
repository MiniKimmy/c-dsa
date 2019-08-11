## 138. Copy List with Random Pointer
[这里](https://leetcode.com/problems/copy-list-with-random-pointer/)
A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.

Return a deep copy of the list.

## hints
```
1. Iterate the original list and duplicate each node. The duplicate
of each node follows its original immediately.
2. Iterate the new list and assign the random pointer for each
duplicated node.
3. Restore the original list and extract the duplicated nodes.

ex:
original list：A->B->C->D
copy list:A'、B'、C'、D'
part1: A->A'->B->B'->C->C'->D->D'->null
part2: set original list randoms ptr to copy list
part3: Restore the original list and copy list
like: A->B->C->D->null 、A'->B'->C'->D'->null
```

## Solution
``` csharp
/*
// Definition for a Node.
public class Node {
    public int val;
    public Node next;
    public Node random;

    public Node(){}
    public Node(int _val,Node _next,Node _random) {
        val = _val;
        next = _next;
        random = _random;
}
*/
public class Solution {
    public Node CopyRandomList(Node head) {
        if(head == null) return head;

        // A->A'->B->B'->C->C'->D->D'->null
        Node p = head;
        while(p != null)
        {
            Node copy = new Node(p.val,p.next,null);
            p.next = copy;
            p = p.next.next;
        }

        p = head;


        while(p != null)
        {
            if(p.random != null) p.next.random = p.random.next;
            p = p.next.next;
        }


        p = head;
        Node ret = p.next;
        Node q = ret;
        while(p != null)
        {
            Node t = p.next.next;
            if(p.next.next != null) p.next.next = t.next;
            p.next = t;
            p = t;
        }

        return ret;
    }
}
```