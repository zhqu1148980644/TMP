### Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.

```
Example:

Input: 1->2->4, 1->3->4
Output: 1->1->2->3->4->4
```

### Solutions

1. #### The same process used in merge sort.

```c++
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode * head = (ListNode *) malloc(sizeof(ListNode));
        ListNode * now = head;
        while (11 && l2) {
            while (l1 && (!l2 || (l1->val <= l2->val))) {
                now->next = l1;
                now = now->next;
                l1 = l1->next;
            }
            while (l2 && (!l1 || (l2->val < l1->val))) {
                now->next = l2;
                now = now->next;
                l2 = l2->next;
            }
        }
        now->next = l1 ? l1 : l2;
        return head->next;
    }
};
```