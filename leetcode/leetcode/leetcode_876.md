---
title: Middle of the Linked List
date: 2021-01-04
---
#### Given a non-empty, singly linked list with head node head, return a middle node of linked list.

If there are two middle nodes, return the second middle node.

 

```
Example 1:

Input: [1,2,3,4,5]
Output: Node 3 from this list (Serialization: [3,4,5])
The returned node has value 3.  (The judge's serialization of this node is [3,4,5]).
Note that we returned a ListNode object ans, such that:
ans.val = 3, ans.next.val = 4, ans.next.next.val = 5, and ans.next.next.next = NULL.

Example 2:

Input: [1,2,3,4,5,6]
Output: Node 4 from this list (Serialization: [4,5,6])
Since the list has two middle nodes with values 3 and 4, we return the second one.
```

 

#### Note:

- The number of nodes in the given list will be between 1 and 100.


#### Solutions

1. ##### two pointers

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
    ListNode* middleNode(ListNode* head) {
        ListNode * fast = head;
        while (fast && fast->next) {
            head = head->next;
            fast = fast->next->next;
        }
        return head;
    }
};
```

2. ##### two pass

```cpp
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        int len = 0;
        ListNode * tmp = head;
        while (tmp && ++len) tmp = tmp->next;

        len /= 2;
        while (len--)
            head = head->next;
        return head;
    }
};
```