---
title: Remove Duplicates from Sorted List II
date: 2021-01-04
---
#### Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.

```
Example 1:

Input: 1->2->3->3->4->4->5
Output: 1->2->5
Example 2:

Input: 1->1->1->2->3
Output: 2->3
```


#### Solutions

1. ##### Straight forward with iteration

- Whenever meet a `cur/head` node, set `cur` to the first node whose next node is different from this node.
- If `cur` node equals to the `head` node, then this is a unique node, link to previous node's next pointer.
- At the end of each iteration, move `head/cur` to `cur`'s next node.

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

typedef struct ListNode node;
struct ListNode* deleteDuplicates(struct ListNode* head){
    if (!head) return NULL;
    node * phead = head, ** pphead = &phead, * cur = head;
    while (cur) {
        // Find the first node whose next node is a different one.
        // if the next node is NULL, this node is unique too.
        while (cur->next && cur->next->val == head->val)
            cur = cur->next;
        // this happens only when the head node is unique.
        if (head == cur) {
            *pphead = head; // set the last node'next to this unique node
            pphead = &(head->next); // reset pointet to pointer
        }
        // move to the next node
        head = cur = cur->next;
    }
    // set the tail to NULL;
    *pphead = NULL;
    return phead;
}
```

Or
- Whenever we meet a `cur` node, check if it's unique.
- If this node is unique:
    - link the previous node's next pointer to this unique node.
- If this node is not unique:
    - get to the first node whose next node is different.
- At the end of each iteration, move `cur` to `cur`'s next node.


```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


typedef struct ListNode node;
struct ListNode* deleteDuplicates(struct ListNode* head){
    if (!head) return NULL;
    node ** pphead = &head, * cur = head;
    while (cur) {
        // if this node is not unique.
        if (cur->next && cur->next->val == cur->val) {
            cur = cur->next; // you can just comment this line.
            while (cur->next && cur->next->val == cur->val)
                cur = cur->next;
        // link prev->next to this node if it's unique
        } else {
            *pphead = cur;
            pphead = &(cur->next);
        }
        // always get to the next node
        cur = cur->next;
    }
    // set the tail to NULL;
    *pphead = NULL;
    return head;
}
```


2. ##### recursion

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
typedef struct ListNode node;

node * nextUniqNode(node * head) {
    if (!head || !head->next) return head;
    if (head->next->val == head->val) {
        while (head->next && head->next->val == head->val)
            head = head->next;
        head = nextUniqNode(head->next);
    } else
        head->next = nextUniqNode(head->next);

    return head;
}

struct ListNode* deleteDuplicates(struct ListNode* head){
    return nextUniqNode(head);
}
```
