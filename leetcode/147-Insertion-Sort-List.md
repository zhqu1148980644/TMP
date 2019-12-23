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
 *     struct ListNode *next;
 * };
 */


typedef struct ListNode node;

struct ListNode* insertionSortList(struct ListNode* head){
    if (!head || !head->next) return head;
    node * cur = head;
    node fake_head; fake_head.next = head;

    while (cur->next) {
        if (cur->next->val < cur->val) {
            head = &fake_head;
            while (head->next->val < cur->next->val)
                head = head->next;
            node * inode = cur->next;
            cur->next = inode->next;
            inode->next = head->next;
            head->next = inode;
        } else
            cur = cur->next;
    }
    return fake_head.next;
}
```