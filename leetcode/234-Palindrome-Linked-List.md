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

- Use a fast pointer and low pointer moves 2 an 1 node in each step and revere the node traversed by the low pointer.
- When the faster moves to the end, the first half of the link list is reversed and the slower pointer is right in the middle of the link list.
- Check if the link list is palindrome start from the center moving oppositely.

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
        ListNode * prev = nullptr, * right = head;
        // reverse the fist half
        while (right && right->next) {
            right = right->next->next;
            ListNode * tmp = head->next;
            head->next = prev;
            prev = head;
            head = tmp;
        }
        // right is the fast pointer, should be at n / 2
        ListNode * lhead = prev;
        prev = head;
        // right is not null means the length is odd, move head one step forward
        if (right)
            head = head->next;
        bool ispalin = true;
        while (lhead) {
            if (lhead->val != head->val)
                ispalin = false;
            ListNode * tmp = lhead;
            lhead = lhead->next;
            tmp->next = prev;
            prev = tmp;
            head = head->next;
        }
        // if no need to reverse back the original list
        // while (lhead && lhead->val == head->val) {
        //     lhead = lhead->next;
        //     head = head->next;
        // }
        // return !lhead;
        return ispalin;
    }
};
```


2. ##### two pass


- Loop through the linked list to count the length.
- Then reverse the first half of the linked list.
- Checking.
- Similar to problem 61, the counterintuitive part is that this method moves the same number of times as the first method.

```c++
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) return true;
        int len = 1;
        ListNode * tmp = head, * prev = nullptr;
        while (tmp = tmp->next) len++;

        bool odd = len % 2;
        len /= 2;
        while (len--) {
            tmp = head->next;
            head->next = prev;
            prev = head;
            head = tmp;
        }
        
        ListNode * lhead = prev;
        prev = head;
        if (odd) head = head->next;
        bool ispalin = true;
        while (lhead) {
            if (lhead->val != head->val)
                ispalin = false;
            ListNode * tmp = lhead;
            lhead = lhead->next;
            tmp->next = prev;
            prev = tmp;
            head = head->next;
        }
        return ispalin;
    }
};
```