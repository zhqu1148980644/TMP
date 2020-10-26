#### Given a singly linked list, determine if it is a palindrome.

```
Example 1:

Input: 1->2
Output: false
Example 2:

Input: 1->2->2->1
Output: true
```

#### Follow up:
Could you do it in O(n) time and O(1) space?


#### Solutions

1. ##### two pointers

- Fast pointer and slow pointer moves 2 an 1 nodes in each step.
- When the fast pointer moves to the end, the first half of the link list is reversed and the slower pointer is right at the middle(if the length is odd) of the link list.
- Check if the linked list is a palindrome by moving two linked lists simultaneously.

```c++
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
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) return true;

        ListNode * prev = nullptr, * slow = head, * fast = head;
        while (fast && fast->next) {
            // move fast
            fast = fast->next->next;
            // move slow and reverse
            ListNode * next = slow->next;
            slow->next = prev;
            prev = slow;
            slow = next;
        }
        // check if the length is odd
        bool odd = fast != nullptr;
        ListNode * lhead = prev, * rhead = odd ? slow->next : slow;
        prev = slow;

        bool ispalin = true;
        while (lhead) {
            if (lhead->val != rhead->val)
                ispalin = false;
            // move lhead and reverse
            ListNode * next = lhead->next;
            lhead->next = prev;
            prev = lhead;
            lhead = next;
            // move rhead
            rhead = rhead->next;
        }
        
        // if the original list is not required to be preserved, we can:
        // while (lhead) {
        //     if (lhead->val != rhead->val)
        //         return false;
        //     lhead = lhead->next;
        //     rhead = rhead->next;
        // }

        return ispalin;
    }
};
```


2. ##### two pass


- Loop through the linked list to count the length.
- Then reverse the first half of the link list and the following steps are the same as steps in the first method.

```c++
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
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) return true;
        // count the number of nodes
        ListNode * tmp = head;
        int len = 1;
        while (tmp = tmp->next) len++;
        bool odd = len % 2;
        len /= 2;
        // reverse the first half(n // 2) nodes
        ListNode * prev = nullptr;
        while (len--) {
            tmp = head->next;
            head->next = prev;
            prev = head;
            head = tmp;
        }
        // prev is the head of left list
        // head or head->next is the head of right list
        ListNode * lhead = prev, * rhead = odd ? head->next : head;
        prev = head;
        bool ispalin = true;
        while (lhead) {
            if (lhead->val != rhead->val)
                ispalin = false;
            // traverse and reverse left list
            tmp = lhead->next;
            lhead->next = prev;
            prev = lhead;
            lhead = tmp;
            // traverse right list
            rhead = rhead->next;
        }

        return ispalin;
    }
};
```