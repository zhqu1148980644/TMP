---
title: Plus One Linked List
date: 2021-01-04
---
Given a non-negative integer represented as non-empty a singly linked list of digits, plus one to the integer.

You may assume the integer do not contain any leading zero, except the number 0 itself.

The digits are stored such that the most significant digit is at the head of the list.

Example :

Input: [1,2,3]
Output: [1,2,4]


#### Solutions

1. ##### recursion

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
    int add(ListNode * head) {
        if (!head) return 1;
        int remain = add(head->next);
        if ((head->val += remain) > 9) {
            head->val = 0;
            return 1;
        }
        else
            return 0;
    }
    ListNode* plusOne(ListNode* head) {
        if (!head) return nullptr;
        int remain = add(head);
        return remain ? new ListNode {1, head} : head;
    }
};
```


2. ##### iteration

- Borrowed from the official answer
- The idea is to increase the last `non-9` digit by 1, then set all `9` after it to 0.

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
    ListNode* plusOne(ListNode* head) {
        if (!head) return nullptr;
        ListNode * cur = head, * non_nine = nullptr;
        head = cur;
        // find the last non-9
        while (cur) {
            if (cur->val != 9)
                non_nine = cur;
            cur = cur->next;
        }

        if (!non_nine) {
            head = new ListNode(1, head);
            non_nine = head;
        }
        else
            non_nine->val++;

        while (non_nine->next) {
            non_nine->next->val = 0;
            non_nine = non_nine->next;
        }
        

        return head;
    }
};
```