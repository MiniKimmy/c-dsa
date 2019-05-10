## 138. Copy List with Random Pointer
[这里](https://leetcode.com/problems/copy-list-with-random-pointer/)

## hints1
* ![参考](../../../../leetcode/medium/138/copyRandomList.md)
* [youtube_VedioTutorial](https://www.youtube.com/watch?time_continue=911&v=OvpKeraoxW0)
## Solution1
``` cpp
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(!head) return NULL;

        Node* p = head;
        while(p)
        {
            Node* copy = new Node (p->val,p->next, NULL);
            p->next = copy;
            p = p->next->next;
        }

        p = head;
        while(p){
            if(p->random) p->next->random = p->random->next;
            p = p->next->next;
        }

        p = head;
        Node* ret = p->next;
        while(p)
        {
            Node* t = p->next->next;
            if(p->next->next) p->next->next = t->next;
            p->next = t;
            p = t;
        }

        return ret;
    }
};
```
## hints2
* use "for" replace "while"
## Solution2
``` csharp
public class Solution {
    public Node CopyRandomList(Node head) {
        if(head == null) return null;

        for(Node p = head; p!= null;p=p.next){
            Node copy = new Node(p.val,p.next,null);
            p.next = copy;
            p=p.next;
        }

        for(Node p = head;p!=null;p=p.next){
            if(p.random != null) p.next.random = p.random.next;
            p = p.next;
        }

        Node ret = head.next;
        for(Node p=head;p!=null;p=p.next){
            Node t = p.next.next;
            if(t != null) p.next.next = t.next;
            p.next = t;
        }

        return ret;
    }
}
```