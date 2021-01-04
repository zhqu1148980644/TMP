---
title: Add Two Numbers
date: 2021-01-04
---
### You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

### Example

```
Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
Explanation: 342 + 465 = 807.
```


### Solutions

1. #### straight forward

- Emulate the process of adding two numbers. Do not care about reversion, Store carry when forwarding.


```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


typedef struct ListNode Node;
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    if (!l1 && !l2) return NULL;
    Node dummy = {0, 0};
    Node * prev = &dummy;
    int remain = 0;
    while (l1 || l2 || remain) {
        if (l1) {
            remain += l1->val;
            l1 = l1->next;
        }
        if (l2) {
            remain += l2->val;
            l2 = l2->next;
        }
        Node * cur = (Node *) malloc(sizeof(Node));
        prev->next = cur; prev = cur;
        if (remain / 10) {
            cur->val = remain % 10;
            remain = remain / 10;
        }
        else {
            cur->val = remain;
            remain = 0;
        }
    }

    prev->next = NULL;
    return dummy.next;;
}
```