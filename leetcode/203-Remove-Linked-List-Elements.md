#### Remove all elements from a linked list of integers that have value val.

```
Example:

Input:  1->2->6->3->4->5->6, val = 6
Output: 1->2->3->4->5
```

#### Solutions

1. ##### Straight forward

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


typedef struct ListNode node;

struct ListNode* removeElements(struct ListNode* head, int val){
    if (!head) return head;
    node * cur = head;
    while (cur) {
        while (cur->next && cur->next->val == val)
            cur->next = cur->next->next;
        cur = cur->next;
    }
    return (head->val == val) ? head->next : head;
}
```