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
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

typedef ListNode node;

class Solution {
private:
    // Find the sublist's tail and return
    // Set next to NULL to mark the end of the sublist that will be used in merge.
    node * split(node * head, int n) {
        for (int i = 1; head && i < n; i++)
            head = head->next;
        if (head) {
            node * tail = head->next;
            head->next = NULL;
            return tail;
        } else
            return NULL;
    }
    // merge two sorted list. head is the pointer of the node before left.
    node * merge(node * l, node * r, node * head) {
        while (l && r) {
            if (r->val < l->val) {
                head->next = r; r = r->next;
            } else {
                head->next = l; l = l->next;
            }
            head = head->next;
        }
        // can not be both NULL
        l = l ? l : r; head->next = l;
        while (l->next) l = l->next;
        // return the merged list's last node. this node will be the head parameter in the next merge call.
        return l;
    }

public:
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head;
        node * cur = head;
        int len = 0;
        while (cur && ++len) cur = cur->next;

        // use a dummy node to make the loop work.
        // can also use a pointer to pointer trick the save the space.
        node fake_head(0); fake_head.next = head;
        node * tail, * left, * right;
        for (int step = 1; step < len; step <<= 1) {
            tail = &fake_head;
            cur = tail->next;
            while (cur) {
                left = cur;
                right = split(left, step);
                cur = split(right, step);
                tail = merge(left, right, tail);
                // When execution reachs here:   tail->cur
            }
        }
        return fake_head.next;
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
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

typedef ListNode node;
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        return head ? mergeSort(head) : NULL;
    }

    node * mergeSort(node * head) {
        if (!head || !(head->next)) return head;
        node * slow, * fast, * right;
        slow = fast = head;
        // find the mid point
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        // make sure each recursion are the same. i.e. corretly splited
        right = slow->next;
        slow->next = NULL;
        // divide into two subproblem
        head = mergeSort(head);
        right = mergeSort(right);
        // merge two sorted list
        return mergeSorted(head, right);
    }

    node * mergeSorted(node * left, node * right) {
        if (!left || !right) return left ? left : right;
        node * head, ** phead = &head;
        while (left && right) {
            if (right->val < left->val) {
                *phead = right; phead = &(right->next);
                right = right->next;
            } else {
                *phead = left; phead = &(left->next);
                left = left->next;
            }
        }
        *phead = left ? left : right;
        return head;
    }
};

```
