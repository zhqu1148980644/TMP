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

Do not care about reversion, Store carry when forwarding.

- [] Code below is a little messy.

```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode * p_list = (struct ListNode *) malloc(sizeof(struct ListNode));
    struct ListNode * now = p_list;
    int remain = 0;
    int tmp = 0;
    while (l1 || l2) {
        now->next = (struct ListNode *) malloc(sizeof(struct ListNode));
        now = now->next;
        if (l1 && l2) {
            tmp = l1->val + l2->val + remain;
            l1 = l1->next;
            l2 = l2->next;
        } else if (l1) {
            tmp = l1->val + remain;
            l1 = l1->next;
        } else {
            tmp = l2->val + remain;
            l2 = l2->next;
        } 
        if (remain = tmp / 10)
            now->val = tmp % 10;
        else
            now->val = tmp;
    }
    if (remain) {
        struct ListNode * head = p_list->next;
        now->next = p_list;
        p_list->val = remain;
        p_list->next = NULL;
        return head;
    } else {
        now->next = NULL;
        struct ListNode * head = p_list->next;
        free(p_list);
        return head; 
    }
}
```