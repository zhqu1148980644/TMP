#### Sort a linked list using insertion sort.


A graphical example of insertion sort. The partial sorted list (black) initially contains only the first element in the list.
With each iteration one element (red) is removed from the input data and inserted in-place into the sorted list
![](https://upload.wikimedia.org/wikipedia/commons/0/0f/Insertion-sort-example-300px.gif)

#### Algorithm of Insertion Sort:

- Insertion sort iterates, consuming one input element each repetition, and growing a sorted output list.
- At each iteration, insertion sort removes one element from the input data, finds the location it belongs within the sorted list, and inserts it there.
- It repeats until no input elements remain.

```
Example 1:

Input: 4->2->1->3
Output: 1->2->3->4
Example 2:

Input: -1->5->3->4->0
Output: -1->0->3->4->5
```

#### Solutions

1. ##### straight forward

- `cur` pointer represents the last element has been sorted.

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
    ListNode* insertionSortList(ListNode* head) {
        if (!head || !head->next) return nullptr;
        ListNode dummy {INT_MIN, head}, * cur = &dummy; 
        // cur represents the tail head of the sorted list
        while (cur->next) {
            int next_val = cur->next->val;
            // simply move tail one node forward
            if (next_val >= cur->val)
                cur = cur->next;
            else {
                // find the fist node whose next node is larger than the inserting node.
                head = &dummy;
                while (head->next->val <= next_val)
                    head = head->next;
                ListNode * nnext = cur->next->next;
                cur->next->next = head->next;
                head->next = cur->next;
                cur->next = nnext;
            }
        }

        return dummy.next;
    }
};
```