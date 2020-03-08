### Reverse Nodes in k-Group

### Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

k is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

### Example

```
Given this linked list: 1->2->3->4->5

For k = 2, you should return: 2->1->4->3->5

For k = 3, you should return: 3->2->1->4->5
```

### Note

- Only constant extra memory is allowed.
- You may not alter the values in the list's nodes, only nodes itself may be changed.

### Solutions

1. #### iteration combined with recursion O(n)

- Write a function: At each step, iteratively reverse k-node. Just Ignore the requirement that do not swap when the lasting nodes are smaller than k. In each step:
    - Let pprev point to the pointer: (current head's previous node)->next.
    - Maintain cur and next pointer, For k times: reverse the forward edge within cur and next, then move cur and next one node forward.
    - When we can't move node forward further(moved k times or next is NULL). link two times and reset pprev.

- If the reversed node in the last step are smaller then k, Use the same function reverse back this part of node

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* reverseKGroup(struct ListNode* head, int k){
    struct ListNode * hhead = head;
    struct ListNode ** pprev = &hhead, * cur, * next, *nnext;// pprev is the pointer of (imaginary node)->next. And next points to the current head;
    int reversed;
    // get the current and the next pointer.
    while ((cur = *pprev) && (next = cur->next)) {
        reversed = 0;
        while (++reversed < k && next) {// reverse k - 1 times.
            nnext = next->next;
            next->next = cur;
            cur = next;
            next = nnext;
        }
        // if reversed k - 1 times, set head->next to next; set (prehead->next) to cur;
        head = *pprev;
        head->next = next;
        // this step is essential to use recursion to revsere back the reversed part.
        if (reversed != k) break;
        *pprev = cur;
        pprev = &(head->next);
    }
    // Failed to reverse k - 1 times. reverse these nodes back to normal order. Will only be called once.
    if (reversed && reversed != k) reverseKGroup(cur, reversed);
    return hhead;
}
```

2. #### Iteration O(n)

- Firstly iterate the linked list to get the total length `N`.
- Then reverse k-group `N // k` times using the method in `problem 92`.

```c++
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        int len = 0;
        ListNode * cur = head;
        while (cur && ++len) cur = cur->next;

        ListNode * dummy = new ListNode(0);
        dummy->next = head; head = dummy;
        for (int i = 0; i < len / k; i++) {
            cur = head->next;
            for (int j = 0; j < k - 1; j++) {
                ListNode * tmp = head->next;
                head->next = cur->next;
                cur->next = cur->next->next;
                head->next->next = tmp;
            }
            head = cur;
        }
        return dummy->next;
    }
};
```

Or recall the same function to reverse back the tail.

```c++
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (k <= 1)
            return head;
        ListNode dummy(0); dummy.next = head;
        head = &dummy;
        while (head->next) {
            ListNode * cur = head->next;
            int inserted = 0;
            while (cur->next && inserted < k - 1) {
                ListNode * tmp = head->next;
                head->next = cur->next;
                cur->next = cur->next->next;
                head->next->next = tmp;
                inserted++;
            }
            if (inserted && inserted < k - 1) {
                head->next = reverseKGroup(head->next, inserted + 1);
                // head is no longer the real tail, we must manually exit
                break;
            }
            head = cur;
        }

        return dummy.next;
    }
};
```


3. #### Recursion O(n) S(n)

```c

```