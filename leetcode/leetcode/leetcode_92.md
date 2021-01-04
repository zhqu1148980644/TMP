---
title: Reverse Linked List II
date: 2021-01-04
---
#### Reverse a linked list from position m to n. Do it in one-pass.

#### Note: 
1 ≤ m ≤ n ≤ length of list.

```
Example:

Input: 1->2->3->4->5->NULL, m = 2, n = 4
Output: 1->4->3->2->5->NULL
```


#### Solutions

1. ##### Iteration. reverse link one by one

- This is a simplified reverse-nodes-in-k-group problem(25). ie: reverse-nodes-in-k-group one time.
- Just copy paste the reverse-k nodes code

```cpp
typedef struct ListNode node;
struct ListNode* reverseBetween(struct ListNode* head, int m, int n){
    node * next, * nnext, * hhead = head, ** pprev = &hhead;
    n = n - m; m -= 1;
    while (m--) pprev = &((*pprev)->next);
    head = *pprev; next = head->next;
    // reverse link one by one
    while (n--) {
        nnext = next->next;
        next->next = head;
        head = next;
        next = nnext;
    }
    // relink
    (*pprev)->next = next;
    *pprev = head;

    return hhead;
}
```


2. ##### Iterration. insertion

- Borrowed from others.
- Set the former node of the m'th(1 based) node as the `head` node or docking point.
- Set the m'th node as `cur` node.
- In each step, insert the `cur node's next node` after the `head` node. The head node and cur node are not changed during the whole process.
- After inserted `n - m` times, reversion done.
- In this pespective, it's easy to rewrite `reverse-list-in-k-group` quickly and concisely with the same idea.

```cpp
typedef struct ListNode node;
struct ListNode* reverseBetween(struct ListNode* head, int m, int n){
    node dummpy = {0, head}, * cur;
    head =  &dummpy;
    for (int i = 0; i < n; i++) {
        if (i < m - 1)
            head = head->next;
        else if (i == m - 1)
            cur = head->next;
        else {
            node * tmp = head->next;
            head->next = cur->next;
            cur->next = cur->next->next;
            head->next->next = tmp;
        }
    }
    return dummpy.next;
}
```


3. ##### Recursion
