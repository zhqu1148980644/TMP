---
title: Reorder List
date: 2021-01-04
---
#### Given a singly linked list L: L0→L1→…→Ln-1→Ln,
reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…

You may not modify the values in the list's nodes, only nodes itself may be changed.

```
Example 1:

Given 1->2->3->4, reorder it to 1->4->2->3.
Example 2:

Given 1->2->3->4->5, reorder it to 1->5->2->4->3.
```

#### Solutions

1. ##### reverse then merge

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

typedef struct ListNode node;

void reorderList(struct ListNode* head){
    if (!head) return head;
    node * slow = head, * fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast =fast->next->next;
    }
    node * pre = NULL, * cur = slow->next;
    slow->next = NULL;
    // reverse the last half
    while (cur) {
        node * tmp = cur->next;
        cur->next = pre;
        pre = cur; cur = tmp;
    }
    // merge version
    // slow = head->next; fast = pre;
    // while (fast) {
    //     head->next = fast; fast = fast->next;
    //     head = head->next;
    //     head->next = slow; slow = slow->next;
    //     head = head->next;
    // }
    // return;

    // insert version
    slow = head; fast = pre;
    while (fast) {
        node * pre = fast->next;
        fast->next = slow->next;
        slow->next = fast;
        fast = pre;
        if (!slow->next->next) break;
        else slow = slow->next->next;
    }
    return;
}
```