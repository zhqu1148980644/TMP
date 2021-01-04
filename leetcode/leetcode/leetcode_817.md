---
title: Linked List Components
date: 2021-01-04
---
We are given head, the head node of a linked list containing unique integer values.

We are also given the list G, a subset of the values in the linked list.

Return the number of connected components in G, where two values are connected if they appear consecutively in the linked list.

Example 1:

Input: 
head: 0->1->2->3
G = [0, 1, 3]
Output: 2
Explanation: 
0 and 1 are connected, so [0, 1] and [3] are the two connected components.
Example 2:

Input: 
head: 0->1->2->3->4
G = [0, 3, 1, 4]
Output: 2
Explanation: 
0 and 1 are connected, 3 and 4 are connected, so [0, 1] and [3, 4] are the two connected components.
Note:

If N is the length of the linked list given by head, 1 <= N <= 10000.
The value of each node in the linked list will be in the range [0, N - 1].
1 <= G.length <= 10000.
G is a subset of all values in the linked list.

#### Solutions

1. ##### UnionFind O(n)

```cpp
struct UnionFind {
    vector<int> nodes, sizes;
    UnionFind(int size) : nodes(size), sizes(size, 1) {
        iota(nodes.begin(), nodes.end(), 0);
    }
    int find(int node) {
        if (nodes[node] != node)
            return nodes[node] = find(nodes[node]);
        else
            return node;
    }
    bool merge(int node1, int node2) {
        int f1 = find(node1), f2 = find(node2);
        if (f1 == f2) return true;
        if (sizes[f1] > sizes[f2])
            swap(f1, f2);
        nodes[f1] = nodes[f2];
        sizes[f2] += sizes[f1];
        return true;
    }

};
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
    int numComponents(ListNode* head, vector<int>& G) {
        int comsize = G.size();
        unordered_set<int> g;
        for (auto node : G) g.insert(node);

        UnionFind uf(10001);
        while (head->next) {
            if (g.count(head->val) && g.count(head->next->val))
                comsize -= uf.merge(head->val, head->next->val);
            head = head->next;
        }

        return comsize;
    }
};
```

2. ##### hashset O(n)

- Find the last element in a community.

```cpp
class Solution {
public:
    int numComponents(ListNode* head, vector<int>& G) {
        unordered_set<int> g;
        for (auto node : G) g.insert(node);

        int com = 0;
        while (head) {
            if (g.count(head->val) && (!head->next || !g.count(head->next->val)))
                com++;
            head = head->next;
        }
        return com;
    }
};
```