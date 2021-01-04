---
title: Remove Nth Node From End of List
date: 2021-01-04
---
### Given a linked list, remove the n-th node from the end of list and return its head.

### Example:

```
Given linked list: 1->2->3->4->5, and n = 2.

After removing the second node from the end, the linked list becomes 1->2->3->5.
```

### Note:

Given n will always be valid.

### Follow up:

Could you do this in one pass?


### Solutions

1. #### slow and fast pointer

Create a slow pointer n steps before.

```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
    struct ListNode * now1 = head;
    struct ListNode * now2 = head;
    for (int i = 0; i < n; i++) now1 = now1->next;
    if (now1 == NULL) return head->next;
    while (now1->next) {
        now1 = now1->next;
        now2 = now2->next;
    }
    now2->next = now2->next->next;
    return head;
}
```