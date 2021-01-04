---
title: Linked List Random Node
date: 2021-01-04
---
Given a singly linked list, return a random node's value from the linked list. Each node must have the same probability of being chosen.

Follow up:
What if the linked list is extremely large and its length is unknown to you? Could you solve this efficiently without using extra space?

Example:

// Init a singly linked list [1,2,3].
ListNode head = new ListNode(1);
head.next = new ListNode(2);
head.next.next = new ListNode(3);
Solution solution = new Solution(head);

// getRandom() should return either 1, 2, or 3 randomly. Each element should have equal probability of returning.
solution.getRandom();

#### Solutions

1. ##### Reservoir Sampling

- Each element will be selected with probability `m/n`.

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    /** @param head The linked list's head.
        Note that the head is guaranteed to be not null, so it contains at least one node. */
    ListNode * head, * cur;
    Solution(ListNode* head) {
        this->head = cur = head;
    }
    
    /** Returns a random node's value. */
    int getRandom() {
        int cnt = 2;
        cur = head->next;
        int val = head->val;
        while (cur) {
            // m equal to 1, use a single value to represent it
            if (rand() % cnt == 0) val = cur->val;
            cur = cur->next; cnt++;
        }
        return val;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(head);
 * int param_1 = obj->getRandom();
 */
```