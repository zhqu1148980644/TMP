Given the head of a linked list, we repeatedly delete consecutive sequences of nodes that sum to 0 until there are no such sequences.

After doing so, return the head of the final linked list.  You may return any such answer.

 

(Note that in the examples below, all sequences are serializations of ListNode objects.)

Example 1:

Input: head = [1,2,-3,3,1]
Output: [3,1]
Note: The answer [1,2,1] would also be accepted.
Example 2:

Input: head = [1,2,3,-3,4]
Output: [1,2,4]
Example 3:

Input: head = [1,2,3,-3,-2]
Output: [1]
 

Constraints:

The given linked list will contain between 1 and 1000 nodes.
Each node in the linked list has -1000 <= node.val <= 1000.


#### Solutions

1. ##### simulation

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
    ListNode* removeZeroSumSublists(ListNode* head) {
        ListNode dummy; dummy.next = head;

        unordered_set<ListNode *> del;
        unordered_map<int,  ListNode *> m;
        int sum = 0; m[0] = &dummy;

        while (head) {
            sum += head->val;
            if (m.count(sum) && !del.count(m[sum])) {
                ListNode * remove = m[sum]->next;
                m[sum]->next = head->next;
                // mark these nodes has been deleted
                while (remove && remove != head->next) {
                    del.insert(remove);
                    remove = remove->next;
                }
            }
            else if (!m.count(sum) || del.count(m[sum]))
                    m[sum] = head;

            head = head->next;
        }

        return dummy.next;
    }
};
```

2. ##### recusion

```c++
class Solution {
public:
    ListNode* removeZeroSumSublists(ListNode* head) {
        if(!head) return nullptr;
        head->next = removeZeroSumSublists(head->next);

        ListNode * cur = head;
        int sum = 0;
        while(cur){
            if ((sum += cur->val) == 0)
                return cur->next;
            cur = cur->next;
        }

        return head;
    }
};

```