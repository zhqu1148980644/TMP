---
title: Swap Nodes in Pairs
date: 2021-01-04
---
### Given a linked list, swap every two adjacent nodes and return its head.

You may not modify the values in the list's nodes, only nodes itself may be changed.



```
Example:

Given 1->2->3->4, you should return the list as 2->1->4->3.
```

### Solutions

1. #### Iteration

- Simplify the logic with a dummy node.

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (!head) return nullptr;
        ListNode dummy {0, head};

        ListNode * cur = &dummy;

        while (cur->next && cur->next->next) {
            ListNode * nnext = cur->next->next;
            cur->next->next = nnext->next;
            nnext->next = cur->next;
            cur->next = nnext;
            cur = nnext->next;
        }

        return dummy.next;
    }
};
```


- Borrowed from stephan.
- The trick of pointer of pointer will be used again in problem 25.

```cpp
// solution.  So so elegant.
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

2. #### recursion

```cpp
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (!head || !head->next)
            return head;
        ListNode * next = head->next;
        head->next = swapPairs(next->next);
        next->next = head;
        return next;
    }
};
```