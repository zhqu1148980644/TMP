---
title: Remove Duplicates from Sorted List
date: 2021-01-04
---
#### Given a sorted linked list, delete all duplicates such that each element appear only once.

```
Example 1:

Input: 1->1->2
Output: 1->2
Example 2:

Input: 1->1->2->3->3
Output: 1->2->3
```

#### Solutions

1. ##### Straight forward

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
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode * left = head;
        while (left && left->next)
            if (left->next->val == left->val)
                left->next = left->next->next;
            else
                left = left->next;
        return head;
    }
};
```