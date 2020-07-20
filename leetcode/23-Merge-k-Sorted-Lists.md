### Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.

```
Example:

Input:
[
  1->4->5,
  1->3->4,
  2->6
]
Output: 1->1->2->3->4->4->5->6
```

### Solutions

list number: k.
length of the final merged list: n.

1. #### Compare values in each list. O(kn) S(1)

For each item, we need compare `k` times in k list to get the smallest one.

2. #### Compare values with priority queue. O(nlog(k)) S(k)

Use a priority queue to reduce complexity of select-smallest operation to `O(1)` plus `O(logk)` for every pop and insert.

2. #### Merge 2-list k/2 times. O(kn) S(1)

3. #### divide and conquer with iteration O(nlog(k)) S(1)

Merge will be called `log(k)` times.

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

void mergeList(ListNode * l, ListNode * r) {
    ListNode * head = l;
    l = l->next;
    while (l && r) {
        if (r->val < l->val) {
            head->next = r;
            r = r->next;
            head->next->next = l;
        } else
            l = l->next;
        head = head->next;
    }
    if (r) head->next = r;
}

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // Queue are not necessary. Just for elegance.
        queue<ListNode *> q;
        for (const auto & e : lists) if (e) q.push(e);
        while (q.size() > 1) {
            ListNode * l = q.front(); q.pop();
            ListNode * r = q.front(); q.pop();
            if (l->val > r->val) swap(l, r);
            mergeList(l, r);
            q.push(l);
        }
        return q.size() ? q.front() : NULL;
    }
};
```


4. #### divide and conquer with recursion. O(nlog(K)) S(n)

Elegant solution borrowed from other.

```c++
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return NULL;
        return partition(lists, 0, lists.size() - 1);
    }
 
    ListNode* partition(vector<ListNode*>& lists, int left, int right) {
        if (left == right) return lists[left];
        int mid = left + (right - left) / 2;
        ListNode* l = partition(lists, left, mid);
        ListNode* r = partition(lists, mid + 1, right);
        return merge(l, r);
    }
 
    ListNode* merge(ListNode* l1, ListNode* l2) {
        if (!l1) return l2;
        if (!l2) return l1;
        if (l1->val > l2->val) {
            l2->next = merge(l1, l2->next);
            return l2;
        }
        else {
            l1->next = merge(l1->next, l2);
            return l1;
        }
    }
};
```