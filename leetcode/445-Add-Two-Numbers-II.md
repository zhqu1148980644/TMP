#### You are given two non-empty linked lists representing two non-negative integers. The most significant digit comes first and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

#### Follow up:
What if you cannot modify the input lists? In other words, reversing the lists is not allowed.

```
Example:

Input: (7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 8 -> 0 -> 7
```

#### Solutions

1. ##### two stacks

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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        stack<int> s1, s2;
        while (l1) {
            s1.push(l1->val);
            l1 = l1->next;
        }
        while (l2) {
            s2.push(l2->val);
            l2 = l2->next;
        }
        ListNode * dummy = new ListNode(-1), * nnext;
        int remain = 0, num1, num2;
        while (s1.size() || s2.size() || remain) {
            num1 = num2 = 0;
            if (s1.size()) {
                num1 = s1.top(); s1.pop();
            }
            if (s2.size()) {
                num2 = s2.top(); s2.pop();
            }
            int cur = num1 + num2 + remain;
            nnext = dummy->next;
            dummy->next = new ListNode(cur % 10);
            dummy->next->next = nnext;
            remain = cur / 10;
        }
        nnext = dummy->next;
        delete dummy;
        return nnext;
    }
};
```

2. ##### recursion

- Another way is to padd the shorter list till two lists have the same number of nodes.
- `listnum` returns the remainder.

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
    void insertNode(ListNode * root, int val) {
        ListNode * tmp = root->next;
        root->next = new ListNode(val);
        root->next->next = tmp;
    }
    int listnum(ListNode * l1, ListNode * l2, ListNode * root, int skip) {
        if (!l1) return 0;
        int cur;
        if (skip)
            cur = l2->val + listnum(l1, l2->next, root, --skip);
        else
            cur = l1->val + l2->val + listnum(l1->next, l2->next, root, 0);
        insertNode(root, cur % 10);
        return cur / 10;
    }
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode * tmp;
        int len1 = 0, len2 = 0;
        tmp = l1;
        while (tmp && ++len1)
            tmp = tmp->next;
        tmp = l2;
        while (tmp && ++len2)
            tmp = tmp->next;
        
        if (len1 != len2 && len1 > len2) {
            swap(len1, len2);
            swap(l1, l2);
        }

        ListNode dummy(-1);
        int remain = listnum(l1, l2, &dummy, len2 - len1);
        if (remain) insertNode(&dummy, remain);
        return dummy.next;
    }
};
```