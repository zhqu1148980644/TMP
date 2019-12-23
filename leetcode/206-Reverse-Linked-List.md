
#### Reverse a singly linked list.

```
Example:

Input: 1->2->3->4->5->NULL
Output: 5->4->3->2->1->NULL
Follow up:

A linked list can be reversed either iteratively or recursively. Could you implement both?
```





#### Solutions

1. ##### Iteration

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


typedef struct ListNode node;

struct ListNode* reverseList(struct ListNode* head){
    if (!head) return head;
    node * tmp;
    node * next = head->next;
    head->next = NULL;
    while (next) {
        tmp = next->next;
        next->next = head;
        head = next;
        next = tmp;
    }
    return head;
}
```

2. ##### recursion

```c++
typedef struct ListNode node;

struct ListNode* reverse(node * pre, node * cur) {
    if (!cur) return pre;
    node * cur_next = cur->next;
    cur->next = pre;
    return reverse(cur, cur_next);
}

struct ListNode* reverseList(struct ListNode* head){
    return reverse(NULL, head);
}
```