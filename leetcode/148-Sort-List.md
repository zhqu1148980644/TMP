##### Sort a linked list in O(n log n) time using constant space complexity.

```
Example 1:

Input: 4->2->1->3
Output: 1->2->3->4
Example 2:

Input: -1->5->3->4->0
Output: -1->0->3->4->5
```

#### Solutions

1. ##### iterative merge sort O(nlog(n)) S(1)

- from bottom to up, start from merging 2 nodes, 4 nodes .....
- The outer for loop will execute `log(n)` times.
- In each for loop, `findTaill` will taverse the whole linked list in `O(n)` time and merge two sorted sublist will cost `O(n)` time, thus the total time is asymptotic `O(n)`.
- The final result is `n(nlog(n))`.

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    // merge two sorted lists and return the tail node
    ListNode * merge(ListNode * l, ListNode * r, ListNode * head) {
        if (!head) return nullptr;
        while (l && r) {
            if (l->val <= r->val) {
                head = head->next = l;
                l = l->next;
            }
            else {
                head = head->next = r;
                r = r->next;
            }
        }
        head->next = l ? l : r;
        while (head->next)
            head = head->next;
        return head;
    }

    // move node forward and 
    // return tail's next as the next head
    // set the tail's next to nullptr
    ListNode * forward(ListNode * head, int step) {
        ListNode * tail = nullptr;
        while (step && head) {
            tail = head;
            head = head->next;
            step--;
        }
        if (tail) tail->next = nullptr;
        return head;
    }

    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode * cur = head;
        int len = 0;
        while (cur && ++len) cur = cur->next;
        // tail represents the tail node of former nodes
        // cur repreents the head of the current nodes
        ListNode dummy(0, head), * h1, * h2;
        for (int step = 1; step < len; step *= 2) {
            ListNode * tail = &dummy;
            ListNode * cur = tail->next;
            while (cur) {
                h1 = cur;
                h2 = forward(h1, step);
                cur = forward(h2, step);
                tail = merge(h1, h2, tail);
            }
        }

        return dummy.next;
    }
};
```

The python version seems non-pythonic and with approximately the same length of codes.

```python
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None


class Solution:
    def sortList(self, head: ListNode) -> ListNode:
        def split(head, step):
            curstep = 1
            while head and (curstep < step):
                head, curstep = head.next, curstep + 1
            if head:
                head.next, head = None, head.next
            return head

        def merge(l, r, head):
            while l and r:
                if r.val < l.val:
                    head.next, r= r, r.next
                else:
                    head.next, l = l, l.next
                head = head.next

            head.next = l = l if l else r
            while l.next: l = l.next

            return l

        cur, length = head, 0
        while cur:
            cur, length = cur.next, length + 1

        hhead = ListNode(0)
        hhead.next = head
        step = 1
        while step < length:
            head, cur = hhead, hhead.next
            while cur:
                left = cur
                right = split(left, step)
                cur = split(right, step)
                head = merge(left, right, head)
            step *= 2

        return hhead.next
```

2. ##### recursive merge sort O(nlog(n)) S(log(n))

- Does not satisfy the O(1) sapce requirement.
- Recursively sovle two subproblem using divide and conquer strategy.

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode * slow = head, * fast = head;
        // find the midpoint
        while (fast->next && fast->next->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        fast = slow->next;
        slow->next = nullptr;
        slow = head;
        // solve two subproblem
        slow = sortList(slow); 
        fast = sortList(fast);
        // merge two sorted list
        ListNode dummy; head = &dummy;
        while (slow && fast) {
            if (slow->val <= fast->val) {
                head = head->next = slow;
                slow = slow->next;
            }
            else {
                head = head->next = fast;
                fast = fast->next;
            }
        }
        head->next = slow ? slow : fast;

        return dummy.next;   
    }
};
```
