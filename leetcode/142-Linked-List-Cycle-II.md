#### Given a linked list, return the node where the cycle begins. If there is no cycle, return null.

To represent a cycle in the given linked list, we use an integer pos which represents the position (0-indexed) in the linked list where tail connects to. If pos is -1, then there is no cycle in the linked list.

#### Note: Do not modify the linked list.

 

```
Example 1:

Input: head = [3,2,0,-4], pos = 1
Output: tail connects to node index 1
Explanation: There is a cycle in the linked list, where tail connects to the second node.
```

![](https://assets.leetcode.com/uploads/2018/12/07/circularlinkedlist.png)

```
Example 2:

Input: head = [1,2], pos = 0
Output: tail connects to node index 0
Explanation: There is a cycle in the linked list, where tail connects to the first node.
```

![](https://assets.leetcode.com/uploads/2018/12/07/circularlinkedlist_test2.png)

```
Example 3:

Input: head = [1], pos = -1
Output: no cycle
Explanation: There is no cycle in the linked list.
```

![](https://assets.leetcode.com/uploads/2018/12/07/circularlinkedlist_test3.png)

 

##### Follow-up:
Can you solve it without using extra space?


#### Solutions

1. two steps

- Use floyd method to check if the loop exists in the linked list.
    - At the first glance, I thought the resulting node returnd in the problem 141 is the answer. Finally I realized that it can't be like this because there is no single start point in the loop.
    - Though the resulting node may not be the answer we want, it can be used as an imaginary tail in a normal non-cycled linked list.
    - we call this node `head1`.
- Use the method in problem 160 to find the intersection/crossing nodes.
    - In the problem 160, the qestion is to find the intersection node where two linked lists converge.
    - Here we can find two linked lists acts exactly the same as in problem 160:
        - One linked list starting from `head` and ending at the former node of  `head1`.
        - Another linked list starting from `head1` and ending at the former node of `head1`.

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

typedef struct ListNode node;

struct ListNode *detectCycle(struct ListNode *head) {
    if (!head) return NULL;
    node * slow = head, * fast = head->next;
    // fint the meeting node. ie head1
    while (slow != fast) {
        if (!fast || !fast->next) return NULL;
        slow = slow->next;
        fast = fast->next->next;
    }
    // edge case. ie self loop.
    if (slow->next == slow) return slow;
    node * tail = slow;
    slow = head;
    while (slow != fast) {
        // implicitly redirect slow pointer to the second list.
        slow = slow->next;
        // explicitly redirect fast pointer to the first list(head).
        fast = fast->next;
        if (fast == tail)
            fast = head;
    }
    return slow;
}
```

2. ##### optimized solution 1

- Because the fast pointer is two times faster than the slow pointer, the path made by the fast pointer twice the path of slow pointer.
    - support the nonloop region's length is `x` and the length between intersection point and the meeting point is `y`. the length of the loop is `c`
    - `(x + n1 * c + y) * 2 = x + n2 * c`
    - `x + y = (2 * n1 - n2) * c`
    - fast node is now at `y` point, fast node will be at the intersection node when it forwards `x` steps as `x + y = n * c`.
    - By moving slow at the head of the list, and let slow and fast continues to move forward with the same peace, they will both be at the intersection node after forwarded `x` steps.
- Watch out the changes when initializing fast pointer.

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

typedef struct ListNode node;

struct ListNode *detectCycle(struct ListNode *head) {
    if (!head) return NULL;
    // set fast to head
    node * slow = head, * fast = head;
    // Changed a little bit.
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;
    }
    // exited the loop normally.
    if (!fast || !fast->next) return NULL;
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}
```