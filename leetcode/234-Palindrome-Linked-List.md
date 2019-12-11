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
 *     struct ListNode *next;
 * };
 */

typedef struct ListNode node;

bool isPalindrome(struct ListNode* head){
    if (!head || !head->next) return true;
    node * prev = NULL;
    node * right = head;
    // move and reverse slowly
    // When looping is finished, the head will be at (n + 1) / 2.
    while (right && right->next) {
        right = right->next->next;
        node * tmp = head->next;
        head->next = prev;
        prev = head;
        head = tmp;
    }
    // Right is not NULL means the length of the linked list is even. So we need to move the head one step forward.
    if (right) head = head->next;
    while (prev && (prev->val == head->val)) {
        prev = prev->next;
        head = head->next;
    }
    return !prev;
}
```


2. ##### two pass


- Loop through the linked list to count the length.
- Then reverse the first half of the linked list.
- Checking.
- Similar to problem 61, the counterintuitive part is that the simple one moves the same number of times as the first method.

```c++
typedef struct ListNode node;

bool isPalindrome(struct ListNode* head){
    if (!head || !head->next) return true;
    int length = 1;
    node * tmp = head,  * prev = NULL;
    // count the total length
    while (tmp = tmp->next) length++;

    bool odd = length % 2 == 0;
    length = length / 2;
    // reverse the first half of the linked list.
    while (length--) {
        tmp = head->next;
        head->next = prev;
        prev = head;
        head = tmp;
    }
    // move head one step forward when the length is a even number.
    if (!odd) head = head->next;
    while (prev && (prev->val == head->val)) {
        prev = prev->next;
        head = head->next;
    }
    return !prev;
}
```