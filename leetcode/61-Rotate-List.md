### Given a linked list, rotate the list to the right by k places, where k is non-negative.

```
Example 1:

Input: 1->2->3->4->5->NULL, k = 2
Output: 4->5->1->2->3->NULL
Explanation:
rotate 1 steps to the right: 5->1->2->3->4->NULL
rotate 2 steps to the right: 4->5->1->2->3->NULL
Example 2:

Input: 0->1->2->NULL, k = 4
Output: 2->0->1->NULL
Explanation:
rotate 1 steps to the right: 2->0->1->NULL
rotate 2 steps to the right: 1->2->0->NULL
rotate 3 steps to the right: 0->1->2->NULL
rotate 4 steps to the right: 2->0->1->NULL
```

### Solutions

1. two pinters

```c++
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head || !head->next || !k) return head;
        ListNode * right = head;
        int remain = k;
        while (remain && right->next) {
            right = right->next;
            remain--;
        }
        if (!remain) {
            ListNode * left = head;
            while (right->next) {
                left = left->next;
                right = right->next;
            }
            right->next = head;
            right = left->next;
            left->next = NULL;
            return right;
        } else
            return rotateRight(head, k % (k - remain + 1));
    }
};
```

2. first count the length then rotate

- This simple method seems contain more useless opeation for counting the length, however these two solutions move the same number of times.

```c++
class Solution {
public:
    ListNode * rotateRight(ListNode * head, int k) {
        if (!head || !head->next || !k) return head;
        ListNode * tail = head;
        int len = 1;
        while (tail->next) {
            tail = tail->next;
            len++;
        }

        if ((k = k % len)) {
            tail->next = head;
            for (int i = 0; i < len - k; i++) {
                tail = tail->next;
            }
            head = tail->next;
            tail->next = NULL;
        }
        return head;
    }
};
```