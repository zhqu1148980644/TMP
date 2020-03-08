### Given a linked list, swap every two adjacent nodes and return its head.

You may not modify the values in the list's nodes, only nodes itself may be changed.

 

```
Example:

Given 1->2->3->4, you should return the list as 2->1->4->3.
```

### Solutions

1. #### Iteration

- Borrowed from stephan.
- The trick of pointer of pointer will be used again in problem 25.

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
// solution.  So so beautiful.
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode **pre = &head, *a, *b;
        while ((a = *pre) && (b = a->next)) {
            a->next = b->next;
            b->next = a;
            *pre = b; // change last pointer(x->next)'s value. 
            pre = &(a->next);
        }
        return head;
    }
};
```

2. #### recursion.